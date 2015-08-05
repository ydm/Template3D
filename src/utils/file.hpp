#ifndef __UTILS_FILE_HPP__
#define __UTILS_FILE_HPP__

#include <fstream>
#include <string>


namespace utils
{
  namespace file
  {
    // ydm TODO: Specify encoding!
    std::string read(const std::string& filename)
    {
      std::ifstream s(filename);
      if (s)
        {
          return std::string(std::istreambuf_iterator<char>(s),
                             std::istreambuf_iterator<char>());
        }
      else
        {
          return "";
        }
    }
  } // file
} // utils

#endif // __UTILS_FILE_HPP__
