#include "log.hpp"
#include <cstdio>


namespace
{

// ------------------------
// Handlers
// ------------------------

#ifdef logHandler
#  error "logHandler is already defined"
#endif

#define logHandler(prefix, identifier)                                  \
    void prefix##LogHandler(const std::ostringstream& stream)           \
    {                                                                   \
        std::printf("[%c] %s", identifier, stream.str().c_str());       \
    }

logHandler(verbose, 'V');
logHandler(debug,   'D');
logHandler(info,    'I');
logHandler(warning, 'W');
logHandler(error,   'E');

#undef logHandler

} // namespace


namespace t3d
{

namespace log_private
{

StreamProxy::StreamProxy(const HandlerFunction& handler)
: handler_(handler)
, stream_()
{
}


StreamProxy::~StreamProxy()
{
    // NOOP
}


std::string StreamProxy::operator<<(const ConvertToStringToken&)
{
    return stream_.str();
}


StreamProxy& StreamProxy::operator<<(const EndToken&)
{
    handler_(stream_);
    stream_.str("");
    return *this;
}


StreamProxy& StreamProxy::operator<<(const EndLineToken&)
{
    stream_ << '\n';
    handler_(stream_);
    stream_.str("");
    return *this;
}

} // namespace log_private


namespace log
{

const log_private::ConvertToStringToken str;
const log_private::EndLineToken         endl;
const log_private::EndToken             end;

log_private::StreamProxy v(verboseLogHandler);  // Level 0
log_private::StreamProxy d(debugLogHandler);    // Level 1
log_private::StreamProxy i(infoLogHandler);     // Level 2
log_private::StreamProxy w(warningLogHandler);  // Level 3
log_private::StreamProxy e(errorLogHandler);    // Level 4

} // namespace log

} // namespace t3d
