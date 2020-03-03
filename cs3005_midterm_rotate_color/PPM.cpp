#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
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
	int answer;                                                                                                          answer = (row*mwidth*3)+(column*3)+channel;
	if(answer < 0 or channel < 0 or channel >= 3 or row >= mheight or row < 0 or column < 0 or column >=  mwidth){
		return -1;
	}else{
		return image[answer];                                                                                        }                                                                                                                }

bool PPM::indexValid(const int& row, const int& column, const int& channel) const{
	if( row >= 0 and row < mheight){
		if( column >= 0 and column < mwidth){
			if( channel >= 0 and channel <= 2){                                                                                          return true;}}}
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

void PPM::grayFromChannel( PPM& dst, const int& src_channel ) const{
	int height = this -> getHeight();
	int width = this -> getWidth();
	int max = this -> getMaxColorValue();
	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max);
	int i = 0;
	int j = 0;
	for (; i < height; ++i){//goes through all rows
		for(j = 0; j < width; ++j){// goes through all columns
			int color = this -> getChannel(i,j,src_channel);
			dst.setPixel(i,j,color,color,color);
}
}
	return;
}

void PPM::grayFromRed( PPM& dst ) const{
	grayFromChannel(dst ,0);
	return;
}

void PPM::grayFromGreen( PPM& dst ) const{
	grayFromChannel(dst,1);
	return;
}

void PPM::grayFromBlue( PPM& dst ) const{
	grayFromChannel(dst,2);
	return;
}

double PPM::linearColorimetricPixelValue( const int& row, const int& column ) const{
	int red = this -> getChannel(row,column,0);
	int green =  this -> getChannel(row,column,1);
	int blue =  this -> getChannel(row,column,2);
	double brightness = .2126*red+.7152*green+.0722*blue;
	return brightness;
}

void PPM::grayFromLinearColorimetric( PPM& dst ) const{
	int h = this -> getHeight();
	int w = this -> getWidth();
	int height = this -> getHeight();
	int width = this -> getWidth();
	int max = this -> getMaxColorValue();
	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max);
	int i = 0;
	int j = 0;
	for (; i < h; ++i){//goes through all rows
		for(j = 0; j < w; ++j){// goes through all columns
			int color = this -> linearColorimetricPixelValue(i,j);
			dst.setPixel(i,j,color,color,color);
}
}
	return;
}

void PPM::rotateColorFilter(PPM& dst) const{
	int height = this -> getHeight();
        int width = this -> getWidth();
        int max = this -> getMaxColorValue();
        dst.setHeight(height);
        dst.setWidth(width);
        dst.setMaxColorValue(max);
	int i = 0;
	int j = 0;
	int red,green,blue;
	for (; i < height; ++i){//goes through all rows
                for(j = 0; j < width; ++j){// goes through all columns
			red = this -> getChannel(i,j,0);
			green = this -> getChannel(i,j,1);
			blue = this -> getChannel(i,j,2);
			dst.setPixel(i,j,green,blue,red);
		}
	}
	return;
}

