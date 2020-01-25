#include <FastLED.h>

#define NUM_LEDS        256
#define DATA_PIN        3
#define LED_TYPE        WS2811
#define COLOR_ORDER     GRB

// Array containing the LEDs in the strip.
CRGB leds[NUM_LEDS];

// Returns the index in the array based on the coordinates of the LED.
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

// Clears the LED board.
int clearAll()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = 0;
    }
}

// Sets multiple LEDS to the x coordinates and y coordinates described.
int setLeds(int x[], int y[], int count, CRGB color)
{
    for (int i = 0; i < count; i++)
    {
        leds[getId(x[i], y[i])] = color;
    }
}

// Displays a new frame scrolled over based on the position argument.
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

// Displays a short pong animation on the LEDs.
void pong(int frameNo)
{
    int scFrame = frameNo % 32;
    frameNo = frameNo % 12;
    
    CRGB colors[8] {
        CRGB::DarkRed,
        CRGB::DarkRed,
        CRGB::DarkRed,
        CRGB::DarkRed,
        CRGB::DarkRed,
        CRGB::DarkRed,
        CRGB::DarkRed,
        CRGB::DarkRed
    };

    for (int i = 0; i <= scFrame; i++)
    {
        scroll(colors, 0, 0, i);
    }
    if (frameNo == 0)
    {
        int a[9] {1, 2, 3, 4, 1, 2, 3, 4, 3};
        int b[9] {0, 0, 0, 0, 7, 7, 7, 7, 4};
        setLeds(a, b, 9, CRGB::Blue);
    } else if (frameNo == 1)
    {
        int a[9] {1, 2, 3, 4, 1, 2, 3, 4, 4};
        int b[9] {0, 0, 0, 0, 7, 7, 7, 7, 5};
        setLeds(a, b, 9, CRGB::Blue);
    } else if (frameNo == 2)
    {
        int a[9] {2, 3, 4, 5, 2, 3, 4, 5, 5};
        int b[9] {0, 0, 0, 0, 7, 7, 7, 7, 6};
        setLeds(a, b, 9, CRGB::Blue);
    } else if (frameNo == 3)
    {
        int a[9] {3, 4, 5, 6, 3, 4, 5, 6, 6};
        int b[9] {0, 0, 0, 0, 7, 7, 7, 7, 5};
        setLeds(a, b, 9, CRGB::Blue);
    } else if (frameNo == 4)
    {
        int a[9] {4, 5, 6, 7, 4, 5, 6, 7, 7};
        int b[9] {0, 0, 0, 0, 7, 7, 7, 7, 4};
        setLeds(a, b, 9, CRGB::Blue);
    } else if (frameNo == 5)
    {
        int a[9] {5, 6, 7, 8, 5, 6, 7, 8, 9};
        int b[9] {0, 0, 0, 0, 7, 7, 7, 7, 2};
        setLeds(a, b, 9, CRGB::Blue);
    } else if (frameNo == 6)
    {
        int a[9] {6, 7, 8, 9, 6, 7, 8, 9, 10};
        int b[9] {0, 0, 0, 0, 7, 7, 7, 7, 1};
        setLeds(a, b, 9, CRGB::Blue);
    } else
    {
        int a[12] {7, 7, 7, 9,  11, 11, 11, 12, 12, 13, 13, 13};
        int b[12] {2, 3, 4, 3,   2,  3,  4,  2,  4,  2,  3,  4};
        setLeds(a, b, 12, CRGB::Blue);
    }
}

void setup()
{
    FastLED.addLeds<WS2811, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    Serial.begin(9600);
}

uint16_t frame {0};

void loop()
{
    clearAll();

    pong(frame);
    
    FastLED.show();
    delay(100);
    frame++;
}
