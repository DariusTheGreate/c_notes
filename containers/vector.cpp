#include <iostream>
#include <vector>
#include <algorithm>

static int memory_uses = 0;

struct NotTrivialType{
	int a = 3;
	int b = 2;
	int c = 1;
	char id = '0';	
	NotTrivialType(char id_in) noexcept : id(id_in){}
	friend std::ostream& operator <<(std::ostream& os, NotTrivialType nt) noexcept{
		os << nt.id << " ";
		return os;
	}

};

template<typename T>
class own_allocator{
public:
	T* allocate(size_t n);
	void deallocate(T* ptr){
		memory_uses--;
		::operator delete(ptr);
	}

	template<typename... Args>
	void construct(T* ptr, Args&... args);
	void destroy(T* ptr){
		ptr->~T();
	}
};

template<class T>
T* own_allocator<T>::allocate(size_t n){
	memory_uses++;
	return reinterpret_cast<T*>(::operator new(n * sizeof(T)));
}

template<class T>
template<typename... Args>
void own_allocator<T>::construct(T* ptr, Args&... args){
	new (ptr) T(args...);
}

template<class T, class Alloc = own_allocator<T>>
struct vec{

class iterator {
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value = T;
		using pointer = T*;
		using reference = T&;
	
		iterator(pointer ptr_in) : ptr(ptr_in) {}
		
		reference operator *() noexcept {
			return *ptr;
		}

		pointer operator ->() noexcept {
			return ptr;
		}

		iterator& operator ++() noexcept {
			ptr++;
			return *this;
		}

		iterator operator ++(int) noexcept {
			iterator prev_version = *this;
			++(*this);
			return prev_version;
		}

		friend bool operator !=(const iterator& a, const iterator& b) noexcept {
			return a.ptr != b.ptr;
		}

		friend bool operator ==(const iterator& a, const iterator& b) noexcept {
			return a.ptr == b.ptr;
		}

	private:
		pointer ptr = nullptr;

};

public:
	vec(size_t size_in) noexcept : size(0), cap(size_in*2) {
		data = reinterpret_cast<T*>(new char[cap * sizeof(T)]);
	}

	void reserve(int volume) noexcept {
		/*
		//NOT USING ALLOCATOR
		if(volume <= cap) return;
		//exception handling of std bad alloc
		T* new_data_place = reinterpret_cast<T*>(new char[volume * sizeof(T)]);// in case T is hard type, that has slow constructor
		//exception handling in case of bad constructing -> thencatch and delete all that was created and throw again
		for(size_t i = 0; i < size; ++i){
			new (new_data_place + i) T(data[i]);//requires copy constructor
		}
		//if exception occurse in destructor - standart ignores it
		for(size_t i = 0; i < size; ++i){
			data[i].~T();
		}

		delete [] reinterpret_cast<char*>(data);
		data = new_data_place;
		new_data_place = nullptr;
		cap = volume;
		*/

		//USING ALLOCATOR

		if(volume <= cap)
			return;
		T* new_data = alloc.allocate(volume);
		for(size_t i = 0; i < size; ++i){
			alloc.construct(new_data + i, data[i]);
		}

		for(size_t i = 0; i < size; ++i){
			alloc.destroy(data + i);
		}

		alloc.deallocate(data);

		data = new_data;
		new_data = nullptr;//for good
		cap = volume;


	}

	void push_back(T&& val) noexcept {
		if(size == cap)
			reserve(2 * size);
		new (data + size) T(val);
		size++;
 	}

 	iterator begin() noexcept {
 		return iterator(&data[0]);
 	}


 	iterator end() noexcept {
 		return iterator(&data[size]);
 	}

 	T& operator[](int id) noexcept {
 		return data[id];
 	}

 	size_t get_size() const noexcept { return size; }
 	
 	size_t get_cap() const noexcept { return cap; }

 	~vec() noexcept{
 		for(size_t i = 0; i < size; ++i)
 			data[i].~T();
 		delete [] reinterpret_cast<char*>(data);
 	}

private:
	Alloc alloc;
	T* data;
	size_t size;
	size_t cap;
};

typedef std::function<void (NotTrivialType&)> TTargetFunc;

template<class ForwardIterator>
inline void process_data(ForwardIterator first, ForwardIterator end, TTargetFunc functor){
	for(; first != end; ++first)
		functor(*first);

}

inline void set_to_val(NotTrivialType& t){
	t.id = 's';
}

void test_vec(){
	NotTrivialType a('d');
	vec<NotTrivialType> numbers(1);	
	numbers.push_back(std::move(a));
	numbers.push_back(std::move(a));
	numbers.push_back(std::move(a));
	numbers.push_back(std::move(a));

	for(auto i: numbers)
		std::cout << i;
	
	std::cout << "\n";
	
	std::fill(numbers.begin(), numbers.end(), 120);
	process_data(numbers.begin(), numbers.end(), set_to_val);
	
	for(auto i: numbers)
		std::cout << i;
}

struct buffer_new{};
buffer_new buff_new;	

void* operator new(size_t n, buffer_new){
	std::cout << "my alloc\n";
	return malloc(n*1024);
}


void operator delete(void* ptr){
	std::cout << "my alloc\n";
	free(ptr);
}

int main(){
	//int* test_own_new = new(buff_new) int(5);
	//operator delete(test_own_new, buffer_new);
	//test_placement_new(3.8, 3);
	//std::vector<bool> v(10, false);
	test_vec();
	//std::cout << sizeof(v) << " " << sizeof(bool);
	std::cout << "\n\n\napplication work ends well, memory_leaks: " << memory_uses << "\n";
	return 0;
}

