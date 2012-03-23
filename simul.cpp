#include <iostream>

#include <boost/random/uniform_01.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/linear_congruential.hpp>

#include <random>

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

void UniformCompare(size_t buffer_size, size_t CPU_power, size_t betta, size_t iteration_number, size_t max_size_block, size_t max_value_in_block)
{
	std::random_device rg;
	boost::mt19937 gen (rg);

	buffer bufFIFO = buffer (buffer_size, FIFO,  CPU_power, betta);
	buffer bufOPT = buffer (buffer_size, OPT,  CPU_power, betta);
	buffer bufNOTPUSH = buffer (buffer_size, NOTPUSH,  CPU_power, betta);
	buffer bufNOTDEL = buffer (buffer_size, NOTDEL,  CPU_power, betta);

	boost::uniform_int<> uniform (0, max_size_block);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > gener(gen, uniform);

	for (int i = 0; i < iteration_number; ++i)
	{		
		size_t block_size = gener (max_size_block);
		block new_block = block(block_size, max_value_in_block, UNIFORM);

		// std::cout<< i << ") ";
		// new_block.print();
		
		bufFIFO.tact(new_block);
		bufOPT.tact(new_block);
		bufNOTPUSH.tact(new_block);
		bufNOTDEL.tact(new_block);

		// std::cout<< "FIFO done_packet = "; bufFIFO.print();
		// std::cout<< "OPT done_packet = "; bufOPT.print();
		// std::cout<< "NOTPUSH done_packet = "; bufNOTPUSH.print();
		// std::cout<< "NOTDEL done_packet = "; bufNOTDEL.print();

		//std::cout<<std::endl;
	}
	// std::cout<< "FIFO done_packet = " << bufFIFO.done_packet << std::endl;
	// std::cout<< "OPT done_packet = " << bufOPT.done_packet << std::endl;
	// std::cout<< "NOTPUSH done_packet = " << bufNOTPUSH.done_packet << std::endl;
	// std::cout<< "NOTDEL done_packet = " << bufNOTDEL.done_packet << std::endl;

	bufFIFO.done_packet += bufFIFO.data.size();
	bufOPT.done_packet += bufOPT.data.size();
	bufNOTPUSH.done_packet += bufNOTPUSH.data.size();
	bufNOTDEL.done_packet += bufNOTDEL.data.size();	


	std::cout<< "FIFO done_packet = " << bufFIFO.done_packet << std::endl;
	std::cout<< "OPT done_packet = " << bufOPT.done_packet << std::endl;
	std::cout<< "NOTPUSH done_packet = " << bufNOTPUSH.done_packet << std::endl;
	std::cout<< "NOTDEL done_packet = " << bufNOTDEL.done_packet << std::endl;
}


int main()
{
	size_t buffer_size = 10;
	size_t CPU_power = 1;
	size_t betta = 2;

	size_t iteration_number = 300;

	size_t max_size_block = 5;
	size_t max_value_in_block = 7;

	
	UniformCompare(buffer_size, CPU_power, betta, iteration_number, max_size_block, max_value_in_block);
	//UniformCompare(10, 1, 30000, 5, 7);

	return 0;
}