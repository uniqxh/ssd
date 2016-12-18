#include<iostream>
using namespace std;
union A{
	int a[5];
	char b;
	int c;
};
int main(){
	cout<<"int :"<<sizeof(int)<<endl;
	cout<<"char :"<<sizeof(char)<<endl;
	cout<<"long :"<<sizeof(long)<<endl;
	cout<<"float :"<<sizeof(float)<<endl;
	cout<<"double :"<<sizeof(double)<<endl;
	cout<<sizeof(A)<<endl;
	return 0;
}
