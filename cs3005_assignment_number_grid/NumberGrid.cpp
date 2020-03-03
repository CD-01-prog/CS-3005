#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "NumberGrid.h"

NumberGrid::NumberGrid( ){
	mheight = 300;
	mwidth = 400;
	mMaxValue = 255;
	image.resize(mheight*mwidth,0);
	std::fill(image.begin(),image.end(),0);
}

NumberGrid::NumberGrid( const int& height, const int& width ){
	mheight = height;
	mwidth = width;
	mMaxValue = 255;
	image.resize(mheight*mwidth,0);
	std::fill(image.begin(),image.end(),0);
}

int NumberGrid::getHeight( ) const{
	return mheight;
}

int NumberGrid::getWidth( ) const{
	return mwidth;
}

int NumberGrid::getMaxNumber( ) const{
	return mMaxValue;
}

void NumberGrid::setGridSize( const int& height, const int& width ){
	if ((height >= 2) and (width >= 2)){
		mheight = height;
		mwidth = width;
		image.resize(height * width);
	}
	return;
}

void NumberGrid::setMaxNumber( const int& number ){
	if (number >= 0){
		mMaxValue = number;
	}
	return;
}

const std::vector< int >& NumberGrid::getNumbers( ) const{
	return image;
}

int NumberGrid::index( const int& row, const int& column ) const{
	return (row * mwidth + column);
}

bool NumberGrid::indexValid( const int& row, const int& column ) const{
	if ( row < mheight and row >=0 and column < mwidth and column >=0){
		return true;
	}
	return false;
}

bool NumberGrid::numberValid( const int& number ) const{
		if (number <= mMaxValue and number >= 0){
			return true;
		}
		return false;
}

int NumberGrid::getNumber( const int& row, const int& column ) const{
	int value;
	if (indexValid(row,column)){
		value = image[index(row,column)];
		if (numberValid(value)){
			return value;
		}
	}
	return -1;
}
void NumberGrid::setNumber( const int& row, const int& column, const int& number ){
	if (numberValid(number) and indexValid(row,column)){
		image[index(row,column)] =number;
			}
	return;
}
void NumberGrid::setPPM( PPM& ppm ) const{
	ppm.setHeight(mheight);
	ppm.setWidth(mwidth);
	ppm.setMaxColorValue(63);
	int i = 0;
	int j = 0;
	int c = 0;
	ppm.setPixel(0,0,0,0,0);
	for(; i <= mheight; ++i){
		for(j=0; j <= mwidth; ++j){
			c = getNumber(i,j);
			if ((c) == 0){
				ppm.setPixel(0,0,0,0,0);
				c +=1;
			}
			else if (c == mMaxValue){
				ppm.setPixel(i,j,63,31,31);
				c +=1;
			}
			else if (c % 8 == 0){
	                        ppm.setPixel(i,j,63,63,63);
				c +=1;

	                }
			else if (c % 8 == 1){
	                        ppm.setPixel(i,j,63,31,31);
				c +=1;

      		        }
			else if (c % 8 == 2){
	                        ppm.setPixel(i,j,63,63,31);
				c +=1;
	                }
			else if (c % 8 == 3){
	                        ppm.setPixel(i,j,31,63,31);
				c +=1;
	                }
			else if (c % 8 == 4){
	                        ppm.setPixel(i,j,0,0,0);
				c +=1;
	                }
			else if (c % 8 == 5){
               		         ppm.setPixel(i,j,31,63,63);
				 c +=1;
               	 	}
			else if (c % 8 == 6){
        	                ppm.setPixel(i,j,31,31,63);
				c +=1;
       	         	}
			else if (c % 8 == 7){
	                        ppm.setPixel(i,j,63,31,63);
				c +=1;
                }}}

	return;


		
			
	}

