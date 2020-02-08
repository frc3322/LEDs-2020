#include <FastLED.h>
#include <Wire.h>

#define NUM_LEDS        256
#define DATA_PIN        3
#define LED_TYPE        WS2811
#define COLOR_ORDER     GRB

#define LASER_RED       0xAA0000
#define LASER_DARKRED   0x701A00
#define LASER_POWERUP   0x882800
#define LASER_POWERED1  0x9A8600
#define LASER_POWERED2  0x96A055
#define LASER_POWERED3  0xD8D085

enum Animations
{
    SHOOT,
    TARGET,
    IDLE
};

Animations currAnim = Animations::IDLE;

CRGB alliance = CRGB::Green;

// Array containing the LEDs in the strip.
CRGB leds[NUM_LEDS];

// Returns the index in the array based on the coordinates of the LED.
short getId(short x, short y)
{
    short id = 0;

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
int setLeds(short x[], short y[], int count, CRGB color)
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
//void pong(uint16_t frameNo, CRGB alliance)
//{
//    int scFrame = frameNo % 32;
//    frameNo = frameNo % 12;
//    
//    CRGB colors[8] {
//        CRGB::DarkRed,
//        CRGB::DarkRed,
//        CRGB::DarkRed,
//        CRGB::DarkRed,
//        CRGB::DarkRed,
//        CRGB::DarkRed,
//        CRGB::DarkRed,
//        CRGB::DarkRed
//    };
//
//    for (int i = 0; i <= scFrame; i++)
//    {
//        scroll(colors, 0, 0, i);
//    }
//    if (frameNo == 0)
//    {
//        short a[9] {1, 2, 3, 4, 1, 2, 3, 4, 3};
//        short b[9] {0, 0, 0, 0, 7, 7, 7, 7, 4};
//        setLeds(a, b, 9, CRGB::Blue);
//    } else if (frameNo == 1)
//    {
//        short a[9] {1, 2, 3, 4, 1, 2, 3, 4, 4};
//        short b[9] {0, 0, 0, 0, 7, 7, 7, 7, 5};
//        setLeds(a, b, 9, CRGB::Blue);
//    } else if (frameNo == 2)
//    {
//        short a[9] {2, 3, 4, 5, 2, 3, 4, 5, 5};
//        short b[9] {0, 0, 0, 0, 7, 7, 7, 7, 6};
//        setLeds(a, b, 9, CRGB::Blue);
//    } else if (frameNo == 3)
//    {
//        short a[9] {3, 4, 5, 6, 3, 4, 5, 6, 6};
//        short b[9] {0, 0, 0, 0, 7, 7, 7, 7, 5};
//        setLeds(a, b, 9, CRGB::Blue);
//    } else if (frameNo == 4)
//    {
//        short a[9] {4, 5, 6, 7, 4, 5, 6, 7, 7};
//        short b[9] {0, 0, 0, 0, 7, 7, 7, 7, 4};
//        setLeds(a, b, 9, CRGB::Blue);
//    } else if (frameNo == 5)
//    {
//        short a[9] {5, 6, 7, 8, 5, 6, 7, 8, 9};
//        short b[9] {0, 0, 0, 0, 7, 7, 7, 7, 2};
//        setLeds(a, b, 9, CRGB::Blue);
//    } else if (frameNo == 6)
//    {
//        short a[9] {6, 7, 8, 9, 6, 7, 8, 9, 10};
//        short b[9] {0, 0, 0, 0, 7, 7, 7, 7, 1};
//        setLeds(a, b, 9, CRGB::Blue);
//    } else
//    {
//        short a[12] {7, 7, 7, 9,  11, 11, 11, 12, 12, 13, 13, 13};
//        short b[12] {2, 3, 4, 3,   2,  3,  4,  2,  4,  2,  3,  4};
//        setLeds(a, b, 12, CRGB::Blue);
//    }
//}

void LaserAnimation(uint16_t frame, CRGB alliance)
{
  frame = frame % 50;//however many frames you have 

  if (frame < 18) {//base of the shooter, until it starts moving
    short x[29] {2,6, 1,4,7,8, 1,5,6,9, 1,6,8,9,10,11, 1,5,6,9, 1,4,7,8, 2,6, 3,4,5};
    short y[29] {0,0, 1,1,1,1, 2,2,2,2, 3,3,3,3,3, 3,  4,4,4,4, 5,5,5,5, 6,6, 7,7,7};
    setLeds(x, y, 29, LASER_RED);
    
    short xa[30] {0,1,3,4,5, 0,2,3,5,6, 0,2,3,4,7,8, 0,2,3,4,5,7, 0,2, 0, 0,1, 0,1,2};
    short ya[30] {0,0,0,0,0, 1,1,1,1,1, 2,2,2,2,2,2, 3,3,3,3,3,3, 4,4, 5, 6,6, 7,7,7};
    setLeds(xa, ya, 30, LASER_DARKRED);
  }

  if (frame == 3 || frame == 4) {

    leds[getId(13, 4)] = CRGB::Grey;
  }

  if (frame == 4) {
    leds[getId(13, 3)] = CRGB::Grey;
  }
  
  if (frame == 5) {
    leds[getId(13, 3)] = CRGB::Grey;
    leds[getId(13, 2)] = CRGB::Grey;
    leds[getId(12, 1)] = CRGB::Grey;
  }
  if (frame == 6) {
    short x[5] {11,12, 12, 13, 11};
    short y[5] {0, 0,  1,  2,  7};
    setLeds(x, y, 5, CRGB::Grey);
  }
  if (frame == 7) {
    short x[5] {11, 12, 10,11,12};
    short y[5] {0,  6,  7, 7, 7};
    setLeds(x, y, 5, CRGB::Grey);
  }

  if (frame == 8) {
    short x[7] {11, 13, 13, 12,13, 11, 12};
    short y[7] {0,  4,  5,  6, 6,  7,  7};
    setLeds(x, y, 7, CRGB::Grey);
  }

  if (frame == 9) {
    short x[9] {3,4, 3, 14, 13,14, 13, 12,13};
    short y[9] {0,0, 1, 3,  4, 4,  5,  6, 6};
    setLeds(x, y, 9, CRGB::Grey);
  }
  if (frame == 10) {
    short x[16] {3, 2,3,12,13, 2,3,14, 2,14, 2,13,14, 13,14, 13};
    short y[16] {0, 1,1,1, 1,  2,2,2,  3,3,  4,4, 4,  5, 5,  6};
    setLeds(x, y, 16, CRGB::Grey);
  }
  if (frame == 11) {
    short x[16] {11, 12, 12,13, 2,13,14, 2,13,14, 2,13, 2,3,12, 3};
    short y[16] {0,  1,  2, 2,  3,3, 3,  4,4, 4,  5,5,  6,6,6,  7};
    setLeds(x, y, 16, CRGB::Grey);
  }
  if (frame == 12) {
    short x[10] {9,10,11, 10,11,12, 13, 10, 9,10};
    short y[10] {0,0, 0,  1, 1, 1,  2,  6,  7,7};
    setLeds(x, y, 10, CRGB::Grey);
  }
  if (frame == 13) {
    short x[15] {8,9,10,11, 7,8,9,12, 7, 10, 10,11, 10,11, 10};
    short y[15] {0,0,0, 0,  1,1,1,1,  2, 4,  5, 5,  6, 6,  7};
    setLeds(x, y, 15, CRGB::Grey);
    leds[getId(8, 5)] = LASER_POWERUP;
  }
  if (frame == 14) {
    short x[10] {8,9,10, 7,8, 7, 10, 10,11, 11};
    short y[10] {0,0,0,  1,1, 2, 4,  5, 5,  6};
    setLeds(x, y, 10, CRGB::Grey);
    
    leds[getId(8, 5)] = LASER_POWERUP;
    leds[getId(7, 5)] = LASER_POWERUP;
  }
  if (frame == 15) {
    short x[4] {7, 7, 10, 10};
    short y[4] {1, 2, 4,  5};
    setLeds(x, y, 4, CRGB::Grey);
    short xa[3] {6, 7,8};
    short ya[3] {4, 5,5};
    setLeds(xa, ya, 3, LASER_POWERUP);
  }
  if (frame == 16) {
    short x[5] {6, 6, 6, 7,8};
    short y[5] {2, 3, 4, 5,5};
    setLeds(x, y, 5, LASER_POWERUP);
    leds[getId(7, 2)] = CRGB::Grey;
    leds[getId(10, 4)] = CRGB::Grey;
  }
  if (frame == 17) {
    short x[7] {7,8, 6, 6, 6, 7,8};
    short y[7] {1,1, 2, 3, 4, 5,5};
    setLeds(x, y, 7, LASER_POWERUP);
  }
  if (frame == 18) {
    short x[20] {1,5, 0,3, 0,4, 0,7,8,9,10, 0,4, 0,3, 1,5, 2,3,4};
    short y[20] {0,0, 1,1, 2,2, 3,3,3,3,3,  4,4, 5,5, 6,6, 7,7,7};
    setLeds(x, y, 20, LASER_RED);
    
    short xa[22] {0,2,3,4, 1,2,4,5, 1,2,3,6,7, 1,2,3,4,6, 1, 0, 0,1};
    short ya[22] {0,0,0,0, 1,1,1,1, 2,2,2,2,2, 3,3,3,3,3, 4, 6, 7,7};
    setLeds(xa, ya, 22, LASER_DARKRED);
    
    short xb[9] {6,7, 5,8, 5, 5,8, 6,7};
    short yb[9] {1,1, 2,2, 3, 4,4, 5,5};
    setLeds(xb, yb, 9, LASER_POWERUP);
  }
  
  if (frame == 19) {
    short x[15] {0,4, 2, 3, 6,7,8,9, 3, 2, 0,4, 1,2,3};
    short y[15] {0,0, 1, 2, 3,3,3,3, 4, 5, 6,6, 7,7,7};
    setLeds(x, y, 15, LASER_RED);
    
    short xa[19] {1,2,3, 0,1,3,4, 0,1,2,5,6, 0,1,2,3,5, 0, 0};
    short ya[19] {0,0,0, 1,1,1,1, 2,2,2,2,2, 3,3,3,3,3, 4, 7};
    setLeds(xa, ya, 19, LASER_DARKRED);

    short xb[9] {5,6, 4,7, 4, 4,7, 5,6};
    short yb[9] {1,1, 2,2, 3, 4,4, 5,5};
    setLeds(xb, yb, 9, LASER_POWERED1);
  }
  if (frame == 20) {
    short x[12] {2, 0, 1, 4,5,6,7, 1, 0, 2, 0,1};
    short y[12] {0, 1, 2, 3,3,3,3, 4, 5, 6, 7,7};
    setLeds(x, y, 12, LASER_RED);
    
    short xa[10] {0,1, 1,2, 0,3,4, 0,1,3};
    short ya[10] {0,0, 1,1, 2,2,2, 3,3,3};
    setLeds(xa, ya, 10, LASER_DARKRED);

    short xb[9] {3,4, 2,5, 2, 2,5, 3,4};
    short yb[9] {1,1, 2,2, 3, 4,4, 5,5};
    setLeds(xb, yb, 9, LASER_POWERED2);
  }
  if (frame == 21) {
    short x[4] {0,1,2,3};
    short y[4] {3,3,3,3};
    setLeds(x, y, 4, LASER_RED);

    short xb[4] {0, 1, 1, 0};
    short yb[4] {1, 2, 4, 5};
    setLeds(xb, yb, 4, LASER_POWERED3);
  }
  if (frame == 22) {
    leds[getId(0, 3)] = LASER_RED;
    leds[getId(1, 3)] = LASER_RED;
  }
  if (frame >= 23 && frame <= 26) {
    leds[getId(0, 3)] = LASER_RED;
  }
  if (frame == 25 || frame == 26) {
    short x[3] {0,1,0};
    short y[3] {2,3,4};
    setLeds(x, y, 3, LASER_RED);
  }
  if (frame == 27 || frame == 28) {
    short x[15] {1,2, 3, 0,1,3, 0,1,3, 0,1,3, 3, 1,2};
    short y[15] {0,0, 1, 2,2,2, 3,3,3, 4,4,4, 5, 6,6};
    setLeds(x, y, 15, LASER_RED);
  }
  if (frame == 27 || (frame >= 30 && frame <= 34)) {
    leds[getId(0, 3)] = CRGB::Grey;
  }
  if (frame == 29) {
    short x[32] {2, 4, 0,1,4, 0,1, 7,8,9,10,11,12, 17,18,19,20,21,22,23,24,25,26,27,28,29,30, 0,1,4, 1,3};
    short y[32] {0, 1, 2,2,2, 3,3, 3,3,3,3, 3, 3,  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  4,4,4, 7,7};
    setLeds(x, y, 32, LASER_RED);
  }
  if (frame == 30) {
    short x[37] {3, 0,1, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31, 0,1, 5};
    short y[37] {1, 2,2, 3,3,3,3,3,3,3,3,3,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  4,4, 6};
    setLeds(x, y, 37, LASER_RED);
  }
  if (frame == 31 || frame == 32) {
    short x[35] {0,1, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31, 0,1};
    short y[35] {2,2, 3,3,3,3,3,3,3,3,3,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  4,4};
    setLeds(x, y, 35, LASER_RED);
  }
  if (frame == 33) {
    short x[31] {0,1, 1,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30, 0,1};
    short y[31] {2,2, 3,3,3,3,3,3,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  4,4};
    setLeds(x, y, 31, LASER_RED);
  }
  if (frame == 34) {
    short x[26] {0,1, 1,4,5,6,7,8,9,11,12,13,14,15,16,17,19,20,21,22,25,27,28,30, 0,1};
    short y[26] {2,2, 3,3,3,3,3,3,3,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  4,4};
    setLeds(x, y, 26, LASER_RED);
  }
  if (frame == 35 || frame == 36) {
    short x[8] {22,28, 6,7,8,9,16,17};
    short y[8] {2, 2,  3,3,3,3,3, 3};
    setLeds(x, y, 8, LASER_RED);
  }
  if (frame == 35) {
    short x[4] {0, 0,1, 0};
    short y[4] {2, 3,3, 4};
    setLeds(x, y, 4, LASER_RED);
  }
  if (frame >= 37 && frame <= 39) {
    short x[5] {22,28, 7,8,17};
    short y[5] {2, 2,  4,4,4};
    setLeds(x, y, 5, LASER_RED);
  }
  if (frame >= 40 && frame <= 42) {
    short x[5] {22,29, 8, 8,17};
    short y[5] {2, 2,  3, 4,4};
    setLeds(x, y, 5, LASER_RED);
  }
  if (frame >= 43 && frame <= 49) {
    leds[getId(23, 2)] = LASER_RED;
    leds[getId(8, 3)] = LASER_RED;
  }
  if (frame >= 43 && frame <= 46) {
    leds[getId(29, 2)] = LASER_RED;
  }
} 

void TargetAnimation(uint16_t frame, CRGB alliance) {
  frame = frame % 51;

  if (frame == 2) {
    leds[getId(0,1)] = alliance;
    leds[getId(0,7)] = alliance;
  }
  if (frame == 3) {
    short x[10] = {3, 0,1, 2, 0,2, 2, 0,1, 3};
    short y[10] = {1, 2,2, 3, 4,4, 5, 6,6, 7};
    setLeds(x, y, 10, alliance);
  }
  short n = 0;
  if (frame == 5) {
    n += 3;
  }
  if (frame == 6) {
    n += 6;
  }
  if (frame == 7) {
    n += 9;
  }
  if (frame == 8 || frame == 18) {
    n += 12;
  }
  if (frame == 9) {
    n += 14;
  }
  if (frame == 10) {
    n += 16;
  }
  if (frame == 11 || frame == 16) {
    n += 17;
  }
  if (frame >= 12 && frame <= 15) {
    n += 18;
  }
  if (frame == 17) {
    n += 15;
  }
  if (frame == 19 || frame == 20) {
    n += 11;
  }
  if (frame >= 4 && frame <= 20) {
    short x[17] {0+n,6+n, 2+n,3+n,4+n, 1+n,5+n, 1+n,3+n,5+n, 1+n,5+n, 2+n,3+n,4+n, 0+n,6+n};
    short y[17] {1,1, 2,2,2, 3,3, 4,4,4, 5,5, 6,6,6, 7,7};
    setLeds(x, y, 17, alliance);
  }
  if ((frame >= 21 && frame <= 33) || (frame >= 37 && frame <= 39) || (frame >= 43 && frame <= 45)  || (frame >= 49 && frame <= 51)) {
    short x[13] = {13,14,15, 12,16, 12,14,16, 12,16, 13,14,15};  
    short y[13] = {2, 2, 2,  3, 3,  4, 4, 4,  5, 5,  6, 6, 6};
    setLeds(x, y, 13, alliance);
  }
  if (frame == 21) {
    short x[3] = {12, 18, 10};
    short y[3] = {0,2,6};
    setLeds(x, y, 3, alliance);
  }
  if (frame == 21 || frame == 22) {
    short x[3] = {12, 18, 10};
    short y[3] = {0,2,6};
    setLeds(x, y, 3, alliance);
  }
  if (frame == 23 || frame == 24) {
    short x[3] = {13, 18, 10};
    short y[3] = {0,3,5};
    setLeds(x, y, 3, alliance);
  }
  if (frame == 23 || frame == 24) {
    short x[3] = {13, 18, 10};
    short y[3] = {0,3,5};
    setLeds(x, y, 3, alliance);
  }
  if (frame == 25 || frame == 26) {
    short x[4] = {14,11,17,14};
    short y[4] = {1, 4, 4, 7};
    setLeds(x, y, 4, alliance);
  }
  if (frame == 29 || frame == 30) {
    short x[4] = {14,13,15,14};
    short y[4] = {3, 4, 4, 5};
    setLeds(x, y, 4, alliance);
  }
}

//! ----------------------------------------
//! START OF MAIN CODE
//! ----------------------------------------


void receive(int len)
{
    byte input = Wire.read();
    
    while (0 < Wire.available())
    {
        byte a = Wire.read();
    }

    if (input == 255)
    {
        alliance = CRGB::Red;
    } else if (input == 254) {
        alliance = CRGB::Blue;
    } else if (input == 253) {
        alliance = CRGB::Green;
    } else if (input == 0) {
        currAnim = Animations::SHOOT;
    } else if (input == 1) {
        currAnim = Animations::TARGET;
    }

void setup()
{
    FastLED.addLeds<WS2811, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    Serial.begin(9600);

    Wire.begin();
    Wire.onReceive(receive);
}

uint16_t frame {0};

void loop()
{
    clearAll();

    TargetAnimation(frame, alliance);

        
    FastLED.show();
    delay(50);
    frame++;
}
