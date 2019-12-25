#include<gb/gb.h>
#include<gb/drawing.h>
#include<string.h>

unsigned int regs[24];
unsigned int wave[16];
char *regname[23] = {
    "NR10", "NR11", "NR12", "NR13", "NR14",
    "NR20", "NR21", "NR22", "NR23", "NR24",
    "NR30", "NR31", "NR32", "NR33", "NR34",
    "NR40", "NR41", "NR42", "NR43", "NR44",
    "NR50", "NR51", "NR52"
};

void init(){
    int i, j, digit, base;
    char bin[12] = "00000000";
    NR52_REG = 0x80U;
    for(i = 0xff10; i != 0xff26; i++) (*(__REG)i) = 0x00U;
    for(i = 0; i < 23; i++) regs[i] = 0;
    regs[23] = 0x80U;

    gotogxy(0, 0);
    gprintf("----SOUND EDITOR----");
    for(i = 0; i < 5; i++){
        gotogxy(2, 3 * i + 2);
        strcpy(bin, "00000000");
        j = 7;
        base = 1;
        digit = regs[i];
        while (digit > 0){
            if(digit % 2) bin[j] = '1';
            digit /= 2;
            j--;
        }
        if(regs[i] < 16){
            gprintf("%s 0%x", regname[i], regs[i]);
        }else{
            gprintf("%s %x", regname[i], regs[i]);
        }
        gotogxy(10, 3 * i + 2);
        gprintf("%s", bin);
    }
    gotogxy(1, 2);
    wrtchr(259);
    gotogxy(0, 17);
    gprintf("-SELECT: help---1/4-");
}

void play(){

}

void scroll(int direction){

}

void edit(int cursor){
    // upperArrow 257
}

void changePage(int direction){

}

void help(){

}

void main(){
    int isPlay = 0;
    int keyState = 0;
    int cursor = 0;
    int i;

    init();

    while(1){
        keyState = joypad();
        if(keyState & J_UP){
            scroll(0);
        }else if(keyState & J_DOWN){
            scroll(1);
        }else if(keyState & J_A){
            edit(cursor);
        }else if(keyState & J_RIGHT){
            changePage(0);
        }else if(keyState & J_LEFT){
            changePage(1);
        }else if(keyState & J_START){
            play();
        }
    }
}
