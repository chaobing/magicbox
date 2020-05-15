#include "common.hpp"

#define MAGIC_BUILD_YEAR                                                       \
  ((__DATE__[7] - '0') * 1000 + (__DATE__[8] - '0') * 100 +                    \
   (__DATE__[9] - '0') * 10 + (__DATE__[10] - '0'))

// version related
#define MAGIC_MAJOR_VERSION 0
#define MAGIC_MINOR_VERSION 1
#define MAGIC_VERSION_NUMBER                                                   \
  ((MAGIC_MAJOR_VERSION << 8) | (MAGIC_MINOR_VERSION))
#define MAGIC_MAJOR_NUMBER(ver) (ver >> 8)
#define MAGIC_MINOR_NUMBER(ver) (ver & 0xff)
#define MAGIC_COPYRIGHT_STRING(year)                                           \
  (("Copyright @" + std::to_string(year) +                                     \
    " GreenHand. All Rights Reserved.\n")                                      \
       .c_str())

#ifndef MAGIC_TAG_branch
#define MAGIC_TAG_branch "unkonwn"
#endif

#ifndef MAGIC_TAG_commit_id
#define MAGIC_TAG_commit_id "unkonwn"
#endif

#ifndef MAGIC_TAG_commit_date
#define MAGIC_TAG_commit_date "unkonwn"
#endif
