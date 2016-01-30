#ifndef __T3D_LOG_HPP__
#define __T3D_LOG_HPP__

#include <string>


namespace t3d
{

namespace log_private
{

class StreamProxy
{
    
};

} // namespace log_private

namespace log
{

void v(const std::string& s); // Level 0
void d(const std::string& s); // Level 1
void i(const std::string& s); // Level 2
void w(const std::string& s); // Level 3
void e(const std::string& s); // Level 4

} // namespace log
} // namespace t3d

#endif // __T3D_LOG_HPP__
