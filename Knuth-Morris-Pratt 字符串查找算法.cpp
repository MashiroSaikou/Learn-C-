//字符串查找Knuth-Morris-Prattsuanfa实现
//
#include "iostream"
#include "string"
using namespace std;
void getNextStr(string, int*);
int kmpSearch(string, string, int*);
int main(int argc, char const *argv[])
{
	string Origin = "BBC ABCDAB ABCDABDDABDE";
	string Target = "ABCDABD";

	//get the next string of Target
	int *Next = new int[Target.size()];
	getNextStr(Target, Next);
	//return the  index of first character of string in Origin if it exists
	//if not return -1;
	int Position = kmpSearch(Origin, Target, Next);
	cout<<Position;
	return 0;
}

void getNextStr(string Target, int *Next){
	int k = -1, j = 0;
	int lenTarget = Target.size();
	Next[0] = k;
	//Target[k] 表示前缀 Target[j]表示后缀
	Next[0] = -1;

	while(j < lenTarget-1){
		if(k == -1||Target[k] == Target[j]){
			j = j+1;
			k = k+1;
		//提前比较以减少重复匹配
			if(Target[j] = Target[k])
					Next[j] = Next[k];
			else
				Next[j] = Next[k]+1;
		}
		else{
			k = Next[k];
		}
	}
}	

int kmpSearch(string Origin, string Target, int *Next){
	int i = 0, j = 0;
	//Origin[i]表示被查找字符串,Target[j]表示参考字符串

	int lenTarget = Target.size();
	int lenOrigin = Origin.size();
	int Position;
	while(j < lenTarget&&i < lenOrigin){
		if(Origin[i] == Target[j]){
			i ++;
			j ++;
		}
		else if(j == 0){
			i ++;
		}
		else{
			j = Next[j];
		}
	}
	if(j == lenTarget){
		return i - j;
	}
	else return -1;
}
