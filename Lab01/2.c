#include <stdio.h>

char filename[10], last_line[200];

int main() {
    scanf("%s", filename);
    FILE* f = fopen(filename, "w");
    
    scanf("%s", last_line);
    while (last_line[0] != 'E' || last_line[0] == '\n') {
        fputs(last_line, f);
        fputs("\n", f);
        scanf("%s", last_line);
        //printf("%s", last_line);
    }
    return 0;
}