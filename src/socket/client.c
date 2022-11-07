#include <stdio.h>
#include <math.h>

int main(void){
    for (int i = 0; i <= 365; i++){
        printf("(%f, %f)", cos(i * (M_PI / 180)), sin(i * (M_PI / 180)));
    }

    return 0;
}