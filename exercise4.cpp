// Najkrótsze drogi w grafie - autor: Mateusz Mikolajczak
#include <cstdlib>
#include <iostream>
using namespace std;
int *d, *p;
void wyswietlTrase(int x, bool ostatni) {
	if(p[x] != -1) wyswietlTrase(p[x], false);
	cout << x+1;
	if(ostatni != true) cout << "-";
}
int main(int argc, char *argv[]) {
	int testy, wierzcholki, krawedzie, w1, w2;
	int **macierz;
	bool *odwiedzone;
	bool warunek;
	cin >> testy;
	for(int i = 0; i < testy; ++i) {
		cin >> wierzcholki >> krawedzie;
		macierz = new int*[wierzcholki];
		for(int j = 0; j < wierzcholki; ++j) {
			macierz[j] = new int[wierzcholki];
			for(int k = 0; k < wierzcholki; ++k) macierz[j][k] = 0;
		}		
		for(int j = 0; j < krawedzie; ++j) {
			cin >> w1 >> w2;
			cin >> macierz[(w1-1)][(w2-1)];
		}
		odwiedzone = new bool[wierzcholki];
		d = new int[wierzcholki];
		p = new int[wierzcholki];
		for(int j = 0; j < wierzcholki; ++j) {
			odwiedzone[j] = 0;
			d[j] = 2147483647;
			p[j] = -1;
		}
		d[0] = 0;
		do {
			//przechodzimy przez wszystkie nieodwiedzone i szukamy w nich tego z najmniejszym d
			int najmniejsze_d = 2147483647, wierzcholek_najmniejsze_d;
			for(int j = 0; j < wierzcholki; ++j) {
				if(odwiedzone[j] == 0 && d[j] < najmniejsze_d) {
					najmniejsze_d = d[j];
					wierzcholek_najmniejsze_d = j;
				}
			}
			//ustawiamy znaleziony na odwiedzony
			odwiedzone[wierzcholek_najmniejsze_d] = 1;
			//przegladamy jego wszystkich sasiadow
			//dla kazdego sasiada sprawdzamy czy jego d jest wieksze od d naszego wierzcholka + waga krawedzi miedzy nimi
			//jesli tak to ustawiamy d sasiada na ta wartosc a p sasiada na nasz wierzcholek
			for(int j = 0; j < wierzcholki; ++j){
				if(macierz[wierzcholek_najmniejsze_d][j] > 0) {
					if(d[j] > (d[wierzcholek_najmniejsze_d] + macierz[wierzcholek_najmniejsze_d][j])) {
						d[j] = d[wierzcholek_najmniejsze_d] + macierz[wierzcholek_najmniejsze_d][j];
						p[j] = wierzcholek_najmniejsze_d;
					}
				}
			}			
			warunek = 0;
			for(int j = 0; j < wierzcholki; ++j) if(odwiedzone[j]==false) warunek = 1; 
		} while(warunek);
		
		cout << "Graf nr " << i+1 << endl;
		for(int j = 1; j < wierzcholki; ++j) {	
			wyswietlTrase(j,true);
			cout << " " << d[j] << endl;
		}	
		for(int j = 0; j < wierzcholki; j++) delete [] macierz[j];
		delete [] macierz;
		delete [] odwiedzone;
		delete [] d;
		delete [] p;
	}
	return 0;
}
