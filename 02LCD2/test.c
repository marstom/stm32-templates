#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint8_t getbit(uint8_t byte){
  for (int8_t bit_number = 8; bit_number >= 0; bit_number--){
    if(byte & (1 << bit_number)){
      printf("1");
    }else{
      printf("0");
    }
  }
}

int main(int argc, char const *argv[])
{
    uint8_t liczba = 0b00000101;

    printf("L %d\n", liczba);

    getbit(liczba);
    printf("\n");
    return 0;
}
