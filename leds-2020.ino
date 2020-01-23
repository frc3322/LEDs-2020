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

void scroll(CRGB colors[], int cutoffL, int cutoffR, int position)
{
    for (int i = 0; i < 8; i++)
    {
        if (!(cutoffL > 31 - position) && !(cutoffR > position))
        {
            leds[getId(31 - position, i)] = colors[i];
        }
    }
}

void setup()
{
    FastLED.addLeds<WS2811, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
     Serial.begin(9600);
}

void loop()
{
    clearAll();

    FastLED.show();
    delay(50);
}
