#include <iostream>
#include <cmath>
#include <string>
#include "MandelbrotSet.h"

MandelbrotSet::MandelbrotSet()
	:ComplexFractal(){
}

MandelbrotSet::MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
	:ComplexFractal(height,width,min_x,max_x,min_y,max_y){
}

MandelbrotSet::~MandelbrotSet(){}

void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const{
	x1 = x0 * x0 - y0 * y0 + a;
	y1 = 2 * x0 * y0 + b;
	return;
	}

int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const{
	int count = 0;
        double x1 = 0.0;
        double y1 = 0.0;
        double x2 = 0.0;
        double y2 = 0.0;
	double distance = 0.0;
        while (distance <= 2){
		calculateNextPoint(x1,y1,a,b,x2,y2);
                distance = sqrt(pow(x2,2) + pow(y2,2));
                if (distance > 2){
                        return count;}
                if (count >= mMaxValue){
                        return count;}
                x1 = x2;
                y1 = y2;
                count += 1;
        }
        return -1;

}

int MandelbrotSet::calculateNumber( const int& row, const int& column ) const{
	int count;
        if (row >= NumberGrid::getHeight() or row < 0 or column >= NumberGrid::getWidth() or column < 0){
                return -1;
        }
        count = calculatePlaneEscapeCount(ComplexFractal::calculatePlaneXFromPixelColumn(column),ComplexFractal::calculatePlaneYFromPixelRow(row));
        return count;

}

