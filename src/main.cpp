#include <Arduino.h>
#include <Keypad.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C address 0x3F for a 16 chars and 2 line display

#define WIRE Wire

const int ROW_NUM = 4;
const int COLUMN_NUM = 3;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pin_rows[ROW_NUM] = {8,9,10,11};
byte pin_column[COLUMN_NUM] = {2, 3, 4};

Keypad keypad = Keypad( makeKeymap(keys), (byte*)pin_rows, (byte*)pin_column, ROW_NUM, COLUMN_NUM );

/* ------- */

LiquidCrystal_I2C lcd(0x3F, 16, 2);

/* ------- */

void setup() {

    lcd.init();
    lcd.backlight();
    lcd.write(55);

    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    WIRE.begin();
}
void findI2CAddress();
void loop() {
    // char key = keypad.getKey();
    digitalWrite(LED_BUILTIN, HIGH);
    // if (key) {
    //     Serial.println(key);
    // }
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);

    findI2CAddress();
}

void findI2CAddress(){
        byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    WIRE.beginTransmission(address);
    error = WIRE.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan

}