#include <Adafruit_NeoPixel.h>
#include "otaku_saber.h"

#define PIN_DO      6
#define PIN_SW_L    2
#define PIN_SW_C    1
#define PIN_SW_R    0
#define PIN_SW_A    4
#define PIN_SW_B    3
#define NUMPIXELS   1
#define TICK        200  // 制御ループの周期[ms]
#define LONG_PUSH_T 1000 // 長押し検知時間[ms]

ul time;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_DO, NEO_GRB + NEO_KHZ800);

uc switch_detection(){
  uc tmp = 0;

  tmp = !digitalRead(PIN_SW_B);
  tmp |= (!digitalRead(PIN_SW_A)) << 1;
  tmp |= (!digitalRead(PIN_SW_R)) << 2;
  tmp |= (!digitalRead(PIN_SW_C)) << 3;
  tmp |= (!digitalRead(PIN_SW_L)) << 4;

  return tmp;
}

uc switch_state(uc sw){
  static uc sw_old = 0;
  static bool flg_sw_block = false;  // 渡り押しフラグ
  static bool flg_sw_long = false;   // 長押しフラグ
  static ui sw_long_cnt = 0;         // 長押し検知カウンタ
  uc res = PUSH_NONE;

  // スイッチが離された
  if(sw==PUSH_NONE){
    // 前回何かしらのスイッチが押されていた
    if(sw_old!=PUSH_NONE){
      switch (sw_old)
      {
      case PUSH_L:
      case PUSH_C:
      case PUSH_R:
      case PUSH_A:
      case PUSH_B:
        if(!flg_sw_block){
          if(flg_sw_long){
            res = sw_old | PUSH_LONG;
          }
          else{
            res = sw_old;
          }
        }
        break;
      default:
        res = PUSH_NONE;
        break;
      }
      flg_sw_block = false;
      flg_sw_long = false;
      sw_long_cnt = 0;
    }
  }
  // スイッチが押されている
  else{
    if(sw_old!=PUSH_NONE){
      // 前回とスイッチの状態が違う(渡り押し)
      if(sw_old!=sw){
        flg_sw_block = true;
        sw_long_cnt = 0;
      }
      // 連続押し
      else{
        if(sw_long_cnt<LONG_PUSH_T){
          sw_long_cnt += TICK;
        }
        // 長押し確定
        else{
          flg_sw_long = true;
        }
      }
    }
  }

  sw_old = sw;

  return res;
}

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pinMode(PIN_SW_L, INPUT);
  pinMode(PIN_SW_C, INPUT);
  pinMode(PIN_SW_R, INPUT);
  pinMode(PIN_SW_A, INPUT);
  pinMode(PIN_SW_B, INPUT);
  Serial.begin(9600);      // 9600bpsでシリアルポートを開く
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  delay(10);
}

void loop() {
  static i color_r = 0;
  static enum MODE state = MODE_SLEEP;
  uc sw = 0;

  // 処理時間計測開始
  time = millis();

  Serial.print("state:");
  Serial.println(state);
  sw = switch_state(switch_detection());

  // 状態遷移
  switch (state)
  {
  case MODE_SLEEP:
    if(sw == (PUSH_C | PUSH_LONG)){
      state = MODE_NORMAL;
      pixels.setPixelColor(0, pixels.Color(0, 10, 0));
      pixels.show();
    }
    break;
  case MODE_NORMAL:
    break;
  
  default:
    break;
  }

  // 処理時間表示
  delay(TICK);
  Serial.println(millis()-time);

}
