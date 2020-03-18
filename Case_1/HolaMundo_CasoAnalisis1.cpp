#include <stdio.h>
#include "Utils.cpp"

using namespace utils;
#define max(a,b) a > b ? a : b

int main() {

    int a, b;

    #ifndef THEMESSAGE
        printf(THEMESSAGE);
    #else
        saludo();
    #endif

    a = 24;
    b = 54;

    printf("El mayor entre a: %d y b: %d es -> %d ",a,b,(max(a, b)));

    return 0;
}
