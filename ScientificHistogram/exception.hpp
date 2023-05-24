#pragma once
#include <exception>

class histogram_exception : public std::exception {};

class histogram_overlap_exception : public histogram_exception {
    const char* what() const noexcept override;
};

class invalid_value_exception : public histogram_exception {
    const char* what() const noexcept override;
};