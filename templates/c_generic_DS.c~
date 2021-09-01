#include <stdio.h>

// you can define macros-like function:
#define MAX(a, b) (a > b) ? a : b

void test_max(){
    int res = MAX(5,6);
}


//macro-concatenation:
//
#define SHOW(type, msg) show##type(msg)

struct DataHandler{
    int data = 222;
};

void show_data(char* msg){
   printf(msg);
}

int main(){
   SHOW(_data, "sss"); 
}
