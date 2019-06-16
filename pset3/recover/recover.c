#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

//this is our 512 block of bytes stored in a block
//address + (sizeof(datatype)*index)
BYTE *buffer = malloc(sizeof(BYTE)*512);

int main(int argc, char *argv[])
{
    char *infile = argv[2];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    printf("loaded")
    //pull bytes and check those bytes
    //if byte1 ==
    //if byte2 ==
    //if byte3 ==
    int x = 0xea;
    //this if statement tests your fourth byte in recover.
    if (x <= 0xef && x >= 0xe0)
    {
        printf("the statement is 0xe0 and 0xef\n")
    }
    else
    {
        printf("the statement is false\n")
    }
    //at end of file fread gives back feof
    //while fread()!=feof
}
