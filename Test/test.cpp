#include "pch.h"
#include <random>
#include <string>
#include "histogram.hpp"
#include "exception.hpp"
#include "cmath"


//-------------------------------------------------------------------------------------------------//

TEST(TestCase_OperatorOperatorCopy, Test_1) {
	std::mt19937 rng(111);
	std::uniform_int_distribution<std::mt19937::result_type> numeral(0, 1000);
	std::vector<double> data;

	for (auto i = 0; i < 20; i++) {
		data.push_back((numeral(rng) - 500) / 100);
	}

	const Histogram histogram1(0, 100, 25, data);
	const Histogram histogram2 = histogram1;

	EXPECT_TRUE(histogram1 == histogram2);
}


//-------------------------------------------------------------------------------------------------//

TEST(TestCase_OperatorEquals, Test_1) {
	std::mt19937 rng(111);
	std::uniform_int_distribution<std::mt19937::result_type> numeral(0, 1000);
	std::vector<double> data;

	for (auto i = 0; i < 20; i++) {
		data.push_back((numeral(rng) - 500) / 100);
	}

	const Histogram histogram1(-10, 10, 25, data);
	const Histogram histogram2(-10, 10, 25, data);

	EXPECT_TRUE(histogram1 == histogram2);
}


TEST(TestCase_OperatorEquals, Test_2) {
	std::vector<double> data;

	for (auto i = 0; i < 20; i++) {
		data.push_back(1);
	}

	const Histogram histogram1(0, 2, 3, data);
	data.clear();

	for (auto i = 0; i < 20; i++) {
		data.push_back(2);
	}
	const Histogram histogram2(0, 2, 3, data);

	EXPECT_TRUE(!(histogram1 == histogram2));
}

//-------------------------------------------------------------------------------------------------//

TEST(TestCase_OperatorMinus, Test_1) {
	std::mt19937 rng(111);
	std::uniform_int_distribution<std::mt19937::result_type> numeral(0, 1000);
	std::vector<double> data;

	for (auto i = 0; i < 50; i++) {
		data.push_back((numeral(rng) - 500) / 100);
	}

	Histogram histogram1(0, 100, 25, data);
	Histogram histogram2(0, 100, 25, data);

	Histogram histogram_res = histogram1 - histogram2;

	for (auto bin = histogram_res.begin(); bin != histogram_res.end(); bin.operator++(1))
	{
		EXPECT_TRUE(*bin == 0);
	}
}


TEST(TestCase_OperatorMinus, Test_2) {
	std::mt19937 rng(111);
	std::uniform_int_distribution<std::mt19937::result_type> numeral(0, 1000);
	std::vector<double> data;
	std::vector<double> data_half;

	for (auto i = 0; i < 50; i++) {
		data.push_back((numeral(rng) - 500) / 100);;
	}
	Histogram histogram_real(0, 100, 25, data);

	for (auto i = 0; i < 50; i++) {
		const int rand_num = (numeral(rng) - 500) / 100;
		data.push_back(rand_num);
		data_half.push_back(rand_num);
	}
	Histogram histogram1(0, 100, 25, data);
	Histogram histogram2(0, 100, 25, data_half);

	Histogram histogram_supposed = histogram1 - histogram2;

	for (auto bin_supposed = histogram_supposed.begin(); bin_supposed != histogram_supposed.end(); bin_supposed.operator++(1))
	{
		bool is_equals = false;
		if (*bin_supposed == 0)
		{
			continue;
		}

		for (auto bin_real = histogram_real.begin(); bin_real != histogram_real.end(); bin_real.operator++(1))
		{
			if (*bin_supposed == *bin_real)
			{
				is_equals = true;
			}
		}
		EXPECT_TRUE(is_equals);
	}
}

TEST(TestCase_OperatorMinus, Test_exception) {
	Histogram histogram1(0, 10, 5);
	Histogram histogram2(0, 15, 5);

	EXPECT_THROW(histogram1 - histogram2, histogram_overlap_exception);
}