std::istream& operator >> (std:: istream& is, PPM& rhs ){
	int height, width, max;
	int filler = 0;
	char * null1 = new char [filler];
	is >> null1;
	is >> width;
	is >> height;
	is >> max;
	is.read(null1,1);
	unsigned char rawpoint;
	int i = 0;
	int j = 0;
	int k = 0;
	rhs.setHeight(height);
	rhs.setWidth(width);
	rhs.setMaxColorValue(max);
	for (; i < height; ++i){//goes through all rows
		for(j = 0; j < width; ++j){// goes through all columns
			for (k = 0; k < 3; ++k){// goes through the 3 channels 0,1,2
				is.read(null1,1);
				rawpoint = null1[0];
				rhs.setChannel(i,j,k,rawpoint);
}
}
}
	return is;
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

bool PPM::operator==( const PPM& rhs ) const{
	if (rhs.getHeight() * rhs.getWidth() == this -> getHeight() * this -> getWidth()){
		return true;
}
	return false;
}

bool PPM::operator!=( const PPM& rhs ) const{
	if (rhs.getWidth() * rhs.getHeight() != this -> getWidth() * this -> getHeight()){
		return true;
}
	return false;
}

bool PPM::operator<( const PPM& rhs ) const{
	if (rhs.getWidth() * rhs.getHeight() > this -> getWidth() * this -> getHeight()){
		return true;
}
	return false;
}

bool PPM::operator<=( const PPM& rhs ) const{
	if (rhs.getWidth() * rhs.getHeight() >= this -> getWidth() * this -> getHeight()){
		return true;
}
	return false;
}

bool PPM::operator>( const PPM& rhs ) const{
	if (rhs.getWidth() * rhs.getHeight() < this -> getWidth() * this -> getHeight()){
		return true;
}
	return false;
}

bool PPM::operator>=( const PPM& rhs ) const{
	if (rhs.getWidth() * rhs.getHeight() <= this -> getWidth() * this -> getHeight()){
		return true;
}
	return false;
}
PPM& PPM::operator+=( const PPM& rhs ){
	int h = rhs.getHeight();
	int w =	 rhs.getWidth();
	int m = rhs.getMaxColorValue();
	int i = 0;
	int j = 0;
	int red = 0;
	int green = 0;
	int blue = 0;
	int Tred = 0;
	int Tgreen = 0;
	int Tblue = 0;
	for (; i < h; ++i){//goes through all rows
		for(j = 0; j < w; ++j){// goes through all columns
			red = rhs.getChannel(i,j,0);
			green = rhs.getChannel(i,j,1);
			blue = rhs.getChannel(i,j,2);
			Tred = this -> getChannel(i,j,0);
			Tgreen = this -> getChannel(i,j,1);
			Tblue = this -> getChannel(i,j,2);
			red = Tred + red;
			green = Tgreen + green;
			blue = Tblue + blue;

			if(red > m){
				red = m;
}
			if(blue > m){
				blue = m;
}
			if (green > m){
				green = m;
}
			if(red < 0){
				red = 0;
}
			if(blue < 0){
				blue = 0;
}
			if (green < 0){
				green = 0;
}				
			this -> setPixel(i,j,red,green,blue);
}}
	return *this;
}

PPM& PPM::operator-=( const PPM& rhs ){
	int h = rhs.getHeight();
	int w = rhs.getWidth();
	int i = 0;
	int j = 0;
	int red = 0;
	int green = 0;
	int blue = 0;
	int Tred = 0;
	int Tgreen = 0;
	int Tblue = 0;
	for (; i < h; ++i){//goes through all rows
		for(j = 0; j < w; ++j){// goes through all columns
			red = rhs.getChannel(i,j,0);
			green = rhs.getChannel(i,j,1);
			blue = rhs.getChannel(i,j,2);
			Tred = this -> getChannel(i,j,0);
			Tgreen = this -> getChannel(i,j,1);
			Tblue = this -> getChannel(i,j,2);
			red = Tred-red;
			blue = Tblue-blue;
			green = Tgreen-green;
	
			if(red < 0){
				red = 0;
}
			if(blue < 0){
				blue = 0;
}
			if (green < 0){
				green =	 0;
}
			this -> setPixel(i,j,red,green,blue);}}
	return *this;
}

PPM& PPM::operator*=( const double& rhs ){
	int h = this -> getHeight();
	int w = this -> getWidth();
	int m = this -> getMaxColorValue();
	int i = 0;
	int j = 0;
	double red = 0;
	double green = 0;
	double blue = 0;
	for (; i < h; ++i){//goes through all rows
		for(j = 0; j < w; ++j){// goes through all columns
			red = rhs;
			green = rhs;
			blue = rhs;
			red *= (double)this -> getChannel(i,j,0);
			green *= (double)this -> getChannel(i,j,1);
			blue *= (double)this -> getChannel(i,j,2);
			if(red > m){
				red = m;
}
			if(blue > m){
				blue = m;
}
			if (green > m){
				green = m;
}
			if(red < 0){
				red = 0;
}
			if(blue < 0){
				blue = 0;
}
			if (green < 0){
				green = 0;
}
			this -> setPixel(i,j,red,green,blue);}}
	return *this;
}

PPM& PPM::operator/=( const double& rhs ){
	int h = this -> getHeight();
	int w = this -> getWidth();
	int max = this -> getMaxColorValue();
	int i = 0;
	int j = 0;
	double red = 0;
	double green = 0;
	double blue = 0;
	int Tred = 0;
	int Tgreen = 0;
	int Tblue = 0;
	for (; i < h; ++i){//goes through all row
		for(j = 0; j < w; ++j){// goes through all columns
			red = rhs;
			green = rhs;
			blue = rhs;
			Tred = (double)this -> getChannel(i,j,0);
			Tgreen = (double)this -> getChannel(i,j,1);
			Tblue = (double)this -> getChannel(i,j,2);
			red = Tred/red;
			green = Tgreen/green;
			blue = Tblue/blue;
			if(red > max){
				red = max;
}
			if(blue > max){
				blue = max;
}
			if (green > max){
				green = max;
}
			if(red < 0){
				red = 0;
}
			if(blue < 0){
				blue = 0;
}
			if (green < 0){
				green = 0;
}
			this -> setPixel(i,j,red,green,blue);
}}
	return *this;
}

PPM PPM::operator+( const PPM& rhs ) const{
	PPM dst;
	int height = this -> getHeight();
	int width = this -> getWidth();
	int max = this -> getMaxColorValue();
	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max);
	int h = height;
	int w = width;
	int m = max;
	int i = 0;
	int j = 0;
	int red = 0;
	int green = 0;
	int blue = 0;
	int Tred;
	int Tgreen;
	int Tblue;
	for (; i < h; ++i){//goes through all rows
		for(j = 0; j < w; ++j){// goes through all columns
			red = rhs.getChannel(i,j,0);
			green = rhs.getChannel(i,j,1);
			blue = rhs.getChannel(i,j,2);
			Tred = this -> getChannel(i,j,0);
			Tgreen = this -> getChannel(i,j,1);
			Tblue = this -> getChannel(i,j,2);
			red = Tred + red;
			green = Tgreen + green;
			blue = Tblue + blue;
			if(red > m){
				red = m;
}	
			if(blue > m){
				blue = m;
}
			if (green > m)
			{	green = m;
}	
			if(red < 0){
				red = 0;
}
			if(blue < 0){
				blue = 0;
}
			if (green < 0){
				green = 0;
}
			dst. setPixel(i,j,red,green,blue);
}}		
	return dst;
}

