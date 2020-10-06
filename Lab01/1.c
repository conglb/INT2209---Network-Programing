#include <stdio.h>

char str[1000];

int main() {
    FILE * f = fopen("input", "r");
    fscanf(f, "%s", str);
    //printf("%s", str);

    int i = 0, character_num = 0, number_num = 0, symbol_num = 0;
    while (str[i] != '\0')  {
        if (str[i] >='a' && str[i] <='z') character_num++; else
        if (str[i] >='0' && str[i] <= '9') number_num++; else symbol_num++;
        i++;
    }

    printf("The number of charactors: %d \n", character_num);
    printf("The number of numbers: %d \n", number_num);
    printf("The number of symbol: %d \n", symbol_num);
    return 0;
}