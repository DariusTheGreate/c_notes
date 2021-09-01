#include <iostream>

#define print(input) std::cout << input << "\n";

template<typename T, typename K>
struct pair
{
    T x;
    K y;
};

template<typename T>
using vector = pair<T, T>;


int main()
{
    vector<int> a;
    a.x = 3;
    a.y = 3.14;
    print(a.x);
    return 0;
}
