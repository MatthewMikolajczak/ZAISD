#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <numeric>
using namespace std;
void displayVector(const vector<int> &v, string title = "") {
	if(!title.empty()) cout << title << ":" << endl;
    for (int i = 0; i < (int)v.size(); i++) cout << v.at(i) << " ";
    cout << endl;
}
int shellSortSwap(vector<int> &array, int i, int gap, int computational_complexity) {
	//cout << "zamiana" << endl;
	int temp = array[i];
	array[i] = array[i + gap];
	array[i + gap] = temp;
	//displayVector(array, "Po zamianie");
	if(i - gap >= 0) {
		//cout << "sprawdzam w lewo: porownuje array[" << i - gap << "]=" << array[i - gap] << " i array[" << i << "]=" << array[i] << endl;
		computational_complexity++;
		if(array[i - gap] > array[i]) computational_complexity = shellSortSwap(array, i - gap, gap, computational_complexity);
	}
	return computational_complexity;
}
int shellSort(vector<int> array, vector<int> gaps) {
	int computational_complexity = 0;
	//displayVector(array, "Przed sortowaniem");
	int counter = 0;
	int gap;
	do{
		gap = gaps[counter];
		for(int j = 0; j < gap; j++) {
		for(int i = j; i + gap < array.size(); i+=gap) {
			//cout << "porownuje array[" << i << "]=" << array[i] << " i array[" << i + gap << "]=" << array[i+gap] << endl;
			computational_complexity++;
			//if(array[i] > array[i+gap]) computational_complexity = shellSortSwap(array, i, gap, computational_complexity);
			if(array[i] > array[i+gap]) shellSortSwap(array, i, gap, computational_complexity);
		}		
		}
		counter++;
	}while(counter < gaps.size());
	//displayVector(array, "Po sortowaniu");
	return computational_complexity;
}
int main() {
	int max_array_size = 128000, gap;
	float computational_complexity;
	
	for(int data_case = 1; data_case < 6; data_case++) {
		
		switch(data_case) {
				case 1: // tpo	-	 czas sortowania zbioru posortowanego
					cout << "\ntpo	-	 czas sortowania zbioru posortowanego\n";
					break;
				case 2: // tod	-	 czas sortowania zbioru posortowanego malejąco
					cout << "\ntod	-	 czas sortowania zbioru posortowanego malejąco\n";
					break;
				case 3: // tpp	-	 czas sortowania zbioru posortowanego z losowym elementem na początku
					cout << "\ntpp	-	 czas sortowania zbioru posortowanego z losowym elementem na początku\n";
					break;
				case 4: // tpk	-	 czas sortowania zbioru posortowanego z losowym elementem na końcu
					cout << "\ntpk	-	 czas sortowania zbioru posortowanego z losowym elementem na końcu\n";
					break;
				case 5: // tnp	-	 czas sortowania zbioru z losowym rozkładem elementów
					cout << "\ntnp	-	 czas sortowania zbioru z losowym rozkładem elementów\n";
					break;
			}
		
		for(int array_size = 1000, x = 0; array_size <= max_array_size; x++, array_size = 1000 * pow(2,x)){
				
			vector<int> array;
			vector<int> gaps;
			
			switch(data_case) {
				case 1: // tpo	-	 czas sortowania zbioru posortowanego
					for(int i = 0; i < array_size; i++) {
						array.push_back(i);
					}
					break;
				case 2: // tod	-	 czas sortowania zbioru posortowanego malejąco
					for(int i = 0; i < array_size; i++) {
						array.push_back(array_size - i - 1);
					}
					break;
				case 3: // tpp	-	 czas sortowania zbioru posortowanego z losowym elementem na początku
					for(int i = 0; i < array_size; i++) {
						array.push_back(i);
					}
					srand ( time(NULL) );
					array[0] = (rand() % 128000);
					break;
				case 4: // tpk	-	 czas sortowania zbioru posortowanego z losowym elementem na końcu
					for(int i = 0; i < array_size; i++) {
						array.push_back(i);
					}
					srand ( time(NULL) );
					array[array_size-1] = (rand() % 128000);
					break;
				case 5: // tnp	-	 czas sortowania zbioru z losowym rozkładem elementów
					srand ( time(NULL) );
					for(int i = 0; i < array_size; i++) {
						array.push_back(rand() % 128000);
					}
					break;
			}
			//displayVector(array, "Array:");	
			//cout << endl;
			cout << endl << "Array size: " << array.size() << "  \t  ";
			
			clock_t start, time;
			double time_results[10];
			
			gaps.clear(); // Shell 1959
			gap = array_size;
			while(gap/2 >= 1) {
				gaps.push_back(gap/2);
				gap /= 2;
			}
			
			//displayVector(gaps, "Shell's (1959) gaps");	
			computational_complexity = pow(array_size, 2);
			//cout << "\tSHELL: " << (int)ceil(100 * shellSort(array, gaps) / computational_complexity) << "%  ";
			for(int i = 0; i < 10; i++) {
				start = clock();
				shellSort(array, gaps);
				time = clock() - start;
				double result = time / (double)(CLOCKS_PER_SEC);
				time_results[i] = result;
			}
			
			cout << "\tSHELL: " << accumulate(time_results, time_results + 10, 0.0) << "s ";
			
			gaps.clear(); // Hibbard 1963	
			for(int i = 1; ; i++) {
				gap = pow(2, i);
				if(gap - 1 <= array_size) gaps.push_back(gap - 1);
				else break;
			}
			reverse(gaps.begin(),gaps.end());
			//displayVector(gaps, "Hibbard's (1963) gaps");
			computational_complexity = pow(array_size, (float)3/(float)2);
			//cout << "\tHIBBARD: " << (int)(100 * shellSort(array, gaps) / computational_complexity) << "% ";
			for(int i = 0; i < 10; i++) {
				start = clock();
				shellSort(array, gaps);
				time = clock() - start;
				double result = time / (double)(CLOCKS_PER_SEC);
				time_results[i] = result;
			}
			
			cout << "\tHIBBARD: " << accumulate(time_results, time_results + 10, 0.0) << "s ";
			
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
			//displayVector(gaps, "Pratt's (1971) gaps");
			//computational_complexity = array_size * log2(array_size)/log2(10) * log2(array_size)/log2(10);
			computational_complexity = array_size * log(array_size) * log(array_size);
			//cout << "\tPRATT: " << (int)(100 * shellSort(array, gaps) / computational_complexity) << "% ";
			for(int i = 0; i < 10; i++) {
				start = clock();
				shellSort(array, gaps);
				time = clock() - start;
				double result = time / (double)(CLOCKS_PER_SEC);
				time_results[i] = result;
			}
			
			cout << "\tPRATT: " << accumulate(time_results, time_results + 10, 0.0) << "s ";
			
			gaps.clear(); // Knuth 1973
			for(int i = 1; ; i++) {
				if((pow(3,i)-1)/2 <= ceil(array_size/3)) gaps.push_back((pow(3,i)-1)/2);
				else break;
			}
			reverse(gaps.begin(),gaps.end());
			//displayVector(gaps, "Knuth's (1973) gaps");
			computational_complexity = pow(array_size, (float)3/(float)2);
			//cout << "\tKNUTH: " << (int)(100 * shellSort(array, gaps) / computational_complexity) << "% ";
			for(int i = 0; i < 10; i++) {
				start = clock();
				shellSort(array, gaps);
				time = clock() - start;
				double result = time / (double)(CLOCKS_PER_SEC);
				time_results[i] = result;
			}
			
			cout << "\tKNUTH: " << accumulate(time_results, time_results + 10, 0.0) << "s ";
			
			// Sedgewick 1986
			gaps.clear();
			gaps.push_back(1);
			for(int i = 1; ; i++) {
				if(pow(4, i) + 3 * pow(2, i-1) + 1 <= array_size) gaps.push_back(pow(4, i) + 3 * pow(2, i-1) + 1);
				else break;
			}
			reverse(gaps.begin(),gaps.end());
			//displayVector(gaps, "Sedgewick's (1986) gaps");
			computational_complexity = pow(array_size, (float)4/(float)3);
			//cout << "\tSEDGEWICK: " << (int)(100 * shellSort(array, gaps) / computational_complexity) << "% ";
			for(int i = 0; i < 10; i++) {
				start = clock();
				shellSort(array, gaps);
				time = clock() - start;
				double result = time / (double)(CLOCKS_PER_SEC);
				time_results[i] = result;
			}
			
			cout << "\tSEDGEWICK: " << accumulate(time_results, time_results + 10, 0.0) << "s ";
			
		}
		cout << endl;
	}
	return 0;
}
