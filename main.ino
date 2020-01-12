#include <FastLED.h>

#define NUM_LEDS        256
#define DATA_PIN        3
#define LED_TYPE        WS2811
#define COLOR_ORDER     GRB

class LedBoard
{
    public:
        CRGB board[];
        LedBoard(CRGB board[]);
        void setLed(int x, int y, int r, int g, int b)
        {
            // Get internal id for the LED
            int id = 0;
            id += 8 * x;
            if (x % 2 == 1)
            {
                id += 7 - y;
            } else {
                id += y;
            }

            // Set to correct color
            this->board[id] = 65536 * r + 256 * g + b;
        }
    private:
};

CRGB leds[NUM_LEDS];

void setup()
{
    FastLED.addLeds<WS2811, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
}

void showAndWait(int time)
{
    FastLED.show();
    delay(time);
}

// Get the actual id of the LED based on an x position and y position.
int getLedId(int x, int y)
{
    int led = 0;
    led += 8 * x;
    if (x % 2 == 1)
    {
        led += 7 - y;
    } else {
        led += y;
    }
    // led = 255 - led;
    return led;
}

long rgb(int red, int green, int blue)
{
    return 65536 * red + 256 * green + blue;
}

void loop()
{
    leds[getLedId(7, 7)] = rgb(255, 0, 0);
    showAndWait(750);
    leds[getLedId(7, 7)] = rgb(0, 255, 0);
    showAndWait(750);
    leds[getLedId(7, 7)] = rgb(0, 0, 255);
    showAndWait(750);
    leds[getLedId(7, 7)] = rgb(255, 255, 255);
    showAndWait(750);
    leds[getLedId(7, 7)] = rgb(0, 0, 0);
    showAndWait(750);
}
