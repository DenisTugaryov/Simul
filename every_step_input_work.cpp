#include <iostream>

#include <random>
#include <tuple>
#include <fstream>
#include <string>
#include <sstream>

#include <boost/random/uniform_01.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/poisson_distribution.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

#include "block.h"
#include "buffer.h"

buffer init_buffer ()
{
	size_t buffer_size = 1;
	int type = 0;
	size_t CPU_power = 1;
	std::cout << "BUFFER TYPES: " << std::endl
				<< "FIFO = 0 " << std::endl
				<< "OPT = 1 " << std::endl
				<< "NOTPUSH = 2 " << std::endl
				<< "NOTDEL = 3 " << std::endl;
	std::cout << "Input <buffer_size> <BUFFER_TYPE> <CPU_power>: " << std::endl;
	std::cin >> buffer_size >> type >> CPU_power;
	std::cout << std::endl;
	buffer b (buffer_size, (BUFFER_TYPE)type, CPU_power, 1);
	return b;	
}

block init_block ()
{
	size_t block_size = 0;
	size_t max_value = 1;
	int dist = 0;
	std::cout << "DISTRIBUTION TYPES: " << std::endl
				<< "CONST = 0 " << std::endl
				<< "UNIFORM = 1 " << std::endl
				<< "NORMAL = 2 " << std::endl;
	std::cout << "Input <block_size> <max_value> <DISTRIBUTION_TYPE>: " << std::endl;
	std::cin >> block_size >> max_value >> dist;
	std::cout << std::endl;
	block b (block_size, max_value ,(DISTRIBUTION_TYPE)dist);
	return b;	
}

void work()
{
	buffer buff = init_buffer();
	bool end_work = false;
	while (!end_work)
	{
		block b = init_block();
		b.print();
		buff.tact(b);
		buff.print();
		std::cout << "for close input 1, for continue input 0" << std::endl;
		std::cin >> end_work;
	}
}