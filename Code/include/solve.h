#pragma once


#define width 200
#define height 200
#define time 1000
#define h 200
#define p 200
#define L 50
#define speed 10

typedef struct color_s {
	int r;
	int g;
	int b;
}color_s;

class Solve {
public:
	color_s color[60];

	double surface_data[width][height][time];
	double around_data[width][L][time];

	color_s getColor(double t);

	void init_data();
	void getImage(char* surface, char* around, char* bottom, int t);
};
