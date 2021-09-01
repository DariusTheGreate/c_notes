#include <iostream>



struct Base{
	void foo(){
		std::cout << "base\n";
	}
};

template <class B>
struct Derived{
	void foo(){
		std::cout << "derived\n";
	}

};

int main(){
	Derived d;
	d.foo();//derived
	Base b;
	b = d;
	b.foo();//derived
}
