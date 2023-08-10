#ifndef MYCONSOLE_H
#define MYCONSOLE_H
//virtual scan codes for keys returned by checkWhichKeyPressed
//specialKey will be true in all of the cases below
const int LEFTKEY = 37;
const int UPKEY = 38;
const int RIGHTKEY = 39;
const int DOWNKEY = 40;

////-------------------------------Color Codes------------------------------//
//// Color Codes Hexadecimal values for both Fore Ground and Back Ground //ForeGround|BackGround
//int B_BLACK = 0x00;	int B_Royal_Blue = 0x10;	int B_Dark_Green = 0x20;
//int B_Tale_Blue = 0x30;	int B_Dark_Red = 0x40;	int B_Purple = 0x50;
//int B_Tale_Green = 0x60;	int B_Light_Grey = 0x70; int B_Dark_Gray = 0x80;
//int B_Light_Blue = 0x90; int B_Light_Green = 0xA0;	int B_Sky_Blue = 0xB0;
//int B_Red = 0xC0;	int B_Pink = 0xD0;	int B_Yellow = 0xE0;
//int B_White = 0xF0;
//
//int F_BLACK = 0x00;	int F_Royal_Blue = 0x01; int F_Dark_Green = 0x02;
//int F_Tale_Blue = 0x03;	int F_Dark_Red = 0x04;	int F_Purple = 0x05;
//int F_Tale_Green = 0x06;	int F_Light_Grey = 0x07; int F_Dark_Gray = 0x08;
//int F_Light_Blue = 0x09; int F_Light_Green = 0x0A;	int F_Sky_Blue = 0x0B;
//int F_Red = 0x0C;	int F_Pink = 0x0D;	int F_Yellow = 0x0E;
//int F_White = 0x0F;
//this function checks if a key is pressed and if a key is pressed
//then it returns the ascii code/virtual code of the key pressed
//specialKey would be returned as true if it is a key associated with a non-printable character
//specialKey would be returned as false if ordinary printable characters are typed
//if no key is pressed then specialKey value will not be changed
//the parameter waitTime specifies how long we have to wait for an input
//the default value is 20 millisecond.  If within the wait time no key is pressed
//the function returns zero.
unsigned int CheckWhichKeyPressed(bool& specialKey, int waitTime = 20);
//changes the color of a certain co-ordinate
//An example of usage:
//    PlaceCursor(0,0);
//    cout << '*';
//    SetColorAtPoint(0,0,BACKGROUND|FOREGROUND);
bool SetColorAtPoint(int x, int y, int color);
#endif
