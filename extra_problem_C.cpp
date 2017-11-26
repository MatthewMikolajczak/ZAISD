// Problem C - Strzelanie do balonów - autor: Mateusz Mikolajczak
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;
int main(int argc, char *argv[]) {
    int testy, balony, wx, wy, bx, by, br, licznik, A, B;
    float d;
    bool zamianaOsi;
    cin >> testy;
    for(int i = 0; i < testy; ++i) {
		cin >> balony >> wx >> wy;
		licznik = 0;
		zamianaOsi = false;
		if(wx == 0 && wy == 0) break;
		if(wx == 0) { // wektor X jest zerowy, konieczna zamiana X i Y zarówno wektora jak i balonów (odwracamy układ współrzędnych)
			zamianaOsi = true;
			wx = wy;
			wy = 0;
		}
		if(wx != 0) {
			B = 1;
			A = -(wy / wx);
        }
		for(int j=0; j < balony; ++j) {
			cin >> bx >> by >> br;
			if(zamianaOsi == true){
				int temp = bx;
				bx = by;
				by = temp;
			}
			d = abs(A*bx+B*by)/sqrt(A*A+B*B);
			if(d <= br) licznik++;
		}
		cout << licznik << endl;
    }
    return 0;
}
