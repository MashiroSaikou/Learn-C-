/*
	2017.9.1
	Learn-C++
*/

#include "isotream"
#include "math.h"
#include "iomanip"

using namespace std;

int main(int argc, char const *argv[])
{
	double p = -450.2333;
	
	cout.flags(ios::left);//左对齐
	cout<<setw(10)<<setfill('Q')<<p<<"End"<<endl;//设置宽度为10,以Q填充
	
	cout.flags(ios::right);//右对齐
	cout<<setpresicion(2)<<p<<"End"<<endl;//设置精度为2
	
	cout.flags(ios::internal);//两端对齐
	cout<<setw(10)<<p<<"End"<<endl;

	cout<<endl<<endl;
	

	int n = -12450

	cout.flags(ios::showpos);//显示符号
	cout<<hex<<n<<"End"<<endl;//16进制显示
	cout<<dec<<n<<"End"<<endl;//10进制显示
	cout<<oct<<n<<"End"<<endl;//8进制显示

/*	格式化输出
	setpresicion(n) 设置精度
	setw(n) 设置宽度
	setfill(c) 以c字符填充空白
	setiosflags() 格式化格式内容
	resetisoflags() 终止已设置的输出格式状态

	格式化输出标志
	ios::left	输出数据在本域宽范围内向左对齐
	ios::right	输出数据在本域宽范围内向右对齐
	ios::internal	数值的符号位在域宽内左对齐，数值右对齐，中间由填充字符填充
	ios::dec	设置整数的基数为10
	ios::oct	设置整数的基数为8
	ios::hex	设置整数的基数为16
	ios::showbase	强制输出整数的基数(八进制数以0打头，十六进制数以0x打头)
	ios::showpoint	强制输出浮点数的小点和尾数0
	ios::uppercase	在以科学记数法格式E和以十六进制输出字母时以大写表示
	ios::showpos	对正数显示“+”号
	ios::scientific	浮点数以科学记数法格式输出
	ios::fixed	浮点数以定点格式(小数形式)输出
	ios::unitbuf	每次输出之后刷新所有的流
	ios::stdio	每次输出之后清除stdout, stderr
	
	return 0;
}