#include <stdio.h>

void func2() {
    printf("Inside func2\n");
}

void func1() {
    printf("Inside func1\n");
    func2();  
}

int main() {
    printf("Inside main\n");
    func1();  
    return 0;
}