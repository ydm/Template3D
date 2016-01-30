#ifndef __T3D_LOG_HPP__
#define __T3D_LOG_HPP__

#include <functional>
#include <sstream>
#include <string>


namespace t3d
{

namespace log_private
{

struct ConvertToStringToken {};
struct EndToken             {};
struct EndLineToken         {};


class StreamProxy
{
public:
    typedef std::function<void (std::ostringstream &)> HandlerFunction;
    StreamProxy(const HandlerFunction& handler);
    ~StreamProxy();

    template<typename T>
    StreamProxy& operator<<(const T& obj)
    {
        stream_ << obj;
        return *this;
    }

    std::string operator<<(const ConvertToStringToken&);
    StreamProxy& operator<<(const EndToken&);
    StreamProxy& operator<<(const EndLineToken&);

private:
    const HandlerFunction handler_;
    std::ostringstream stream_;
};

} // namespace log_private


namespace log
{

extern const log_private::ConvertToStringToken str;
extern const log_private::EndToken             end;
extern const log_private::EndLineToken         endl;

extern log_private::StreamProxy v;  // Level 0
extern log_private::StreamProxy d;  // Level 1
extern log_private::StreamProxy i;  // Level 2
extern log_private::StreamProxy w;  // Level 3
extern log_private::StreamProxy e;  // Level 4

} // namespace log
} // namespace t3d

#endif // __T3D_LOG_HPP__
