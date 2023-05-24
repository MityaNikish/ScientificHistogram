#include "exception.hpp"

const char* histogram_overlap_exception::what() const noexcept {
    return "The parameters of the histograms do not match";
}

const char* invalid_value_exception::what() const noexcept {
    return "Invalid parameter value/s";
}