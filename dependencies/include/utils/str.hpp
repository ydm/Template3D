#ifndef __UTILS_STR_HPP__
#define __UTILS_STR_HPP__

#include <cctype>
#include <functional>
#include <initializer_list>
#include <sstream>
#include <string>


namespace utils
{
    namespace str
    {
        std::string join(const std::string& glue, std::initializer_list<const std::string> strings)
        {
            std::ostringstream output;
            bool first = true;
            for (std::initializer_list<const std::string>::const_iterator it = strings.begin();
                 it != strings.end();
                 it++)
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    output << glue;
                }
                output << *it;
            }
            return output.str();
        }

        std::string lstrip(const std::string& s)
        {
            static const std::function<int (int)> spacep = std::ptr_fun<int, int>(std::isspace);
            const std::string::const_iterator it = std::find_if_not(s.begin(), s.end(), spacep);
            return std::string(it, s.end());
        }

        std::string rstrip(const std::string& s)
        {
            static const std::function<int (int)> spacep = std::ptr_fun<int, int>(std::isspace);
            const std::string::const_reverse_iterator it = std::find_if_not(s.rbegin(), s.rend(), spacep);
            return std::string(s.begin(), it.base());
        }

        static bool startsWith(const std::string& s, const std::string& part)
        {
	        return s.find(part) == 0;
        }

        std::string strip(const std::string& s)
        {
            return lstrip(rstrip(s));
        }

    } // namespace str
} // namespace utils

#endif // __UTILS_STR_HPP__
