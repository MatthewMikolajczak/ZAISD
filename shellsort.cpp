#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>
#include <algorithm>
using namespace std;
void displayVector(const vector<int> &v, string title = "") {
	if(!title.empty()) cout << title << ":" << endl;
    for (int i = 0; i < (int)v.size(); i++) cout << v.at(i) << " ";
    cout << endl;
}
void shellSortSwap(vector<int> &array, int i, int gap) {
	//cout << "zamiana" << endl;
	int temp = array[i];
	array[i] = array[i + gap];
	array[i + gap] = temp;
	//displayVector(array, "Po zamianie");
	if(i - gap >= 0) {
		//cout << "sprawdzam w lewo: porownuje array[" << i - gap << "]=" << array[i - gap] << " i array[" << i << "]=" << array[i] << endl;
		if(array[i - gap] > array[i]) shellSortSwap(array, i - gap, gap);
	}
}
void shellSort(vector<int> array, vector<int> gaps) {
	displayVector(array, "Przed sortowaniem");
	int counter = 0;
	int gap;
	do{
		gap = gaps[counter];
		for(int i = 0; i + gap < array.size(); i++) {
			//cout << "porownuje array[" << i << "]=" << array[i] << " i array[" << i + gap << "]=" << array[i+gap] << endl;
			if(array[i] > array[i+gap]) shellSortSwap(array, i, gap);
		}		
		counter++;
	}while(counter < gaps.size());
	displayVector(array, "Po sortowaniu");
}
int main() {
	int array_size = 10, gap;
	vector<int> array;
	vector<int> gaps;
	srand ( time(NULL) );
	for(int i = 0; i < array_size; i++) {
		array.push_back(rand() % 100);
	}
	
	gaps.clear(); // Shell 1959
	gap = array_size;
	while(gap/2 >= 1) {
		gaps.push_back(gap/2);
		gap /= 2;
	}
	displayVector(gaps, "Shell's (1959) gaps");	
	shellSort(array, gaps);
	
	gaps.clear(); // Hibbard 1963	
	for(int i = 1; ; i++) {
		gap = pow(2, i);
		if(gap - 1 <= array_size) gaps.push_back(gap - 1);
		else break;
	}
	reverse(gaps.begin(),gaps.end());
	displayVector(gaps, "Hibbard's (1963) gaps");
	shellSort(array, gaps);
	
	gaps.clear(); // Pratt 1971
	int pmax = log2(array_size);
	int qmax = log2(array_size)/log2(3);
	for(int p = 0; p <= pmax; p++)
		for(int q = 0; q <= qmax; q++) {
			if(pow(2, p) * pow(3, q) <= array_size) gaps.push_back(pow(2, p) * pow(3, q));
			else break;
		}
	sort(gaps.begin(), gaps.end());
	reverse(gaps.begin(),gaps.end());
	displayVector(gaps, "Pratt's (1971) gaps");
	shellSort(array, gaps);
	
	gaps.clear(); // Knuth 1973
	for(int i = 1; ; i++) {
		if((pow(3,i)-1)/2 <= ceil(array_size/3)) gaps.push_back((pow(3,i)-1)/2);
		else break;
	}
	reverse(gaps.begin(),gaps.end());
	displayVector(gaps, "Knuth's (1973) gaps");
	shellSort(array, gaps);
	
	// Sedgewick 1986
	gaps.clear();
	gaps.push_back(1);
	for(int i = 1; ; i++) {
		if(pow(4, i) + 3 * pow(2, i-1) + 1 <= array_size) gaps.push_back(pow(4, i) + 3 * pow(2, i-1) + 1);
		else break;
	}
	reverse(gaps.begin(),gaps.end());
	displayVector(gaps, "Sedgewick's (1986) gaps");
	shellSort(array, gaps);
	
	return 0;
}
