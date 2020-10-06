#include <stdio.h>

char str[1000];

int main() {
    FILE * fr = fopen("input", "r");
    FILE * fw = fopen("output", "w");
    fscanf(fr, "%s", str);
    while (str[0] >='a')  {
        fprintf(fw, "%s", str);
        fscanf(fr, "%s", str);
    }

    return 0;
}