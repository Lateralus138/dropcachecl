// -----------------------------------------------
// 'dropcachecl' - Edit "drop-caches" file
// located at '/proc/sys/vm/drop-caches'
// Copyright © 2022
// Ian Pride @ New Pride Software/Services
// Sat 17 Sep 2022 13:03:04 CST
// -----------------------------------------------
#include <iostream>
#include <fstream>
#include <map>
#include <filesystem>
#include "Globals.h"
#include <pwd.h>
#include "ParseArgs.h"
int main(int argc, const char *argv[])
{
  // TODO Add switches
  // -h,--help          // This HELP message
  // -l,--logoutput     // enable stdout logging
  // -L,--logerrors     // enable stderr logging
  // -q,--quiet         // Non-verbose output
  // -x,--logdelete     // Delete '/var/log/dropcachecl.log'
  // -d,--default       // 0
  // -p,--pagecache     // 1
  // -s,--slabobjects   // 2
  // -f,--fullcache     // 3
  // -m,--mode          // specify mode by name or int from the option_map
  Options options_;
  // ParseArgs::SetOptions(options_, false, false, false, "default");
  ParseArgs::Parse(argc, argv, options_);

  // ParseArgs::SetOptions
  // (
  //   options_,
  //   options_.isQuiet,
  //   !options_.logStdout,
  //   !options_.logStderr,
  //   "fullcache"
  // );

  ExitCode genericCode;
  Globals::DefaultExitCode(genericCode);
  
  std::ofstream logger;
  if (options_.logStderr || options_.logStdout)
  {
    logger.open("/var/log/dropcachecl.log", std::ios_base::app);
  }
  
  const std::filesystem::path dropCachesPath("/proc/sys/vm/drop_caches");
  // TODO put map in ParseArgs
  std::map<std::string, int> option_map =
  {
    {"default", 0},     {"0", 0},
    {"pagecache", 1},   {"1", 1},
    {"slabobjects", 2}, {"2", 2},
    {"fullcache", 3},   {"3", 3}
  };
  std::ofstream ofile(dropCachesPath.native().c_str());
  if (ofile.is_open())
  {
    ofile << option_map[options_.optionString];
    if (options_.logStdout && logger.is_open())
    {
      std::string logMessage
      (
        "Drop Cache set to [" + std::to_string(option_map[options_.optionString]) +
        ":" + options_.optionString + "] @ " + Globals::time_utc() + "\n"
      );
      logger << logMessage;
    }
    ofile.close();
  }
  else
  {
    try
    {
      genericCode.value = 2;
      genericCode.message =
        std::string
        (
          "Could not open '" +
          dropCachesPath.native() +
          "' for writing.\nDo you have root privileges?"
        );
      throw genericCode;
    }
    catch(ExitCode & code)
    {
      std::cerr << code.message << '\n';
      if (options_.logStderr && logger.is_open())
      {
        const std::string logMessage =
          "Could not open'" +
          dropCachesPath.native() + "' for writing @ " +
          Globals::time_utc() + "\n";
        logger << logMessage;
        logger.close();
      }
      std::exit(code.value);
    }
  }
  if (logger.is_open())
  {
    logger.close();
  }
  return genericCode.value;
}
