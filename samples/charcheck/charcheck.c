#include<gb/gb.h>
#include<stdio.h>

int main(){
  int i = 33;
  char ii = 33;
  printf("%d %c\n", i, ii);
  while(1){
    if(joypad()){
      i++;
      ii++;
      printf("%d %c\n", i, ii);
      delay(50);
    }
  }
}
