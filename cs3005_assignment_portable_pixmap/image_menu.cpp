#include <iostream>
#include <string>
#include "image_menu.h"
#include <fstream>
#include "PPM.h"

std::string getString( std::istream& is, std::ostream& os, const std::string& prompt ){
  std::string color;
  os << prompt;
  is >> color;
  return color;
}

int getInteger( std::istream& is, std::ostream& os, const std::string& prompt ){
  int integer;
  os << prompt;
  is >> integer;
  return integer;
}
double getDouble( std::istream& is, std::ostream& os, const std::string& prompt ){
  double number;
  os << prompt;
  is >> number;
  return number;
}

void writeUserImage(std::istream& is, std::ostream& os, const PPM& p){
	std::string file;
	file = getString(is, os, "Output filename? ");
	std::ofstream targetF;
	targetF.open(file, std::ios::binary);
	targetF << p;
	targetF.close();
	return;	

}

int assignment2(std::istream& is, std::ostream& os){
  	int height;
  	int width;
  	height = getInteger(is, os, "Image height? ");
  	width = getInteger(is, os, "Image width? ");
 	PPM image(height, width);
	image.setMaxColorValue((height+width)/3);
	int m = image.getMaxColorValue();
	int i = 0;
	int j = 0;
	int k = 0;
	int red;
	int green;
	int blue;
	for (; i < height; ++i){//goes through all rows
                for(j = 0; j < width; ++j){// goes through all columns
                        for (k = 0; k < 3; ++k){// goes through the 3 channels 0,1,2
                        if (i < height/2){
				red = 0;
			}else{
				red = m;
			}
			if (j < width/2){
				blue = 0;
			}else{
				blue = m;
			}
			green = (i + j)%(m+1);
			image.setPixel(i,j,red,green,blue);
				
                        }
                }
        }


	writeUserImage(is,os,image);


    
 return 0; 
}

/*
int assignment1( std::istream& is, std::ostream& os ){
  std::string color;
  color = getString(is, os, "What's your favorite color?");

  int integer;
  integer = getInteger(is, os,  "What's your favorite integer?");

  double number;
  number = getDouble(is, os, "What's your favorite number?" );

  int i = 1;
  for(; i < integer; i++ ){
    os << i << ' ' << color << ' ' << number << std::endl;
    }

  return integer;
}
*/
