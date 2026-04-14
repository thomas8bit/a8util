

#include <stdio.h>

 

FILE  *Source;

 

int main(int argc, char **argv) {
    unsigned int a, b, i;
    unsigned int result;


    Source = stdin;
    while (!feof(Source)) {

        result = 0;
        for (i = 0; i < 4; i++) {
            a = fgetc(Source); /* index */
            b = fgetc(Source); /* alpha */

            a &= 0x03;
            a = a << (6 - 2*i);
            result |= a;
                
        }

        if (!feof(Source)) {
            putchar(result);
        }
    }
    a = 0x00;
    putchar(a);
    a = 0x87;
    putchar(a);
    a = 0x0f;
    putchar(a);
    a = 0x8;
    putchar(a);
    return 0;
}

