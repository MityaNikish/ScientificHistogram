#include "tools.hpp"

int main()
{
    std::vector<Histogram> hist_list;
    while (true)
    {
		int number_1 = 0;
		int number_2 = 0;
        int key = inspector("\n\n[-1 - exit;\t1 - addition histogram in list;\t2 - delete from the sheet;\n"
							"3 - check list histogram;\t4 - perform histogram subtraction;\t5 - perform histogram summation;]\nChoose an action: ");
		system("cls");

	    switch (key)
	    {
	    case exit_:
			return 0;
	    case add:
			add_hist(hist_list);
			break;
	    case del:
			number_1 = inspector("Input index histogram in list: ");
			if (number_1 >= 0 && number_1 < hist_list.size())
			{
				std::cout << "\nComplete.\n" << std::endl;
				hist_list.erase(hist_list.begin() + number_1);
			}
			std::cout << "\nError!\n" << std::endl;
			break;
	    case show:
			number_1 = 0;
			for (auto hist : hist_list)
			{
				std::cout << "[" << number_1 << "]" << " Histogram:" << std::endl;
				draw_histogram(hist);
				std::cout << std::endl;
				number_1++;
			}
			break;
	    case sum:
			number_1 = inspector("Input index first histogram: ");
			number_2 = inspector("Input index second histogram: ");
			if (!operation(hist_list, number_1, number_2))
			{
				break;
			}
			hist_list.push_back(hist_list[number_1] + hist_list[number_2]);
			std::cout << "\nThe resulting histogram is added to the list.\n" << std::endl;
			break;
	    case sub:
			number_1 = inspector("Input index first histogram: ");
			number_2 = inspector("Input index second histogram: ");
			if (!operation(hist_list, number_1, number_2))
			{
				break;
			}
			hist_list.push_back(hist_list[number_1] - hist_list[number_2]);
			std::cout << "\nThe resulting histogram is added to the list.\n" << std::endl;
			break;
		default:
			break;
	    }
    }
}