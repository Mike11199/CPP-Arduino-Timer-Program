
#include <TM1637Display.h>
#include <Keypad.h>
#include <U8glib.h>
#include <Key.h>

#define CLK 3  // clock 
#define DIO 2  // digital audio


U8GLIB_SH1106_128X64  My_u8g_Panel(U8G_I2C_OPT_NONE); // I2C / TWI
const byte ROWS = 4;
const byte COLS = 4;
int seconds = 59;
int milliseconds = 99;
unsigned long previousMillis;
unsigned long currentMillis;

int buzzer = 4;             // pin 4 drives the buzzer
int tones[ROWS][COLS] = {   // a frequency tone for each button
    {31, 93, 147, 208},
    {247, 311, 370, 440},
    {523, 587, 698, 880},
    {1397, 2637, 3729, 4978}
};

 
char buttons[ROWS][COLS] = {
  {'1', '2', '3', 'A'},  // 1st row
  {'4', '5', '6', 'B'},  // 2nd row
  {'7', '8', '9', 'C'},  // 3rd row
  {'*', '0', '#', 'D'}   // 4th row
};

byte colPins[ROWS] = {10, 11, 12, 13};
byte rowPins[COLS] = {9, 8, 7, 6};

Keypad myAwesomePad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS);

TM1637Display myDisplay = TM1637Display(CLK, DIO);

//array to turn all segments on
const uint8_t all_on[] = {0xff, 0xff, 0xff, 0xff};  // 0xff is hex all 1s

//array to turn all segments on
const uint8_t all_off[] = {0x00, 0x00, 0x00, 0x00};  // 0xff is hex all 1s

bool displayOn = true;


char KeypadCheck() {

  char result = myAwesomePad.getKey();
 
  if (result == '1'){
    tone(buzzer, 350, 250);  // ... and play the tone frequency 200hz for a half second 500 ms
    draw_string_OLED("Button 1 Pressed.");
    delay(100);
    draw_string_OLED("60 Second timer...");
    seconds = 59;
    milliseconds = 99;
    previousMillis = millis();
  }
  if (result == '2'){
    tone(buzzer, 350, 250);  // ... and play the tone frequency 200hz for a half second 500 ms
    draw_string_OLED("Button 2 Pressed");
    delay(100);
    draw_string_OLED("10 Second timer...");
    seconds = 9;
    milliseconds = 99;
    previousMillis = millis();
  }
  if (result == '3'){
    tone(buzzer, 350, 250);  // ... and play the tone frequency 200hz for a half second 500 ms
    draw_string_OLED("Button 3 Pressed.");
    delay(100);
    draw_string_OLED("5 Second timer...");
    seconds = 4;
    milliseconds = 99;
    previousMillis = millis();
  }
  if (result == '4'){
    tone(buzzer, 350, 250);  // ... and play the tone frequency 200hz for a half second 500 ms
    draw_string_OLED("Button 4 Pressed.");
    delay(100);
    draw_string_OLED("Welcome to my");
    delay(100);
    draw_string_OLED("Arduino program.");
    delay(100);
    draw_string_OLED("programmed in");
    delay(100);
    draw_string_OLED("C++ by ");
    delay(100);
    draw_string_OLED("Michael Iwanek");
    delay(100);
    seconds = 0;
    milliseconds = 0;
    previousMillis = millis();
  }
    if (result == '5'){
      tone(buzzer, 350, 250);  // ... and play the tone frequency 200hz for a half second 500 ms
      draw_string_OLED("Button 5 Pressed.");
      delay(100);
      draw_string_OLED("Generating prime");
      delay(100);
      draw_string_OLED("numbers from ");
      delay(100);
      draw_string_OLED("1 to 9999.");
      delay(100);
      draw_string_OLED("Press 1");
      delay(100);
      draw_string_OLED("to exit.");
      delay(200);

      int PrimeInteger = 0;

      while (PrimeInteger < 9999) {
        if (isPrime(PrimeInteger)){
          myDisplay.showNumberDec(PrimeInteger);
          delay(500);
          char result2 = myAwesomePad.getKey();
          if (result2 == '1'){
            break;
          }

        }
        PrimeInteger ++;
      }

      seconds = 0;
      milliseconds = 0;
      previousMillis = millis();
  }
  if (result == '6'){
    tone(buzzer, 350, 250);  // ... and play the tone frequency 200hz for a half second 500 ms
      draw_string_OLED("Button 6 Pressed.");
      delay(100);
      draw_string_OLED("Generating powers");
      delay(100);
      draw_string_OLED("of 2.");
      delay(100);
      draw_string_OLED("Press 1");
      delay(100);
      draw_string_OLED("to exit.");
      delay(200);

  int Power = 0;
  int Raise = 1;  // 2^0 = 1

  while (Raise < 9999) {
    delay(500);
    Power++;
    Raise = 1 << Power;  // Use bit-shifting for powers of 2
    myDisplay.showNumberDec(Raise);

    char result2 = myAwesomePad.getKey();
    if (result2 == '1') {
      break;
    }
  }

      seconds = 0;
      milliseconds = 0;
      previousMillis = millis();
  }

  return result;

}



