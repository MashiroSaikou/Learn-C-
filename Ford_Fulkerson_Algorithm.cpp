#include "iostream"
#include "limits.h"
#include "string.h"
#include "queue"

#define n 6
using namespace std;


//Group[n][n] 给出的flow图
//residualGroup[n][n] 残留图
//flow_path[n] 残留图得到的路径
bool BFS(int residualGroup[n][n],int flow_start,int flow_end, int flow_path[n]){
	bool *isVisited = new bool[n];
	memset(isVisited,0,sizeof(isVisited[0]));
	//起点的设置
	isVisited[flow_start] = true;
	flow_path[flow_start] = -1;

	queue<int> flow_queue;
	flow_queue.push(flow_start);

	while(flow_queue.empty() == false){
		int _flow_end = flow_queue.front();
		flow_queue.pop();
		for(int i = 0; i < n; i++){
			if(residualGroup[_flow_end][i] > 0&&isVisited[i] == false){
				flow_queue.push(i);
				flow_path[i] = _flow_end;
				isVisited[i] = true;
			}
		}
	}
	return isVisited[flow_end];
}


int Ford_Fulkerson_Algorithm(int Group[n][n],int flow_start,int flow_end){
	/*当从残余图中的依然能找到一个路径的时候，说明flow可以增加*/
	//新建残余图并初始化
	int residualGroup[n][n];
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			residualGroup[i][j] = Group[i][j];
		}
	}
	//最大流量
	int group_flow_max = 0;
	//存放残余图中的路径
	int flow_path[n];
	//循环操作
	while(BFS(residualGroup,flow_start,flow_end,flow_path)){
		//记录单次路径中的最小流量
		int _group_flow_max = INT_MAX;
		//设立查找游标
		int cursor = flow_end;
		/*待确定flow_path的表示方式*/
		while(cursor!=flow_start){
			//
			int flow_between_vertice = residualGroup[flow_path[cursor]][cursor];
			if(_group_flow_max > flow_between_vertice)
				_group_flow_max = flow_between_vertice;
			//cursor后移
			cursor = flow_path[cursor];
		}

		cursor = flow_end;
		while(cursor!=flow_start){
			//residualGroup更新
			residualGroup[flow_path[cursor]][cursor] -= _group_flow_max;
			
			residualGroup[cursor][flow_path[cursor]] += _group_flow_max;
			
			cursor = flow_path[cursor];
		}

		group_flow_max += _group_flow_max;
	}
	return group_flow_max;
}

int main(int argc, char const *argv[])
{
    int graph[n][n] = { {0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}
                      };
 
    cout << "The maximum possible flow is " << Ford_Fulkerson_Algorithm(graph, 0, 5);
 
    return 0;
}
