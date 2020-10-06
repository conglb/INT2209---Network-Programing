#include <stdio.h>
#include "md5sum.c"

char str[100];
int main() {
    FILE * f = fopen("input", "r");
    FILE * fo = fopen("output", "w");

    while (!feof(f)) {
        fscanf(f, "%s", str);
        fprintf(fo, "%s", str);
    }

    FILE * f1 = fopen("input", "r");
    FILE * f2 = fopen("output", "r");

    sum(f1, "input");
    sum(f2, "output");
    
    
    return 0;
}