#include "ParseArgs.h"
#include <iostream>
namespace ParseArgs
{
  void Parse(int argc, const char * argv[], Options & options_)
  {
    SetOptions(options_, false, false, false, "default");
  }
  void SetOptions
  (
    Options & options_,
    bool isQuiet,
    bool logStdout,
    bool logStderr,
    std::string optionString
  )
  {
    options_.isQuiet      = isQuiet;
    options_.logStdout    = logStdout;
    options_.logStderr    = logStderr;
    options_.optionString = optionString;
  }
};