#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
void displayVector(const vector<int> &v, string title = "") {
	if(!title.empty()) cout << title << ":" << endl;
    for (int i = 0; i < (int)v.size(); i++) cout << v.at(i) << " ";
    cout << endl;
}
void shellSortSwap(vector<int> &array, int i, int gap) {
	if(array[i] > array[i+gap]) {
				cout << "zamiana" << endl;
				int temp = array[i];
				array[i] = array[i + gap];
				array[i + gap] = temp;
				displayVector(array, "Po zamianie");
				if(i - gap >= 0) {
					cout << "sprawdzam w lewo: porownuje array[" << i - gap << "]=" << array[i - gap] << " i array[" << i << "]=" << array[i] << endl;
					if(array[i - gap] > array[i]) shellSortSwap(array, i - gap, i);
				}
			}
}
void shellSort(vector<int> array) {
	displayVector(array, "Przed sortowaniem");
	int gap = array.size();
	while(gap / 2 >= 1) {
		gap /= 2;
		for(int i = 0; i + gap < array.size(); i++) {
			cout << "porownuje array[" << i << "]=" << array[i] << " i array[" << i + gap << "]=" << array[i+gap] << endl;
			shellSortSwap(array, i, gap);
		}		
	}
}
int main() {
	int array_size = 10;
	vector<int> array;
	srand ( time(NULL) );
	for(int i = 0; i < array_size; i++) {
		array.push_back(rand() % 100);
	}
	shellSort(array);
	return 0;
}
