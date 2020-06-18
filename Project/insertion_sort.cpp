#include <iostream>
#include "insertion_sort.h"
using namespace std;

void insertion_sort(vector<VideoGame>& data) {
	int num = 0;
	for (int i = 1; i < data.size(); i++) {
		for (int j = i; j > 0; j--) {
			if (data[j - 1].get_name() > data[j].get_name()) {
				swap(data[j], data[j - 1]);
				num++;
			}
		}
	}
	cout << "\nNumber of insertion swaps: " << num << endl;
}