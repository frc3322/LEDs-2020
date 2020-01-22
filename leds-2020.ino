#include <FastLED.h>

#define NUM_LEDS        256
#define DATA_PIN        3
#define LED_TYPE        WS2811
#define COLOR_ORDER     GRB

CRGB leds[NUM_LEDS];

int getId(int x, int y)
{
    int id = 0;

    id += 8 * x;
    if (x % 2 == 1)
    {
        id += 7 - y;
    } else {
        id += y;
    }

    return id;
}

int clearAll()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = 0;
    }
}

int setLeds(int x[], int y[], int count, CRGB color)
{
    for (int i = 0; i < count; i++)
    {
        leds[getId(x[i], y[i])] = color;
    }
}

void setup()
{
    FastLED.addLeds<WS2811, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    // Serial.begin(9600);
}

int redX[5] {0, 1, 2, 3, 4};
int redY[5] {0, 0, 0, 0, 0};
int greenX[5] {31, 30, 29, 28, 27};
int greenY[5] {7, 7, 7, 7, 7};

void loop()
{
    clearAll();
    
    setLeds(redX, redY, 5, CRGB::DarkRed);
    setLeds(greenX, greenY, 5, CRGB::DarkGreen);
    
    int tmpRedX[5];
    int tmpRedY[5];
    int tmpGreenX[5];
    int tmpGreenY[5];
    
    for (int i = 0; i < 4; i++)
    {
        tmpRedX[i] = redX[i + 1];
        tmpRedY[i] = redY[i + 1];
        tmpGreenX[i] = greenX[i + 1];
        tmpGreenY[i] = greenY[i + 1];
    }

    int trX = tmpRedX[3] + 1;
    int trY = tmpRedY[3];
    int tgX = tmpGreenX[3] - 1;
    int tgY = tmpGreenY[3];

    if (trX == 32)
    {
        trX = 0;
        trY += 1;
    }
    if (trY == 8)
    {
        trY = 0;
    }

    if (tgX == -1)
    {
        tgX = 31;
        tgY -= 1;
    }
    if (tgY == -1)
    {
        tgY = 7;
    }

    tmpRedX[4] = trX;
    tmpRedY[4] = trY;
    tmpGreenX[4] = tgX;
    tmpGreenY[4] = tgY;

    for (int i = 0; i < 5; i++)
    {
        redX[i] = tmpRedX[i];
        redY[i] = tmpRedY[i];
        greenX[i] = tmpGreenX[i];
        greenY[i] = tmpGreenY[i];
    }

    FastLED.show();
}
