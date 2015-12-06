/*
 * sort_by_ntz.c: 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <strings.h>

unsigned int ctz(unsigned int x)
{    
    return (x > 0) ? ffs(x) - 1 : 32;
}

unsigned int clz(unsigned int x)
{
    unsigned int y;
    int n = 32, c = 16;    
    do {
        y = x >> c;
        if (y != 0) {
            n = n - c;
            x = y;
        }
        c = c >> 1;
    } while (c != 0);
    n = n - (x >> 31);
    return n - x;
}

void fill_bits(int x, int nbits, char *bits)
{
    for (int i = 0; i < nbits; i++)
        bits[nbits - i - 1] = (x & (1 << i)) ? '1' : '0';
}

int main(int argc, char *argv[]) 
{
    int p = argc > 1 ? atoi(argv[1]) : 48;
    int *ranks = malloc(sizeof(*ranks) * p);
    for (int i = 0; i < p; i++) {
        ranks[i] = i;
    }        
    
    for (int i = 0; i < p - 1; i++) {
        int maxidx = i;
        for (int j = i + 1; j < p; j++) {
            if (ctz(ranks[j]) >= ctz(ranks[maxidx]))
                maxidx = j;
        }
        if (maxidx != i) {
            int temp = ranks[i];
            ranks[i] = ranks[maxidx];
            ranks[maxidx] = temp;
        }
    }
    
    int nbits = 32 - clz(p);
    char bits[nbits + 1];
    bits[nbits] = '\0';
    for (int i = 0; i < p; i++) {
        fill_bits(ranks[i], nbits, bits);
        printf("%-3d: %s\n", ranks[i], bits);
    }

    free(ranks);
    return 0;
}

