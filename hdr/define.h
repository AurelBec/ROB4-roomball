#ifndef DEFINE_H
#define DEFINE_H

#define PI 3.14159265

#define W_WINDOW	600
#define H_WINDOW	800

#define H_BORD		8

#define W_CAGE		80
#define H_CAGE		40

#define FONT_SIZE	15

#define PLAY_TIME	120


enum Action { Action_LEFT = 0, Action_RIGHT = 1, Action_UP = 2, Action_DOWN = 3 };


#include <sstream>
template <typename T>
std::string num2str ( T Number )
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

#endif 