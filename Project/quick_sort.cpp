#include <iostream>
#include "quick_sort.h"
using namespace std;

void quick_sort(vector<VideoGame>& data, int left, int right) {
	if (right <= left) {
		return;
	}

	VideoGame& pivot = data[left];
	int i = left + 1;
	int j = right;
	while (i <= j && i <= right && j > left) {

		while (i <= right && data[i].get_rank() <= pivot.get_rank()) {
			i++;
		}

		while (data[j].get_rank() > pivot.get_rank() && j > left) {
			j--;
		}

		if (i < j) {
			swap(data[i], data[j]);
		}
	}

	swap(pivot, data[j]);
	quick_sort(data, left, j - 1);
	quick_sort(data, j + 1, right);
}

void quick_sort(vector<VideoGame>& data) {
	quick_sort(data, 0, data.size() - 1);
}