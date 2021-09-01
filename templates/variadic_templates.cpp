#include <iostream>

void print(){
	std::cout << "\n";
}

//Args for compiler means "packet" and this packet we can unwrap using Args&... after that compiler will put all content of packet 
template <typename Head, typename... Tail>
void print(const Head& head, const Tail&... tail){
		std::cout << head << " ";
	    print(tail...);	
}

template<typename First, typename Second, typename... Tail>
struct is_homogeneous{
	static const bool value = std::is_same<First, Second>::value && is_homogeneous<Second, Tail...>::value;
};

template<typename First, typename Second>
struct is_homogeneous<First, Second>{
	static const bool value = std::is_same<First, Second>::value;
};

//fold expressions:

template <typename... Tail>
void print_fold(const Tail&... tail){
	(std::cout << ... <<  tail) << " "; // tail1 op tail2 op ... tail
	print(tail...);	
}

int main(){
	print(1,2,3,4, "313", 5);

	std::cout << is_homogeneous<int,int,char>::value;
}

