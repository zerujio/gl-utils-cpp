#ifndef GLUTILSCPP_ERROR_HPP
#define GLUTILSCPP_ERROR_HPP

#include <stdexcept>

namespace GL {

struct Error : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

} // GL

#endif //GLUTILSCPP_ERROR_HPP
