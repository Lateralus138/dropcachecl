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
  extern std::string to_lower(std::string anyCaseString);
  extern void try_catch_exit(ExitCode &exitcode_, bool isQuiet);
  extern void DefaultExitCode(ExitCode &code_);
  extern void switch_check(std::string switch_, ExitCode &exitcode_, Options &options_);
  extern void set_check_options(Options &options_, std::string lower, std::string switch_);
};
#endif
