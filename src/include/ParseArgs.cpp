#include "ParseArgs.h"
#include <iostream>
#include "Globals.h"
#include <vector>
std::map<std::string, int> option_map
{
  {"default", 0},     {"0", 0},
  {"pagecache", 1},   {"1", 1},
  {"slabobjects", 2}, {"2", 2},
  {"fullcache", 3},   {"3", 3}
};
namespace ParseArgs
{
  void Parse(int argc, const char *argv[], Options &options_, ExitCode & exitcode_)
  {
    SetOptions(options_, false, false, false, false, "default");
    if (argc > 1)
    {
      bool isHelp = false;
      std::vector<std::string> args(argv + 1, argv + argc);
      int index = -1;
      for (std::string &string_ : args)
      {
        index++;
        if (string_.substr(0, 2) == "--")
        {
          std::string switch_ = string_.substr(2);
          if (switch_.empty())
          {
            exitcode_.value = 190;
            exitcode_.message = "No switch provided with '--'.";
            try_catch_exit(exitcode_, options_.isQuiet);
          }
          const std::string lower = to_lower(switch_);
          isHelp                = (lower == "help");
          options_.isQuiet      = (lower == "quiet");
          options_.logStdout    = (lower == "logoutput");
          options_.logStderr    = (lower == "logerrors");
          options_.doDeleteLog  = (lower == "logdelete");
          options_.optionString = (lower == "default")?"default":options_.optionString;
          options_.optionString = (lower == "pagecache")?"default":options_.optionString;
          options_.optionString = (lower == "slabobjects")?"slabobjects":options_.optionString;
          options_.optionString = (lower == "fullcache")?"fullcache":options_.optionString;
          if (lower == "mode")
          {
            if (args[index + 2].empty())
            {
              try
              {
                exitcode_.value = 189;
                exitcode_.message = "Argument for '" + string_ + "' not provided.";
                throw exitcode_;
              }
              catch(ExitCode & error)
              {
                std::cerr << error.message << '\n';
                std::exit(error.value);
              }
            }
            std::string newString = to_lower(args[index + 1]);
            try
            {
              if (option_map.find(newString) == option_map.end())
              {
                exitcode_.value = 188;
                exitcode_.message = "Key '" + newString + "' was not found in modes.";
                throw exitcode_;
              }
            }
            catch(ExitCode & error)
            {
              std::cerr << error.message << '\n';
              std::exit(error.value);
            }
            options_.optionString = newString;
          }
          continue;
        }
        if (string_.substr(0, 1) == "-")
        {
          std::string switch_ = string_.substr(1);
          if (switch_.empty())
          {
            exitcode_.value = 191;
            exitcode_.message = "No switch provided with '-'.";
            try_catch_exit(exitcode_, options_.isQuiet);
          }
          const std::string lower = to_lower(switch_);
          isHelp                = (lower == "h");
          options_.isQuiet      = (lower == "q");
          options_.logStdout    = (switch_ == "l");
          options_.logStderr    = (switch_ == "L");
          options_.doDeleteLog  = (lower == "x");
          options_.optionString = (lower == "default")?"default":options_.optionString;
          options_.optionString = (lower == "pagecache")?"default":options_.optionString;
          options_.optionString = (lower == "slabobjects")?"slabobjects":options_.optionString;
          options_.optionString = (lower == "fullcache")?"fullcache":options_.optionString;
          if (lower == "m")
          {
            if (args[index + 2].empty())
            {
              try
              {
                exitcode_.value = 189;
                exitcode_.message = "Argument for '" + string_ + "' not provided.";
                throw exitcode_;
              }
              catch(ExitCode & error)
              {
                std::cerr << error.message << '\n';
                std::exit(error.value);
              }
            }
            std::string newString = to_lower(args[index + 1]);
            try
            {
              if (option_map.find(newString) == option_map.end())
              {
                exitcode_.value = 188;
                exitcode_.message = "Key '" + newString + "' was not found in modes.";
                throw exitcode_;
              }
            }
            catch(ExitCode & error)
            {
              std::cerr << error.message << '\n';
              std::exit(error.value);
            }
            options_.optionString = newString;
          }
          continue;
        }
      }
      if (isHelp)
      {
        std::cout <<
          "                                                  "
          "\n 'nomediar' - Recursively create or delete        "
          "\n .nomedia placefiller files in empty directories. "
          "\n The default mode is to create.                   "
          "\n                                                  "
          "\n @USAGE:                                          "
          "\n   nomediar[OPTIONS]... [PATH]                    "
          "\n                                                  "
          "\n @OPTIONS:                                        "
          "\n   -h,--help     This help message.               "
          "\n   -q,--quiet    All output is silent.            "
          "\n   -d,--delete   Delete mode.                     "
          "\n                                                  "
          "\n @PATH:                                           "
          "\n   The default path is the current path (./), but "
          "\n   a different path can be provided by adding     "
          "\n   additional arguments which will be joined      "
          "\n   together by a space character to create a new  "
          "\n   path.                                          "
          "\n                                                  \n";
        std::exit(EXIT_SUCCESS);
      }
    }
  }
  void SetOptions
  (
    Options & options_,
    bool isQuiet,
    bool logStdout,
    bool logStderr,
    bool doDeleteLog,
    std::string optionString
  )
  {
    options_.isQuiet      = isQuiet;
    options_.logStdout    = logStdout;
    options_.logStderr    = logStderr;
    options_.doDeleteLog  = doDeleteLog;
    options_.optionString = optionString;
  }
  std::string to_lower(std::string anyCaseString)
  {
    std::string lower;
    const int stringLength = anyCaseString.length();
    for (int index = 0; index < stringLength; index++)
    {
      lower[index] = tolower(anyCaseString[index]);
    }
    lower[stringLength] = '\0';
    return lower.c_str();
  }
  void try_catch_exit(ExitCode & exitcode_, bool isQuiet)
  {
    try
    {
      throw exitcode_;
    }
    catch (ExitCode &ecode)
    {
      if (!isQuiet)
      {
        std::cerr << ecode.message << '\n';
      }
      std::exit(ecode.value);
    }
  }
  void DefaultExitCode (ExitCode & code_)
  {
    code_.value = 0;
    code_.message = "Success.";
  }
};