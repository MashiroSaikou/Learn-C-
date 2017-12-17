//c++实现B-Tree

#include "iostream"
#include "cstdio"
#include "algorithm"

using namespace std;
//class BTreeNode;
class BTreeNode
{
public:
	int degree; //节点的度
	int *key; 	//关键字数组
	BTreeNode **child;	//子节点指针数组
//	BTreeNode *parent;	//双亲指针
	bool isLeaf;	//是否为叶子节点
	int count_key;	//当前关键字个数

	BTreeNode(int _degree, bool _isLeaf);
	//遍历函数
	void traverse();
	//搜索函数
	BTreeNode* search(int _find_key);
	
	void splitChild(int _key_range, BTreeNode* targetNode);

	void insertNonFull(int _key);
	friend class BTree;
};

//一个BTree
class BTree
{
public:
	BTreeNode* root;	//根节点
	int degree;	//根节点的度
	BTree(int _degree)
	{root = NULL; degree = _degree;}
	
	//遍历函数
	void traverse()
	{if(root != NULL) root->traverse();}

	//搜索函数
	BTreeNode* search(int _find_key)
	{return (root == NULL)?NULL:root->search(_find_key);}

	void insertNode(int _key);
};

BTreeNode::BTreeNode(int _degree, bool _isLeaf){
	degree = _degree;
	isLeaf = _isLeaf;
	count_key = 0;
	key = new int[degree+1]; //0号未用
	child = new BTreeNode*[degree+1];
}

void BTreeNode::traverse(){
	for (int i = 0; i <= count_key; ++i){
		if(i > 0)
			cout<<key[i]<<' ';
		if(isLeaf == false)
			child[i]->traverse();
	}
}

BTreeNode* BTreeNode::search(int _find_key){
	int i = 1;
	//定位_find_key位置
	while(i <= count_key && _find_key > key[i]) i++;
	//相等
	if(_find_key == key[i])	return this;
	//不等但已经是叶子节点
	if(isLeaf == true) return NULL;
	//不等但是不是叶子节点，继续找
	return child[i-1]->search(_find_key);
}

void BTree::insertNode(int _key){
	//插入，根节点为空的情况
	if(root == NULL){
		root = new BTreeNode(degree, true);
		root->key[1] = _key;
		root->count_key = 1;
	}
	//根节点不为空的情况
	else{
		//根节点满
		if(root->count_key == degree){
			BTreeNode *temp_node = new BTreeNode(degree,false);

			temp_node->child[0] = root;
			temp_node->splitChild(1,root);

			//_key小就在左边，否则就取右边
			int i = 0;
			if(_key > temp_node->key[1]) i++;
			//对合适的子节点进行插入
			temp_node->child[i]->insertNonFull(_key);
			//改变根节点为新建节点
			root = temp_node;
		}
		//跟不满的情况下直接对根节点进行插入
		else
			root->insertNonFull(_key);
	}
}


void BTreeNode::insertNonFull(int _key){
	int i = count_key;
	//当前节点是叶子节点
	if(isLeaf == true){
		//找到应当插入的位置，并且将比_key大的关键字后移
		while(i > 0&&_key < key[i]){
			key[i+1] = key[i];
			i --;
		}
		key[i+1] = _key;
		//关键字个数增加
		count_key = count_key+1;
	}
	//非叶子节点
	else if(isLeaf == false){
		//找到应当插入的子节点
		while(i > 0&&_key < key[i]) i--;

		//子节点满，分裂
		if(child[i]->count_key==child[i]->degree){
			splitChild(i+1,child[i]);

			if(key[i+1] < _key) i++;
		}
		child[i]->insertNonFull(_key);
	}
}
//分裂节点，只有在节点关键字满的情况下分裂
//min_index是中间的数，向上取整， targetNode是被分裂节点
void BTreeNode::splitChild(int _key_range, BTreeNode* targetNode){
	//新建分裂出的子节点
	BTreeNode* other_node = new BTreeNode(targetNode->degree,targetNode->isLeaf);
	other_node->count_key = targetNode->degree/2;
	//新建节点对应旧节点的位置
	int other_node_start = (targetNode->degree+1)/2+1;
	//上传至父节点的关键字
	int mid_key = targetNode->key[(targetNode->degree+1)/2];
	//复制旧节点后面的数据到新建节点
	for (int i = other_node_start,j = 1; i <= targetNode->degree; ++i,++j){
		other_node->key[j] = targetNode->key[i];
		other_node->child[j] = targetNode->child[i];
		child[i] = NULL;
	}
	other_node->child[0] = child[other_node_start-1];
	targetNode->count_key = (targetNode->degree+1)/2-1;

	//移动父节点的关键字和子节点位置
	for(int i = count_key;i >= _key_range; i--){
		key[i+1] = key[i];
		child[i+1] = child[i];
	}
	key[_key_range] = mid_key;
	child[_key_range] = other_node;
	//关键字个数增加1
	count_key = count_key+1;
}

int main(int argc, char const *argv[])
{
	BTree t(5); // A B-Tree with minium degree 3
    t.insertNode(10);
    t.traverse();cout<<endl; 
    t.insertNode(20);
    t.traverse();cout<<endl;
    t.insertNode(5);
    t.traverse();cout<<endl;
    t.insertNode(6);
    t.traverse();cout<<endl;
    t.insertNode(12);
    t.traverse();cout<<endl;
    t.insertNode(30);
    t.traverse();cout<<endl;
    t.insertNode(7);
    t.traverse();cout<<endl;
    t.insertNode(17);
    t.traverse();cout<<endl;
 
    cout << "Traversal of the constucted tree is ";
    t.traverse();
 
    int k = 6;
    (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
 
    k = 15;
    (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present";
 	
	return 0;
}
