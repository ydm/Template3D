#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <string>


namespace logging
{
    void v(const std::string& s); // Level 0
    void d(const std::string& s); // Level 1
    void i(const std::string& s); // Level 2
    void w(const std::string& s); // Level 3
    void e(const std::string& s); // Level 4
}

#endif // __LOG_HPP__
