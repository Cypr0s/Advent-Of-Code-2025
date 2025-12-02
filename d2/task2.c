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


        for (long num = start_int; num < end_int + 1; num++) {
            sprintf(start, "%ld", num);
            int len = strlen(start);
            for (int window_size = 1; window_size <= len / 2; window_size++) { // window size
                if( len % window_size != 0) {
                    continue;
                }
                int flag = 1;
                for(int i = 1; i < len / window_size; i++) {
                    for(int j = 0; j < window_size; j++) {
                        if(start[j] != start[i*window_size + j]) {
                            flag = 0;
                            break;
                        }
                    }
                }
                if (flag) { 
                    printf("valid %s\n", start);
                    result+= num;
                    break;
                }
            }
        }
    }

    printf("%lld", result);

    fclose(f);
    free(start);
    return 0;
}
