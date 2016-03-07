#include "writer.h"

void printChar(char printData, uint16* curX, uint16* curY)
{
    if(printData == '\t')
    {
        uint8 insCount = *curX % 4;
        insCount = insCount == 0 ? 4 : insCount;
        while(insCount-- > 0)
        {
            // The brackets are meant to be there. DO NOT DELETE
            printCharAt(' ', black, (*curX)++ % sw, *curY);
        }
    }
    else if(printData == '\n')
    {
        // The bracket thing:
        // *ptr++ increments pointer -> derefernces (shorthand for ptr++; *ptr)
        // (*ptr)++ derefernces pointer -> increments (shorthand for *ptr += 1)
        (*curY)++; *curX = 1;
    }
    else
    {
        printCharAt(printData, black, (*curX)++ % sw, *curY);
    }
}

void appendln(strbuilder_t* data, uint16* curX, uint16* curY, uint32* index)
{
    (*curY)++; *curX = 1;
    strbuilder_insertc(data, '\n', (*index)++);
}

void writerHelp()
{
	newline();
	print("Showing help for writer:",magenta);
	newline();
	print("Writer is a simple text editor built into Q OS\n",yellow);
	print("Your text will probably be saved when you exit with Control + Z\n",yellow);
	print("To start a new document simply type 'writer new'\n",yellow);
	print("To access your last document type 'writer' with no arguments.\n",yellow);
	print("After the first line of text saved your document may be shown unformatted.\n",yellow);
	print("Press 'i' after opening writer to start editing your document.",yellow);
}

void oldWriter()
{
	paintScreen(screen_color);

	drawFrame(header_background, 0, 0, 80, 4);
	printAt("Q OS Text Editor\r\n", header_foreground, 1, 1);
	printAt("Simple Text Editor built for Q OS by Raph Hennessy & Plankp T",desc_foreground,1,2);

	drawBorder(screen_background, 0, 4, 80, sh - 1);

	cursorY = 5;
	cursorX = 1;
	updateCursor();

	writing = true;
	printAt(writerContents,black,1,5);
	writerContents = readstr();
	writing = false;
}

void cursorBoundsCheck(uint16 *curX, uint16 *curY, uint32 *index) {
    if (*curX == 0)
    {
        (*curX)++;
        (*index)++;
    }
    if (*curX > 79)
    {
	    *curX = 1;
	    (*curY)++;
    }
    if (*curY < 5)
    {
	    *curY = 5;
	    *curX = 1;
    }
}

static inline void moveCursorLeft(uint16 *curX, uint16 *curY, uint32 *index)
{
    (*curX)--;
    (*index)--;
    cursorBoundsCheck(curX, curY, index);
}

static inline void moveCursorRight(uint16 *curX, uint16 *curY, uint32 *index)
{
    (*curX)++;
    (*index)++;
    cursorBoundsCheck(curX, curY, index);
}

static inline void printStatus(uint16 curX, uint16 curY, bool inCmdMode)
{
    // The trailing spaces clears out junky characters! Keep them
    // Also the 181 and 198 are hybrid boxed drawing chars. Not adding them
    printCharAt((char) 181, black, 1, 24);
    printAt(inCmdMode ? " CMD     " : " INS     ", dark_grey, 2, 24);
    printAt(itos10(curX - 1), black, 7, 24);
    printAt(":     ", black, 10, 24);
    printAt(itos10(curY - 5), black, 12, 24);
    printCharAt((char) 198, black, 16, 24);
}

static inline void reprintText(uint16* curX, uint16* curY, uint32* index, strbuilder_t data)
{
    *curX = 1; *curY = 5;
    uint16 oldX = 1, oldY = 5, indexClone = *index;
    paintLine(blue, 1, *curY, sw);
    for(uint16 loopi = 0; loopi < data.ilist.size; loopi++) {
        printChar(strbuilder_charAt(data, loopi), curX, curY);
        if(*curY > oldY)
        {
            indexClone -= oldX;
        }
        oldY = *curY;
        oldX = *curX;
    }
    *curX = indexClone + 1;
}

