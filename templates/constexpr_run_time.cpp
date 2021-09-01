#include <iostream>


struct Node{
	Node(int v) : value(v){}
	int value;
};


constexpr int getValue(Node node){
	return node.value;
}

int main(){
	int run_v;
	std::cin >> run_v;
	Node n(run_v);
	int res = getValue(n);
	std::cout << res;
	return 0;
}
