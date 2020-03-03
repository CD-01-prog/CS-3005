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
	os << "\nActions available:\n\n" << std::endl;
        os <<	"read1) Read file into input image 1.\n" << std::endl;
	os <<	"read2) Read file into input image 2.\n" << std::endl;
	os <<	"grid) Configure the grid.\n" << std::endl;
	os <<	"grid-set) Set a single value in the grid.\n" << std::endl;
	os <<	"grid-apply) Use the grid values to set colors in the output image.\n" << std::endl;
	os <<   "julia) Choose to make a Julia set.\n" << std::endl;
	os <<   "mandelbrot) Choose to make a Mandelbrot set.\n" << std::endl;
	os <<	"fractal-plane-size) Set the dimensions of the grid in the complex plane.\n" << std::endl;
	os <<	"fractal-calculate) Calculate the escape values for the fractal.\n" << std::endl;
	os <<	"julia-parameters) Set the parameters of the Julia Set function.\n" << std::endl;
	os <<	"write) Write output image to file.\n" << std::endl;
	os <<	"copy) Copy input image 1 to output image.\n" << std::endl;
	os <<	"red-gray) Set output image from input image 1's grayscale from red.\n" << std::endl;
	os <<	"green-gray) Set output image from input image 1's grayscale from green.\n" << std::endl;
	os <<	"blue-gray) Set output image from input image 1's grayscale from blue.\n" << std::endl;
	os <<	"linear-gray) Set output image from input image 1's grayscale from linear colorimetric.\n" << std::endl;
	os <<	"v-edge) Set output image from input image 1's vertical edge detection\n" << std::endl;
	os <<	"h-edge) Set output image from input image 1's horizontal edge detection\n" << std::endl;
	os <<	"+) Set output image from sum of input image 1 and input image 2\n" << std::endl;
	os <<	"+=) Set input image 1 by adding in input image 2\n" << std::endl;
	os <<	"-) Set output image from difference of input image 1 and input image 2\n" << std::endl;
	os <<	"-=) Set input image 1 by subtracting input image 2\n" << std::endl;
	os <<	"*) Set output image from input image 1 multiplied by a number\n" << std::endl;
	os <<	"*=) Set input image 1 by multiplying by a number\n" << std::endl;
	os <<	"/) Set output image from input image 1 divided by a number\n" << std::endl;
	os <<	"/=) Set input image 1 by dividing by a number\n" << std::endl;
	os <<	"# Comment to end of line\n" << std::endl;
	os <<	"size) Set the size of input image 1\n" << std::endl;
	os <<	"max) Set the max color value of input image 1\n" << std::endl;
	os <<	"channel) Set a channel value in input image 1\n" << std::endl;
	os <<	"pixel) Set a pixel's 3 values in input image 1\n" << std::endl;
	os <<	"clear) Set all pixels to 0,0,0 in input image 1\n" << std::endl;
	os <<	"diamond) Draw a diamond shape in input image 1\n" << std::endl;
	os <<	"circle) Draw a circle shape in input image 1\n" << std::endl;
	os <<	"box) Draw a box shape in input image 1\n" << std::endl;
	os <<	"quiet) Toggle output quieting\n" << std::endl;
	os <<	"run) Run commands from another file\n" << std::endl;
	os <<	"quit) Quit\n\n";
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
void takeAction( std::istream& is, std::ostream& os, const std::string& choice, PPM& input_image1, PPM& input_image2, PPM& output_image, NumberGrid& grid){
	if (choice == "write"){
		writeUserImage(is,os,output_image);
		return;
}
	else if (choice == "grid"){
		configureGrid(is,os,grid);
		return;
	}
	else if (choice == "grid-set"){
		setGrid(is,os,grid);
		return;
	}
	else if (choice == "grid-apply"){
		applyGrid(is,os,grid,output_image);
		return;
	}
	else if (choice == "julia"){
		return;
	}
	else if (choice == "mandelbrot"){
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
	else if (choice == "fractal-plane-size"){
		setFractalPlaneSize(is,os,grid);
		return;
	}

	else if (choice == "fractal-calculate"){
		calculateFractal(is,os,grid);
		return;
	}
	else if (choice == "julia-parameters"){
		setJuliaParameters(is,os,grid);
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
	NumberGrid *gptr = new JuliaSet();
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
			takeAction(is,cloak,choice,input_image1,input_image2,output_image,*gptr);
			if (choice == "julia"){
                        	setJuliaFractal(is,os,gptr);
                	}
		        if (choice == "mandelbrot"){
                	        setMandelbrotFractal(is,os,gptr);
                        }


		}else {
			showMenu(os);
			choice = getChoice(is,os);
			takeAction(is,os,choice,input_image1,input_image2,output_image,*gptr);
			if (choice == "julia"){
                	        setJuliaFractal(is,os,gptr);
                }
	                if (choice == "mandelbrot"){
        	                setMandelbrotFractal(is,os,gptr);
                        }


		}}
	if (gptr != 0){
		delete gptr;}
		

	return 0;
}

