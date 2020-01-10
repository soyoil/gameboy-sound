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
int nowPage = 0;
int cursor = 0;

void help();

void display(int channel){
  int i, j, digit, base;
  char bin[12] = "00000000";
  gotogxy(0, 0);
  gprintf("----SOUND EDITOR----");
  for(i = 0; i < 5; i++){
    gotogxy(1, 3 * i + 2);
    strcpy(bin, "00000000");
    j = 7;
    base = 1;
    digit = regs[i + 5 * channel];
    while (digit > 0){
      if(digit % 2) bin[j] = '1';
      digit /= 2;
      j--;
    }
    if(channel == 4 && i > 2){
      gprintf("                   ");
      gotogxy(0, 3 * i + 3);
      gprintf("                   ");
      continue;
    }else if(regs[i] < 16){
      gprintf(" %s 0%x ", regname[i + 5 * channel], regs[i + 5 * channel]);
    }else{
      gprintf(" %s %x ", regname[i + 5 * channel], regs[i + 5 * channel]);
    }
    gotogxy(10, 3 * i + 2);
    gprintf("%s", bin);
    gotogxy(0, 3 * i + 3);
    gprintf("                   ");
  }
  gotogxy(1, 3 * cursor + 2);
  wrtchr(259);
  gotogxy(0, 17);
  gprintf("-SELECT: help---%d/5-", nowPage+1);
}

void init(){
  int i;
  NR52_REG = 0x80U;
  for(i = 0xff10; i != 0xff26; i++) (*(__REG)i) = 0x00U;
  for(i = 0; i < 23; i++) regs[i] = 0;
  regs[23] = 0x80U;
  display(0);
}

void play(){
  gotogxy(0, 17);
  gprintf("-PLAYING--------1/5-");
}

void scroll(int direction){
  int limit = nowPage == 4 ? 2 : 4;
  if(!direction && cursor != 0){
    gotogxy(1, 3 * cursor + 2);
    wrtchr(' ');
    gotogxy(1, 3 * cursor - 1);
    wrtchr(259);
    cursor--;
  }else if(direction && cursor != limit){
    gotogxy(1, 3 * cursor + 2);
    wrtchr(' ');
    gotogxy(1, 3 * cursor + 5);
    wrtchr(259);
    cursor++;
  }
}

void edit(){
  int keyState = 0;
  int cursorPos = 7;
  gotogxy(1, 3 * cursor + 2);
  wrtchr(' ');
  gotogxy(7, 3 * cursor + 3);
  wrtchr(257);
  while(1){
    keyState = joypad();
    if(keyState & J_B){
      break;
    }else if((keyState & J_RIGHT) && cursorPos < 17){
      if(cursorPos == 8) cursorPos++;
      gotogxy(++cursorPos-2, 3 * cursor + 3);
      gprintf("  %c", 257);
    }else if((keyState & J_LEFT) && cursorPos > 7){
      if(cursorPos == 10) cursorPos--;
      gotogxy(--cursorPos, 3 * cursor + 3);
      gprintf("%c  ", 257); 
    }else if(keyState & J_UP){
      // inc
    }else if(keyState & J_DOWN){
      //dec
    }else if(keyState & J_SELECT){
      help();
      gotogxy(1, 3 * cursor + 2);
      wrtchr(' ');
      gotogxy(cursorPos, 3 * cursor + 3);
      wrtchr(257);
    }

    delay(200);
  }
  gotogxy(0, 3 * cursor + 3);
  gprintf("                   ");
  gotogxy(1, 3 * cursor + 2);
  wrtchr(259);
  // upperArrow 257
}

void changePage(int direction){
  if(direction && nowPage != 0){
    nowPage--;
    display(nowPage);
  }else if(!direction && nowPage != 4){
    nowPage++;
    if(nowPage == 4 && cursor > 2) cursor = 2;
    display(nowPage);
  }
}

void help(){
  int i;
  char *keys[5] = {
    "Up,Down key:       ",
    "Left,Right key:    ",
    "A button:          ",
    "B button:          ",
    "START button:      "
    };
  char *insts[5] = {
    "select register  ",
    "change channels  ",
    "edit value       ",
    "back             ",
    "play/stop        "
  };
  gotogxy(0, 0);
  gprintf("-----HOW TO USE-----");
  for(i = 0; i < 5; i++){
    gotogxy(1, 3 * i + 2);
    gprintf(keys[i]);
    gotogxy(3, 3 * i + 3);
    gprintf(insts[i]);
  }
  gotogxy(9, 17);
  gprintf("back------");
  delay(100);
  while(!(joypad() & (J_SELECT | J_B))) {}
  display(nowPage);
}

void main(){
  int isPlay = 0;
  int keyState = 0;
  //int i;

  init();

  while(1){
    keyState = joypad();
    if(keyState & J_UP){
      scroll(0);
    }else if(keyState & J_DOWN){
      scroll(1);
    }else if(keyState & J_A){
      edit();
    }else if(keyState & J_RIGHT){
      changePage(0);
    }else if(keyState & J_LEFT){
      changePage(1);
    }else if(keyState & J_START){
      play();
    }else if(keyState & J_SELECT){
      help();
    }
    if(keyState) delay(200);
  }
}
