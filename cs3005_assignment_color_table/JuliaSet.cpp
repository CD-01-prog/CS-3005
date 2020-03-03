#include <iostream>
#include <cmath>
#include <string>
#include "JuliaSet.h"

JuliaSet::JuliaSet()
	:ComplexFractal(){
	mA = -0.650492;
        mB = -0.478235;

}

JuliaSet::JuliaSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b)
	:ComplexFractal(height,width,min_x,max_x,min_y,max_y){
	mA = a;
        mB = b;

	}

JuliaSet::~JuliaSet(){}

double JuliaSet::getA() const{
        return mA;
}

double JuliaSet::getB() const{
        return mB;
}

void JuliaSet::setParameters(const double& a, const double& b){
	if( a >= -2.0 and a <= 2.0 and b >= -2.0 and b <= 2.0 ){
		mA = a;
		mB = b;
	}
	return;
}
void JuliaSet::calculateNextPoint(const double x0, const double y0, double& x1, double &y1) const{
	x1 = x0 * x0 -y0*y0 + mA;
	y1 = 2*x0*y0 + mB;
	return;
}
int JuliaSet::calculatePlaneEscapeCount(const double& x0, const double& y0) const{
	int count = 0;
	double x1 = 0.0;
	double y1 = 0.0;
	double x2 = 0.0;
	double y2 = 0.0;
	double distance = sqrt(pow(x0,2) + pow(y0,2));
	if (distance > 2){
		return count;}
	x1 = x0;
	y1 = y0;
	count = 1;
	while (distance <= 2){
		calculateNextPoint(x1,y1,x2,y2);
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
int JuliaSet::calculateNumber(const int& row, const int& column) const{	
	int count;
	if (row >= NumberGrid::getHeight() or row < 0 or column >= NumberGrid::getWidth() or column < 0){
		return -1;
	}
	double x,y;
	x = ComplexFractal::calculatePlaneXFromPixelColumn(column);
	y = ComplexFractal::calculatePlaneYFromPixelRow(row);
	count = calculatePlaneEscapeCount(x,y);
	return count;
	return 0;
}



