#include "parser.hpp"
#include <string>

namespace 
{
	[[nodiscard]] bool check_type(const std::string& value)
	{
		const char* pattern = "0123456789-.";
		return value.find_first_not_of(pattern) == std::string::npos;

	}
}

std::vector<double> read_number(std::istream& fin)
{
	std::vector<double> data;
	std::string value;

	while (fin >> value)
	{
		if (check_type(value))
		{
			double number = stod(value);
			data.emplace_back(number);
		}
	}

	return data;
}