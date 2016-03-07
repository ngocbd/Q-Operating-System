#include "user.h"

bool loggedIn = false;

void logout()
{
    loggedIn = false;

    clearLine(0,26,0x44);

    drawFrame(header_background, 20, 8, 60, 11);
    printAt("Locked", desc_foreground, 21, 9);

    while(!loggedIn)
    {
        login();
    }
}

void login()
{
    while (!loggedIn)
    {
        string buffPassword = "";
        buffPassword = messageBox_Pass("Enter your password to unlock your\n\raccount.");

        if(!streql(buffPassword,password))
        {
            messageBox("Invalid Password!");
        }
        else
        {
            loggedIn = true;
        }
    }

    printIntro();
    drawBorder(screen_background, 0, 4, 80, sh - 1);

    actualY = 5;

}
