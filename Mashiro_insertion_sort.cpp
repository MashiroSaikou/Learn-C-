/*----------------------------
	Mashiro
	Insertion Sort
------------------------------*/

#include "iostream"

using namespace std;

int main(int argc, char const *argv[])
{
	const int n = 9;
	int data[n] = {0,49,38,65,97,76,13,27,49};
	for (int i = 2; i < n; ++i)
	{
		//data[0]暂存位
		data[0] = data[i];
		int j;
		for ( j = i-1; data[j] > data[0]; --j){
			data[j+1] = data[j];
		}
		data[j+1] = data[0];
	}
	data[0] = 0;
	for (int i = 0; i < n; ++i)
	{
		cout<<data[i]<<' ';
	}
	return 0;
}