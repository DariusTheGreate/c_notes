#include <iostream>
#include <vector>
#include <functional>

#define print(a) std::cout << a << "\n"

template<typename T>
struct array{
	T* array_data;
	size_t size;
};

template <typename T, template <typename> class Container = array>
struct Stack{
	Container<T> c;
};

void test_stack(){
	Stack<int> s;
}

template<class T, template <class K = T> class Container = array>
void foo(T value_in){
	print("sss");	
}

template <class T, template <class K> class DataWrapperType>
class DataManager{
	DataWrapperType<T> data;
};


int main(){
	int x = 222;
	int& xref = x;
	DataManager<int, array> dataHandler;
	foo(dataHandler);
	test_stack();
	return 0;
}
