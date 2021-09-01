#include <iostream>

#define print(a) std::cout << a << "\n"

//templates llow as to compute some functions in compile time

template<size_t N>
struct Fibo{
	static const int value = Fibo<N - 1>::value + Fibo<N - 2>::value;
};

template<>
struct Fibo<1>{
	static const int value = 1;
};

template<>
struct Fibo<2>{
	static const int value = 2;
};

//another example -> checks for prime of number:

template<size_t N, size_t D>
struct IsPrimeHelper{
	static const bool value = N % D == 0 ? false : IsPrimeHelper<N, D-1>::value;
};

template<size_t N>
struct IsPrimeHelper<N, 1>{
	static const bool value = true;
};

template<size_t N>
struct IsPrime{
	static const bool value = IsPrimeHelper<N, N-1>::value;
};


template<int number, int power>
struct NPower{
	static const int value = number * NPower<number, power-1>::value;
};

template<int number>
struct NPower<number, 2>{
	static const int value = number * number;
};

template<int number>
struct NPower<number, 1>{
	static const int value = number;
};



template<int A, int B>
struct NOD{
	static const int value = NOD<B, int(A%B) >::value;
};

template<int A>
struct NOD<A, 0>{
	static const int value = A;
};




int main(){
//	std::cout << NOD<10,10>::value;
	std::cout << NPower<4, 4>::value;
//	print(Fibo<3>::value);
//	print(IsPrime<11>::value);
}

