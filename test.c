#include "rot.h"
#include <stdio.h>

void print_m3x3(M3x3 m){
    printf("m3x3:\n");
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("\t%f", m.m[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    M3x3 m1 = { .m = {
        { 1,2,3 },
        { 4,5,6 },
        { 7,8,9 }
    }};
    M3x3 m2 = { .m = {
        { 1,2,3 },
        { 4,5,6 },
        { 7,8,9 }
    }};
    M3x3 m3 = mul_3x3_3x3(m1,m2);
    print_m3x3(m3);
    return 0;
}
