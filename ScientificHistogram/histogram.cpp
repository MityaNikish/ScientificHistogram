#include "histogram.hpp"
#include  "exception.hpp"
#include "algorithm"



Histogram::Histogram(const int min, const int max, const size_t bin_count) : min(min), max(max), bin_count(bin_count), segment_sizes(bin_count), step((max - min) / static_cast<double>(bin_count))
{
    if (min > max || bin_count == 0)
    {
        throw invalid_value_exception();
    }
}

Histogram::Histogram(const int min, const int max, const size_t bin_count, const std::vector<double>& data) : min(min), max(max), bin_count(bin_count), segment_sizes(bin_count), step((max - min) / static_cast<double>(bin_count)) {
    if (min > max || bin_count <= 0)
    {
        throw invalid_value_exception();
    }

    //const double step = (max - min) / static_cast<double>(bin_count);
    for (const double value : data) {
        add_value(value);
    }
}

Histogram Histogram::operator+(const Histogram& other) const{
    if (same_parameters(other))
    {
        throw histogram_overlap_exception();
    }

    if (segment_sizes.empty())
    {
        return *this;
    }

	Histogram result(*this);
    std::transform(segment_sizes.begin(), segment_sizes.end(), other.segment_sizes.begin(), result.segment_sizes.begin(), std::plus<int>());
    return result;
}

Histogram Histogram::operator-(const Histogram& other) const {
    if (same_parameters(other))
    {
        throw histogram_overlap_exception();
    }

    if (segment_sizes.empty())
    {
        return *this;
    }

    Histogram result(*this);
    std::transform(segment_sizes.begin(), segment_sizes.end(), other.segment_sizes.begin(), result.segment_sizes.begin(), std::minus<int>());
    return result;
}

std::vector<int>::const_iterator Histogram::begin() const noexcept
{
    return segment_sizes.begin();
}

std::vector<int>::const_iterator Histogram::end() const noexcept
{
    return segment_sizes.end();
}

bool Histogram::same_parameters(const Histogram& other) const
{
    return max != other.max || min != other.min || bin_count != other.bin_count;
}

void Histogram::add_value(const double value_)
{
    double value = std::clamp(value_, static_cast<double>(min), static_cast<double>(max));

    int bin = floor((value - min) / step);

    if (bin == bin_count)
    {
    	--bin;
    }
    ++segment_sizes[bin];
}