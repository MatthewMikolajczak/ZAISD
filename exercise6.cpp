// Przynależność punktu do wielokąt - autor: Mateusz Mikolajczak
#include <cstdlib>
#include <iostream>
using namespace std;
int matrixDeterminant(int x1, int y1, int x2, int y2, int x3, int y3) {
	return x1*y2 + x2*y3 + x3*y1 - x3*y2 - x1*y3 - x2*y1;
}
bool pointOnLineSegment(int x1, int y1, int x2, int y2, int px, int py) {
	if(matrixDeterminant(x1, y1, px, py, x2, y2) != 0) return false;
	if(px >= min(x1, x2) && px <= max(x1, x2) && py >= min(y1, y2) && py <= max(y1, y2)) return true;
	return false;
}
bool compareSign(int a, int b) {
	if(a >=0 && b >= 0) return true;
	if(a < 0 && b < 0) return true;
	return false;
}
bool crossingLineSegments(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	if(pointOnLineSegment(x1, y1, x2, y2, x3, y3)) return true;
	if(pointOnLineSegment(x1, y1, x2, y2, x4, y4)) return true;
	if(pointOnLineSegment(x3, y3, x4, y4, x1, y1)) return true;
	if(pointOnLineSegment(x3, y3, x4, y4, x2, y2)) return true;
	if(compareSign(matrixDeterminant(x1, y1, x2, y2, x3, y3), matrixDeterminant(x1, y1, x2, y2, x4, y4))) return false;
	if(compareSign(matrixDeterminant(x3, y3, x4, y4, x1, y1), matrixDeterminant(x3, y3, x4, y4, x2, y2))) return false;
	return true;
}
int main(int argc, char *argv[]) {
	int testy, wierzcholki, x, y, maxx, counter, k;
	int **wierzcholek;
	cin >> testy;
	for(int i = 0; i < testy; ++i) {
		cin >> wierzcholki >> x >> y;
		wierzcholek = new int*[wierzcholki];
		maxx = -1000000;
		counter = 0;
		for(int j = 0; j < wierzcholki; ++j) {
			wierzcholek[j] = new int[2];
			cin >> wierzcholek[j][0] >> wierzcholek[j][1];
			if(wierzcholek[j][0] > maxx) maxx = wierzcholek[j][0];
		}
		maxx++;
		for(int j = 0; j < wierzcholki; ++j) {
			if((j+1) == wierzcholki) k = 0;
			else k = j + 1;
			if(crossingLineSegments(x, y, maxx, y, wierzcholek[j][0], wierzcholek[j][1], wierzcholek[k][0], wierzcholek[k][1])) counter++;
		}
		if(counter%2 != 0) cout << "TAK" << endl;
		else cout << "NIE" << endl;
		for(int j = 0; j < wierzcholki; ++j) delete [] wierzcholek[j];
		delete [] wierzcholek;
	}	
	return 0;
}
