#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int zeroes = 0;
    int start = 50;
    char op_buff[6]; // expect 5 chars max ( not optimal but works for this)

    if(argc != 2) {
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if(f == NULL) {
        return 1;
    }

    while(fgets(op_buff, sizeof(op_buff), f) != NULL) {
        char op = op_buff[0];
        char *end;
        int x = strtol(op_buff + 1, &end, 10);
        if(!(*end == '\n' || *end == '\0')) {
            fclose(f);
            return 1;
        }
        if (op == 'L') {
            if(x >= start){
                if(start == 0) {
                    zeroes += (x - start) / 100;
                }
                else{
                    zeroes += (x - start) / 100 + 1;
                }
            }
            start = (start - x) % 100;
            if(start < 0) {
                start += 100;
            }
        }
        else {
            zeroes += (start + x) / 100;
            start = (start + x) % 100;
        }
    }
    printf("%d", zeroes);
    fclose(f);
    return 0;
}