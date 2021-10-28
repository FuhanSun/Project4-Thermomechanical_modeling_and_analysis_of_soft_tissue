#pragma once
#include "cmath"
#include <fstream>
#include <iostream>
#include<windows.h>
using namespace std;

#define width 200
#define height 200
#define time 1000
#define h 200
#define p 200
#define L 50

typedef struct color_s {
	int r;
	int g;
	int b;
}color_s;

double min, max;

color_s color[60];
