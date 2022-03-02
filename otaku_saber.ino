#include <Adafruit_NeoPixel.h>
#include "otaku_saber.h"

#define PIN_DO     6
#define PIN_SW_L   2
#define PIN_SW_C   1
#define PIN_SW_R   0
#define PIN_SW_A   4
#define PIN_SW_B   3
#define NUMPIXELS  1
#define TICK      100 // 制御ループの周期

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
          res = sw_old;
        }
        break;
      default:
        res = PUSH_NONE;
        break;
      }
      flg_sw_block = false;
    }
  }
  // スイッチが押されている
  else{
    // 前回とスイッチの状態が違う(渡り押し)
    if((sw_old!=PUSH_NONE)&&(sw_old!=sw)){
      flg_sw_block = true;
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
  pixels.setPixelColor(0, pixels.Color(0, 10, 0));
  pixels.show();
}

void loop() {
  static i color_r = 0;
  uc sw = 0;

  // 処理時間計測開始
  time = millis();

  sw = switch_detection();
  Serial.println(switch_state(sw));

  // 処理時間表示
  delay(TICK);
  Serial.println(millis()-time);

}
