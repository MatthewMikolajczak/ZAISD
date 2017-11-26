// Problem A - Bilard - autor: Mateusz Mikolajczak
#include <cstdlib>
#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
    int testy, sx, sy, wx, wy, odbicia, kierunekx, kieruneky;
    float px, py, a, b, przecieciex, przecieciey;
    cin >> testy;
    for(int i = 0; i < testy; ++i) {
        cin >> sx >> sy >> px >> py >> wx >> wy;
        // 0. SPRAWDŹ CZY WEKTOR NIE JEST (0,0)
        if(wx == 0 && wy == 0) cout << "NIE" << endl;
        else {
			odbicia = 0;
            while(1) {
                // 1. OBLICZ FUNKCJĘ WEKTORA (y=ax+b) I KIERUNEK BILI
                if(wx != 0) {
                    a = wy / wx;
                    b = py - a * px;
                }
                if(wx > 0) kierunekx = 1;
                else if(wx < 0) kierunekx = -1;
                else kierunekx = 0;
                if(wy > 0) kieruneky = 1;
                else if(wy < 0) kieruneky = -1;
                else kieruneky = 0;
                // 2. POSZUKAJ PRZECIĘCIA Z KRAWĘDZIAMI STOŁU
                // jeśli kierunekx==-1 i kieruneky==-1 to punkt przecięcia (-b/a, 0) lub (0, b)
                if(kierunekx == -1 && kieruneky == -1) {
                    przecieciex = - b / a;
                    przecieciey = b;
                    if(przecieciex <= sx && przecieciex >= 0) przecieciey = 0;
                    else if(przecieciey <= sy && przecieciey >= 0) przecieciex = 0;
                    else cout << "ERROR!!!!!" << endl;
                }
                // jeśli kierunekx==-1 i kieruneky==0 to punkt przecięcia (0, b)
                else if(kierunekx == -1 && kieruneky == 0) {
                    przecieciex = 0;
                    przecieciey = py;
                }
                // jeśli kierunekx==-1 i kieruneky==1 to punkt przecięcia (0, b) lub ( (sy-b)/a, sy)
                else if(kierunekx == -1 && kieruneky == 1) {
                    przecieciex = (sy - b) / a;
                    przecieciey = b;
                    if(przecieciex <= sx && przecieciex >= 0) przecieciey = sy;
                    else if(przecieciey <= sy && przecieciey >= 0) przecieciex = 0;
                    else cout << "ERROR!!!!!" << endl;
                }
                // jeśli kierunekx==0 i kieruneky==-1 to punkt przecięcia (px, 0)
                else if(kierunekx == 0 && kieruneky == -1) {
                    przecieciex = px;
                    przecieciey = 0;
                }
                // jeśli kierunekx==0 i kieruneky==1 to punkt przecięcia (px, sy)
                else if(kierunekx == 0 && kieruneky == 1) {
                    przecieciex = px;
                    przecieciey = sy;
                }
                // jeśli kierunekx==1 i kieruneky==-1 to punkt przecięcia (-b/a, 0) lub (sx, a*sx+b)
                else if(kierunekx == 1 && kieruneky == -1) {
                    przecieciex = - b / a;
                    przecieciey = a * sx + b;
                    if(przecieciex <= sx && przecieciex >= 0) przecieciey = 0;
                    else if(przecieciey <= sy && przecieciey >= 0) przecieciex = sx;
                    else cout << "ERROR!!!!!" << endl;
                }
                // jeśli kierunekx==1 i kieruneky==0 to punkt przecięcia (sx, a*sx+b)
                else if(kierunekx == 1 && kieruneky == 0) {
                    przecieciex = sx;
                    przecieciey = py;
                }
                // jeśli kierunekx==1 i kieruneky==1 to punkt przecięcia ( (sy-b)/a, sy) lub (sx, a*sx+b)
                else if(kierunekx == 1 && kieruneky == 1) {
                    przecieciex = (sy - b) / a;
                    przecieciey = a * sx + b;
                    if(przecieciex <= sx && przecieciex >= 0) przecieciey = sy;
                    else if(przecieciey <= sy && przecieciey >= 0) przecieciex = sx;
                    else cout << "ERROR!!!!!" << endl;
                }
                else{
                    cout << "ERROR!!!!!" << endl;
                    break;
                }
                // 2.2 USTAW PX I PY NA PUNKT PRZECIĘCIA
                px = przecieciex;
                py = przecieciey;
                // 3. SPRAWDŹ CZY PUNKT PRZECIĘCIA NIE JEST ŁUZĄ
                if(przecieciex == 0 && przecieciey == 0) {
					cout << "DL " << odbicia << endl;
					break;
                }
                else if(przecieciex == 0 && przecieciey == sy) {
					cout << "GL " << odbicia << endl;
					break;
                }
                else if(przecieciex == sx && przecieciey == 0) {
					cout << "DP " << odbicia << endl;
					break;
                }
                else if(przecieciex == sx && przecieciey == sy) {
					cout << "GP " << odbicia << endl;
					break;
                }
                else if(przecieciex == sx/2 && przecieciey == 0) {
					cout << "DS " << odbicia << endl;
					break;
                }
                else if(przecieciex == sx/2 && przecieciey == sy) {
					cout << "GS " << odbicia << endl;
					break;
                }
                else odbicia += 1;
                // 3.2 SPRAWDŹ CZY NIE ODBIJAMY SIĘ POD KĄTEM PROSTYM (ZAPĘTLILIŚMY SIĘ)
				if(wx == 0 || wy == 0) {
					cout << "NIE" << endl;
					break;
				}
                // 4. OBLICZ NOWY WEKTOR
				if(przecieciex == 0 || przecieciex == sx) wx = - wx;
				else if(przecieciey == 0 || przecieciey == sy) wy = - wy;
				else cout << "ERROR!" << endl;
            }
        }
    }
    return 0;
}
