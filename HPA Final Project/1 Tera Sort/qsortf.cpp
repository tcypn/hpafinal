/* C implementation QuickSort */
#include<stdio.h>
#include<fstream>
#include<iostream>
// A utility function to swap two elements
using namespace std;

void swap(float* a, float* b,string* c,string* d)
{
	float t = *a;
	*a = *b;
	*b = t;
    string s=*c;
    *c=*d;
    *d=s;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (pair<string,float> arr[], int low, int high)
{
	float pivot = arr[high].second; // pivot
	int i = (low - 1); // Index of smaller element

	for (int j = low; j <= high- 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (arr[j].second <= pivot)
		{
			i++; // increment index of smaller element
			swap(&arr[i].second, &arr[j].second,&arr[i].first,&arr[j].first);
		}
	}
	swap(&arr[i + 1].second, &arr[high].second,&arr[i + 1].first,&arr[high].first);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(pair<string,float> arr[], int low, int high)
{
	if (low < high)
	{

		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

/* Function to print an array */
void printArray(pair<string,float> arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		cout<<arr[i].first<<" "<<arr[i].second<<endl;

}
 
// Driver program to test above functions
int main()
{
    pair<string,float> arr[] = {make_pair("a",0.10),make_pair("b",0.4), make_pair("c",0.8), make_pair("d",0.3), make_pair("e",0.2), make_pair("f",0.5)};
    int n = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, 0, n-1);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}