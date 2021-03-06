#include <iostream>
#define print(a) std::cout << a << "\n"
//I want S to be like this all of the time except some cases..
template<class T>
struct S{
	T x;
};

//now lets specialize some cases
template<>
struct S<int>{
	int y = 0;
};

void test_S(){
	S<double> sd;
	S<int> si;
	sd.x;//good
	si.x;// not good
	//more over:
	S<float> sf = sd;// CE cause from point of view of compiler S<float> and S<double> are two independent types and it doesnt matter that float is like double
}

//example std::hash
// he doesnt have own realization and for each type you want it to have hash you specialize struct Hash
template<typename T>
struct Hash;
// BUT IN ORDER TO SPECIALIZE SOME STRUCT YOU MUST HAVE NOT SPECIALIZED VARIANT
//like this:

template<>
struct Hash<int>{
	size_t operator ()(int x){
		return x * x;
	}
};

void test_own_hash(){
	Hash<int> hi;//gooood
	Hash<double> hd;// not good
}

//function specialization:

template<class T>
void foo(T x){
	print(1);
}

template<>
void foo(int x){
	print(2);
}

//IMPORTANT: specialization and overloading of functions not the same!
// for example if we define not template function:

void foo(int x){
	print(3);
}

void test_foo(){
	foo("sss");
}

int main(){

	return 0;
}




