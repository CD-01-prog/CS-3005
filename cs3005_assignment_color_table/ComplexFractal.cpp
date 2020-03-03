#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "ComplexFractal.h"

ComplexFractal::ComplexFractal(){
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

ComplexFractal::ComplexFractal(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y){
        NumberGrid::setGridSize(height,width);
        mheight = height;
        mwidth = width;
        mMaxValue = 255;
        mdelta_x = calculateDeltaX();
        mdelta_y = calculateDeltaY();
        mmin_x = min_x;
        mmin_y = min_y;
        mmax_x = max_x;
        mmax_y = max_y;
        mSet.resize(height,width);}

ComplexFractal::~ComplexFractal(){}

double ComplexFractal::getMinX() const{
        return mmin_x;
}

double ComplexFractal::getMaxX() const{
        return mmax_x;
}

double ComplexFractal::getMinY() const{
        return mmin_y;
}

double ComplexFractal::getMaxY() const{
        return mmax_y;
}

void ComplexFractal::setGridSize(const int& height, const int& width){
        if( height >= 2 and width >=2){
                NumberGrid::setGridSize(height,width);
                mheight = height;
                mwidth = width;
                setDeltas(calculateDeltaX(), calculateDeltaY());
        }
        return;
}

void ComplexFractal::setPlaneSize(const double& min_x, const double& max_x, const double& min_y, const double& max_y){
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

double ComplexFractal::getDeltaY() const{
        return mdelta_y;
}
double ComplexFractal::getDeltaX() const{
        return mdelta_x;
}
void ComplexFractal::setDeltas( const double& delta_x, const double& delta_y){
        if (delta_x >= 0 and delta_y >= 0){
                mdelta_x = delta_x;
                mdelta_y = delta_y;
        }

        return;
}
double ComplexFractal::calculateDeltaY() const{
        return ((mmax_y - mmin_y) / (mheight - 1));
}
double ComplexFractal::calculateDeltaX() const{
        return ((mmax_x - mmin_x) / (mwidth - 1));}
double ComplexFractal::calculatePlaneYFromPixelRow(const int& row) const{
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
double ComplexFractal::calculatePlaneXFromPixelColumn(const int& column) const{
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
void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double&x, double& y) const{
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



