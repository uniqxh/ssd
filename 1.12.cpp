#include<iostream>
using namespace std;

union Test{
	short a;
	char b[sizeof(short)];
};
int main(){
	Test test;
	test.a = 0x0102;
	if(test.b[0] == 0x01) cout<<"big endian."<<endl;
	else if(test.b[0] == 0x02) cout<<"little endian."<<endl;
	else cout<<"unknown"<<endl;
	return 0;
}
