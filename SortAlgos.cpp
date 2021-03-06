// SortAlgos.cpp : Program to utilize insertion, quick, heap, and merge sort on sorted and unsorted vectors and measure execution times.
//					Outputs the runtimes to separate CSV times (sorted and unsorted inputs) for easy graphing of data.  Also creates a 
//					txt file containing 100 randomly generated values from 1-20000 for iteration of n = 100.

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
#include <string>
#include <sstream>


int n_array[7] = { 100, 500, 1000, 2000, 5000, 8000, 10000 }; //array used to hold the n values needed for each iteration


void insertion(std::vector<int> arr) { //insertion sort function
	int p, tmp, j;

	for (p = 0; p < arr.size()-1; p++) { //iterate through array
		tmp = arr[p];					
		for (j = p; j > 0 && tmp < arr[j - 1]; j--) {  //iterate back through array to compare and find values to fit parameters
			arr[j] = arr[j - 1];		//move element
		}
		arr[j] = tmp;
	}
}

void swap(int* a, int* b) //swap function to swap places in the vector using pointers - used with partitioning part of quicksort algorithm
{
	int t = *a;  
	*a = *b;
	*b = t;
}

int part(std::vector<int> arr, int low, int high) { //partition function for quicksort
	int pivot = arr[high]; //use last value as pivot
	int i = low-1; //determine low value

	for (int j = low; j < high; j++) {  //iterate through the vector, if a value is less than or equal to the pivot, increment i and swap the low and current value
		if (arr[j] <= pivot) {			
			i++;
			swap(&arr[i], &arr[j]);  //uses the swap function declare above
		}
	}
	swap(&arr[i + 1], &pivot);//swap with pivot
	return (i + 1);  
}

void quick(std::vector<int> arr, int low, int high) { //quicksort function
	if (high > low) {
		int partition = part(arr, low, high); //partitioning vector
		quick(arr, low, partition - 1); //before partition
		quick(arr, partition + 1, high); //after partition
	}
}


void makeHeap(std::vector<int> arr, int i, int n) { //function to heapify using binary heap
	
	int left = 2 * n + 1;  
	int right = 2 * n + 2;
	int largest = n; //root

	if (left<i&&arr[left]>arr[largest]) //left greater than root
		largest = left;
	if (right < i && arr[right]> arr[largest]) //right greater than root
		largest = right;
	if (largest != n) { //not equal to root
		std::swap(arr[n], arr[largest]); //swap using stl
		makeHeap(arr, i, largest); //recur heapification
	}
}

void heap(std::vector<int> arr) { //heap sort function
	for (int i = arr.size() / 2-1; i >= 0; i--) { //create heap
		makeHeap(arr, arr.size(), i); //uses makeHeap function above
	}
	for (int i = arr.size() - 1; i >= 0; i--) { //grab elements from heap
		std::swap(arr[0], arr[i]); 
		makeHeap(arr, i, 0); //reduced heap heapification
	}
}

