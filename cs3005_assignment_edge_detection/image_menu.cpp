#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>
#include "image_menu.h"

std::string getString( std::istream& is, std::ostream& os, const std::string& prompt ){
	std::string color;
	os << prompt;
	is >> color;
	return color;
}

int getInteger( std::istream& is, std::ostream& os, const std::string& prompt ){
	int integer; os << prompt; is >> integer;
	return integer;
}
double getDouble( std::istream& is, std::ostream& os, const std::string& prompt ){
	double number;
	os << prompt;
	is >> number; return number;
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

void showMenu(std::ostream& os){
	os << "\nActions available:\n\nread1) Read file into input image 1.\nread2) Read file into input image 2.\nwrite) Write output image to file.\ncopy) Copy input image 1 to output image.\nred-gray) Set output image from input image 1's grayscale from red.\ngreen-gray) Set output image from input image 1's grayscale from green.\nblue-gray) Set output image from input image 1's grayscale from blue.\nlinear-gray) Set output image from input image 1's grayscale from linear colorimetric.\nv-edge) Set output image from input image 1's vertical edge detection\nh-edge) Set output image from input image 1's horizontal edge detection\n+) Set output image from sum of input image 1 and input image 2\n+=) Set input image 1 by adding in input image 2\n-) Set output image from difference of input image 1 and input image 2\n-=) Set input image 1 by subtracting input image 2\n*) Set output image from input image 1 multiplied by a number\n*=) Set input image 1 by multiplying by a number\n/) Set output image from input image 1 divided by a number\n/=) Set input image 1 by dividing by a number\n# Comment to end of line\nsize) Set the size of input image 1\nmax) Set the max color value of input image 1\nchannel) Set a channel value in input image 1\npixel) Set a pixel's 3 values in input image 1\nclear) Set all pixels to 0,0,0 in input image 1\ndiamond) Draw a diamond shape in input image 1\ncircle) Draw a circle shape in input image 1\nbox) Draw a box shape in input image 1\nquiet) Toggle output quieting\nrun) Run commands from another file\nquit) Quit\n\n";
	return;
}

std::string getChoice(std::istream& is, std::ostream& os){
	std::string choice;
	choice = getString(is,os, "Choice? ");
	return choice;
}

void commentLine(std::istream& is){
	std::string comment;
	getline(is, comment);
	return;
	}
void setSize( std::istream& is, std::ostream& os, PPM& src ){
	int height=0;
	int width=0;
	height = getInteger(is,os, "Height? ");
	width = getInteger(is,os, "Width? ");
	src.setHeight(height);
	src.setWidth(width);
	return;
}
void setMaxColorValue( std::istream& is, std::ostream& os, PPM& src ){
	int max=0;
	max = getInteger(is,os,"Max color value? ");
	src.setMaxColorValue(max);
	return;
}
void setChannel( std::istream& is, std::ostream& os, PPM& src ){
	int row=0 ,column=0 ,channel=0 ,value=0;
	row = getInteger(is,os, "Row? ");
	column = getInteger(is,os, "Column? ");
	channel = getInteger(is,os, "Channel? ");
	value = getInteger(is,os, "Value? ");
	src.setChannel(row,column,channel,value);
	return;
}
void setPixel( std::istream& is, std::ostream& os, PPM& src ){
	int row=0 ,column=0 ,red=0 ,green=0 ,blue=0;
	row = getInteger(is,os, "Row? ");
	column = getInteger(is,os, "Column? ");
	red = getInteger(is,os, "Red? ");
	green = getInteger(is,os, "Green? ");
	blue = getInteger(is,os, "Blue? ");
	src.setPixel(row,column,red,green,blue);
	return;
}
void clearAll(PPM& src){
	int height = src.getHeight();
	int width = src.getWidth();
	int i = 0;
	int j = 0;
	int k = 0;
	for (; i < height; ++i){//goes through all rows   
		for(j = 0; j < width; ++j){// goes through all columns
			for (k = 0; k < 3; ++k){// goes through the 3 channels 0,1,2
				src.setPixel(i,j,0,0,0);
}
}
}
}
void drawDiamond(std::istream& is, std::ostream& os, PPM& src){
	int crow=0 ,ccolumn=0 ,size=0 ,red=0 ,green=0 ,blue=0;
	crow = getInteger(is,os, "Center Row? ");
	ccolumn = getInteger(is,os, "Center Column? ");
	size = getInteger(is,os, "Size? ");
	red = getInteger(is,os, "Red? ");
	green = getInteger(is,os, "Green? ");
	blue = getInteger(is,os, "Blue? ");
	int height = src.getHeight();
	int width = src.getWidth();
	int i = 0;
	int j = 0;
	for (; i <= height; ++i){//goes through all rows
		for(j = 0; j <= width; ++j){// goes through all columns
			if ((std::abs((i-crow)) + std::abs(j-ccolumn)) <= size){
				src.setPixel(i,j,red,green,blue);
}
}
}
}
void drawCircle(std::istream& is, std::ostream& os, PPM& src){
	int crow=0 ,ccolumn=0 ,radius=0 ,red=0 ,green=0 ,blue=0;
	crow = getInteger(is,os, "Center Row? ");
	ccolumn = getInteger(is,os, "Center Column? ");
	radius = getInteger(is,os, "Radius? ");
	red = getInteger(is,os, "Red? ");
	green = getInteger(is,os, "Green? ");
	blue = getInteger(is,os, "Blue? ");
	int height = src.getHeight();
	int width = src.getWidth();
	int i = 0;
	int j = 0;
	for (; i < height; ++i){//goes through all rows
		for(j = 0; j < width; ++j){// goes through all columns
			if (std::sqrt((i-crow)*(i-crow)+(j-ccolumn)*(j-ccolumn)) <= radius){
				src.setPixel(i,j,red,green,blue);
}
}
}
}
void drawBox(std::istream& is, std::ostream& os, PPM& src){
	int trow=0 ,brow=0 ,lcolumn=0 ,rcolumn=0 ,red=0 ,green=0 ,blue=0;
	trow = getInteger(is,os, "Top Row? ");
	lcolumn = getInteger(is,os, "Left Column? ");
	brow = getInteger(is,os, "Bottom Row? ");
	rcolumn = getInteger(is,os, "Right Column? ");
	red = getInteger(is,os, "Red? ");
	green = getInteger(is,os, "Green? ");
	blue = getInteger(is,os, "Blue? ");
	int i = 0;
	int j = 0;
		for(i=trow; i <= brow; ++i){
		for(j=lcolumn; j <= rcolumn; ++j){
			src.setPixel(i,j,red,green,blue);
}
}
}
void readUserImage( std::istream& is, std::ostream& os, PPM& ppm ){
	std::string Ifile;
	Ifile = getString(is,os,"Input filename? ");
	std::ifstream file;
	file.open(Ifile);
	file >> ppm;
	file.close();
	return;
}
void takeAction( std::istream& is, std::ostream& os, const std::string& choice, PPM& input_image1, PPM& input_image2, PPM& output_image){
	if (choice == "write"){
		writeUserImage(is,os,output_image);
		return;
}
	else if (choice == "copy"){
		output_image = input_image1;
		return;
}
	else if(choice == "size"){
		setSize(is,os,input_image1);
		return;
}
	else if(choice == "max"){
		setMaxColorValue(is,os,input_image1);
		return;
}
	else if(choice == "channel"){
		setChannel(is,os,input_image1);
		return;
}
	else if(choice =="pixel"){
		setPixel(is,os,input_image1);
		return;
}
	else if(choice == "clear"){
		clearAll(input_image1);
		return;
}
	else if(choice == "diamond"){
		drawDiamond(is,os,input_image1);
		return;
}
	else if(choice =="circle"){
		drawCircle(is,os,input_image1);
		return;
}
	else if(choice == "box"){
		drawBox(is,os,input_image1);
			return;
}
	else if(choice == "quit"){
		return;
}
	else if (choice.compare(0,1,"#") == 0){
		commentLine(is);
		return;
}
	else if (choice == "read1"){
		readUserImage(is,os,input_image1);
		return;
}
	else if (choice =="red-gray"){
		input_image1.grayFromRed(output_image);
		return;
}
	else if (choice =="green-gray"){
		input_image1.grayFromGreen(output_image);
		return;
}
	else if (choice =="blue-gray"){
		input_image1.grayFromBlue(output_image);
		return;
}
	else if (choice =="linear-gray"){
		input_image1.grayFromLinearColorimetric(output_image);
		return;
}
	else if (choice == "read2"){
		readUserImage(is,os,input_image2);
		return;
}
	else if (choice == "+"){
		plus(is,os,input_image1,input_image2,output_image);
		return;
}
	else if (choice == "+="){
		plusEquals(is,os,input_image1,input_image2);
		return;
}
	else if (choice == "-="){
		minusEquals(is,os,input_image1,input_image2);
		return;
}
	else if (choice == "*="){
		timesEquals(is,os,input_image1);
		return;
}
	else if (choice == "/="){
		divideEquals(is,os,input_image1);
		return;
}
	else if (choice == "-"){
		minus(is,os,input_image1,input_image2,output_image);
		return;
}
	else if (choice == "*"){
		times(is,os,input_image1, output_image);
		return;
}
		else if (choice == "/"){
		divide(is,os,input_image1,output_image);
		return;
	}
	else if ( choice == "v-edge"){
		output_image.findVerticalEdges(input_image1);
		return;
	}
	else if ( choice == "h-edge"){
		output_image.findHorizontalEdges(input_image1);
		return;
	}
	else if( choice == "quiet"){
		return;
	}
	else if( choice == "run" ){
		runFile(is,os,input_image1,input_image2,output_image);
		return;
	}
	else{
		os << "Unknown action '" << choice << "'." << std::endl;
		return;
}
}
int imageMenu(std::istream& is, std::ostream& os){
	PPM input_image1;
	PPM input_image2;
	PPM output_image;
	bool quiet = false;
	std::stringstream cloak;
	int run = 0;
	std::string choice;
	
	while (run == 0){
		if (choice == "quiet"){
			quiet = not quiet;
		}
		if (choice == "quit"){
			run = 1;
			break;}
		else if (quiet == true){
			choice = getChoice(is,cloak);
			takeAction(is,cloak,choice,input_image1,input_image2,output_image);
		}else {
			showMenu(os);
			choice = getChoice(is,os);
			takeAction(is,os,choice,input_image1,input_image2,output_image);
}
}
	return 0;
}
void plusEquals(std::istream& is, std::ostream& os, PPM& src1, const PPM& src2){
	(void)is;
	(void)os;
	src1 += src2;
	return;
}
void minusEquals(std::istream& is, std::ostream& os, PPM& src1, const PPM& src2 ){
	(void)is;
	(void)os;
	src1 -= src2;
	return;
}
void timesEquals(std::istream& is, std::ostream& os, PPM& src){
	double factor = getDouble(is,os,"Factor? ");
	src *= factor;
	return;
}
void divideEquals(std::istream& is, std::ostream& os, PPM& src){
	double factor = getDouble(is,os,"Factor? ");
	src /= factor;
	return;
}
void plus(std::istream& is, std::ostream& os, const PPM& src1, const PPM& src2, PPM& dst){
	(void)is;
	(void)os;
	dst = (src1 + src2);
	return;
}
void minus(std::istream& is, std::ostream& os, const PPM& src1, const PPM& src2, PPM& dst){
	(void)is;
	(void)os;
	dst = src1 - src2;
	return;
}
void times(std::istream& is, std::ostream& os, const PPM& src, PPM& dst){
	double factor = getDouble(is,os,"Factor? ");
	dst = src * factor;
	return;
}
void divide(std::istream& is, std::ostream& os, const PPM& src, PPM& dst){
	double 	factor = getDouble(is,os,"Factor? ");
	dst = src/factor;
	return;
}
int runFile(std::istream& is, std::ostream& os, PPM& input_image1, PPM& input_image2, PPM& output_image){
	std::ifstream file;
	std::string filename, choice;
	filename = getString(is,os,"File? ");
	file.open(filename);
	if(file.fail()){
		return 1;
	}
	std::stringstream flow;
	while(file.good() and choice != "quit"){
		choice = getChoice(file,flow);
		takeAction(file,flow,choice,input_image1,input_image2,output_image);
	}
	return 0;
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
