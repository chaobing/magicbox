#pragma once

#include <iostream>

class Point{
	public:
		Point();
		Point(int x, int y);
		~Point();
		void show();
	private:
		int xvalue_;
		int yvalue_;
};

