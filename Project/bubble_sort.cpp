#include <iostream>
#include "bubble_sort.h"
using namespace std;

void bubble_sort(vector<VideoGame>& data) {
	bool sorted;
	int num = 0;
	for (int i = 0; i < 10 - 1; i++) {		
		sorted = true;
		for (int j = 0; j < data.size() - 1 - i; j++) { 

			if (data[j].get_name() > data[j + 1].get_name()) {
				swap(data[j], data[j + 1]);
				num++;
				sorted = false;
			}
		}

		if (sorted) {
			break;
		}
	}
	cout << "\nNumber of bubble swaps: " << num << endl;
}