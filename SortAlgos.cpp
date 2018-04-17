// SortAlgos.cpp : Program to utilize insertion, quick, heap, and merge sort on sorted and unsorted vectors and measure execution times.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include <time.h>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>

int n_array[7] = { 100, 500, 1000, 2000, 5000, 8000, 10000 };


void insertion(std::vector<int> arr) {
	int p, tmp, j;

	for (p = 0; p < arr.size(); p++) {
		tmp = arr[p];
		for (j = p; j > 0 && tmp < arr[j - 1]; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = tmp;
	}
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int part(std::vector<int> arr, int low, int high) {
	int pivot = arr[high];
	int i = low-1;

	for (int j = low; j < high; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &pivot);
	return (i + 1);
}

void quick(std::vector<int> arr, int low, int high) {
	if (high > low) {
		int partition = part(arr, low, high);
		quick(arr, low, partition - 1);
		quick(arr, partition + 1, high);
	}
}


void makeHeap(std::vector<int> arr, int i, int n) {
	
	int left = 2 * n + 1;
	int right = 2 * n + 2;
	int largest = n;

	if (left<i&&arr[left]>arr[largest])
		largest = left;
	if (right < i && arr[right]> arr[largest])
		largest = right;
	if (largest != n) {
		std::swap(arr[n], arr[largest]);
		makeHeap(arr, i, largest);
	}
}

void heap(std::vector<int> arr) {
	for (int i = arr.size() / 2-1; i >= 0; i--) {
		makeHeap(arr, arr.size(), i);
	}
	for (int i = arr.size() - 1; i >= 0; i--) {
		std::swap(arr[0], arr[i]);
		makeHeap(arr, i, 0);
	}
}

void merge(std::vector<int> arr) {
	int middle = arr.size()/2

}

std::vector<int> loadvector(std::vector<int> arr) {
	int i, x;
	bool check;

	for (i = 0; i < arr.size(); i++) {
		do {
			x = rand() % 20000;
			check = true;
			for (int y = 0; x < arr.size(); x++) {  //check for duplicates
				if (x == arr[y]) {
					check = false;
					break;
				}
			}
		} while (!check);
		arr[i] = x;
	}
	return arr;
}

int main()
{
	std::ofstream output;
	std::ofstream output1;

	std::string file1 = "unsorted.csv";
	std::string file2 = "sorted.csv";

	output.open(file1, std::ios::app);
	output << "Selection" << "," << "Quick" << "," << "Heap" << "," << "Merge" << "," << " n size" <<std::endl;

	output1.open(file2, std::ios::app);
	output1 << "Selection" << "," << "Quick" << "," << "Heap" << "," << "Merge" << "," << " n size" <<std::endl;

	int q = 1;

	int num, x = 0;
	int y;

	srand(time(NULL));
	for (x = 0; /*x<1*/x < sizeof(n_array)/ sizeof(int); x++) {
		std::vector<int> array;
		array.resize(n_array[x]);
		std::vector<int> larray = loadvector(array);

		auto start = std::chrono::high_resolution_clock::now();
		insertion(larray);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Selection Sort: " << duration.count() << "uS" << std::endl;
		output << duration.count() << ",";
		
		start = std::chrono::high_resolution_clock::now();
		quick(larray,0, (sizeof(n_array) / sizeof(int))-1);
		stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Quick Sort: " << duration.count() << "uS" << std::endl;
		output << duration.count() << ",";

		start = std::chrono::high_resolution_clock::now();
		heap(larray);
		stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Heap Sort: " << duration.count() << "uS" << std::endl;
		output << duration.count() /*<< "," */<< std::endl;

		//start = std::chrono::high_resolution_clock::now();
		////merge();
		//stop = std::chrono::high_resolution_clock::now();
		//duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		//std::cout << "Merge Sort: " << duration.count() << "uS" << std::endl;
		
		std::sort(larray.begin(), larray.end());

		start = std::chrono::high_resolution_clock::now();
		insertion(larray);
		stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Sorted Selection Sort: " << duration.count() << "uS" << std::endl;
		output1 << duration.count() << ",";

		start = std::chrono::high_resolution_clock::now();
		quick(larray, 0, (sizeof(n_array) / sizeof(int)) - 1);
		stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Sorted Quick Sort: " << duration.count() << "uS" << std::endl;
		output1 << duration.count() << ",";

		start = std::chrono::high_resolution_clock::now();
		heap(larray);
		stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "Sorted Heap Sort: " << duration.count() << "uS" << std::endl;
		output1 << duration.count() /*<< ","*/ << std::endl;

		//start = std::chrono::high_resolution_clock::now();
		////merge();
		//stop = std::chrono::high_resolution_clock::now();
		//duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		//std::cout << "Merge Sort: " << duration.count() << "uS" << std::endl;


	}
	
}

