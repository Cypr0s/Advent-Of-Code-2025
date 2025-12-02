#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// actually bad code xd
int main(int argc, char** argv) {
    long long result = 0;

    if (argc != 2) {
        return 1;
    }

    char* start = (char*) malloc(sizeof(char) * 64);
    if (start == NULL) {
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        free(start);
        return 1;
    }

    char c;
    int i = 0;

    c = fgetc(f);
    while (c != EOF) {
        while (c != '-' && c != EOF) {
            start[i++] = c;
            c = fgetc(f);
        }
        start[i] = '\0';
        i = 0;
        if (c == EOF) break;
        c = fgetc(f);
        char* b;
        long start_int = strtol(start, &b, 10);
        while (c != ',' && c != '\n' && c != EOF) {
            start[i++] = c;
            c = fgetc(f);
        }
        start[i] = '\0';
        i = 0;

        long end_int = strtol(start, &b, 10);

        if (c == ',') {
            c = fgetc(f);
        }


        for (long j = start_int; j < end_int + 1; j++) {
            sprintf(start, "%ld", j);
            int len = strlen(start);
            int flag = 1;
            if(len % 2 != 0) continue;
            len = len / 2;
            for (int k = 0; k < len; k++) {
                if (start[k] != start[k + len]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) result+= j;
        }
    }

    printf("%lld", result);

    fclose(f);
    free(start);
    return 0;
}
