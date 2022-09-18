#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H
#include <string>
struct ExitCode
{
  int value;
  std::string message;
};
namespace Globals
{
  extern std::string to_lower(std::string anyCaseString);
  extern std::string time_utc();
};
namespace Globals
{
  extern void DefaultExitCode(ExitCode &code_);
};
#endif
