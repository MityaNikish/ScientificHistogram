#include "histogram.hpp"
#include  "exception.hpp"


Histogram::Histogram(const int min, const int max, const size_t bin_count) : min(min), max(max), bin_count(bin_count)
{
    if (min > max || bin_count == 0)
    {
        throw invalid_value_exception();
    }
}

Histogram::Histogram(const int min, const int max, const size_t bin_count, const std::vector<double>& data) : min(min), max(max), bin_count(bin_count) {
    if (min > max || bin_count <= 0)
    {
        throw invalid_value_exception();
    }

    dictionary.resize(bin_count);

    const double step = (max - min) / static_cast<double>(bin_count);
    for (const auto& value : data) {

        if (value <= min)
        {
            ++dictionary[0];
            continue;
        }

        if (value >= max)
        {
            ++dictionary[bin_count - 1];
            continue;
        }

        for (size_t bin = 0; bin < bin_count; bin++)
        {
            if ((min + step * static_cast<double>(bin) < value && value <= min + step * static_cast<double>((bin + 1))))
            {
                ++dictionary[bin];
                break;
            }
        }
    }
}

Histogram Histogram::operator+(const Histogram& other) const {
    is_equals_params_except(other);
    if (dictionary.empty())
    {
        return *this;
    }

	Histogram result(*this);
    for (size_t bin = 0; bin < bin_count; bin++)
    {
        result.dictionary[bin] += other.dictionary[bin];
    }
    return result;
}

Histogram Histogram::operator-(const Histogram& other) const {
    is_equals_params_except(other);

    if (dictionary.empty())
    {
        return *this;
    }

    Histogram result(*this);
    for (size_t bin = 0; bin < bin_count; bin++)
    {
        result.dictionary[bin] -= other.dictionary[bin];
    }
    return result;
}


std::vector<int>::const_iterator Histogram::begin() const noexcept
{
    return dictionary.begin();
}

std::vector<int>::const_iterator Histogram::end() const noexcept
{
    return dictionary.end();
}

void Histogram::is_equals_params_except(const Histogram& other) const
{
    if (max != other.max || min != other.min || bin_count != other.bin_count)
    {
        throw histogram_overlap_exception();
    }
}

bool Histogram::is_equals_params(const Histogram& other) const
{
    return max != other.max || min != other.min || bin_count != other.bin_count;
}

