#include<iostream>
#include<vector>

using namespace std;
void print(const vector<int> &v){
	cout<<"size: "<< v.size() <<" capacity: "<< v.capacity() <<endl;
}
int main(){
	cout<<"sizeof(unsigned int): "<< sizeof(unsigned int)<<endl;
	cout<<"sizeof(vector): "<<sizeof(vector<long>)<<endl;
	cout<<"sizeof(vector<char>): "<<sizeof(vector<char>)<<endl;
	vector<int> v;
	cout<<sizeof(v)<<endl;
	print(v);
	for(int i=0;i<10;++i){
		v.push_back(i);
		print(v);
	}
	vector<int>(v).swap(v);
	cout<<"调整后: ";
	print(vector<int>(v));
	print(v);
	cout<<sizeof(v)<<endl;
	for(vector<int>::iterator it = v.begin(); it != v.end();){
		if((*it)%3 == 0) it = v.erase(it);
		else ++it;
	}
	for(vector<int>::iterator it = v.begin(); it != v.end(); ++it){
		cout<<*it<<" ";
	}
	cout<<endl;
	return 0;
}
