#include <FastLED.h>

#define NUM_LEDS        256
#define DATA_PIN        3
#define LED_TYPE        WS2811
#define COLOR_ORDER     GRB

class LedBoard
{
    public:
        CRGB board[NUM_LEDS];
        

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

        void clearLed(int x, int y)
        {
            this->setLed(x, y, 0, 0, 0);
        }

        void clearAll()
        {
            for (int i = 0; i < NUM_LEDS; i++)
            {
                this->board[i] = 0;
            }
        }
};

CRGB leds[NUM_LEDS];
LedBoard Ex32;

void setup()
{
    for (int i = 0; i < 256; i++) {
        Ex32.board[i] = leds[i];
    }
    FastLED.addLeds<WS2811, DATA_PIN, COLOR_ORDER>(Ex32.board, NUM_LEDS);
}

int x = 0;
int y = 0;
boolean drawing = true;

void loop()
{
    if (drawing)
    {
        Ex32.setLed(x, y, 100, 0, 0);
    } else {
        Ex32.clearLed(x, y);
    }
    x++;
    if (x > 31)
    {
        x = 0;
        y++;
    }
    if (y > 7)
    {
        y = 0;
        drawing = !drawing;
    }
    FastLED.show();
    delay(20);
}
