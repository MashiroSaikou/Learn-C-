#include "iostream"
#include "stack"
using namespace std;

typedef struct _treeNode{
	int value;
	_treeNode *left;
	_treeNode *right;
	bool isLeftThead;//1为是线索
	bool isRightThead;
}treeNode;

/*
	前序遍历创建二叉树
	example
				1
			2		3
		4				5
			6
		7   	8
*/
void creatTreeByPre(treeNode *&node){
	char c_value;
	c_value = getchar();
	if(c_value == '*'){
		node = NULL;
	}
	else{
		node = new treeNode;
		node->isLeftThead = node->isRightThead = false;
		node->value = (int)(c_value-'0');
		creatTreeByPre(node->left);
		creatTreeByPre(node->right);
	}
}

//中序递归线索化
//上一个访问结点
treeNode *preVisit = NULL;
void recursionInTraversal(treeNode *node){
	if(node!=NULL){
		recursionInTraversal(node->left);
		cout<<node->value<<' ';
		if(!node->left){
			node->isLeftThead = true;
			node->left = preVisit;
		}
		if(preVisit!=NULL&&preVisit->right==NULL){
			preVisit->isRightThead = true;
			preVisit->right = node;
		}
		preVisit = node;
		recursionInTraversal(node->right);
	}
}

treeNode* researchInorderPre(treeNode *node){
	//如果node->isLeftThead是1,那么直接找到前驱
	if(node->isLeftThead){
		return node->left;
	}
	//否则找到左结点下的最右下角的结点
	else{
		treeNode *lastRight = node->left;
		while(lastRight->right){
			lastRight = lastRight->right;
		}
		return lastRight;
	}
}

treeNode* researchInorderNext(treeNode *node){
	//如果node->isRightThead是1，那么直接找到后继
	if(node->isRightThead == true){
		return node->right;
	}
	//如果不是，找到右结点最左下角的结点
	else{
		treeNode *lastLeft = node->right;
		while(lastLeft->left){
			lastLeft = lastLeft->left;
		}
		return lastLeft;
	}
}

//穿梭遍历线索二叉树
void crossTraversal(treeNode *node){
	treeNode *flag = node;
	while(flag != NULL){
		while(flag->isLeftThead == false){
			flag = flag->left;
		}
		cout<<flag->value<<' ';
		while(flag->isRightThead == true&&flag->right!=NULL){
			flag = flag->right;
			cout<<flag->value<<' ';
		}
		flag = flag->right;		
	}

}
int main(int argc, char const *argv[]){
	treeNode *root = NULL;
	//以前序遍历的方式读取数据
	creatTreeByPre(root);

	//中序递归遍历
	cout<<"recursionInTraversal:";
	recursionInTraversal(root);
	cout<<endl;
	crossTraversal(root);
	return 0;
}
