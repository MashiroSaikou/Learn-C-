#include "iostream"
#include "fstream"
#include "string"
#include "set"
using namespace std;
typedef struct _node
{
	char ch;
	//存放字母，内部节点不会用到
	int freq;
	//记录字符出现的频数
	_node *nodeLeft;
	_node *nodeRight;
	//左右子树
}node;
//单词查找树节点定义

class Huffman
{
public:
	Huffman(char *_fileName)
			:fileName(_fileName)
	{}
	Huffman();
	~Huffman(){};

	string fileName;
	//被压缩文件名称
	int *freq;
	//记录频数的数组
	node *root;
	//单词查找树根节点

	//构建压缩准备工作
	string *st = new string[128];
	int* bulidfreq();		//统计频数
	node* buildTries(int*);	//生成单词查找树
	void buildCode(node *);
	void buildCode(node *,string);

	//开始哈夫曼编码
	void encodeHuffman();
	//生成压缩文件
	string filenameCompression;
	void generateCompression();

	//解码
	void decodeHuffman();
};


/*
	建立字符频数数组
*/
int* Huffman::bulidfreq(){
//	this->R = 0;
	int *_freq = new int[128]();
	char _ch;
	ifstream getFreq(fileName.c_str(),ios::in);
	while((_ch = getFreq.get())!=EOF){
		_freq[(int)_ch] ++;
//		if(++_fre[(int)_ch] == 1)
//			this->R ++;
	}
	return _freq;
}

/*
	构建单词查找树
	用set容器进行储存
*/
struct freqLess{
	bool operator()(const node *a,const node *b){
		return (a->freq <= b->freq);
	}
};
node* Huffman::buildTries(int *_freq){
	std::set<node*,freqLess> Tries; //构建set容器，并以freq的升序排列
	for(char _ch = 0; _ch < 127; _ch++){
		if(_freq[_ch] > 0)
			Tries.insert(new node({_ch, _freq[_ch], NULL, NULL}));
//			cout<<_ch<<':'<<_freq[_ch]<<' ';
	}

	//合并单词查找树
	while(Tries.size() > 1){
		node *x = *(Tries.begin());
		Tries.erase(Tries.begin());
		node *y = *(Tries.begin());
		Tries.erase(Tries.begin());
		node *parent = new node({'\0', x->freq+y->freq, x, y});
		Tries.insert(parent);
	}
	return *Tries.begin();
}
/*
	打印，测试用
*/
/*
void printRoot(node *root){
	if(root->nodeLeft == NULL&root->nodeRight == NULL){
			cout<<root->ch<<' '<<root->freq<<'\t';
			return;
	}
	printRoot(root->nodeLeft);
	printRoot(root->nodeRight);
}
*/
/*
	递归构建编码表
*/
void Huffman::buildCode(node *_root){
//	string[] _st = new string[128];
	buildCode(_root,"");
}
void Huffman::buildCode(node *_root, string s){
	if(_root->nodeLeft == NULL&&_root->nodeRight == NULL){
		this->st[_root->ch] = s;
		return;
	}
	buildCode(_root->nodeLeft,s+'0');
	buildCode(_root->nodeRight,s+'1');
}
/*
	压缩生成二进制文件
*/
void Huffman::generateCompression(){
	char _ch;
	filenameCompression = "Compression"+fileName;
	ofstream binaryFile(filenameCompression.c_str());
	ifstream asciiFile(fileName.c_str());
	while((_ch = asciiFile.get())!=EOF){
		binaryFile<<st[_ch];
		cout<<_ch<<' ';
	}
	binaryFile.close();
	asciiFile.close();
}
/*
	压缩开始入口
*/
void Huffman::encodeHuffman(){
	freq = bulidfreq();
	root = buildTries(freq);
	buildCode(root);
	generateCompression();
}

void Huffman::decodeHuffman(){
	ifstream binaryFile(filenameCompression.c_str());
	string filenameUncompression = "Un" + filenameCompression;
	ofstream asciiFile(filenameUncompression.c_str());
	char _ch;
	node *cursor = root;
	_ch = binaryFile.get();
	do{
		if(cursor->nodeRight == NULL&&cursor->nodeLeft == NULL){
			asciiFile<<cursor->ch;
			cursor = root;
		}
		else if(_ch == '0')	{
			cursor = cursor->nodeLeft;
			_ch = binaryFile.get();
 		}
		else if(_ch == '1'){
			cursor = cursor->nodeRight;
			_ch = binaryFile.get();
		}
	}while(_ch != EOF);
	asciiFile<<cursor->ch;
	binaryFile.close();
	asciiFile.close();
}
int main(int argc, char const *argv[])
{
	Huffman test("test.txt");
	test.encodeHuffman();
/*
	for(int i = 0; i < 128; i++){
		cout<<test.freq[i]<<' ';
	}
	cout<<endl;

	for (int i = 0; i < 128; ++i){
		if(test.st[i]!=""){
			cout<<test.st[i];
			cout<<i<<endl;
		}
	}
*/
	test.decodeHuffman();
	// printRoot(test.root);
	return 0;
}
