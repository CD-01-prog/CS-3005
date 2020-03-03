#ifndef  image_menu
#define image_menu
#include <iostream>
#include <string>
#include "PPM.h"

int assignment2(std::istream& is, std::ostream& os);

void writeUserImage(std::istream& is, std::ostream& os, const PPM& p);

std::string getString( std::istream& is, std::ostream& os, const std::string& prompt );

int getInteger( std::istream& is, std::ostream& os, const std::string& prompt );

double getDouble( std::istream& is, std::ostream& os, const std::string& prompt );

/*int assignment1( std::istream& is, std::ostream& os );*/
#endif
