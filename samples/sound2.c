#include <gb/gb.h>

void main() {
  int freq[] = {0x60AU, 0x642U, 0x672U, 0x689U, 0x6B2U, 0x6D6U, 0x6F7U, 0x706U};
  int i;

  NR52_REG = 0x80U;
  NR50_REG = 0x77U;
  NR51_REG = 0xFFU;

  NR10_REG = 0x00U;
  NR11_REG = 0x83U;
  NR12_REG = 0xF0U;
  
  for(i = 0; i < 8; i++){
    NR13_REG = freq[i] % 0x100U;
    NR14_REG = 0x80U + (freq[i] / 0x100U);
    delay(1000);
  }

  NR52_REG = 0x00U;
}
