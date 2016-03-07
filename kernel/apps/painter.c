#include "painter.h"

uint8 paintX;
uint8 paintY;

void painterIntro()
{
    drawFrame(header_background, 0, 0, 80, 4);
    printAt("Q OS Drawing Application\r\n", header_foreground, 1, 1);
    printAt("Dumb Drawing App for Q OS by Raph Hennessy",desc_foreground,1,2);
}

void resetPainter()
{
    paintX = sw / 2;
    paintY = sh / 2;

    paintScreen(screen_color);

    painterIntro();

    drawBorder(screen_background, 0, 4, 80, sh - 1);
}

static inline void printStatus(bool inColorMode)
{
    // The trailing spaces clears out junky characters! Keep them
    // Also the 181 and 198 are hybrid boxed drawing chars. Not adding them
    printCharAt((char) 181, black, 2, 24);
    printAt(inColorMode ? " PENCIL "
                        : " ERASER ", dark_grey, 3, 24);
    printCharAt((char) 198, black, 11, 24);
}

int painter(string args)
{
    if (streql(splitArg(args, 1), "-H"))
    {
        print("\nPainter is a simple drawing app for Q OS",red);
        print("\nTo use it, type 'painter' on the command line.",red);
        print("\nUse the arrow keys to draw lines on your screen.",red);
        print("\nPress the spacebar to reset your drawing.",red);
        print("\nPress X to change the X location of your pen and Y to change the Y location.",red);
    }
    else
    {
        // Run the setup function for painter
        resetPainter();
        bool isDrawing = true;
#define GET_PAINT_COLOR isDrawing ? 0x00 : screen_color
        // Begin the actual painter program
        while (true)
        {

            if (paintX < 1)
            {
                paintX = 1;
            }
            else if (paintX > 78)
            {
                paintX = 78;
            }

            if (paintY < 5)
            {
                paintY = 5;
            }
            else if (paintY > 23)
            {
                paintY = 23;
            }

            printAt("*",0xDD,paintX,paintY);
            printStatus(isDrawing);

            int key = getKeycode() / KC_MAGIC_VAL;

            switch (key)
            {
            case 1:
                // Escape Pressed
                clearScreen();
                return 0;
            case 72:
                // Up Arrow Pressed
                printAt(" ", GET_PAINT_COLOR, paintX, paintY);
                paintY--;
                break;
            case 80:
                // Down Arrow Pressed
                printAt(" ", GET_PAINT_COLOR, paintX, paintY);
                paintY++;
                break;
            case 75:
                // Left Arrow Pressed
                printAt(" ", GET_PAINT_COLOR, paintX, paintY);
                paintX--;
                break;
            case 77:
                // Right Arrow Pressed
                printAt(" ", GET_PAINT_COLOR, paintX, paintY);
                paintX++;
                break;
            case 57:
                // Spacebar Pressed
                resetPainter();
                break;
            case 0x2E:
                // C pressed
                isDrawing = true;
                break;
            case 0x12:
                // E pressed
                isDrawing = false;
                break;
            case -82:
                // X Released
                printAt(" ",screen_color,paintX,paintY);

                drawFrame(header_background, 0, 0, 80, 4);
                printAt("What X Posiiton do you want to move the pen to?\r\n", header_foreground, 1, 1);

                cursorX = 1;
                cursorY = 2;

                // we need to make the text below when input show in a blue on aqua font...
                paintX = stoi(readstr());

                painterIntro();
                break;
            case -106:
                // Y Pressed
                printAt(" ",screen_color,paintX,paintY);

                drawFrame(header_background, 0, 0, 80, 4);
                printAt("What Y Posiiton do you want to move the pen to?\r\n", header_foreground, 1, 1);

                cursorX = 1;
                cursorY = 2;

                // we need to make the text below when input show in a blue on aqua font...
                paintY = stoi(readstr());

                painterIntro();
                break;
            default:
                break;
            }
        }
    }


    return 0;

}
