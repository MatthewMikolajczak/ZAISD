// Minimalne drzewo rozpinające algorytmem Kruskala - autor: Mateusz Mikołajczak
#include <cstdlib>
#include <iostream>
#include <list>
using namespace std;
typedef struct krawedz krawedz;
struct krawedz
{
	int wierzcholek1, wierzcholek2, waga;	
	bool operator< (const krawedz& other)
	{
		return this->waga < other.waga;
	}
};
int rozmiar;
list <krawedz> lista;//lista krawędzi grafu, ktora zostanie uporządkowana rosnąco
int** macierzMST;//macierz z krawędziami szukanego minimalnego drzewa rozpinającego
int* kolor;//tablica z kolorami wierzcholkow do kolorowania przy przechodzeniu grafu
bool cyklicznosc;
void dfs(int wierzcholek, int poprzedni)
{
	kolor[wierzcholek]=1;
	for(int r=0; r<rozmiar; r++) 
	{
		if(macierzMST[wierzcholek][r]!=0 && kolor[r]!=0 && r!=poprzedni && poprzedni!=NULL) cyklicznosc=1;//SPRAWDZANIE CYKLICZNOSCI
		if(macierzMST[wierzcholek][r]!=0 && kolor[r]==0) dfs(r,wierzcholek);		
	}
}
int czy_jest_mst()//sprawdzanie czy mamy już MST (czyli czy nowy graf jest spójny)
{
	bool spojnosc;
	//PRZECHODZENIE GRAFU W GŁĄB (DFS) z kolorowaniem (kod poprzedniego zadania)
	kolor = new int[rozmiar];
	for(int j=0; j<rozmiar; j++) kolor[j]=0;
	dfs(0, NULL);
	//SPRAWDZANIE SPÓJNOŚCI
	spojnosc=1;
	for(int j=0; j<rozmiar; j++) if(kolor[j]==0) spojnosc=0;
	delete [] kolor;
	return spojnosc;
}
int czy_jest_cykl()
{
	cyklicznosc=0;
	//PRZECHODZENIE GRAFU W GŁĄB (DFS) z kolorowaniem (kod poprzedniego zadania)
	kolor = new int[rozmiar];
	for(int j=0; j<rozmiar; j++) kolor[j]=0;
	for(int a=0; a<rozmiar; a++) if(kolor[a]==0) dfs(a, NULL);	
	delete [] kolor;
	return cyklicznosc;
}
void pobierz_krawedz(list<krawedz>::iterator it)
{
	//dodajemy krawedz do zbioru (do macierzyMST)
	int x, y, w;
	x = it->wierzcholek1;
	y = it->wierzcholek2;
	w = it->waga;
	macierzMST[x][y]=macierzMST[y][x]=w;
	//sprawdzamy czy nie ma cyklu
	//jesli jest cykl usuwamy krawedz ze zbioru
	if(czy_jest_cykl()) macierzMST[x][y]=macierzMST[y][x]=0;
}
int main(int argc, char *argv[])
{
	int testy, krawedzie, k1, k2, waga;
	cin >> testy;
	for(int i=0; i<testy; i++){	
		cin >> rozmiar >> krawedzie;
		macierzMST = new int*[rozmiar];
		for(int i=0; i<rozmiar; ++i)
		{
			macierzMST[i] = new int[rozmiar];
			for(int j=0; j<rozmiar; ++j) macierzMST[i][j]=0;
		}
		for(int i=0; i<krawedzie; ++i)
		{
			cin >> k1 >> k2 >> waga;
			k1--;
			k2--;
			lista.push_back(krawedz{k1,k2,waga});
		}
		lista.sort();//porządkowanie listy krawędzi grafu rosnąco do algorytmu Kruskala
		//przechodzenie po wszystkich krawędziach od najmniejszej (algorytm Kruskala)
		for (list<krawedz>::iterator it = lista.begin(); it != lista.end(); ++it)
		{
			pobierz_krawedz(it);
			if(czy_jest_mst())
			{
				//wyswietl sume krawedzi macierzyMST
				int suma=0;
				for(int m=0; m<rozmiar; ++m)
					for(int n=0; n<rozmiar; ++n) suma+=macierzMST[m][n];
				cout << suma/2 << endl;
				break;
			}
		}		
		lista.clear();
		for(int i = 0; i < rozmiar; ++i) delete [] macierzMST[i];
		delete [] macierzMST;
	}
	return 0;
}
