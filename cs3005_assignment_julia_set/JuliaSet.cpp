#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "JuliaSet.h"

JuliaSet::JuliaSet(){
	mA = -0.650492;
	mB = -0.478235;
	mMaxValue = 255;
	mdelta_x = 0.01;
	mdelta_y = 0.01;
	mmin_x = -1.5;
	mmax_x = 1.5;
	mmin_y = -1;
	mmax_y = 1;
	NumberGrid::setGridSize(200,300);
	mheight = 200;
	mwidth = 300;
}

JuliaSet::JuliaSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b){
	NumberGrid::setGridSize(height,width);
	mheight = height;
	mwidth = width;
	mMaxValue = 255;
	mA = a;
       	mB = b;
	mdelta_x = calculateDeltaX();
	mdelta_y = calculateDeltaY();
	mmin_x = min_x;
	mmin_y = min_y;
	mmax_x = max_x;
	mmax_y = max_y;
	mSet.resize(height,width);
}

JuliaSet::~JuliaSet(){}

double JuliaSet::getMinX() const{
	return mmin_x;
}

double JuliaSet::getMaxX() const{
        return mmax_x;
}   

double JuliaSet::getMinY() const{
        return mmin_y;
}

double JuliaSet::getMaxY() const{
        return mmax_y;
}

double JuliaSet::getA() const{
        return mA;
}

double JuliaSet::getB() const{
        return mB;
}

void JuliaSet::setGridSize(const int& height, const int& width){
	if( height >= 2 and width >=2){
		NumberGrid::setGridSize(height,width);
		mheight = height;
		mwidth = width;
		setDeltas(calculateDeltaX(), calculateDeltaY());
	}
	return;
}
void JuliaSet::setPlaneSize(const double& min_x, const double& max_x, const double& min_y, const double& max_y){
	if (min_x >= -2.0 and min_x <= 2.0 and max_x >= -2.0 and max_x <= 2.0 and min_y >= -2.0 and min_y <= 2.0 and max_y >= -2.0 and max_y <= 2.0){
		if (min_x != max_x and min_y != max_y){
			//if minx is bigger then max but y is okay
			if ( min_x > max_x and min_y < max_y){
				mmin_x = max_x;
                                mmin_y = min_y;
                                mmax_x = min_x;
                                mmax_y = max_y;
                                setDeltas(calculateDeltaX(), calculateDeltaY());	
			}
			//if miny is bigger but x is okay
			if ( min_x < max_x and min_y > max_y){
				mmin_x = min_x;
                                mmin_y = max_y;
                                mmax_x = max_x;
                                mmax_y = min_y;
                                setDeltas(calculateDeltaX(), calculateDeltaY());
			}
			// if both are bigger then their maxes
			if ( min_x > max_x and min_y > max_y){
				mmin_x = max_x;
                                mmin_y = max_y;
                                mmax_x = min_x;
                                mmax_y = min_y;
                                setDeltas(calculateDeltaX(), calculateDeltaY());
			}
			// if everything is okay
			if (min_y < max_y and min_x < max_x){
				mmin_x = min_x;
				mmin_y = min_y;
				mmax_x = max_x;
				mmax_y = max_y;
				setDeltas(calculateDeltaX(), calculateDeltaY());}

		}
	}
	return; 
}
void JuliaSet::setParameters(const double& a, const double& b){
	if( a >= -2.0 and a <= 2.0 and b >= -2.0 and b <= 2.0 ){
		mA = a;
		mB = b;
	}
	return;
}
double JuliaSet::getDeltaY() const{
	return mdelta_y;
}
double JuliaSet::getDeltaX() const{
	return mdelta_x;
}
void JuliaSet::setDeltas( const double& delta_x, const double& delta_y){
	if (delta_x >= 0 and delta_y >= 0){
		mdelta_x = delta_x;
		mdelta_y = delta_y;
	}
	
	return;
}
double JuliaSet::calculateDeltaY() const{
	return ((mmax_y - mmin_y) / (mheight - 1));
}
double JuliaSet::calculateDeltaX() const{
	return ((mmax_x - mmin_x) / (mwidth - 1));}
double JuliaSet::calculatePlaneYFromPixelRow(const int& row) const{
	double answer;
	answer = mmax_y - row * mdelta_y;
	if (row < 0 or row > mheight){
		return 0;
	}
	if (answer > mmax_y){
		return 0;
	}
	if (answer < mmin_y){
		return 0;
	}
	return answer;
}
double JuliaSet::calculatePlaneXFromPixelColumn(const int& column) const{
	double answer;
	answer = mmin_x + column * mdelta_x;
	if (column < 0 or column > mwidth){
                return 0;
        }
	if ( answer > mmax_x){
		return 0;
	}
	if (answer < mmin_x){
		return 0;
	}
	return answer;
}
void JuliaSet::calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double&x, double& y) const{
	double planeY = calculatePlaneYFromPixelRow(row);
	double planeX = calculatePlaneXFromPixelColumn(column);
	if (row >= mheight or row < 0 or column >= mwidth or column < 0){
		x = 0;
		y = 0;
		return;
	}
	else{
		x = planeX;
		y = planeY;
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
	if (row >= mheight or row < 0 or column >= mwidth or column < 0){
		return -1;
	}
	count = calculatePlaneEscapeCount(calculatePlaneXFromPixelColumn(column),calculatePlaneYFromPixelRow(row));
	return count;
}

