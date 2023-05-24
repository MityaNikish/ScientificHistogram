#pragma once
#include <string>
#include <unordered_map>
#include <vector>


class Histogram {
public:
    Histogram() = delete;
    Histogram(int min, int max, size_t bin_count);
    Histogram(int min, int max, size_t bin_count, const std::vector<double>& data);
    Histogram(const Histogram& other) = default;
    ~Histogram() = default;

public:
    Histogram& operator=(const Histogram&) = default;
    bool operator==(const Histogram& other) const = default;
    Histogram operator+(const Histogram& other) const;
    Histogram operator-(const Histogram& other) const;

public:
    std::vector<int>::const_iterator begin() const noexcept;
    std::vector<int>::const_iterator end() const noexcept;

public:
    bool is_equals_params(const Histogram& other) const;

private:
    void is_equals_params_except(const Histogram& other) const;

private:
    std::vector<int> dictionary;
    //std::unordered_map<std::string, int> dictionary;
    int min, max;
    size_t bin_count;
};