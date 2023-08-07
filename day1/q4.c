#include <stdio.h>

typedef struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
}PKT;

int main() {
    unsigned int originalNumber; 
    PKT packet; 
    printf("The input numbe= ");
    scanf("%u", &originalNumber);

    packet.ch1 = originalNumber & 0xFF;
    packet.ch2[0] = (originalNumber >> 8) & 0xFF;
    packet.ch2[1] = (originalNumber >> 16) & 0xFF;
    packet.ch3 = (originalNumber >> 24) & 0xFF;

    printf("Digit in byte 1= %u\n",packet.ch1);
    printf("Digit in byte 2= %u\n",packet.ch2[0]);
    printf("Digit in byte 3= %u\n",packet.ch2[1]);
    printf("Digit in byte 4= %u\n",packet.ch3);
    

    printf("Content of the structure:\n");
    printf("ch1: %u\n", packet.ch1);
    printf("ch2: %u %u\n", packet.ch2[0], packet.ch2[1]);
    printf("ch3: %u\n", packet.ch3);

    unsigned int reconstructedNumber =
        ((unsigned int)packet.ch3 << 24) +
        ((unsigned int)packet.ch2[1] << 16) +
        ((unsigned int)packet.ch2[0] << 8) +
        (unsigned int)packet.ch1;

    printf("Reconstructed Number: %u\n", reconstructedNumber);

}