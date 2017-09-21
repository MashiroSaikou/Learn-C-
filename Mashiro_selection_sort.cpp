/*--------------------------------
	Mashiro
	Selection Sort
---------------------------------*/

#include "iostream"

using namespace std;

int main(int argc, char const *argv[])
 {
	const int n = 9;
	int data[n] = {0,49,38,65,97,76,13,27,49};
	//data[0] = data[1];
	for (int i = 1; i < n; ++i){
		data[0] = data[i];
		int pos;
		for (int j = i; j < n; ++j){
			if (data[0] > data[j]){
				data[0] = data[j];
				pos = j;
			}
		}
		data[pos] = data[i];
		data[i] = data[0];
	}
	data[0] = 0;
	for (int i = 0; i < n; ++i){
		cout<<data[i]<<' ';
	} 	
 	return 0;
 } 