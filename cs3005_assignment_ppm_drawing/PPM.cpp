#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "PPM.h"

PPM::PPM() {
	mwidth = 0;
	mheight = 0;
	mMaxColor = 0;
	image.resize(mwidth*mheight*3);
}

PPM::PPM(const int& height, const int& width){
      mwidth = width;
      mheight = height;
      mMaxColor = 0;
      image.resize(mwidth*mheight*3);
    }

int PPM::getHeight() const{
	return mheight;
    
}
int PPM::getWidth() const{
	return mwidth;
    }

int PPM::getMaxColorValue() const{
	return mMaxColor;
    }

int PPM::getChannel(const int& row, const int& column, const int& channel) const{ 
	int answer;   
	answer = (row*mwidth*3)+(column*3)+channel;
	if(answer < 0 or channel < 0 or channel >= 3 or row >= mheight or row < 0 or column < 0 or column >=  mwidth){
		return -1;
	}else{
		return image[answer];
	}
    }

bool PPM::indexValid(const int& row, const int& column, const int& channel) const{
	if( row >= 0 and row < mheight){
		if( column >= 0 and column < mwidth){
			if( channel >= 0 and channel <= 2){
				return true;}}}
	
	return false;
}

int PPM::index( const int& row, const int& column, const int& channel ) const{
	int index;
	index = (row*mwidth*3+column*3+channel);
	return index;
}

bool PPM::valueValid( const int& value ) const{
	if( value >= 0 and value <= mMaxColor){
		return true;}
	return false;
	}

void PPM::setHeight( const int& height ){
	if( height == mheight){
		return;}
	if( height < 0){
		return;}
	else{
		mheight = height;
		image.resize(mheight * mwidth * 3);
		return;}
}
	

void PPM::setWidth( const int& width ){
        if( width == mwidth){
                return;}
        if( width < 0){
                return;}
	mwidth = width;
        image.resize(mheight * mwidth * 3);
        return;
}


void PPM::setMaxColorValue( const int& max_color_value ){
        if( max_color_value == mMaxColor){
                return;}
        if( max_color_value < 0 or max_color_value > 255){
                return;}
        mMaxColor = max_color_value;
        return;
}


void PPM::setChannel( const int& row, const int& column, const int& channel, const int& value ){
	if (valueValid(value)){
		if (indexValid(row,column,channel)){
			image[row*mwidth*3+column*3+channel] = value;

		}	
	}
	return;
}
	

void PPM::setPixel( const int& row, const int& column, const int& red, const int& green, const int& blue ){
	setChannel(row,column,0,red);
	setChannel(row,column,1,green);
	setChannel(row,column,2,blue);
	return;
}

std::ostream& operator<< (std::ostream& os, const PPM& rhs){
	int i = 0;
	int j = 0;
	int k = 0;
	int h;
	int w;
	int m;
	h = rhs.getHeight();
	w = rhs.getWidth();
	m = rhs.getMaxColorValue();
	os << "P6" << " " << w << " " << h << " " << m << '\n';
	for (; i < h; ++i){//goes through all rows
		for(j = 0; j < w; ++j){// goes through all columns
			for (k = 0; k < 3; ++k){// goes through the 3 channels 0,1,2
			char point = rhs.getChannel(i,j,k);
			os.write((char *) &point, sizeof(char));
			}
		}
	}
	return os;
}
