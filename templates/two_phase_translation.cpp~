#include <iostream>

//6.7 template instantiation.

template <int N>
struct Danger{
	int a[N];
};


template <typename T, int N>
//in case of virtual inheritance he not instantiate methods
struct S : public virtual Base{
	void f(){
		Danger<N> d;
	}

	void g(){
		Danger<-1> d;
	}
	

	// in case class have virtual function - we need to create VTable and vpointer. this vpointer points to code..So we need to instantiate
	// more over, obviously we cant create template virtual function, cause it means compiler needs to instantiate h() for each type in program
//	virtual void h(){
//		Danger<-555> d;
//	}
};



//in case you create type he needs to be defined AND instantiated
//---------------------------------------------------------------
//but you can ask compiler to explicitly instanciate template:
	
template struct S<int, 5>;//it will instantiate only struct, not methods.


//lazy control, if we do not execute anything he dont care.
//this behaviour explains by the fact that compiler will not checks every possible compilation branch
int main(){
	//he dont even care if we do this
	S<int, 5> ss;//in this moment he istantiate class, but not his methods.. But he do instantiate and checks his fields
	//and this
	ss.f();
	//but..
	//ss.g();

	//but that okay, cause compiler do not need instance of object to deal with reference or pointer to that object:
	S<int, -2>* sptr = nullptr;
	int x = 5;
	S<int, -1>& sref = reinterpret_cast<S<int, -1>&>(x); // but S<int, -1> and S<int, -2> different type. at all

	//actually same happens if we have pointer to some not defined struct:
	struct not_declared;
	not_declared* ptr = nullptr;

	//in case you create type he needs to be defined AND instantiated
	//---------------------------------------------------------------
	//but you can ask compiler to explicitly instanciate template:
	
	//template struct S<int, -1>;//it will instantiate only struct, not methods.

}
