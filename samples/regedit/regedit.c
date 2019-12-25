#include<gb/gb.h>
#include<gb/drawing.h>

unsigned int regs[24];
unsigned int wave[16];
char **regname = {
    "NR10", "NR11", "NR12", "NR13", "NR14",
    "NR20", "NR21", "NR22", "NR23", "NR24",
    "NR30", "NR31", "NR32", "NR33", "NR34",
    "NR40", "NR41", "NR42", "NR43", "NR44",
    "NR50", "NR51", "NR52"
};

void init(){
    __REG *i;
    int j;
    NR52_REG = 0x80U;
    for(i = NR10_REG; i != NR52_REG; i++) i = 0x00U;
    for(j = 0; j < 23; j++) regs[j] = 0;
    regs[23] = 0x80U;
}

void main(){
    init();
    gotogxy(0, 0);
    gprintf("---SOUND EDITOR---");
}