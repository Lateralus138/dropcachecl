#pragma once
#ifndef PARSEARGS_H
#define PARSEARGS_H
#include <string>
struct Options
{
  bool isQuiet;
  bool logStdout;
  bool logStderr;
  bool doDeleteLog;
  std::string optionString;
};
namespace ParseArgs
{
  extern void Parse(int argc, const char * argv[], Options & opts_);
  extern void SetOptions
  (
    Options & options_,
    bool isQuiet,
    bool logStdout,
    bool logStderr,
    bool doDeleteLog,
    std::string optionString
  );
};
#endif
