#include "curses-clock.h"

#include <cmath>

#include <ncurses.h>

#include <time.h>


void drawclock(double width, double height, Coordinates2D center, bool miniticks, struct timeval time) {
	
	Coordinates2D point1 = center;
	Coordinates2D point2 = {.x = 25, .y=0};
	
	
	time_t rawtime;
	struct tm * timeinfo;
	
	// Base
	point1.x = center.x - width;
	point1.y = center.y;
	point2.x = center.x + width;
	point2.y = center.y;
	ln(point1, point2);
	
	point1.x = center.x;
	point1.y = center.y + height;
	point2.x = center.x;
	point2.y = center.y - height;
	ln(point1, point2);
	
	point1 = center;
	point2.x = 25;
	point2.y = 0;
	
	// Minute "mini" ticks
	if (miniticks) {
		attron(COLOR_PAIR(3));
		for (double i = 1; i <= 60; i+=1) {
			double x = center.x + ((double)width)*sin(i *M_PI*2.0/60.0);
			double y = center.y - ((double)height)*cos(i *M_PI*2.0/60.0);
			drawDotFloat(x,y);
//			mvaddch(y, x, '*');
		}
		attroff(COLOR_PAIR(3));
	}
	
//	time ( &rawtime );
	rawtime = time.tv_sec;
	timeinfo = localtime ( &rawtime );
	
	attron(A_BOLD);
	attron(COLOR_PAIR(1));
	double seconds = M_PI*2.0/60.0*((double)timeinfo->tm_sec + time.tv_usec/1000000.0);
	point2.x = point1.x + width*sin(seconds)*0.90;
	point2.y = point1.y - height*cos(seconds)*0.90;
	ln(point1, point2);
	attroff(COLOR_PAIR(1));
	
	attron(COLOR_PAIR(2));
	double minutes = M_PI*2.0/60.0*(double)timeinfo->tm_min + seconds/60.0;
	point2.x = point1.x + width*sin(minutes)*0.80;
	point2.y = point1.y - height*cos(minutes)*0.80;
	ln(point1, point2);
	attroff(COLOR_PAIR(2));
	
	attron(COLOR_PAIR(3));
	double hours = M_PI*2.0/12.0*(double)timeinfo->tm_hour + minutes/12.0;
	point2.x = point1.x + width*sin(hours)*0.6;
	point2.y = point1.y - height*cos(hours)*0.6;
	ln(point1, point2);
	attroff(COLOR_PAIR(3));
	attroff(A_BOLD);
	
	
	
	
	//		attron(COLOR_PAIR(5));
	
	
	
	attron(A_BOLD);
	//		attron(COLOR_PAIR(7));
	for (double i = 1; i <= 12; i+=1) {
		int x = center.x + width*sin(i *M_PI*2.0/12.0) - (i >= 10 ? 0.5 : 0);
		int y = center.y - height*cos(i *M_PI*2.0/12.0);
		mvprintw(y, x, "%d", (int)i);
	}
	//		attroff(COLOR_PAIR(7));
	
	attroff(A_BOLD);
	//		attroff(COLOR_PAIR(5));
	
	
	
}
