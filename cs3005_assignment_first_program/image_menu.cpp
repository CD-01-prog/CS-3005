#include <iostream>
#include <string>
#include "image_menu.h"

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

int assignment1( std::istream& is, std::ostream& os ){
  std::string color;
  color = getString(is, os, "What's your favorite color? ");

  int integer;
  integer = getInteger(is, os,  "What's your favorite integer? ");

  double number;
  number = getDouble(is, os, "What's your favorite number? " );

  int i = 1;
  for(; i <(integer + 1); i++ ){
	os << i << ' ' << color << ' ' << number << std::endl;
    }

  return integer;
}