void configureGrid(std::istream& is, std::ostream& os, NumberGrid& grid){
	int height, width, max;
	height = getInteger(is,os,"Grid Height? ");
	width = getInteger(is,os,"Grid Width? ");
	max = getInteger(is,os,"Grid Max Value? ");
	grid.setMaxNumber(max);
	grid.setGridSize(height, width);
	return;
}

void setGrid(std::istream& is, std::ostream& os, NumberGrid& grid){
	int row, column, value;
	row = getInteger(is,os,"Grid Row? ");
        column = getInteger(is,os,"Grid Column? ");
        value = getInteger(is,os,"Grid Value? ");
	grid.setNumber(row,column,value);
	return;
}

void applyGrid(std::istream& is, std::ostream& os, NumberGrid& grid, PPM& dst){
	(void) is;
	(void)os;
	grid.setPPM(dst);
	return;
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
	NumberGrid *gptr= new JuliaSet();
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
		takeAction(file,flow,choice,input_image1,input_image2,output_image,*gptr);
	}
	return 0;
}

void setFractalPlaneSize(std::istream& is, std::ostream& os, NumberGrid& grid){
	ComplexFractal *ptr = dynamic_cast<ComplexFractal*>(&grid);
	if(ptr != 0){
		double min_x = getDouble(is,os,"Min X? ");
		double max_x = getDouble(is,os,"Max X? ");
		double min_y = getDouble(is,os,"Min Y? ");
		double max_y = getDouble(is,os,"Max Y? ");	
		ptr -> setPlaneSize(min_x,max_x,min_y,max_y);
	       	return;
	}

	else{
		os << "Not a JuliaSet object. Can't set plane size." << std::endl;
		return;
	}
	
}

void calculateFractal(std::istream& is, std::ostream& os, NumberGrid& grid){
	(void)is;
	(void)os;
	grid.calculateAllNumbers();
	return;
}

void setJuliaParameters(std::istream& is, std::ostream& os, NumberGrid& grid){
	JuliaSet *ptr = dynamic_cast<JuliaSet*>(&grid);
	if(ptr != 0){	
		double a = getDouble(is,os,"Parameter a? ");
		double b = getDouble(is,os,"Parameter b? ");
		ptr -> setParameters(a,b);
		return;
	}
	else{
		os << "Not a JuliaSet object. Can't set parameters." << std::endl;
		return;
	}
	}

void setJuliaFractal(std::istream& is, std::ostream& os, NumberGrid*& grid){
	(void)is;
	(void)os;
	if (grid != 0){
		delete grid;
	}
	grid = new JuliaSet();
	return;
	
}

void setMandelbrotFractal(std::istream& is, std::ostream& os, NumberGrid*& grid){
	(void)is;
	(void)os;
	if (grid != 0){
		delete grid;
	}
	grid = new MandelbrotSet();
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