void merge(std::vector<int> &arr, int left, int middle, int right) { //merge sort function utilizing divide-and-conquer
	int lend = middle-left +1; //find left end
	int rend = right - middle; //find right end
	int i, j, k;

	std::vector<int> L; //left side
	L.resize(lend);
	std::vector<int> R; //right side
	R.resize(rend);

	for (i = 0; i < lend; i++) { //load left side values into left vector
		L[i] = arr[left + i];
	}
	for (j = 0; j < rend; j++) { //load right side values into right vector
		R[j] = arr[middle + 1 + j];
	}

	i = 0; //initialize indices for merging of left and right
	k = 0;
	k = left;

	while (i < lend && j < rend) { //merge the left anf right into arr
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		} 
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < lend) { //in case there are remaining values of L
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < rend) { //for remaining values of R
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(std::vector<int> &arr, int left, int right) { //merge sort function
		
	if (left < right) {
		int middle = (left +(right-1))/2; //find middle
		mergeSort(arr, left, middle);  //recur using first half
		mergeSort(arr, middle + 1, right); //recur using second half

		merge(arr, left, middle, right);
	}
}

std::vector<int> loadvector(std::vector<int> arr) { //loads vector with random values from 1-20000 and checks for duplicates, returns loaded vector
	int i, x;											
	bool check;

	std::ofstream out;						//output to .txt file was added to create file for n = 100
	std::string random = "random.txt";      //create output file random.txt - only used in n=100 case
	out.open(random, std::ios::app);		//open stream to write to file

	for (i = 0; i < arr.size(); i++) {
		do { //repeat while check is not true
			x = rand() % 20000; //generate random numbers 1-20000
			check = true;
			for (int y = 0; x < arr.size(); x++) {  //check for duplicates
				if (x == arr[y]) { //if number exists
					check = false; 
					break;
				}
			}
		} while (!check);
		arr[i] = x;		//adding values to vector
		if (arr.size() == 100) {
			out << x << " ";  //outputting to txt file if n = 100
		}
	}
	return arr; //return loaded array
}

int main()
{
	std::ofstream output;        //declare output stream for first file
	std::ofstream output1;		 //declare output stream for second file
	std::string file1 = "unsorted.csv";  //CSV filenames
	std::string file2 = "sorted.csv";

	output.open(file1, std::ios::app); //adding file headers for unsorted file
	output << "Insertion" << "," << "Quick" << "," << "Heap" << "," << "Merge" << "," << " n size" << std::endl; //adding column headers

	output1.open(file2, std::ios::app); //same thing for sorted file
	output1 << "Insertion" << "," << "Quick" << "," << "Heap" << "," << "Merge" << "," << " n size" << std::endl;
	
	int q = 1;
	int num, x = 0;
	int y;

	srand(time(NULL));	//set so rand is truly random

		for (x = 0; x < sizeof(n_array) / sizeof(int); x++) { //iterate through n sizes
			std::vector<int> array; //create vector
			array.resize(n_array[x]);		//give size of n from global array
			std::vector<int> larray = loadvector(array); //function to load random values into the vector depending on the required n size for current iteration

			/*Insertion Sort - unsorted input*/
			auto start = std::chrono::high_resolution_clock::now(); //using chrono library, start a timer
			insertion(larray);
			auto stop = std::chrono::high_resolution_clock::now(); //stop timer
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); //calculate duration in microseconds
			output << duration.count() << ","; //output duration to correct CSV file, move to next cell using comma

			/*Quick Sort - unsorted input*/
			start = std::chrono::high_resolution_clock::now(); //start timer
			quick(larray, 0, (sizeof(n_array) / sizeof(int)) - 1);
			stop = std::chrono::high_resolution_clock::now(); //stop timer
			duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); //calculate duration 
			output << duration.count() << ","; //output duration to correct CSV file, move to next cell using comma

			/*Heap Sort - unsorted input*/
			start = std::chrono::high_resolution_clock::now(); //start timer
			heap(larray);
			stop = std::chrono::high_resolution_clock::now(); //stop timer
			duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); //calculate duration 
			output << duration.count() << ","; //output duration to correct CSV file, move to next cell using comma

			/*Merge Sort - unsorted input*/
			start = std::chrono::high_resolution_clock::now(); //start timer
			mergeSort(larray, 0, larray.size() - 1);
			stop = std::chrono::high_resolution_clock::now(); //stop timer
			duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); //calculate duration 
			output << duration.count() << ","; //output duration to correct CSV file, move to next cell using comma

			output << n_array[x] << std::endl; //add vector size for this iteration to CSV, move to next line

			std::sort(larray.begin(), larray.end()); //sort vector using STL

			/*Insertion Sort - sorted input*/
			start = std::chrono::high_resolution_clock::now(); //start timer
			insertion(larray);
			stop = std::chrono::high_resolution_clock::now(); //stop timer
			duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); //calculate duration 
			output1 << duration.count() << ","; //output duration to correct CSV file, move to next cell using comma

			/*Quick Sort - sorted input*/
			start = std::chrono::high_resolution_clock::now(); //start timer
			quick(larray, 0, (sizeof(n_array) / sizeof(int)) - 1);
			stop = std::chrono::high_resolution_clock::now(); //stop timer
			duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); //calculate duration 
			output1 << duration.count() << ","; //output duration to correct CSV file, move to next cell using comma
			
			/*Heap Sort - sorted input*/
			start = std::chrono::high_resolution_clock::now(); //start timer
			heap(larray);
			stop = std::chrono::high_resolution_clock::now(); //stop timer
			duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); //calculate duration 
			output1 << duration.count() << ","; //output duration to correct CSV file, move to next cell using comma

			/*Merge Sort - sorted input*/
			start = std::chrono::high_resolution_clock::now(); //start timer
			mergeSort(larray, 0, larray.size() - 1);
			stop = std::chrono::high_resolution_clock::now(); //stop timer
			duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); //calculate duration 
			output1 << duration.count() << ","; //output duration to correct CSV file, move to next cell using comma

			output1 << n_array[x] << std::endl;//add vector size for this iteration to CSV, move to next line
		}

	
}

