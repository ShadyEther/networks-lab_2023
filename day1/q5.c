#include <stdio.h>

int isLittleEndian()
{
    int num = 1;
    char *ptr = (char *)&num;
    return (*ptr == 1);
}

unsigned int swapEndianness(unsigned int number)
{
    return ((number >> 24) & 0xFF) |
           ((number >> 8) & 0xFF00) |
           ((number << 8) & 0xFF0000) |
           ((number << 24) & 0xFF000000);
}

int main()
{
    unsigned int number;

    printf("Enter a number: ");
    scanf("%u", &number);

    
    printf("\n------------------------------------------\n");
    printf("\nMemory Address\t->\tValue\n");
    printf("\n------------------------------------------\n");
    printf("%u\t\t  \t%u\n",&((char*)&number)[0],(int)(number & 0xFF));
    printf("%u\t\t  \t%u\n",&((char*)&number)[1],(int)((number >> 8) & 0xFF));
    printf("%u\t\t  \t%u\n",&((char*)&number)[2],(int)((number >> 16) & 0xFF));
    printf("%u\t\t  \t%u\n",&((char*)&number)[3],(int)((number >> 24) & 0xFF));
    

    if (isLittleEndian())
    {
        printf("\nThe LSB of the number is stored at the lowest memory address\nHence, the host machine is Little Endian.\n");
    }
    else
    {
        printf("\nThe LSB of the number is stored at the largest memory address\nHence, the host machine is Big Endian.\n\n");
    }
    printf("The Number is converted to Big Endian now\nMemory Representation of the Number...");
    unsigned int convertedNumber = swapEndianness(number);

    printf("\n------------------------------------------\n");
    printf("\nMemory Address\t->\tValue\n");
    printf("\n------------------------------------------\n");
    printf("%u\t\t  \t%u\n",&((char*)&convertedNumber)[0],(int)(convertedNumber & 0xFF));
    printf("%u\t\t  \t%u\n",&((char*)&convertedNumber)[1],(int)((convertedNumber >> 8) & 0xFF));
    printf("%u\t\t  \t%u\n",&((char*)&convertedNumber)[2],(int)((convertedNumber >> 16) & 0xFF));
    printf("%u\t\t  \t%u\n",&((char*)&convertedNumber)[3],(int)((convertedNumber >> 24) & 0xFF));
    
    printf("\n\nThe number after Endianness conversion: %d",convertedNumber);
    
}