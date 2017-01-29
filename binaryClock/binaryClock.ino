#include <Charlieplex\Charlieplex.h>
#include <Timer\Timer.h>
#include <Time\Time.h>
#include <Time\TimeLib.h>


//Number of pins used 
#define CLOCK_PINS_NUMBER 5

byte clockPins[] = { 8, 9, 10, 11, 12 };

Charlieplex charlieplexObject = Charlieplex(clockPins, CLOCK_PINS_NUMBER);

charliePin led1 = { 0 , 1 };
charliePin led2 = { 1, 0 };
charliePin led3 = { 1 , 2 };
charliePin led4 = { 2 , 1 };
charliePin led5 = { 0 , 2 };
charliePin led6 = { 2 , 0 };

charliePin led7 = { 2, 3 };
charliePin led8 = { 3, 2 };
charliePin led9 = { 3 ,4 };
charliePin led10 = { 4 ,3 };
charliePin led11 = { 2 , 4 };
charliePin led12 = { 4 , 2 };

charliePin led13 = { 0, 4 };
charliePin led14 = { 4, 0 };
charliePin led15 = { 1, 4 };
charliePin led16 = { 4 ,1 };
charliePin led17 = { 0 ,3 };

charliePin leds[] = { led1, led2, led3, led4, led5, led6, led7, led8, led9, led10, led11, led12, led13, led14, led15, led16, led17 };
bool ledToLight[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

boolean singleOn = false;

Timer t;

const int buttonHourPin = 2;
const int buttonMinutesPin = 3;

int buttonHourState = 0;
int buttonMinutesState = 0;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);

    initClock();

    setTime(0, 0, 0, 0, 0, 0);

    t.every(50, takeReading);

    pinMode(buttonHourPin, INPUT);
    pinMode(buttonMinutesPin, INPUT);
}

void loop()
{
    int readHourState = digitalRead(buttonHourPin);
    int readMinutesState = digitalRead(buttonMinutesPin);

    if (buttonHourState != readHourState) {
        buttonHourState = readHourState;
        if (buttonHourState == HIGH)
        {
            adjustTime(3600);
            takeReading();
        }
    }

    if (buttonMinutesState != readMinutesState) {
        buttonMinutesState = readMinutesState;
        if (buttonMinutesState == HIGH)
        {
            adjustTime(60);
            takeReading();
        }
    }

    for (int i = 0; i < 17; ++i)
    {
        if (ledToLight[i]) {
            charlieplexObject.charlieWrite(leds[i], HIGH);
            delay(1);
            charlieplexObject.clear();
        }
        charlieplexObject.clear();
    }

    t.update();
}


/**
 * Check the operation of the LEDs.
 */
void initClock()
{
    for (int i = 0; i < 17; ++i)
    {
        charlieplexObject.charlieWrite(leds[i], HIGH);
        delay(100);
        charlieplexObject.clear();
    }
}

void takeReading()
{
    time_t t = now();
    Serial.print("Time : ");
    Serial.print(hour(t));
    Serial.print(":");
    Serial.print(minute(t));
    Serial.print(":");

    int seconds = second(t);
    int minutes = minute(t);
    int hours = hour(t);

    Serial.println(second(t));

    Serial.print(bitRead(seconds, 5));
    Serial.print(bitRead(seconds, 4));
    Serial.print(bitRead(seconds, 3));
    Serial.print(bitRead(seconds, 2));
    Serial.print(bitRead(seconds, 1));
    Serial.println(bitRead(seconds, 0));

    for (int i = 0; i < 6; ++i)
    {
        if (bitRead(seconds, i) == 1)
        {
            ledToLight[i] = true;
        }
        else {
            ledToLight[i] = false;
        }
    }

    for (int i = 0; i <6; ++i)
    {
        if (bitRead(minutes, i) == 1) {
            ledToLight[i + 6] = true;
        }
        else {
            ledToLight[i + 6] = false;
        }
    }

    for (int i = 0; i < 5; ++i)
    {
        if (bitRead(hours, i) == 1) {
            ledToLight[i + 6 + 6] = true;
        }
        else {
            ledToLight[i + 6 + 6] = false;
        }
    }

}
