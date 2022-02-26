#include <Adafruit_NeoPixel.h>

#define PIN        6 // On Trinket or Gemma, suggest changing this to 1
#define PIN_SW_L   2
#define PIN_SW_C   1
#define PIN_SW_R   0
#define PIN_SW_A   4
#define PIN_SW_B   3
#define NUMPIXELS 1 // Popular NeoPixel ring size
#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels

typedef signed char c;
typedef unsigned char uc;
typedef signed int i;
typedef unsigned int ui;
typedef signed long l;
typedef unsigned long ul;

ul time;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

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
}

void loop() {
  static i color_r = 0;

  // 処理時間計測開始
  time = millis();

  // 処理時間表示
  Serial.println(time);
  delay(1000);

}
