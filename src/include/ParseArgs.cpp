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
    SetOptions(options_, false, false, false, false, "default", "/var/log/dropcachecl.log");
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
          switch_check(switch_, exitcode_, options_);
          const std::string lower = to_lower(switch_);
          isHelp                  = (lower == "help");
          check_set_options(options_, lower, switch_);
          if (lower == "mode")
          {
            if (args[index + 2].empty())
            {
              exitcode_.value = 189;
              exitcode_.message = "Argument for '" + string_ + "' not provided.";
              try_catch_exit(exitcode_, options_.isQuiet);
            }
            std::string newString = to_lower(args[index + 1]);
            if (option_map.find(newString) == option_map.end())
            {
              exitcode_.value = 188;
              exitcode_.message = "Key '" + newString + "' was not found in modes.";
              try_catch_exit(exitcode_, options_.isQuiet);
            }
            options_.optionString = newString;
          }
          continue;
        }
        if ((string_.substr(0, 1) == "-") && (string_.substr(1, 1) != "-"))
        {
          std::string switch_ = string_.substr(1);
          switch_check(switch_, exitcode_, options_);
          const std::string lower = to_lower(switch_);
          isHelp                = (lower == "h");
          check_set_options(options_, lower, switch_);
          if (lower == "m")
          {
            if (args[index + 2].empty())
            {
              exitcode_.value = 189;
              exitcode_.message = "Argument for '" + string_ + "' not provided.";
              try_catch_exit(exitcode_, options_.isQuiet);
            }
            std::string newString = to_lower(args[index + 1]);
            if (option_map.find(newString) == option_map.end())
            {
              exitcode_.value = 188;
              exitcode_.message = "Key '" + newString + "' was not found in modes.";
              try_catch_exit(exitcode_, options_.isQuiet);
            }
            options_.optionString = newString;
          }
          continue;
        }
      }
      if (isHelp)
      {
        std::cout << "                                                  "
                     "\n 'Drop Cache CL' - Edit the '/proc/sys/vm/drop-   "
                     "\n  _caches' file with some options.                "
                     "\n                                                  "
                     "\n @USAGE:                                          "
                     "\n   dropcachecl [SWITCH] [OPTION [ARGUMENT]]...    "
                     "\n                                                  "
                     "\n @SWITCH:                                         "
                     "\n   -h,--help         This help message.           "
                     "\n   -d,--default      Set to [default      :0].    "
                     "\n   -p,--pagecache    Set to [pagecache    :1].    "
                     "\n   -s,--slabobjects  Set to [slabobjects  :2].    "
                     "\n   -f,--fullcache    Set to [fullcache    :3].    "
                     "\n   -l,--logoutput    Log output to the log file.  "
                     "\n   -L,--logerrors    Log errors to the log file.  "
                     "\n   -x,--logdelete    Delete the log file. The log "
                     "\n                     file is located at:          "
                     "\n                     '/var/log/dropcachecl.log'   "
                     "\n                                                  "
                     "\n @OPTION:                                         "
                     "\n   -m,--mode         Set the mode by name or      "
                     "\n                     value. This is an            "
                     "\n                     alternative method to the    "
                     "\n                     switches [-d,-p,-s,-f].      "
                     "\n                                                  "
                     "\n @ARGUMENT:                                       "
                     "\n   MODE: One of the modes accessible in the       "
                     "\n   drop_caches file:                              "
                     "\n     Default:       \"default\" or 0                "
                     "\n     Page Cache:    \"pagecahe\" or 1               "
                     "\n     Slab Objects:  \"slobobjects\" or 2            "
                     "\n     Full Cache:    \"fullcache\" or 3              "
                     "\n                                                  \n";
        std::exit(EXIT_SUCCESS);
      }
    }
  }
  void SetOptions
  (
      Options &options_,
      bool isQuiet,
      bool logStdout,
      bool logStderr,
      bool doDeleteLog,
      std::string optionString,
      std::string logFile
  )
  {
    options_.isQuiet      = isQuiet;
    options_.logStdout    = logStdout;
    options_.logStderr    = logStderr;
    options_.doDeleteLog  = doDeleteLog;
    options_.optionString = optionString;
    options_.logFile      = logFile;
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
  void switch_check(std::string switch_, ExitCode &exitcode_, Options &options_)
  {
    if (switch_.empty())
    {
      exitcode_.value = 191;
      exitcode_.message = "No switch provided with '-'.";
      try_catch_exit(exitcode_, options_.isQuiet);
    }
  }
  void check_set_options(Options & options_, std::string lower, std::string switch_)
  {
    options_.isQuiet      = (((lower == "q")    || (lower == "quiet"))      ?true:options_.isQuiet);
    options_.logStdout    = (((switch_ == "l")  || (lower == "logoutput"))  ?true:options_.logStdout);
    options_.logStderr    = (((switch_ == "L")  || (lower == "logerrors"))  ?true:options_.logStderr);
    options_.doDeleteLog  = (((lower == "x")    || (lower == "logdelete"))  ?true:options_.doDeleteLog);
    options_.optionString = (lower == "default")      ?"default"      :options_.optionString;
    options_.optionString = (lower == "pagecache")    ?"pagecache"    :options_.optionString;
    options_.optionString = (lower == "slabobjects")  ?"slabobjects"  :options_.optionString;
    options_.optionString = (lower == "fullcache")    ?"fullcache"    :options_.optionString;
    options_.optionString = (lower == "d")  ?"default"      :options_.optionString;
    options_.optionString = (lower == "p")  ?"pagecache"    :options_.optionString;
    options_.optionString = (lower == "s")  ?"slabobjects"  :options_.optionString;
    options_.optionString = (lower == "f")  ?"fullcache"    :options_.optionString;
  }
  void check_delete_log(Options &options)
  {
    if (options.doDeleteLog)
    {
      if (FILE * open_file = fopen(options.logFile.c_str(), "r"))
      {
        fclose(open_file);
        if (remove(options.logFile.c_str()) == 0)
        {
          if (!options.isQuiet)
          {
            const std::string message =
              "Log file '" +
              options.logFile +
              "' deleted successfully.";
            std::cout << message << '\n';
          }
        }
        else
        {
          if (!options.isQuiet)
          {
            const std::string message = "Log file '" + options.logFile + "' could not be deleted.";
            std::cerr << message << '\n';
          }
        }
      }
      else
      {
        if (!options.isQuiet)
        {
          const std::string message = "Log file '" + options.logFile + "' doesn't exist.";
          std::cout << message << '\n';
        }
      }
      std::exit(0);
    }
  }
}