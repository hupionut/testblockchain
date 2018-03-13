
#include <iostream>
#include <string>
#include <time.h>


#include "utils.h"

std::string printDateTime(time_t myTime) {
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&myTime);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}


std::string hexStr(uint8_t *data, int len)
{
  std::string s(len * 2, ' ');
  for (int i = 0; i < len; ++i) {
    s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
  return s;
}



