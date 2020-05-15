#pragma once
#include "common.hpp"

class Point {
public:
  Point();
  Point(int x, int y);
  ~Point();
  void show();

private:
  int xvalue_;
  int yvalue_;

  DISABLE_COPY_AND_ASSIGN(Point);
};
