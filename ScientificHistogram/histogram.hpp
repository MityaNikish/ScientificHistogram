#pragma once
#include <unordered_map>
#include <vector>


class Histogram final
{
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
    bool same_parameters(const Histogram& other) const;
    void add_value(const double value);

private:
    const double step;
    int min, max;
    size_t bin_count;
    std::vector<int> segment_sizes;
};