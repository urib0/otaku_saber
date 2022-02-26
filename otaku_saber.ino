#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        6 // On Trinket or Gemma, suggest changing this to 1
#define PIN_SW_L   2
#define PIN_SW_C   1
#define PIN_SW_R   0
#define PIN_SW_A   4
#define PIN_SW_B   3
#define NUMPIXELS 1 // Popular NeoPixel ring size
#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels

static int flg_dim = 1;

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
  static int color_r = 0;
  int tmp = 0;
  tmp |= !digitalRead(PIN_SW_L);
  tmp |= !digitalRead(PIN_SW_C);
  tmp |= !digitalRead(PIN_SW_R);
  tmp |= !digitalRead(PIN_SW_A);
  tmp |= !digitalRead(PIN_SW_B);

  pixels.clear(); // Set all pixel colors to 'off'

  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, color_r, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop
  }

  if(flg_dim){
    color_r += 1;  
    if(color_r > 50){
      flg_dim = 0;
    }
  }else{
    color_r -= 1;  
    if(color_r < 1){
      flg_dim = 1;
    }
  }

  if(tmp){
    color_r = 0;
  }

  Serial.print("L:");
  Serial.print(digitalRead(PIN_SW_L));
  Serial.print(",C:");
  Serial.print(digitalRead(PIN_SW_C));
  Serial.print(",R:");
  Serial.print(digitalRead(PIN_SW_R));
  Serial.print(",A:");
  Serial.print(digitalRead(PIN_SW_A));
  Serial.print(",B:");
  Serial.println(digitalRead(PIN_SW_B));
}
