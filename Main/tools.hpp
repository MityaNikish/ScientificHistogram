#pragma once
#include "histogram.hpp"
#include "parser.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

enum KeyPad
{
    exit_ = -1,
    add = 1,
    del,
    show,
    sub,
    sum
};


inline void draw_histogram(const Histogram& hist)
{
    for (auto bin : hist)
    {
        std::cout << bin << "\t";
    }
    std::cout << std::endl;
}


inline int inspector(const std::string& str)
{
    const char* pattern = "0123456789-";
    std::string arg;

    std::cout << str;
    while (true)
    {
        std::cin >> arg;
        std::cout << std::endl;
        if (arg.find_first_not_of(pattern) == std::string::npos)
        {
            return stoi(arg);
        }
        std::cout << "Incorrect data.\nEnter again: ";
    }
}

inline void add_hist(std::vector<Histogram>& hist_list)
{
    const int min = inspector("Input min value: ");
    const int max = inspector("Input max value: ");
    const int bin_count = inspector("Input count bin: ");

    std::string file_name;
    std::cout << "Input file name with date (*.txt): ";
    while (true) {
        std::cin >> file_name;
        if (std::filesystem::exists(file_name) && std::filesystem::path(file_name).extension() == ".txt") break;
        std::cout << "Repeat input file name (*.txt): ";
    }

    std::ifstream fin("date.txt");
    if (!fin.is_open())
    {
        std::cout << "File no open!!!" << std::endl;
    }

    std::vector<double> date = read_number(fin);
    fin.close();

    hist_list.emplace_back(min, max, bin_count, date);
}

inline bool operation(std::vector<Histogram>& hist_list, int number_1, int number_2)
{
    if (!(number_1 >= 0 && number_1 < hist_list.size() && number_2 >= 0 && number_2 < hist_list.size()))
    {
        std::cout << "\nnError! Invalid index.\n" << std::endl;
        return false;
    }
    if (hist_list[number_1].same_parameters(hist_list[number_2]))
    {
        std::cout << "\nError! Various histogram parameters.\n" << std::endl;
        return false;
    }
	return true;
}