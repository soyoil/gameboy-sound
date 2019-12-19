#include <gb/gb.h>
#include <gb/drawing.h>
#include <stdio.h>

void main(){
  gotogxy(1, 1);
  NR52_REG = 0x80U; // サウンド機能ON
  NR50_REG = 0x33U; // 左右ともに中位の出力に設定
  NR51_REG = 0x11U; // ch1の出力ON

  NR10_REG = 0x00U; // スイープ設定なし
  NR11_REG = 0x83U; // デューティー比50%, 長さ設定なし
  NR12_REG = 0xF0U; // 音量最大, エンベロープ設定なし
  NR13_REG = 0x0AU; // 音の高さを0x60A(C5)に設定
  NR14_REG = 0x86U; // ch1キーオン, 長さカウンタ無効
  gprintf("flag on");
  
  while(1){
    if(joypad() & J_UP){
      NR51_REG = 0x11U;
      gotogxy(1, 1);
      gprintf("Flag on ");
      delay(200);
    }else if(joypad() & J_DOWN){
      NR51_REG = 0x00U;
      gotogxy(1, 1);
      gprintf("flag off");
      delay(200);
    }
  }
}
