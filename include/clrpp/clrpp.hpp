#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define CLRPP_EXPORT __declspec(dllexport)
#else
  #define CLRPP_EXPORT
#endif

CLRPP_EXPORT void clrpp();
CLRPP_EXPORT void clrpp_print_vector(const std::vector<std::string> &strings);
