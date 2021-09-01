#include <iostream>

//sometimes we can get situation like this:

template <typename T>
struct S{
	using x = T;
};

template <>
struct S<int>{
	static int x;
};

int a;


template<typename T>
void f(){
	S<T>::x * a; //in this moment compiler can multiply x or defint ponter to T (T* a)  
    // in this moment compiler right before instantiation shall know if this is declaration or just an expression. But he can not do that..
	// in this case X is dependent name, cause it depend on waht we place as T. 
	// in first place in this situation compiler treats it as declaration of variable
	//it could be resolved like this:
	typename S<T>::x a;//but it will throws an error in case T= int. But thats not a problem
}

template <typename T>
struct SS{
	template <int N>
	struct A{};
};

template<>
struct SS<int>{
	static const int A = 5;
};

template<typename T>
void g(){
	SS<T>::A<10> a;	// stupid compiler threats it like this : "SS<T>::A   <   10  >   a" and asks why a not declared
	typename SS<T>::template A<10> a;// it specialize that A is template, not a type. NOW LOOK AT basic_type_traits.cpp
}

//dependent names are occures also in situations like this:

template <typename T>
struct Base{
	int x;
};

template <typename T>
struct Derived : Base<T>{
	void f(){
		//x = 1;// he dont know what x is, cause hes not instantiate any Base<T>
		//it treats like this:
		this->x = 1;
		//or
		Base<T>::x = 1;
	}
};


int main(){
	//S<double> sd;
	//f<double>();
	
	return 0;
}
