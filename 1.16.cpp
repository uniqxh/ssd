#include<iostream>
using namespace std;

union A{
	long i;
	int k[5];
	char c;
};
struct B{
	int cat;
	A cow;
	double dog;
};
int main(){
	cout<<sizeof(B)<<endl;
	cout<<sizeof(A)<<endl;
	return 0;
}
