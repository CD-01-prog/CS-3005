#include <cstdlib>
#include <iostream>
#include "ColorTable.h"

Color::Color(){
        mR = 0;
        mG = 0;
        mB = 0;
}
Color::Color(const int& red, const int& green, const int& blue){
                mR = red;
                mG = green;
                mB = blue;
}
int Color::getRed() const{
        return mR;
}
int Color::getGreen() const{
        return mG;
}
int Color::getBlue() const{
        return mB;
}
int Color::getChannel(const int& channel) const{
        if (channel == 0){
                return mR;
        }
        else if (channel == 1){
                return mG;
        }
        else if (channel == 2){
                return mB;
        }
        else{
                return -1;
        }
}
void Color::setRed(const int& value){
        if (value < 0){
                return;
        }
        mR = value;
        return;
}
void Color::setGreen(const int& value){
        if (value < 0) {
                return;
        }
        mG = value;
        return;
}
void Color::setBlue(const int& value){
        if (value < 0) {
                return;}
	mB = value;
	return;
}
void Color::setChannel(const int& channel, const int& value){
	if(value < 0 or channel > 2){
		return;
	}
	else if (channel == 0) {
		mR = value;
		return;
	}
	else if (channel == 1) {
		mG = value;
		return;
	}
	else{
		mB = value;
		return;
	}
}
void Color::invert(const int& max_color_value){
	if(mR > max_color_value or mG > max_color_value or mB > max_color_value){
		return;
	}
	mR = max_color_value - mR;
	mG = max_color_value - mG;
	mB = max_color_value - mB;
	return;
}
bool Color::operator==(const Color& rhs) const {
	if(this->getRed() != rhs.getRed()){
		return false;
	}
	else if(this -> getGreen() != rhs.getGreen()){
		return false;
	}
	else if(this-> getBlue() != rhs.getBlue()){
		return false;
	}
	else{
		return true;
	}
}





ColorTable::ColorTable(const size_t& num_color){
	Colors.resize(num_color);
}
size_t ColorTable::getNumberOfColors() const{
	return Colors.size();
}
void ColorTable::setNumberOfColors(const size_t& num_color){
	Colors.resize(num_color);
	return;
}
const Color& ColorTable::operator[](const int& i) const{
	if(static_cast<unsigned int>(i) >= Colors.size() or i < 0){
		static Color ec(-1, -1, -1);
		static Color c(-1, -1, -1);
		c = ec;
		return c;
	}
	else{
		return Colors[i];
	}
}
Color& ColorTable::operator[](const int& i) {
	if(static_cast<unsigned int>(i) >= Colors.size() or i < 0) {
		static Color ec(-1, -1, -1);
		static Color c(-1, -1, -1);
		c = ec;
		return c;
	}
	else {
		return Colors[i];
	}
}
void ColorTable::setRandomColor(const int& max_color_value, const size_t& position){
	if(max_color_value < 0 or position >= Colors.size()){
		return;
	}
	Colors[position].setRed(rand() % (max_color_value + 1));
	Colors[position].setGreen(rand() % (max_color_value + 1));
	Colors[position].setBlue(rand() % (max_color_value + 1));
	return;
}
void ColorTable::insertGradient(const Color& color1, const Color& color2, const size_t& position1, const size_t& position2) {
	if(position1 >= position2 or position1 >= Colors.size() or position2 >= Colors.size()){
		return;
	}
	double steps, rs, gs, bs,r,g,b;
	int i = 0;
	steps = position2 - position1;
	rs = (color2.getRed() - color1.getRed()) /steps;
	gs = (color2.getGreen() - color1.getGreen()) / steps;
	bs = (color2.getBlue() - color1.getBlue()) / steps;
	for(;i <= steps; i++){
		r = color1.getRed() + (rs * i);
		g = color1.getGreen() + (gs * i);
		b = color1.getBlue() + (bs * i);
		Color *c = new Color(r,g,b);
		Colors[position1 + i] = *c;
	}
	}
int ColorTable::getMaxChannelValue() const {
	int biggest,i; 
	biggest = Colors[0].getRed();
	for(i = 0; static_cast<unsigned int>(i) < Colors.size(); i++){
		if(Colors[i].getRed() > biggest){
			biggest = Colors[i].getRed();
		}
		if(Colors[i].getGreen() > biggest){
			biggest = Colors[i].getGreen();
		}
		if(Colors[i].getBlue() > biggest){
			biggest = Colors[i].getBlue();
		}
	}
	return biggest;

}

std::ostream& operator<<(std::ostream& os, const Color& color){
	os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue();
	return os;
}
