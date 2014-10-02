#include <iostream>
#include <fstream>

using namespace std;

int main()
{
enum Stany {liczba=1, mozliwa_liczba, nie_liczba};

    Stany stan = nie_liczba;
    Stany poprzedni_stan = nie_liczba;

    fstream plik_odczyt;
    plik_odczyt.open("plik.txt", ios::in);// otwieramy plik;

    fstream plik_zapis;
    plik_zapis.open("done.txt", ios::out);// otwieramy plik;

    string tmp="";

    char biezacy_znak;

    if( plik_odczyt.good() == false )
    {
       cout << "problem z plikiem !!!";
       return 7;
    }

        while ( !plik_odczyt.eof())
        {
            poprzedni_stan = stan;

            biezacy_znak = plik_odczyt.get();

            if(biezacy_znak >= 'A' && biezacy_znak <= 'Z')
            {
              biezacy_znak+=32;
            }

            switch(stan)
            {
              case nie_liczba:
              {
                if (biezacy_znak != '0') tmp="";
                else if(biezacy_znak == '0')
                {
                  stan = mozliwa_liczba;
                  tmp=biezacy_znak;
                }
              }
              break;


              case mozliwa_liczba:
              {
                if (biezacy_znak == '0') stan = mozliwa_liczba;//mozna nic nie robic...w sumie nic sie nie dzieje
                else if(biezacy_znak == 'x')
                {
                  tmp+=biezacy_znak;
                  stan = liczba;
                }
                else stan = nie_liczba;

              }
              break;


              case liczba:
              {
                if( (biezacy_znak >= '0' && biezacy_znak <= '9') || (biezacy_znak >= 'a' && biezacy_znak <= 'f') )
                {
                  stan = liczba;
                  tmp=tmp+biezacy_znak;

                }
                else stan = nie_liczba;
              }
              break;

              default:
              break;

            }

            if(poprzedni_stan==liczba && stan!=liczba && tmp.length()>=3)
            {
              cout <<tmp<<endl;
              plik_zapis << tmp <<'\n';
              tmp="";
            }

        }

plik_odczyt.close();
plik_zapis.close();


return 0;
}

