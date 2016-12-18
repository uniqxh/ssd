#include<iostream>
using namespace std;

class Singleton{
	private:
		Singleton(){}
		static Singleton *p;
	public:
		static Singleton* GetInstance(){
			if(p == NULL) p = new Singleton();
			return p;
		}
};
Singleton* Singleton::p = NULL;
int main(){
	Singleton* p1 = Singleton::GetInstance();
	Singleton* p2 = Singleton::GetInstance();
	if(p1 == p2)
		cout<<"p1==p2"<<endl;
	else cout<<"p1<>p2"<<endl;
	return 0;
}
