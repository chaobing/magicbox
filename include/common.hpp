#pragma once

#include <cstring>
#include <dirent.h>
#include <glog/logging.h>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

#define DISABLE_COPY_AND_ASSIGN(classname)                                     \
private:                                                                       \
  classname(const classname &);                                                \
  classname &operator=(const classname &);
