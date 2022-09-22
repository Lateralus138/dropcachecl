// -----------------------------------------------
// 'dropcachecl' - Edit "drop-caches" file
// Copyright © 2022
// Ian Pride @ New Pride Software/Services
// Sat 17 Sep 2022 13:03:04 CST
// -----------------------------------------------
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Globals.h"
#include <pwd.h>
#include "ParseArgs.h"
int main(int argc, const char *argv[])
{
  ExitCode exitCode;
  ParseArgs::DefaultExitCode(exitCode);
  Options options;
  ParseArgs::Parse(argc, argv, options, exitCode);
  ParseArgs::check_delete_log(options);
  // if (options.doDeleteLog)
  // {
  //   if (remove(options.logFile.c_str()) == 0)
  //   {
  //     if (!options.isQuiet)
  //     {
  //       const std::string message =
  //         "Log file '" +
  //         options.logFile +
  //         "' deleted successfully.";
  //       std::cout << message << '\n';
  //     }
  //   }
  //   else
  //   {
  //    if (!options.isQuiet)
  //     {
  //       const std::string message = "Log file '" + options.logFile + "' could not be deleted.";
  //       std::cerr << message << '\n';
  //     }
  //   }
  // }
  std::ofstream logger;
  if (options.logStderr || options.logStdout)
  {
    logger.open(options.logFile, std::ios_base::app);
  }
  const std::filesystem::path dropCachesPath("/proc/sys/vm/drop_caches");
  std::ofstream ofile(dropCachesPath.native().c_str());
  if (ofile.is_open())
  {
    std::string logMessage
    (
      "Drop Cache set to [" + std::to_string(option_map[options.optionString]) +
      ":" + options.optionString + "] @ " + Globals::time_utc() + "\n"
    );
    if (!options.isQuiet)
    {
      std::cout << logMessage;
    }
    ofile << option_map[options.optionString];
    if (options.logStdout && logger.is_open())
    {
      logger << logMessage;
    }
    ofile.close();
  }
  else
  {
    try
    {
      exitCode.value = 2;
      exitCode.message =
        std::string
        (
          "Could not open '" +
          dropCachesPath.native() +
          "' for writing.\nDo you have root privileges?"
        );
      throw exitCode;
    }
    catch(ExitCode & code)
    {
      const std::string logMessage =
        "Could not open'" +
        dropCachesPath.native() + "' for writing @ " +
        Globals::time_utc() + "\n";
      if (!options.isQuiet)
      {
        std::cerr << code.message << '\n';
      }
      if (options.logStderr && logger.is_open())
      {
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
  return exitCode.value;
}
