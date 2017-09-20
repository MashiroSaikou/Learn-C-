/*-----------------------------
	Mashiro7
	Quick Sort
-------------------------------*/

#include "iostream"

using namespace std;

int medium_data(int *data, int i, int j){
	return data[i]>data[j]?(data[i]>data[(i+j)/2]?data[i]:data[(i+j)/2]):(data[j]>data[(i+j)/2]?data[j]:data[(i+j)/2]);
}
int Partion(int *data,int i,int j){
	int pivot = data[i];
	while(i < j){
		while(i < j&&data[j] > pivot){
			j --;
		}
		if (i < j)
			data[i++] = data[j];
		while(i < j&&data[i] < pivot){
			i ++;
		}
		if(i < j){
			data[j--] = data[i];
		}
	}
	data[i] = pivot;
	return i;
}
void QuickSort(int *data,int low, int high){
	int pivotIndex;
	if (low < high){
		pivotIndex = Partion(data,low,high);
		QuickSort(data,low,pivotIndex-1);
		QuickSort(data,pivotIndex+1,high);
	}
}
int main(int argc, char const *argv[])
{
	int const n = 9;
	int data[n] = {0,49,38,65,97,76,13,27,49};
	QuickSort(data,1,n-1);
	for (int i = 0; i < n; ++i){
		cout<<data[i]<<' ';
	}
	return 0;
}

