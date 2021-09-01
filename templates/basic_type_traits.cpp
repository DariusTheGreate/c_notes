#include <iostream>
#define print(a) std::cout << a << "\n"
#include <type_traits>

//we need to compare T and U : if(T == U) return 0;
//#include <type_traits> //since c++11

template <class T, class U>
void f(T x, U u){
		
	//print((std::is_same<T, U>::value ? 1 : 2));
}

//lets write own is_same:

template<typename T, typename U>
struct is_same{
	static const bool value = false;
};

template<typename T>
struct is_same<T, T>{
	static const bool value = true;
};

//example of meta function:
// I want to remove const from T 
template <typename T>
void g(T x){
	//std::remove_const<T>::type y = x;	
}


//lets write our own remove_const:
template<typename T>
struct remove_const{
	using type = T;
};

template<typename T>
struct remove_const<const T>{
	using type = T;
};

//template <typename T>
//using remove_const_t = remove_const<T>::type;

template <typename T>
void test_own_remove_const(T x){
	typename remove_const<T>::type y = x;// you need typename to tall compiler that he needs to treats it as type name, cause by default he treats it as varible~
	y = 6;
	print(y);
}


//lets write own remove reference:

template<class T>
struct TypeGetter{
	TypeGetter() = delete;
};

template<typename T>
struct remove_ptr{
	using type = T;
};

template<typename T>
struct remove_ptr<T*>{
	using type = T;
};

template<class T>
void test_own_remove_ptr(T x){
	//typename remove_ref<T>::type y = x;
	TypeGetter<T> val;
}

int main(){
	
	
	const int x = 5;
	const int* xptr = &x;
	test_own_remove_ptr(xptr);
	test_own_remove_const(x);

	return 0;
}