PPM PPM::operator-( const PPM& rhs ) const{
	PPM dst;
	int height = this -> getHeight();
	int width = this -> getWidth();
	int max = this -> getMaxColorValue();
	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max);
	int h = height;
	int w = width;
	int i = 0;
	int j = 0;
	int red = 0;
	int green = 0;
	int blue = 0;
	int Tred;
	int Tgreen;
	int Tblue;
	for (; i < h; ++i){//goes through all rows
		for(j = 0; j < w; ++j){// goes through all columns
			red = rhs.getChannel(i,j,0);
			green = rhs.getChannel(i,j,1);
			blue = rhs.getChannel(i,j,2);
			Tred = this -> getChannel(i,j,0);
			Tgreen = this -> getChannel(i,j,1);
			Tblue = this -> getChannel(i,j,2);
			red = Tred - red;
			green = Tgreen - green;
			blue = Tblue - blue;
			if(red > max){
				red = max;
			}
			if(blue > max){
				blue = max;
			}
			if (green > max){
				green = max;
			}
			if (red < 0){
				red = 0;
			}
			if(blue < 0){
				blue = 0;
			}
			if (green < 0){
				green = 0;
			}
			dst. setPixel(i,j,red,green,blue);
}}
	return dst;
}

PPM PPM::operator*( const double& rhs ) const{
	PPM dst;
	int height = this -> getHeight();
	int width = this -> getWidth();
	int max = this -> getMaxColorValue();
	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max);
	int h = height;
	int w = width;
	int i = 0;
	int j = 0;
	double red = 0;
	double green = 0;
	double blue = 0;
	for (; i < h; ++i){//goes through all rows
		for(j = 0; j < w; ++j){// goes through all columns
			red = rhs;
			green = rhs;
			blue = rhs;
			red *= this -> getChannel(i,j,0);
			green *= this -> getChannel(i,j,1);
			blue *= this -> getChannel(i,j,2);
			if(red > max){
				red = max;
			}
			if(blue > max){
				blue = max;
			}
			if (green > max){
				green = max;
			}
			if(red < 0){
				red = 0;
			}
			if(blue < 0){
				blue = 0;
			}
			if (green < 0){
				green = 0;
			}
			dst. setPixel(i,j,red,green,blue);
			}	
	}
	return dst;
}

