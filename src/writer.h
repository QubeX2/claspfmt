#ifndef WRITER_H
#define WRITER_H

#include "format.h"

class Writer {

public:
  static void put(std::vector<Section> sections, std::string filename); 
};

#endif
