#include <iostream>
#include <list>
#include <vector>
#include <span>
//itertors:

struct data{
	int a;
	int b;
	int c;
};

struct miss_get_type{
	miss_get_type(int a){
		
	}

};

template<typename T>
struct custom_data_array{
	using value_type = T;
	T* data = nullptr;
	int size = 0;
	//custom_data(T* data_in, int size_in) : data(data_in), size(size_in){

	//};

	custom_data_array(std::span<T> span_input) : data(span_input.data()), size(span_input.size()) {

	}

	struct iterator{
		T* iterator_item = nullptr;
		
		iterator(T* val){
				iterator_item = val;
		}

		T operator *() const{
			return *iterator_item;//custom_data_array::data[iterator_position];
		}

		//void operator ++(){
		//	iterator_item

		//}
	};

	iterator begin() const{
		return iterator(0);

	}

};

template<class T, class U>
struct is_same{
	static const bool it_is = false;
};

template<class T>
struct is_same<T, T>{
	static const bool it_is = false;	
};


//constexpr void?

void test_is_same(){
	if(is_same<int, int>::it_is)
		std::cout << "it is\n";

}

template<typename T>
struct remove_const
{
	using Type = T;
};

template<typename T>
struct remove_const<const T>
{
	using Type = T;
};

void testremove_const(){
	const int a = 6;

	remove_const<int>::Type b;

}

template<typename T>
struct remove_ptr
{
	using Type = T;
};

template<typename T>
struct remove_ptr<T*>
{
	using Type = T;
};

template<bool B, class T, class V>
struct conditional
{
	using Type = T;
};

template<class T, class V>
struct conditional<true, T, V>{
	using Type = V;
};

template <typename T>
void use_span(std::span<T>){
	std::cout << "bich\n";
}

template<class Iterator>
void my_advance(Iterator& it, int n){
	Iterator it_new = it;
	for(int i = 0; i < n; ++i)
		++it_new;
}


















template<class T, class U>
struct same
{
	static const bool is_it = true;
};


template<class T>
struct same<T, T>
{
	static const bool is_it = false;

};

template<class T>
struct remove_ref
{
	using Type  = T;
};

template<class T>
struct remove_ref<T&>
{
	using Type = T; 
};



template<class T>
struct Node{
private:
	template<typename Iter>
	struct node_iterator
	{
		friend class Node;// not sure why
	public:
		typedef Iter iterator_type;

		typedef iterator_type value_type;
		typedef ptrdiff_t difference_type;
		typedef iterator_type* pointer;
		typedef iterator_type& reference;

		iterator_type* value;
	private:
		node_iterator(Iter* p) : value(p){}
		
	};
public:
	std::unique_ptr<T> left;
	std::unique_ptr<T> right;
	Node* root;//why not unique_ptr?
	T value;

	Node(const T& value_, std::unique_ptr<T> left_, std::unique_ptr<T> right_) : value(value_), left(left_), right(right_) {}
	//stuff..
	typedef node_iterator<Node> iterator;
	typedef node_iterator<const Node> const_iterator;

	iterator begin();
	iterator end();

	const_iterator cbegin() const;
	const_iterator cend() const;
};





int main(){
	std::list<int> a = {1,2,3};
	std::list<int>::iterator it = a.begin();
	//for coutonst:
	const std::list<int> ac = {1,2,3};
	std::list<int>::const_iterator cit = ac.begin();
	
	std::cout << *cit << "\n";

	//iterators invalidation:
	// like with pointers, when we change data that iterator points to -> its invalidation of iterators:

	std::vector<int> vec = {12};
	
	std::vector<int>::iterator vit = vec.begin();
	std::cout << *vit << "\n"; 
	for(int i = 0; i < 100; ++i)
		vec.push_back(i);
	std::cout << *vit;

//----------------------------
	std::cout << "\n\n\n";
	data data_array[1000];// = new int[1000];
	//data_array[0] = 1233;
	custom_data_array<data> data(data_array);
	auto own_it = data.begin();
	//miss_get_type ge_typo(own_it);
	std::cout << (*own_it).a;
	return 0;	
}