void setup() {
  Serial.begin(9600);
  My_u8g_Panel.setColorIndex(1);
}

void loop() {
  
  myDisplay.clear();
  delay(1000);
  displayOn = true;

  tone(buzzer, 50, 500);  // ... and play the tone frequency 50hz for a half second 500 ms
  delay(500);
  noTone(buzzer);

  tone(buzzer, 150, 500);  // ... and play the tone frequency 150hz for a half second 500 ms
  delay(500);
  noTone(buzzer);

  tone(buzzer, 200, 500);  // ... and play the tone frequency 200hz for a half second 500 ms
  delay(500);
  noTone(buzzer);

  if (displayOn == true) {
    myDisplay.setBrightness(7);
    myDisplay.setSegments(all_on);
    delay(10);
    myDisplay.clear();

    milliseconds = 99;
    int displayValue;
    seconds = 59;
    char result = '4';

    draw_string_OLED("Starting timer...");
    delay(100);
    draw_string_OLED("for 60 seconds.");

    previousMillis = millis();

    while (seconds >= 0) {
      
      char result = KeypadCheck();
      displayValue = seconds * 100 + milliseconds;
      myDisplay.showNumberDec(displayValue);
      
      currentMillis = millis();
      
      

      if (currentMillis - previousMillis) {          
          milliseconds -= ((currentMillis - previousMillis) / 10) ;
          if (milliseconds < 0) {
              milliseconds = 99;  
              seconds--;  
              tone(buzzer, 140, 300);  // ... and play the tone frequency 140hz for a half second 500 ms

              if ( seconds < 5){
                tone(buzzer, 350, 250);  // ... and play the tone frequency 200hz for a half second 500 ms
                
                tone(buzzer, 450, 250);  // ... and play the tone frequency 200hz for a half second 500 ms
                
                tone(buzzer, 450, 250);  // ... and play the tone frequency 200hz for a half second 500 ms
                
                tone(buzzer, 450, 250);  // ... and play the tone frequency 200hz for a half second 500 ms
              }
          }
          previousMillis = currentMillis;  // Save the current time for the next iteration
      }
  }

  draw_string_OLED("Finished timer!!");
  delay(500);

  tone(buzzer, 650, 500);  // ... and play the tone frequency 650hz for a half second 500 ms
  delay(500);
  noTone(buzzer);

  tone(buzzer, 450, 500);  // ... and play the tone frequency 450hz for a half second 500 ms
  delay(500);
  noTone(buzzer);

  tone(buzzer, 300, 500);  // ... and play the tone frequency 300hz for a half second 500 ms
  delay(500);
  noTone(buzzer);

  myDisplay.setSegments(all_off);
  }
}

// OLED Display output
void draw_string_OLED(const char* text) {
  My_u8g_Panel.setFont(u8g_font_unifont);  
  My_u8g_Panel.firstPage();  
  do {
    My_u8g_Panel.drawStr(0, 22, text);  
  } while( My_u8g_Panel.nextPage() );    
  delay(300);
  My_u8g_Panel.firstPage();  
  clear_screen();
}

// OLED Display output
void clear_screen(void) {  
    do {
    My_u8g_Panel.drawStr( 0, 22, "          ");  
  } while( My_u8g_Panel.nextPage() );    
}

bool isPrime(unsigned long num) {
    if (num <= 1) return false;

    for (unsigned long i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}