static inline void insertCharAt(uint16* curX, uint16* curY, uint32* index, strbuilder_t* data, char charInput)
{
    strbuilder_insertc(data, charInput, (*index)++);
    reprintText(curX, curY, index, *data);
}

static inline void deleteCharAt(uint16* curX, uint16* curY, uint32* index, strbuilder_t* data)
{
    strbuilder_rmchar(data, --(*index));
    reprintText(curX, curY, index, *data);
}

string initWriter()
{
	string vidmem = (string) 0xb8000;
    char oldmem[strlen(vidmem)];
    strcpy(oldmem, vidmem);

	paintScreen(screen_color);

	drawFrame(header_background, 0, 0, 80, 4);
	printAt("Q OS Text Editor\r\n", header_foreground, 1, 1);
	printAt("Simple Text Editor built for Q OS by Raph Hennessy & Plankp T",desc_foreground,1,2);

	drawBorder(screen_background, 0, 4, 80, sh - 1);

	cursorY = 5;
	cursorX = 1;
	updateCursor();

    bool inCmdMode = true;
    uint16 curX = 1, curY = 5;
    uint32 index = 0;
    strbuilder_t data = strbuilder_init();
    int k;
    while(true)
    {
        cursorX = curX % sw;
        cursorY = curY;
        updateCursor();

        cursorBoundsCheck(&curX, &curY, &index);
        printStatus(curX, curY, inCmdMode);

        if(inCmdMode)
        {
            k = waitUntilKey(7, 0x10 /*Q*/, 0x17 /*I*/, 0x18 /*O*/, 0x3A /*<CAPS>*/, 0x23 /*H*/, 0x26 /*L*/, 0x2D /*X*/);
            switch(k)
            {
            case 0x10:
                goto end;
            case 0x17:
                inCmdMode = false;
                break;
            case 0x18:
                appendln(&data, &curX, &curY, &index);
                inCmdMode = false;
                break;
            case 0x23:
                moveCursorLeft(&curX, &curY, &index);
                break;
            case 0x26:
                moveCursorRight(&curX, &curY, &index);
                break;
            case 0x2D:
                deleteCharAt(&curX, &curY, &index, &data);
                break;
            }
        } else {
            k = getKeycode() / KC_MAGIC_VAL;
            char charInput = ' ';
            switch(k)
            {
            case 0x01:
                inCmdMode = true;
                break;
            case 0x1C:
				cursorBoundsCheck(&curX, &curY, &index);
                appendln(&data, &curX, &curY, &index);
                break;
            case 0x48:
                curY--;
                curX = 1;
				cursorBoundsCheck(&curX, &curY, &index);
                break;
            case 0x4B:
                moveCursorLeft(&curX, &curY, &index);
                break;
            case 0x4D:
                moveCursorRight(&curX, &curY, &index);
                break;
            case 0x50:
                curY++;
                curX = 1;
                cursorBoundsCheck(&curX, &curY, &index);
                break;
            case 0x0E:
                deleteCharAt(&curX, &curY, &index, &data);
                break;
            default:
                if(k < 59 && k > 0)
                {
                    charInput = retCorrespChar(kbShiftChars[k], kbLowerChars[k]);
                    if(charInput == 0)
                    {
                        break;
                    }
                    insertCharAt(&curX, &curY, &index, &data, charInput);
                }
                break;
            }
        }
    }
end: // Sorry for the mom spaghetti code
    // Must be last line (before any prints)
	strcpy(vidmem, oldmem);
    string msg = strbuilder_tostr(data);
    if(msg == NULL)
    {
        msg = "";
    }
    strbuilder_destroy(&data);
    cursorX = 1;
	cursorY = 5;
    print(msg, black);
    return msg;
}

void writer(string args)
{
	if (streql(splitArg(args, 1),"-H"))
	{
		writerHelp();
	}
	else if (streql(splitArg(args, 1),"STABLE"))
	{
		oldWriter();
	}
	else
	{
		//writing = true;
		writerContents = initWriter();
		//writing = false;
		clearScreen();
	}
}
