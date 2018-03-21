#include <iostream>
#include "main.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    test(13,12);
    return 0;
}

void test(int a, int b ){
    if ( a > b){
        std::cout<<"It's bigger.";
    }
}