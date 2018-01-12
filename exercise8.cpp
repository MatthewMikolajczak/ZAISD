#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
int main() {
	
	bool brak;
	int testy, licznik, pozycja, licznik_specjalnych_znakow;
	
	signed char znak;
	
	cin >> testy;
	znak = getchar();
	
	for(int i = 0; i < testy; i++) {
		string wzorzec;
		
		do{
			znak = getchar();
			wzorzec.push_back(znak);
		}while(znak != '\n');
		wzorzec.pop_back();
		//cout << "wzorzec: " << wzorzec << "|" << endl;
	
		brak = true;
		licznik = 0;
		licznik_specjalnych_znakow = 0;
		pozycja = 0;
		
		do{
			znak = getchar();
			if(znak < 0) znak = getchar();
			//cout << endl << "pozycja: " << pozycja << " znak: " << znak << " kod: " << (int)znak;
			if(wzorzec[licznik] < 0) {
				licznik++;
				licznik_specjalnych_znakow++;
			}
			if(znak == wzorzec[licznik]) {
				licznik++;
				if(licznik >= wzorzec.length()) {
					cout << (pozycja + 1 - licznik + licznik_specjalnych_znakow) << " ";
					licznik = 0;
					licznik_specjalnych_znakow = 0;
					brak = false;
				}
			} else {
				licznik = 0;
				licznik_specjalnych_znakow = 0;
			}
			pozycja++;
		}while(znak != '\n');
		if(brak == true) cout << "BRAK";
		cout << endl;
	}
	return 1;
}
