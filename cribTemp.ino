// include the library code:
#include <LiquidCrystal.h>
#include <Adafruit_MLX90614.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const int speaker = 6;
const int echo = 9;
const int trig = 10;

float duration, distance, temperature;

byte degree_symbol[8] =
{

  0b00111,

  0b00101,

  0b00111,

  0b00000,

  0b00000,

  0b00000,

  0b00000,

  0b00000

};

void setup()
{
    mlx.begin();
 
    pinMode(speaker, OUTPUT);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    lcd.begin(16,2);

    lcd.createChar(1, degree_symbol);

    lcd.setCursor(0,0);

    lcd.print(" Termometro ");

    lcd.setCursor(0,1);

    lcd.print(" Digital ");

    delay(4000);

    lcd.clear();

}

void loop()
{
  // Clears the trigPin
    digitalWrite(10, LOW);
    delayMicroseconds(2);
  
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(10, HIGH);
    delayMicroseconds(10);
    digitalWrite(10, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(9, HIGH, 20000);
    // Calculating the distance
    distance= duration*0.0343/2;
    temperature=mlx.readObjectTempC()+8;

    if (distance > 2.5 && distance <= 10)
    {

        delay(10);

        lcd.clear();

        lcd.setCursor(0,0);
      
        if (temperature < 35)
        {

          lcd.print("Temperatura Baja");

            lcd.setCursor(4,1);

            lcd.print(temperature);

            lcd.write(1);

            lcd.print("C");

            tone(speaker, 1000);
            delay(500);
            noTone(speaker);
            delay(300);
            tone(speaker, 1000);
            delay(500);
            noTone(speaker);
        }
      
        else if (temperature > 38)
        {

            lcd.print("Temperatura Alta");

            lcd.setCursor(4,1);

            lcd.print(temperature);

            lcd.write(1);

            lcd.print("C");

            tone(speaker, 1000);
            delay(500);
            noTone(speaker);
            delay(300);
            tone(speaker, 1000);
            delay(500);
            noTone(speaker);
            delay(300);
            tone(speaker, 1000);
            delay(500);
            noTone(speaker);
          }

        else
        {
            lcd.print("Temperatura Normal");

            lcd.setCursor(4,1);

            lcd.print(temperature);

            lcd.write(1);

            lcd.print("C");
            tone(speaker, 1000);
            delay(200);
            noTone(speaker);
        }
      
        delay(2000);
      
        lcd.clear();
    }
  

}