//-------------------------------------------------------------------------------------------------//

TEST(TestCase_OperatorPlus, Test_1) {
	std::mt19937 rng(111);
	std::uniform_int_distribution<std::mt19937::result_type> numeral(0, 1000);
	std::vector<double> data_all;
	std::vector<double> data;

	for (auto i = 0; i < 50; i++) {
		data.push_back((numeral(rng) - 500) / 100);
	}
	data_all.insert(data_all.begin(), data.begin(), data.end());
	Histogram histogram1(0, 100, 25, data);
	data.clear();

	for (auto i = 0; i < 50; i++) {
		data.push_back((numeral(rng) - 500) / 100);
	}
	data_all.insert(data_all.begin(), data.begin(), data.end());
	Histogram histogram2(0, 100, 25, data);

	Histogram histogram_real(0, 100, 25, data_all);

	Histogram histogram_supposed = histogram1 + histogram2;
	EXPECT_TRUE(histogram_supposed == histogram_real);
}


TEST(TestCase_OperatorPlus, Test_2) {
	Histogram histogram1(0, 10, 5);
	Histogram histogram2(0, 10, 5);
	Histogram histogram_real(0, 10, 5);

	Histogram histogram_supposed = histogram1 + histogram2;
	EXPECT_TRUE(histogram_supposed == histogram_real);
}


TEST(TestCase_OperatorPlus, Test_exception) {
	Histogram histogram1(0, 10, 5);
	Histogram histogram2(0, 15, 5);

	EXPECT_THROW(histogram1 + histogram2, histogram_overlap_exception);
}

//-------------------------------------------------------------------------------------------------//

TEST(TestCase_CtorCopy, Test_1) {
	std::vector<double> data;
	data.push_back(1);
	data.push_back(1);
	data.push_back(2);

	Histogram histogram1(1, 2, 2, data);
	Histogram histogram2(histogram1);
	EXPECT_TRUE(histogram1 == histogram2);
}

TEST(TestCase_CtorCopy, Test_exception_1) {
	EXPECT_THROW(Histogram histogram1(5, 2, 2), invalid_value_exception);
}

TEST(TestCase_CtorCopy, Test_exception_2) {
	EXPECT_THROW(Histogram histogram1(5, 2, 0), invalid_value_exception);
}

TEST(TestCase_CtorCopy, Test_exception_3) {
	std::vector<double> data;
	data.push_back(1);
	EXPECT_THROW(Histogram histogram1(5, 2, 0, data), invalid_value_exception);
}

//-------------------------------------------------------------------------------------------------//

TEST(TestCase_OperatorCopy, Test_1) {
	std::vector<double> data;
	data.push_back(1);
	data.push_back(1);
	data.push_back(2);

	Histogram histogram1(1, 2, 2, data);
	Histogram histogram2 = histogram1;
	EXPECT_TRUE(histogram1 == histogram2);
}

//-------------------------------------------------------------------------------------------------//

TEST(TestCase_Iterators, Test_1) {
	std::mt19937 rng(111);
	std::uniform_int_distribution<std::mt19937::result_type> numeral(0, 1000);
	std::vector<double> data;

	for (auto i = 0; i < 50; i++) {
		data.push_back((numeral(rng) - 500) / 100);
	}

	Histogram histogram1(0, 25, 25, data);
	int count = 0;

	for (auto i = histogram1.begin(); i != histogram1.end(); i++)
	{
		count += std::abs(*i);
	}

	EXPECT_TRUE(count == data.size());
}

TEST(TestCase_Add, Test_1) {
	Histogram histogram1(1, 2, 2);
	Histogram histogram2 = histogram1;
	histogram1.add_value(5.5);
	EXPECT_TRUE(histogram1 != histogram2);
}

//-------------------------------------------------------------------------------------------------//


////TEST(TestCaseName, TestName) {
////	EXPECT_EQ(1, 1);
////	EXPECT_TRUE(true);
////}