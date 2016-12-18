#include<iostream>
using namespace std;

class Test{
	public:
		int hello(){
			cout<<"hello world."<<endl;
			return 0;
		}
};
int main(){
	Test test;
	int ret = test.hello();
	cout<<"ret="<<ret<<endl;
	return 0;
}
