#include "Point.hpp"

Point::Point(){
	xvalue_ = 0;
	yvalue_ = 0;
}

Point::Point(int x, int y){
	xvalue_ = x;
	yvalue_ = y;	
}

Point::~Point(){
	std::cout<<"deconstruct..."<<std::endl;
}

void Point::show(){
	std::cout<<"("<<xvalue_<<", "<<yvalue_<<")"<<std::endl;	
}
