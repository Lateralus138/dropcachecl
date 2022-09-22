#pragma once
#ifndef PARSEARGS_H
#define PARSEARGS_H
#include <string>
#include <map>
struct ExitCode
{
  int value;
  std::string message;
};
struct Options
{
  bool isQuiet;
  bool logStdout;
  bool logStderr;
  bool doDeleteLog;
  std::string optionString;
};
extern std::map<std::string, int> option_map;
namespace ParseArgs
{
  extern void Parse(int argc, const char * argv[], Options & opts_, ExitCode & exitcode_);
  extern void SetOptions
  (
    Options & options_,
    bool isQuiet,
    bool logStdout,
    bool logStderr,
    bool doDeleteLog,
    std::string optionString
  );
  std::string to_lower(std::string anyCaseString);
  void try_catch_exit(ExitCode &exitcode_, bool isQuiet);
  void DefaultExitCode(ExitCode &code_);
};
#endif
