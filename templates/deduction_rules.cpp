#include <iostream>

//overloading deduction rules:
//1) for simple functions:
//	1.1) perfect variant always wins
//		but two equaly perfect variant - CE
//	1.2) all standart conversions equal
//		but any standart conversion wins user defined conversion (not explicit constructors)
//	1.3) "..." lose to anything 
//		but void f(...) {print(1)};
//			void f(int& x) {print(2)};
//
//			foo(1)// -> 1
//
//2) for templates:
//	2.1) perfect simple function variant wins template
//	2.2) more specific template wins less specific
//		template<class T> void f(T)
//		template<class T> void f(T*)
//		template<class T> void f(T**)
//		template<class T> void f(T***)
//
//		int** a;
//		f(a);//3
//		f<int*>//2
//
//
//	2.3) less amount of arguments wins a larger amount
//	
//	THIS RULES ARE WRITTEN IN ORDER OF THEIR IMPORTANCE	

//its always overloading and then acess control:
//class Bar{
//	void f(int);
//public:
//	void f(char);
//};
//
//main(){
//	Bar b;
//	b.f(1); // CE
//}

//IMPORTANT: you can maintain instantiation of templtes using extern: 
//	extern template int max<int>(int, int);
//it will not pass instantiated function in object file. Look UP!

//templane deduction rrules:
//1 remember 3 rules about templates : ungeneral(~) better then general; exact variant the best and template should be the same
//2 in time of template deduction references and cv(const/volatile)-classificators are cutted of


template <class T>
class TypeGetter{
	TypeGetter() = delete;
};

template <typename T>
void f(T x){
	//TypeGetter<T>();//allow you to get type when compiler throws an error
}

template<class T>
struct S{
	S(T x){
		
	}
};

template <typename T>
T max(T x, T y){
	return x > y ? x : y;
}


void test_deduction(){
	int x = max(1,3);//for parameters that types its works
	//at time of deduction cv cuts and reference:
	const int& a = 1;
	const int& b = 2;
	x = max(a,b); // -> int max<int>(int, int);
	//it works like this cause in case when we instanciate max() for each possible T we would have lots of instances (max(cosnt int, const int), max(int, const int), max(const int, int), max()....)
	

	// template must be the same type:
	int aa = 34;
	float bb = 55.0;
	//x = max(aa, bb); //CE
}

//template type deduction happens in two steps: 1) type dedcution before type substitution 2) after


//sometimes we need to specialize types in template function (it this case minimalization of instances is not working~):
// but in thos case compiler will treat as as "smart users"
// it is actually good practice to write template functions like this template<class T> T max(T , T) {}. 
// Cause in this case we can pass as T anything, by wrapping it in std::ref

template<typename T> 
T max_sm(const T& a, const T& b){
	return a > b ? a : b;
}

void test_smart_template_functions(){
	int a = 5;
	int* b = &a;
	auto res = max_sm(b, b);
	std::cout << res;
}

/*geterogenn maximum problem:

template <typename T, typename U> ??? max(T t, U u){
	return t > u ? t : u;
}

with type should we return? std::any? std::varint? void*?
*/

//function overloading:

float sqrt(float x) {std::cout << "float\n"; return x;}
double sqrt(double x) {std::cout << "double\n"; return x;}
int sqrt(int x) {std::cout << "int\n";return x;}

void test_function_overloading(){
	sqrt(1.0);//double
	sqrt(1.0f);//float
	sqrt(1);//int
}

//functions cant be overloaded by cv classificators (const volatile)
//but except cv classificators of outside type (like: int&, const int&, int* const int* )




int main(){
	test_function_overloading();
	//test_smart_template_functions();
		//int x  = 44;
	//int& y = x;
	//f(y); // T is int note: std::ref/ std::reference_wrapper => std::vector<std::reference_wrapper>
	return 0;
}

