// Kolorowanie grafu z powrotami - autor: Mateusz Mikołajczak
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
	int testy, rozmiar, ilosc_kolorow, kolor_malowania;
	bool **macierz;
	int *kolor_wierzcholka;
	bool *zajete_kolory;
	bool kolorowanie_mozliwe;
	cin >> testy;
	for(int i=0; i<testy; i++)
	{
		// przygotowanie zmiennych
		kolorowanie_mozliwe = 1;
		cin >> rozmiar >> ilosc_kolorow;
		macierz = new bool*[rozmiar];
		for(int j=0; j<rozmiar; j++)
		{
			macierz[j] = new bool[rozmiar];
			for(int k=0; k<rozmiar; k++) cin >> macierz[j][k];
		}
		kolor_wierzcholka = new int[rozmiar];
		for(int j=0; j<rozmiar; j++) kolor_wierzcholka[j]=0;
		zajete_kolory = new bool[ilosc_kolorow+1];
		zajete_kolory[0]=1;
		// przechodzenie po wierzchołkach grafu i kolorowanie
		for(int j=0; j<rozmiar && kolorowanie_mozliwe; j++)
		{
			for(int k=1; k<rozmiar+1; k++) zajete_kolory[k]=0;
			for(int k=0; k<rozmiar; k++) if(macierz[j][k]==1 && kolor_wierzcholka[k]>0) zajete_kolory[kolor_wierzcholka[k]]=1;
			kolor_malowania = 0;
			for(int k=1; k<ilosc_kolorow+1; k++)
			{
				if(zajete_kolory[k]==0)
				{
					kolor_malowania=k;
					break;
				}
			}
			if(kolor_malowania>0) kolor_wierzcholka[j]=kolor_malowania;
			else
			{///////cofamy się do pierwszego który można pokolorować wyższym niż ma kolorem, usuwając kolor wszystkim po drodze
				for(int k=j-1; k>0; k--)
				{
					for(int l=1; l<rozmiar+1; l++) zajete_kolory[l]=0;
					for(int l=0; l<rozmiar; l++) if(macierz[k][l]==1 && kolor_wierzcholka[l]>0) zajete_kolory[kolor_wierzcholka[l]]=1;
					int zmien_na=0;
					for(int l=kolor_wierzcholka[k]+1; l<ilosc_kolorow+1; l++) if(zajete_kolory[l]==0) zmien_na=l;
					if(zmien_na>0)
					{
						//zmieniamy kolor i zmieniamy zmienna 'j' i jedziemy z kolorwaniem dalej
						kolor_wierzcholka[k] = zmien_na;
						j=k;
						break;
					}					
					else
					{
						//zmieniamy kolor na 0
						kolor_wierzcholka[k] = 0;
						if((k-1)==0) kolorowanie_mozliwe=0;//jeżeli musimy się cofnąć do pierwszego elementu to kolorowanie nie istnieje
					}
				}
			}
		}
		if(!kolorowanie_mozliwe) cout << "NIE";
		else for(int j=0; j<rozmiar; j++) cout << kolor_wierzcholka[j] << " ";
		cout << endl;		
		delete [] kolor_wierzcholka;
		delete [] zajete_kolory;
 		for(int j=0; j<rozmiar; j++) delete [] macierz[j];
		delete [] macierz;
	}
	return 0;
}
