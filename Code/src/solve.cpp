#include "cmath"
#include <fstream>
#include <iostream>
#include<windows.h>
#include "solve.h"
using namespace std;



color_s Solve::getColor(double t) {
	double min = 24.0;
	double max = 40.0;
	//31.5216
	//31.5227
	double piece = (max - min) / 60.0;
	//int index = int((t - min-5*piece) / (piece*1.05));
	//double extra = t - (index*0.00005+ 31.5210);
	int index = int((t - min) / piece);
	return color[ index];
}


void Solve::init_data()
{

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			surface_data[i][j][0] = 25;

	for (int t = 1; t < time; t++) {
		double y = (-(48840 + 2 * h * p) / 3600.0) * exp(-36.0 / 80000.0 * t) + (138840 + 2 * h * p) / 3600.0;
		for (int i = 0; i < height; i++) {
			surface_data[i][0][t] = y;
			surface_data[i][height - 1][t] = y;
		}
		for (int j = 0; j < width; j++) {
			surface_data[0][j][t] = y;
			surface_data[width - 1][j][t] = y;
		}
	}

	for (int t = 1; t < time; t++)
		for (int i = 1; i < width - 1; i++)
			for (int j = 1; j < height - 1; j++) {
				surface_data[i][j][t] = (1 / 8.0) * (surface_data[i + 1][j][t - 1] + surface_data[i - 1][j][t - 1] + surface_data[i][j + 1][t - 1] + surface_data[i][j - 1][t - 1] - 4 * surface_data[i][j][t - 1]) +
					(1 / 8000000.0) * (-3600 * surface_data[i][j][t - 1] + 2 * h * p + 138840) + surface_data[i][j][t - 1];
			}

	//for (int i = 0; i < width/2; i++)
	//	for (int j = 0; j < height/2; j++)
	//		cout << surface_data[i][j][time-1]<<" ";


	ifstream in("color.txt");
	for (int i = 0; i < 60; i++) {
		in >> color[i].r;
		in >> color[i].g;
		in >> color[i].b;
	}
	in.close();

	//cout << surface_data[50][50][time-1] << endl;
	//min = surface_data[width - 1][height - 1][time - 1];
	//max = surface_data[width / 2][height / 2][time - 1];

	//char img[width * height * 3];
	//int index = 0;
	//for (int i = 0; i < width; i++)
	//	for (int j = 0; j < height; j++) {
	//		color_s c = getColor(surface_data[i][j][time - 1]);
	//		img[index++] = c.r;
	//		img[index++] = c.g;
	//		img[index++] = c.b;
	//	}
	//WriteBMP(img, "surface.bmp",width,height);



	for (int t = 0; t < time; t++) {
		for (int i = 0; i < width; i++) {
			around_data[i][0][t] = 37;
			around_data[i][L - 1][t] = surface_data[i][height - 1][t];
		}
	}

	for (int i = 1; i < L - 1; i++) {

		around_data[0][i][0] = 37.0 - (37.0 - 25.0) * i / L;
		for (int j = 1; j < width; j++)
			around_data[j][i][0] = around_data[0][i][0];
	}

	for (int t = 1; t < time; t++) {
		for (int i = 1; i < L - 1; i++) {
			around_data[0][i][t] = 1 / 8.0 * (around_data[0][i + 1][t - 1] + around_data[0][i - 1][t - 1] - 2 * around_data[0][i][t - 1])
				+ (1 / 8000000.0) * ((h * p) * exp(-1000 * h * (L - i)) - 4000 * around_data[0][i][t - 1] + 148840) + around_data[0][i][t - 1];
			around_data[width - 1][i][t] = around_data[0][i][t];
		}
	}




	for (int t = 1; t < time; t++)
		for (int i = 1; i < width - 1; i++)
			for (int j = 1; j < L - 1; j++) {
				around_data[i][j][t] = (1 / 8.0) * (around_data[i + 1][j][t - 1] + around_data[i - 1][j][t - 1] + around_data[i][j + 1][t - 1] + around_data[i][j - 1][t - 1] - 4 * around_data[i][j][t - 1]) +
					(1 / 8000000.0) * (-4000 * around_data[i][j][t - 1] + 2 * h * p * exp(-h * (L - j)) + 148840) + around_data[i][j][t - 1];
			}

	/*
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < L; j++)
			cout << around_data[i][j][0] << " ";
		cout << endl;
	}*/

	//char img1[width * L * 3];
	//index = 0;
	//
	//for (int j = 0; j < L; j++) {
	//	for (int i = 0; i < width; i++) {
	//		//color_s c = getColor(around_data[i][j][time - 1]);
	//		color_s c = getColor(around_data[i][j][0]);
	//		img1[index++] = c.r;
	//		img1[index++] = c.g;
	//		img1[index++] = c.b;
	//	}
	//}
	//WriteBMP(img1, "around.bmp",width,L);

}

void Solve::getImage(char* surface, char* around, char* bottom, int t) {

	int index = 0;
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++) {
			//cout << surface_data[i][j][t] << " ";
			color_s c = getColor(surface_data[i][j][t]);
			surface[index++] = c.r;
			surface[index++] = c.g;
			surface[index++] = c.b;
		}

	index = 0;
	for (int j = 0; j <L; j++) {
		for (int i = 0; i <width; i++) {
			//color_s c = getColor(around_data[i][j][time - 1]);
			color_s c = getColor(around_data[i][j][t]);
			around[index++] = c.r;
			around[index++] = c.g;
			around[index++] = c.b;
		}
	}


	index = 0;
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++) {
			color_s c = getColor(37.0);
			bottom[index++] = c.r;
			bottom[index++] = c.g;
			bottom[index++] = c.b;
		}


}


