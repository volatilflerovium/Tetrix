#ifndef HELPER_H
#define HELPER_H
#include<cmath>


//###################################################################
//###################################################################
//###################################################################
//###################################################################

const int WINDOW_WIDTH=800;
const int WINDOW_HEIGHT=800;

// the width of each square in the board
const float SD=30.0;

// Pixels per centimetre ration  1cm=37.7952 px (depending of the resolution)
const float PX_CM=37.795238;

//###################################################################


struct Point{
	int x;
	int y;
	
	Point(int _x, int _y)
		:x(_x), y(_y){};
	Point(const Point& P){
		x=P.x;
		y=P.y;
	}
	Point()
		:x(0), y(0){};
	Point operator+(const Point& P){
		return Point(x+P.x,y+P.y);
	}
	Point operator-(const Point& P){
		return Point(x-P.x, y-P.y);
	}
	Point& operator+=(const Point& P){
		x+=P.x;
		y+=P.y;
		return *this;
	}
};
//###################################################################
//###################################################################
//###################################################################


#endif