//平衡二叉树（BST）实现
//学习 http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
//学习 http://www.geeksforgeeks.org/avl-tree-set-2-deletion/

#include "iostream"
#include "cstdio"
using namespace std;
//BST node
typedef struct _node{
	int key;
	_node *left;
	_node *right;
	int nodeHeight;
}node;

int findMax(int a, int b){
	return a > b?a:b;
}

int getHeight(node* root){
	if(root == NULL)
		return 0;
	return root->nodeHeight;
}

int getBalance(node* root){
	if(root == NULL)
		return 0;
	return getHeight(root->left) - getHeight(root->right);
}

node* rightRotate(node* root){
	node* _left_root = root->left;
	root->left = _left_root->right;
	_left_root->right = root;

	root->nodeHeight = 1 + findMax(getHeight(root->left),getHeight(root->right));
	_left_root->nodeHeight = 1 + findMax(getHeight(_left_root->right),getHeight(_left_root->left));
	return _left_root;
}

node* leftRotate(node* root){
	node* _right_root = root->right;
	root->right = _right_root->left;
	_right_root->left = root;

	root->nodeHeight = 1 + findMax(getHeight(root->right),getHeight(root->left));
	_right_root->nodeHeight = 1 + findMax(getHeight(_right_root->right),getHeight(_right_root->left));
	return _right_root;
}

node* newNode(int key){
	node* _newnode = new node;
	_newnode->key = key;
	_newnode->right = NULL;
	_newnode->left = NULL;
	_newnode->nodeHeight = 1;
	return _newnode;
}
//BST插入操作
//使用递归
node* insertNodeBST(node* root, int key){
	/*先做通常插入操作*/
	if(root == NULL)
		return newNode(key);
	//Right
	else if(root->key < key)
		root->right = insertNodeBST(root->right, key);
	//Left
	else if(root->key > key)
		root->left = insertNodeBST(root->left, key);
	//null error
	else
		return root;

	/*更新每个节点的高度，计算平衡因子已确定需要什么样的旋转操作*/
	int leftHeight = getHeight(root->left);
	int rightHeight = getHeight(root->right);
	root->nodeHeight = 1+(leftHeight > rightHeight?leftHeight:rightHeight);
	int balance = getBalance(root);

	/*具体操作分为四种*/
	//left left
	if(balance > 1&&key < root->left->key)
		return rightRotate(root);
	//right right
	else if(balance < -1&&key > root->right->key)
		return  leftRotate(root);
	//left right
	else if(balance > 1&&key > root->left->key){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	//right left
	else if(balance < -1&&key < root->right->key){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	//本身已经平衡
	return root;
}
//删除指定关键字的节点
node* findMinKeyNode(node* root){
	if(root->left == NULL)
		return root;
	else
		return findMinKeyNode(root->left);
}
node* deleteNodeBST(node* root, int key){
	/*定位关键字*/
	if(root == NULL)
		return root;
	//Right
	else if(root->key < key){
		root->right = deleteNodeBST(root->right,key);
	}
	//Left
	else if(root->key < key){
		root->left = deleteNodeBST(root->left,key);
	}
	//Equal
	else if(root->key = key){
		/*只有右节点*/
		if(root->left == NULL||root->right == NULL){
			node* _temp_node = (root->left == NULL?root->right:root->left);
			if(_temp_node == NULL){
				_temp_node = root;
				root = NULL;
			}
			else
				*root = *_temp_node;
			delete(_temp_node);
		}
		else{
			node* _temp_node = findMinKeyNode(root->right);
			root->key = _temp_node->key;
			root->right = deleteNodeBST(root->right, _temp_node->key);
		}
	}
	/*更新高度*/
	//只有根节点且被删除
	if(root == NULL)
		return root;

	int leftHeight = getHeight(root->left);
	int rightHeight = getHeight(root->right);
	root->nodeHeight = 1+(leftHeight > rightHeight?leftHeight:rightHeight);
	int balance = getBalance(root);

	/*具体操作分为四种*/
	//left left
	if(balance > 1&&getBalance(root->left)>=0)
		return rightRotate(root);
	//right right
	else if(balance < -1&&getBalance(root->right)<0)
		return  leftRotate(root);
	//left right
	else if(balance > 1&&getBalance(root->left)<0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	//right left
	else if(balance < -1&&getBalance(root->right)>=0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	//本身已经平衡
	return root;

}
void preOrder_print(node* root){
	if(root != NULL){
		cout<<root->key<<' ';
		preOrder_print(root->left);
		preOrder_print(root->right);
	}
}

void test_1(){
/*测试用例*/
	node* root = NULL;
	root = insertNodeBST(root, 10);
	root = insertNodeBST(root, 20);
	root = insertNodeBST(root, 30);
	root = insertNodeBST(root, 40);
	root = insertNodeBST(root, 50);
	root = insertNodeBST(root, 25);

	/* The constructed AVL Tree would be
		    30
		   /  \
		 20   40
		/  \     \
	   10  25    50
	*/

	printf("Preorder traversal of the constructed AVL"
		" tree is \n");
	preOrder_print(root);
}
void test_2(){
 /*测试用例*/
	node* root = NULL;
    root = insertNodeBST(root, 9);
    root = insertNodeBST(root, 5);
    root = insertNodeBST(root, 10);
    root = insertNodeBST(root, 0);
    root = insertNodeBST(root, 6);
    root = insertNodeBST(root, 11);
    root = insertNodeBST(root, -1);
    root = insertNodeBST(root, 1);
    root = insertNodeBST(root, 2);
 
    /* The constructed AVL Tree would be
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6
    */
 
    printf("Preorder traversal of the constructed AVL "
           "tree is \n");
    preOrder_print(root);
 
    root = deleteNodeBST(root, 10);
 
    /* The AVL Tree after deletion of 10
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */
 
    printf("\nPreorder traversal after deletion of 10 \n");
    preOrder_print(root);

    /*Preorder traversal of the constructed AVL tree is 
	9 1 0 -1 5 2 6 10 11 
	Preorder traversal after deletion of 10 
	1 0 -1 9 5 2 6 11 
	*/
}
int main(int argc, char const *argv[])
{
//	test_1();
	test_2();
	return 0;
}
