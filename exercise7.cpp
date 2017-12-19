// Otoczka wypukła - autor: Mateusz Mikolajczak
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
float alpha(int x, int y) {
	float d = abs(x) + abs(y);
	if(d == 0) return 0;
	if(x >= 0 && y >= 0) return (float)(y/d);
	if(x < 0 && y >= 0) return (float)(2 - y/d);
	if(x < 0 && y < 0) return (float)(2 + abs(y)/d);
	if(x >= 0 && y < 0) return (float)(4 - abs(y)/d);
	return false;
}
struct vertex
{
	int x, y, index;
	float alpha;
};
bool compareVertex(vertex left, vertex right){
	float alphal = alpha(left.x,left.y);
	float alphar = alpha(right.x,right.y);
	if(alphal > alphar) return false;
    if(alphal == alphar) if(left.x > right.x) return false;
	return true;
}
float matrixDeterminant(int x1, int y1, int x2, int y2, int x3, int y3) {
	return (float)(x1*y2 + x2*y3 + x3*y1 - x3*y2 - x1*y3 - x2*y1);
}
float triangleArea(int x1, int y1, int x2, int y2, int x3, int y3) {
	float a, b, c, s, area;
	a = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	b = sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
	c = sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
	s=(a+b+c)/2;
	area=sqrt(s*(s-a)*(s-b)*(s-c));
	return area;
}
int main(int argc, char *argv[]) {
	int testy, wierzcholki, indexStartowego, yStartowego, xStartowego, x, y;
	vector <vertex> wierzcholek;
	vector <vertex> otoczka;
	cin >> testy;
	for(int i = 0; i < testy; ++i) {
		cin >> wierzcholki;
		yStartowego = 1000000;
		for(int j = 0; j < wierzcholki; ++j) {			
			cin >> x >> y;
			wierzcholek.push_back({x, y, j, alpha(x,y)});
			if(y < yStartowego || (y == yStartowego && x < xStartowego)){
				indexStartowego = j;
				yStartowego = y;
				xStartowego = x;
			}
		}		
		// usuwanie startowego z tablicy wierzchołków
		wierzcholek.erase(wierzcholek.begin() + indexStartowego);
		// sortowanie tablicy wierzchołków względem kąta do osi X
		sort(wierzcholek.begin(), wierzcholek.end(), compareVertex);
		// przechodzenie po tablicy i robienie otoczki
		otoczka.push_back({xStartowego, yStartowego, indexStartowego});
		otoczka.push_back({wierzcholek[0].x, wierzcholek[0].y, wierzcholek[0].index});
		for(int j = 1; j < wierzcholek.size(); j++) {		
			float wyznacznik = matrixDeterminant(otoczka[otoczka.size()-2].x, otoczka[otoczka.size()-2].y, otoczka[otoczka.size()-1].x, otoczka[otoczka.size()-1].y, wierzcholek[j].x, wierzcholek[j].y);
			//jesli Wj jest po lewej w stosunku do dwoch ostatnich z otoczki to go dodaj do otoczki i continue;
			if(wyznacznik > 0) {
				otoczka.push_back({wierzcholek[j].x, wierzcholek[j].y, wierzcholek[j].index});			
				continue;
			}
			//jesli Wj jest po prawej w stosunku do dwoch ostatnich z otoczki to usuń 1 ostatni z otoczki i dodaj Wj i continue;
			if(wyznacznik <= 0) {
				otoczka.pop_back();
				otoczka.push_back({wierzcholek[j].x, wierzcholek[j].y, wierzcholek[j].index});			
				continue;
			}
		}
		int wyznacznik = matrixDeterminant(otoczka[otoczka.size() - 2].x, otoczka[otoczka.size() - 2].y, otoczka[otoczka.size() - 1].x, otoczka[otoczka.size() - 1].y, otoczka[0].x, otoczka[0].y);
		if(wyznacznik < 0) otoczka.pop_back();
				
		//cout << "Otoczka: \n";
		//for(int xyz = 0; xyz < otoczka.size(); xyz++) cout << "x: " << otoczka[xyz].x << ", y: " << otoczka[xyz].y << ", index: " << otoczka[xyz].index << endl;
		//cout << endl;
		
		// obliczanie pola
		float pole = 0;
		for(int j = 2; j < otoczka.size(); j++) {
			pole += triangleArea(otoczka[0].x, otoczka[0].y, otoczka[j-1].x, otoczka[j-1].y, otoczka[j].x, otoczka[j].y);
		}
		cout << pole << endl;
		wierzcholek.clear();
		otoczka.clear();
	}	
	return 0;
}
