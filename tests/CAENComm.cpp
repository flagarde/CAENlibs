#include "CAENComm.h"

#include <iostream>

int main()
{
  char version[256];
  CAENComm_SWRelease(version);
  std::cout<<version<<std::endl;
}
