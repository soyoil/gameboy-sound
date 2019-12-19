#include <gb/gb.h>

void main() {
  int freq[] = {0x60AU, 0x642U, 0x672U, 0x689U, 0x6B2U, 0x6D6U, 0x6F7U, 0x706U};
  int i;

  NR52_REG = 0x80U;                           // サウンド機能ON
  NR50_REG = 0x77U;                           // 左右ともに最大出力に設定
  NR51_REG = 0x11U;                           // ch1の出力ON

  NR10_REG = 0x00U;                           // スイープ設定なし
  NR11_REG = 0x83U;                           // デューティー比50%, 長さ設定なし
  NR12_REG = 0xF0U;                           // 音量最大, エンベロープ設定なし
  
  for(i = 0; i < 8; i++){
    NR13_REG = freq[i] % 0x100U;              // 周波数の下位8ビットを代入
    NR14_REG = 0x80U + (freq[i] / 0x100U);    // 周波数の上位4ビットとフラグ類を代入
    delay(1000);                              // 1秒待つ
  }

  NR52_REG = 0x00U;                           // サウンド機能off
}
