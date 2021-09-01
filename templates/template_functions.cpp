#include <iostream>
#define print(a) std::cout << a << "\n"

//there are two important rules on template and functinos overloading:
//	1) exact compliance better then overloading
//	2) private better then general (means if u have 2 functions and one of them more special then an other - this one is better)
//  3) if y have function from one teplate parameter - this parameter must be the same (checkk for example bellow)..

template <class T, class U>
void f(T t, U u){
    print("1");
}

template <class T>
void f(T t, T u){
    print("2");
}

void f(int t, int u){
    print("3");
}

void test_rules(){
	f(0.0, 2); // -> 1
	f(0.0, 0.2); // -> 2
	f(3, 5); // -> 3
}

// templates parameter must be the same:

template <class T>
void g(T t, T u){
    print("2");
}

void g(int t, int u){
    print("3");
}

void test_template_rule(){
    g(0.0, 1); // -> 3 cause template parameter must be the same
}

//if rule (3) is not possible to observe its CE:

template <class T>
void m(T t, T u){
    print("2");
}

void test_templte_rule_CE(){
	m(0.0, 2); // -> CE	HE JUST CANT CHOSE WAHT TO DO 
    // but u can specize it:
	m<int>(0.0,2);
}

// 4) templates specialization is wrtten in order

template <class T, class U>
void f(T t, U u){
    print("1");
}

//template <class T>
//void f(T t, T u){
//    print("2");
//}

void f(int t, int u){
    print("3");
}

void test_order(){
	f<int>(2.2, 2);// -> 1 means "first template argument is int, next is your job to deduct"
	f<>(2,2); // -> 1 means "its template function but its your job to decide"
}

//-----------------------------------------
//we always can "specialize" our type:
//for example we can add &. In that case still we cant get like T&&& (compiler will pass us T& just reference) or const const T (const T) etc.

template<typename T>
void jojo(T jojo_in){
	print("1");
}

template<typename T>
void jojo(T& jojo_in){
	print("1");
}

void test_template_specialization(){
    jojo(1);// ->  1 we cant init lvalue ref throw rvalue
	int x = 5;
	jojo(x); // -> ambigius call cause we cant take x as reference and as an value
    // even if we try jojo<int&>(x); cause we can pass in first version and second.....
	
    // IN CASE WE HAVE OVERLOAD OF jojo(const T& jojo_in) - WE COULDNT cause its possible to have reference to const lvalue

	int& xr = x;
	jojo(xr);
	//interesting that CE occur only if we make a call, but not in case we dont

}

//compiler have to know all templaes parameters:
template<class T, class U>
void some(T x){
    print(1);
}

//but we can specialize paramters:
template<class T, class U = int>
void some_fixed(T x){
    print(1);
}

void test_know_all_parameters(){
	some(5);// CE cause compiler cant deduct parametr U
	some_fixed(5); // not CE
}



//--------------------------------------------------------------------------------


template <class T>
struct Node{
	Node() = default;
	
	template<class U>
	Node(U& data_in){
	    print("1");
	}

	Node(const Node<T>&){
	    print("2");
	}

};

//... well first constructor overlay second.second cant be called
void test_constructors(){
	Node n;
	Node nn = n;// -> 1
}

#include <vector>

template <typename T>
void lol(const std::vector<T>& data){
	print(1);
}

void test_lol(){
	vector<int> data = {1,2,3};
	lol(data);//its okay
	lol({1,2,3}); // he cant understand whish type you pass him inside of vector
}



int main(){

}
