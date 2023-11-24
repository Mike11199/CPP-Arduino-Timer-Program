
#include <TM1637Display.h>
#include <Keypad.h>
#include <U8glib.h>


#define CLK 3  // clock 
#define DIO 2  // digital audio


U8GLIB_SH1106_128X64  My_u8g_Panel(U8G_I2C_OPT_NONE); // I2C / TWI
const byte ROWS = 4;
const byte COLS = 4;
int seconds = 59;
int milliseconds = 99;
unsigned long previousMillis;
unsigned long currentMillis;
 
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
    draw_string_OLED("Button 1 Pressed.");
    delay(100);
    draw_string_OLED("60 Second timer...");
    seconds = 59;
    milliseconds = 99;
    previousMillis = millis();
  }
  if (result == '2'){
    draw_string_OLED("Button 2 Pressed");
    delay(100);
    draw_string_OLED("10 Second timer...");
    seconds = 9;
    milliseconds = 99;
    previousMillis = millis();
  }
  if (result == '3'){
    draw_string_OLED("Button 3 Pressed.");
    delay(100);
    draw_string_OLED("5 Second timer...");
    seconds = 4;
    milliseconds = 99;
    previousMillis = millis();
  }
  if (result == '4'){
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

    // put your setup code here, to run once:
  myDisplay.clear();
  delay(1000);
  displayOn = true;
  
  const uint8_t hi_1[] = {
    SEG_E,
    0,
    0,
    0,
  };

  const uint8_t hi_2[] = {
    SEG_B | SEG_C | SEG_F | SEG_E | SEG_G,
    SEG_E,
    0,
    0,
  };

    const uint8_t hi_3[] = {
    0,
    SEG_B | SEG_C | SEG_F | SEG_E | SEG_G,
    SEG_E,
    0,
  };

    const uint8_t hi_4[] = {
    0,
    0,
    SEG_B | SEG_C | SEG_F | SEG_E | SEG_G,
    SEG_E,
  };

    const uint8_t hi_5[] = {
    0,
    0,
    0,
    SEG_B | SEG_C | SEG_F | SEG_E | SEG_G,
  };


  if (displayOn == true) {

  // put your main code here, to run repeatedly:
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

    // Display the value on the 7-segment display
    myDisplay.showNumberDec(displayValue);

    // Check if 10 milliseconds have passed
    currentMillis = millis();
    if (currentMillis - previousMillis) {
        // Update milliseconds and seconds
        milliseconds -= ((currentMillis - previousMillis) / 10) ;
        if (milliseconds < 0) {
            milliseconds = 99;  // Reset milliseconds to 750 when it goes below 0
            seconds--;  // Decrement seconds when milliseconds roll over
        }
        previousMillis = currentMillis;  // Save the current time for the next iteration
    }


  }

  myDisplay.setSegments(all_off);

if (result != '4'){
  draw_string_OLED("Finished timer!!");
}

  }
  else{
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