PPM PPM::operator/( const double& rhs ) const{
	PPM dst;
	int height = this -> getHeight();
	int width = this -> getWidth();
	int max = this -> getMaxColorValue();
	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max);
	int i = 0;
	int j = 0;
	double red = 0;
	double green = 0;
	double blue = 0;
	double Tred;
	double Tgreen;
	double Tblue;
	for (; i < height; ++i){//goes through all rows
		for(j = 0; j < width; ++j){// goes through all columns
			red = rhs;
			green = rhs;
			blue = rhs;
			Tred = this -> getChannel(i,j,0);
			Tgreen = this -> getChannel(i,j,1);
			Tblue = this -> getChannel(i,j,2);
			red = Tred/red;
			green = Tgreen/green;
			blue = Tblue/blue;
			if(red > max){
				red = max;
}
			if(blue > max){
				blue = max;
}
			if (green > max){
				green = max;
}
			if(red < 0){
				red = 0;
}
			if(blue < 0){
				blue = 0;
}
			if (green < 0){
				green = 0;
}
			dst. setPixel(i,j,red,green,blue);
}}
	return dst;
}


int PPM::edgePixelValue(const int& row1, const int& column1, const int& row2, const int& column2) const{
	double color1;
	double color2;
	color1 = linearColorimetricPixelValue(row1,column1);
	color2 = linearColorimetricPixelValue(row2,column2);
	double answer;
	int max = this -> getMaxColorValue();
	answer = abs(color1 - color2);
	std::cout << answer << std::endl;
	if (answer >= .1 * max){
		return max;
	}	
	return 0;
}
void PPM::findVerticalEdges(PPM& dst) const{
	int height = this -> getHeight();
	int width = this -> getWidth();
	int max = this -> getMaxColorValue();
	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max);
	int i = 0;
	int j = 0;
	double color;
	for (; i < height; ++i){//goes through all rows
		for(j = 0; j < width; ++j){// goes through all columns
			if (j == 0){
				dst.setPixel(i,j,0,0,0);
			}
			else{
				color = edgePixelValue(i,j,i,j-1);
				dst.setPixel(i,j,color,color,color);}}}
	return;	
}
void PPM::findHorizontalEdges(PPM& dst) const{
	int height = this -> getHeight();
	int width = this -> getWidth();
	int max = this -> getMaxColorValue();
	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max);
	int i = 0;
	int j = 0;
	int color;
	for (; i < height; ++i){
		for ( j = 0; j < width; ++j) {
			if(i ==0){
				dst.setPixel(i,j,0,0,0);
			}
			else{
				color = edgePixelValue(i,j,i-1,j);
				dst.setPixel(i,j,color,color,color);
			}
			}
			}
	return;
}
