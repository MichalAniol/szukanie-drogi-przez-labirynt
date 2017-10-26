   #include <iostream>
   #include <conio.h>
   #include <cstdlib>
   #include <time.h>
   #include <windows.h>

using namespace std;
  int miara_y = 35, miara_x = 70;
int labirynt[35][70];

    double srednia_dlugosc_drogi;
    int droga_wyjscia[2000][2];

    void labirynto();
    int szukanie_drogi();
    int rysowanie(int licznik_komnat);
    int rysowanie_wstepne(int *pole);

int main()
{
    float ile_labiryntow = 0;
    srednia_dlugosc_drogi = 0;
    int dlugosc_drogi;

    srand(time(NULL)) ;

    cout << "\n\n\n   G E N E R A T O R \n" <<
             "                   ,\n" <<
             "   L A B I R Y N T O W\n\n\n" <<
             "   +   W Y S Z U K I W A R K A\n" <<
             "         ,\n" <<
             "   W Y J S C I A\n\n\n\n" <<
             "   wymiary   x: 70,  y: 35 ";

                 getch();


    for ( ; ; )
    {
        int *pole = &labirynt[0][0];
        for (int i = 0 ; i < miara_y * miara_x ; i++) *pole++ = 0;

        labirynto();

        int ttt = szukanie_drogi();

        /*******************  trawka na wejsciach i wyjsciach **************/

        labirynt[0][0] += 1; labirynt[miara_y - 1][miara_x - 1] += 4; //dorysowanie wejcia i wyjscia

         /*********************  tworzenie piku mapy **************/
        Sleep(1000);

        dlugosc_drogi = rysowanie(ttt);
        srednia_dlugosc_drogi += dlugosc_drogi;


        cout << "   Liczba lab.: " << ++ile_labiryntow;
        cout << "      sednia dlug. drogi: " << srednia_dlugosc_drogi / ile_labiryntow << "                          \n";


        getch();
    }


}

    void labirynto()
    {
        int pozycja_x, pozycja_y;
        int kierunek = 0, wolne[4] = {0,0,0,0};
        int licznik;

        pozycja_x = (rand() % (miara_x - 2)) + 1;
        pozycja_y = (rand() % (miara_y - 2)) + 1;

        licznik = (miara_x * miara_y) - 1 ;

        do {
            do {
                kierunek = 0;

                if (pozycja_x              && labirynt[pozycja_y][pozycja_x - 1] == 0) wolne[kierunek++] = 8;   //lewo
                if (pozycja_x != miara_x-1 && labirynt[pozycja_y][pozycja_x + 1] == 0) wolne[kierunek++] = 2;   //prawo
                if (pozycja_y              && labirynt[pozycja_y - 1][pozycja_x] == 0) wolne[kierunek++] = 1;   //gora
                if (pozycja_y != miara_y-1 && labirynt[pozycja_y + 1][pozycja_x] == 0) wolne[kierunek++] = 4;   //dol


                if (kierunek)
                {
                    int wybor_kierunku = rand() % (kierunek);
                    int przesuniecie = wolne[wybor_kierunku];
                    labirynt[pozycja_y][pozycja_x] += przesuniecie;

                    if (przesuniecie == 8) {pozycja_x--; labirynt[pozycja_y][pozycja_x] = 2; };
                    if (przesuniecie == 2) {pozycja_x++; labirynt[pozycja_y][pozycja_x] = 8; };
                    if (przesuniecie == 1) {pozycja_y--; labirynt[pozycja_y][pozycja_x] = 4; };
                    if (przesuniecie == 4) {pozycja_y++; labirynt[pozycja_y][pozycja_x] = 1; };

                    licznik--;
                }
            } while (kierunek);

            do {
                pozycja_x++; if (pozycja_x == miara_x)
                {
                    pozycja_x = 0; pozycja_y++;
                    if (pozycja_y == miara_y) pozycja_y = 0;
                }
            } while (!labirynt[pozycja_y][pozycja_x]);

        } while (licznik > 0);
    }

    int szukanie_drogi()
    {

        int pacze_y = 0, pacze_x = 0, licznik_komnat = 0;
        int mapa[miara_y][miara_x];
        int *adres = &droga_wyjscia[0][0], *adresss = &mapa[0][0], *adressso = &labirynt[0][0];
        int suma_wyjsc, komnata;

        for (int i = 0 ; i < 2000 ; i++) *adres++ = 0;          //czyszczenie tablicy
        for (int i = 0 ; i < miara_y * miara_x ; i++) *adresss++ = *adressso++;          //przepisanie labiryntu

        do
        {

            komnata = mapa[pacze_y][pacze_x];
            suma_wyjsc = (komnata & 1) + (komnata & 2) / 2 + (komnata & 4) / 4 + (komnata & 8) / 8;

            if (suma_wyjsc == 0)             // slepa uliczka, cofaj do poprzedniego skrzyzowania
            {do { licznik_komnat--;
                  pacze_y = droga_wyjscia[licznik_komnat][0];
                  pacze_x =  droga_wyjscia[licznik_komnat][1];
                } while ( mapa[pacze_y][pacze_x] == 0); continue;}

            droga_wyjscia[licznik_komnat][0] =  pacze_y;               // zapisz klejne lokalizacje
            droga_wyjscia[licznik_komnat][1] =  pacze_x;

            rysowanie_wstepne(&mapa[0][0]);
            cout << "\n  dlugosc drogi do wyjscia liczona w komnatch do przejscia: " << licznik_komnat << "    "
            << "\n  sprawdzane jset miejsce: y: " << pacze_y << "    x: " << pacze_x << "         \n";

            Sleep(1);



            if (komnata & 2) {mapa[pacze_y][pacze_x] -= 2; pacze_x++; mapa[pacze_y][pacze_x] -= 8; licznik_komnat++; continue;}

            if (komnata & 4) {mapa[pacze_y][pacze_x] -= 4; pacze_y++; mapa[pacze_y][pacze_x] -= 1; licznik_komnat++; continue;}

            if (komnata & 1) {mapa[pacze_y][pacze_x] --  ; pacze_y--; mapa[pacze_y][pacze_x] -= 4; licznik_komnat++; continue;}

            if (komnata & 8) {mapa[pacze_y][pacze_x] -= 8; pacze_x--; mapa[pacze_y][pacze_x] -= 2; licznik_komnat++; continue;}

        } while (!(pacze_y == miara_y - 1 && pacze_x == miara_x - 1));

        droga_wyjscia[licznik_komnat][0] =  pacze_y;        // wyjscie
        droga_wyjscia[licznik_komnat][1] =  pacze_x;

            rysowanie_wstepne(&mapa[0][0]);
            cout << "\n  dlugosc drogi do wyjscia liczona w komnatch do przejscia: " << licznik_komnat << "    "
            << "\n  sprawdzane jset miejsce: y: " << pacze_y << "    x: " << pacze_x << "         \n";

        return ++licznik_komnat;
    }

    int rysowanie(int licznik_komnat)
    {
        COORD c ; c.X = 0 ; c.Y = 0;
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );

        int *pole = &labirynt[0][0] ;
        string ekran = "";

        for(int y = 0 ; y < miara_y ; y++)
        {
            for(int x = 0 ; x < miara_x ; x++)
            {
                if (labirynt[y][x] == 1) {ekran += char(192); ekran += ' ';};
                if (labirynt[y][x] == 2) {ekran += ' ' ; ekran +=  char(196);};
                if (labirynt[y][x] == 3) {ekran += char(192) ; ekran +=  char(196);};
                if (labirynt[y][x] == 4) {ekran += char(218) ; ekran +=  ' ';};
                if (labirynt[y][x] == 5) {ekran += char(179) ; ekran +=  ' ';};
                if (labirynt[y][x] == 6) {ekran += char(218) ; ekran +=  char(196);};
                if (labirynt[y][x] == 7) {ekran += char(195) ; ekran +=  char(196);};
                if (labirynt[y][x] == 8) {ekran += char(196) ; ekran +=  ' ';};
                if (labirynt[y][x] == 9) {ekran += char(217) ; ekran +=  ' ';};
                if (labirynt[y][x] == 10) {ekran += char(196) ; ekran +=  char(196);};
                if (labirynt[y][x] == 11) {ekran += char(193) ; ekran +=  char(196);};
                if (labirynt[y][x] == 12) {ekran += char(191) ; ekran +=  ' ';};
                if (labirynt[y][x] == 13) {ekran += char(180) ; ekran +=  ' ';};
                if (labirynt[y][x] == 14) {ekran += char(194) ; ekran +=  char(196);};
                if (labirynt[y][x] == 15) {ekran += char(197) ; ekran +=  char(196);};
                pole++;
            }
            ekran +=  "\n";
        }
        cout << ekran;


        int yyy = 0, xxx = 0;
        int licznik_kom = 0;
        for (int i = 0 ; i < licznik_komnat ; i++)
        {
            yyy = droga_wyjscia[licznik_kom][0];
            xxx = droga_wyjscia[licznik_kom][1];
            int miejsce = labirynt[yyy][xxx];

            c.X = xxx * 2 ; c.Y = yyy;
            SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );

            ekran = "";

            if (miejsce == 1) {ekran += char(200); ekran += ' ';};
            if (miejsce == 2) {ekran += ' ' ; ekran +=  char(205);};
            if (miejsce == 3) {ekran += char(200) ; ekran +=  char(205);};
            if (miejsce == 4) {ekran += char(201) ; ekran +=  ' ';};
            if (miejsce == 5) {ekran += char(186) ; ekran +=  ' ';};
            if (miejsce == 6) {ekran += char(201) ; ekran +=  char(205);};
            if (miejsce == 7) {ekran += char(204) ; ekran +=  char(205);};
            if (miejsce == 8) {ekran += char(205) ; ekran +=  ' ';};
            if (miejsce == 9) {ekran += char(188) ; ekran +=  ' ';};
            if (miejsce == 10) {ekran += char(205) ; ekran +=  char(205);};
            if (miejsce == 11) {ekran += char(202) ; ekran +=  char(205);};
            if (miejsce == 12) {ekran += char(187) ; ekran +=  ' ';};
            if (miejsce == 13) {ekran += char(185) ; ekran +=  ' ';};
            if (miejsce == 14) {ekran += char(203) ; ekran +=  char(205);};
            if (miejsce == 15) {ekran += char(206) ; ekran +=  char(205);};

            licznik_kom++;
            cout << ekran;
            Sleep(10);
        }
        cout << "\n\n   Liczba komnat od wejscia do wyjscia: " << licznik_komnat << "                                 \n";
        return licznik_komnat;
    }


    int rysowanie_wstepne(int *pole)
    {
        COORD c ; c.X = 0 ; c.Y = 0;
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );

        string ekran = "";

        for(int y = 0 ; y < miara_y ; y++)
        {
            for(int x = 0 ; x < miara_x ; x++)
            {
                int komnata = *(pole + (y * miara_x) + x);
                if (komnata == 0) {ekran += ' '; ekran += ' ';};
                if (komnata == 1) {ekran += char(192); ekran += ' ';};
                if (komnata == 2) {ekran += ' ' ; ekran +=  char(196);};
                if (komnata == 3) {ekran += char(192) ; ekran +=  char(196);};
                if (komnata == 4) {ekran += char(218) ; ekran +=  ' ';};
                if (komnata == 5) {ekran += char(179) ; ekran +=  ' ';};
                if (komnata == 6) {ekran += char(218) ; ekran +=  char(196);};
                if (komnata == 7) {ekran += char(195) ; ekran +=  char(196);};
                if (komnata == 8) {ekran += char(196) ; ekran +=  ' ';};
                if (komnata == 9) {ekran += char(217) ; ekran +=  ' ';};
                if (komnata == 10) {ekran += char(196) ; ekran +=  char(196);};
                if (komnata == 11) {ekran += char(193) ; ekran +=  char(196);};
                if (komnata == 12) {ekran += char(191) ; ekran +=  ' ';};
                if (komnata == 13) {ekran += char(180) ; ekran +=  ' ';};
                if (komnata == 14) {ekran += char(194) ; ekran +=  char(196);};
                if (komnata == 15) {ekran += char(197) ; ekran +=  char(196);};
            }
            ekran +=  "\n";
        }
        cout << ekran;
    }
































