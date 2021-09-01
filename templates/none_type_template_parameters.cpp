#include <iostream>

//imagine if templates parameter is number, not a type. its kind of obvious:
// for example: std::array<int, 10>, where 10 is size of array
// or we can define matrices..
// we can use as template parameters only compile time constants

template<typename T, size_t N>
class array{
	T a[N];
public:
	
};

void test_own_array(){
	array<int, 10> a;
	array<int, 12> b;
    array<int 10> aa;
	a = aa;// good
	b = a;// CE	
}

// but float and double is not valid template parameters. alson, obviously own types


//interesting that we can use pointers:
// also notice that we can use previous parameters:
template<typename T, T* TP>
struct MyStruct{
	
};

//then we can define conpiletime types...


template<class Field, size_t N, size_t M>
struct Matrix{};

template<class Field, class N, class M>
Matrix<Field, N, M> operator *(const Matrix<Field, N, M>, const Matrix<Field, N, M>);


int main(){
	return 0;
}
