#include <iostream>
#include <algorithm>
#include <iterator>
#include <random>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

#include <boost/random/uniform_01.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/poisson_distribution.hpp>

#include "block.h"


block::block (size_t size = 0, size_t max_value = 1, DISTRIBUTION_TYPE distribution = UNIFORM) :
	block_size (size),
	max_elem (max_value)
{
	std::random_device rg;
	boost::mt19937 gen (rg);
	
	switch (distribution)
	{
		// case CONST :
		// {
		// 	std::fill_n(std::back_insert_iterator<std::list<size_t> >(data), block_size, max_elem);
		// 	break;
		// }

		case UNIFORM :
		{
			boost::uniform_int<> uniform (1, max_elem);
			boost::variate_generator<boost::mt19937&, boost::uniform_int<> > gener(gen, uniform);
			std::generate_n(std::back_insert_iterator<std::list<size_t> >(data), block_size, gener);
			break;
		}
		// case NORMAL :
		// {
		// 	boost::normal_distribution<double> normal((max_elem / 2), 1);
		// 	boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > gener(gen, normal);
		// 	std::generate_n(std::back_insert_iterator<std::list<size_t> >(data), block_size, gener);
		// 	break;
		// }
		case POISSON :
		{
			const int lambda = 1;
			boost::poisson_distribution<int> poisson (lambda);
 			boost::variate_generator<boost::mt19937&, boost::poisson_distribution<int> > gener(gen, poisson);
			std::generate_n(std::back_insert_iterator<std::list<size_t> >(data), block_size, gener);
			break;
		}
	}
}

bool block::is_empty ()
{
	return (block_size == 0);
}

void block::print ()
{
	if (is_empty() )
	{
		std::cout<< "block is empty" << std::endl;
		return;
	}
	std::cout << "block: ";
	for (std::list<size_t>::iterator it = data.begin(); it != data.end(); ++ it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
