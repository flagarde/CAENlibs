#include "CAENVMElib.h"

#include <iostream>

int main()
{
  char version[256];
  CAENVME_SWRelease(version);
  std::cout<<version<<std::endl;
}
