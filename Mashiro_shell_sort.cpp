/*---------------------------
	Mashiro7
	Shell Sort
------------------------------*/

#include "iostream"

using namespace std;

int main(int argc, char const *argv[])
{
	int const n = 9;
	int data[n] = {0,49,38,65,97,76,13,27,49};
	int step = n;
	while(step > 1){
		step = step/3 + 1;
		for (int i = step +1; i < n; ++i){
			data[0] = data[i];
			int j;
			for (j = i - step;data[j] > data[0]; j-=(step)){
				data[j+step] = data[j];
			}
			data[j+step] = data[0];
		}
		data[0] = 0;
	}
	for (int i = 0; i < n; ++i){
		cout<<data[i]<<' ';
	}
	return 0;
}