#ifndef GLUTILSCPP_ERROR_HPP
#define GLUTILSCPP_ERROR_HPP

#include <stdexcept>

namespace glutils {

    struct GLError : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

} // glutils

#endif //GLUTILSCPP_ERROR_HPP
