#include "Globals.h"
#include <map>
namespace Globals
{
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
  std::string time_utc()
  {
    std::map<int, std::string> days =
    {
      {0, "Sun"}, {1, "Mon"}, {2, "Tue"}, {3, "Wed"},
      {4, "Thu"}, {5, "Fri"}, {6, "Sat"}
    };
    std::map<int, std::string> months =
    {
      {0, "Jan"}, {1, "Feb"}, {2, "Mar"}, {3, "Apr"},
      {4, "May"}, {5, "Jun"}, {6, "Jul"}, {7, "Aug"},
      {8, "Sep"}, {9, "Oct"}, {10, "Nov"}, {11, "Dec"}
    };
    time_t time_raw;
    struct tm tm_ptr;
    time(&time_raw);
    gmtime_r(&time_raw, &tm_ptr);
    const std::string weekday = days[tm_ptr.tm_wday];
    const std::string month = months[tm_ptr.tm_mon];
    const std::string day_of_month(std::to_string(tm_ptr.tm_mday));
    const std::string year = [tm_ptr]()
    {
      return std::to_string((tm_ptr.tm_year) + 1900);
    }();
    const std::string hour = [tm_ptr]()
    {
      std::string hour_string =
          std::to_string(tm_ptr.tm_hour);
      if (hour_string.length() < 2)
      {
        hour_string.insert(0, "0");
      }
      return hour_string;
    }();
    const std::string minute = [tm_ptr]()
    {
      std::string hour_string =
          std::to_string(tm_ptr.tm_min);
      if (hour_string.length() < 2)
      {
        hour_string.insert(0, "0");
      }
      return hour_string;
    }();
    const std::string second = [tm_ptr]()
    {
      std::string hour_string =
          std::to_string(tm_ptr.tm_sec);
      if (hour_string.length() < 2)
      {
        hour_string.insert(0, "0");
      }
      return hour_string;
    }();
    const std::string meridiem = [tm_ptr]()
    {
      return ((int(tm_ptr.tm_hour) < 12)?"AM":"PM");
    }();
    std::string time;
    time.append(weekday);       time.push_back(' ');
    time.append(day_of_month);  time.push_back(' ');
    time.append(month);         time.push_back(' ');
    time.append(year);          time.push_back(' ');
    time.append(hour);          time.push_back(':');
    time.append(minute);        time.push_back(':');
    time.append(second);        time.push_back(' ');
    time.append(meridiem);      time.push_back(' ');
    time.append("UTC");
    return time;
  } 
}
namespace Globals
{
  void DefaultExitCode (ExitCode & code_)
  {
    code_.value = 0;
    code_.message = "Success.";
  }
};