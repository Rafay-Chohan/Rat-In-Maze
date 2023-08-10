#include <windows.h>

#include <WinCon.h>
#include <iostream>
#include <conio.h> 
using namespace std;

#include "myconsole.h"

//this function checks if a key is pressed and if a key is pressed
//then it returns the ascii code/virtual code of the key pressed
//specialKey would be returned as true if it is a key associated with a non-printable character
//specialKey would be returned as false if ordinary printable characters are typed
//if no key is pressed then specialKey value will not be changed
//the parameter waitTime specifies how long we have to wait for an input
//the default value is 20 millisecond.  If within the wait time no key is pressed
//the function returns zero.
unsigned int CheckWhichKeyPressed(bool& specialKey, int waitTime)
{
	HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD r;
	DWORD w = 1;
	DWORD eventss;
	DWORD waitResult = 0;
	int keypressed = false;
	int toReturn = 0;

	waitResult = WaitForSingleObject(h, waitTime);

	if (waitResult == WAIT_OBJECT_0)
	{
		//FlushConsoleInputBuffer(h);..commented out as this takes to asynchronous mode on some systems
		keypressed = ReadConsoleInput(h, &r, 1, &eventss);

		if (keypressed && r.EventType == KEY_EVENT && r.Event.KeyEvent.bKeyDown)
		{
			toReturn = r.Event.KeyEvent.wVirtualKeyCode;

			if (r.Event.KeyEvent.uChar.AsciiChar)
			{
				toReturn = r.Event.KeyEvent.uChar.AsciiChar;
				specialKey = false;
			}
			else
				specialKey = true;

		}
		//this should make sure that checkKeyPressed is not called twice for arrow keys
		if (toReturn == 224)
			toReturn = CheckWhichKeyPressed(specialKey, waitTime);
		FlushConsoleInputBuffer(h);
	}
	return toReturn;
}
//changes the color of a certain co-ordinate
//color can be input using a combination of foreground and Back grounfd Color and | operator
bool SetColorAtPoint(int x, int y, int color)
{
	COORD c, size;
	c.X = y;
	c.Y = x;
	size.X = 1;
	size.Y = 1;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD w = color;
	unsigned long written = 0;
	WriteConsoleOutputAttribute(h, &w, 1, c, &written);

	if (written)
		return true;

	return false;
}