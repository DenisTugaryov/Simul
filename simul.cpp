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

std::tuple<size_t, size_t, size_t, size_t> Test_done_packets ( 
								DISTRIBUTION_TYPE block_size_distribution, size_t buffer_size, 
								size_t CPU_power, double betta, size_t iteration_number, 
								size_t max_size_block, size_t max_value_in_block, int lambda = 1)
{
	std::random_device rg;
	boost::mt19937 gen (rg);

	buffer bufFIFO = buffer (buffer_size, FIFO,  CPU_power, betta);
	buffer bufOPT = buffer (buffer_size, OPT,  CPU_power, betta);
	buffer bufNOTPUSH = buffer (buffer_size, NOTPUSH,  CPU_power, betta);
	buffer bufNOTDEL = buffer (buffer_size, NOTDEL,  CPU_power, betta);

	/* Create generators*/
	/*Uniform distribution*/
	boost::uniform_int<> uniform (0, max_size_block);
 	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > uniform_gener(gen, uniform);

 	/*Poisson distribution*/
 	boost::poisson_distribution<int> poisson (lambda);
 	boost::variate_generator<boost::mt19937&, boost::poisson_distribution<int> > 
 																		poisson_gener(gen, poisson);
 	/*Normal distribution*/
 	boost::normal_distribution<double> normal(max_size_block, std::sqrt(max_size_block));
	boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > burst_gener(gen, normal);

	for (int i = 0; i < iteration_number; ++i)
	{	
		size_t block_size = 0;

		switch (block_size_distribution)
	 	{
			case UNIFORM :
			{
				block_size = uniform_gener (max_size_block);
				break;
			}
			case POISSON : 
			{
				block_size = poisson_gener();
				break;
			}
			case BURST : 
			{
				block_size = burst_gener();
				if (block_size > max_size_block || block_size < 0)
					block_size = 0;
				break;
			}
		}		

		block new_block = block(block_size, max_value_in_block, UNIFORM);

		// std::cout << "BETTA = " << betta << std::endl;
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

		//  std::cout<<std::endl;
	}
	bufFIFO.done_packet += bufFIFO.data.size();
	bufOPT.done_packet += bufOPT.data.size();
	bufNOTPUSH.done_packet += bufNOTPUSH.data.size();
	bufNOTDEL.done_packet += bufNOTDEL.data.size();	

	return std::make_tuple (bufFIFO.done_packet, bufOPT.done_packet, 
						bufNOTPUSH.done_packet, bufNOTDEL.done_packet );
}


void UniformTest ()
{
	const DISTRIBUTION_TYPE block_size_distribution = UNIFORM;
	const size_t buffer_size = 10;
	const size_t max_value_CPU_power = 10;
	const double min_value_betta = 1;
	const double betta_step = 0.1;
	const double max_value_betta = 3;

	const size_t iteration_number = 3000;

	const size_t max_size_block = 5;
	const size_t max_value_in_block = 7;

	size_t done_fifo = 0;
	size_t done_opt = 0;
	size_t done_notpush = 0;
	size_t done_notdel = 0;

	std::ofstream uniform_test ("uniform_test.csv");
	uniform_test<< "block_size_distribution = " << "UNIFORM" << std::endl;
	uniform_test<< "buffer_size = " << buffer_size << std::endl;
	uniform_test<< "max_size_block = " << max_size_block << std::endl;
	uniform_test<< "max_value_in_block = " << max_value_in_block << std::endl;
	uniform_test<< "iteration_number = " << iteration_number << std::endl;
	uniform_test<< "CPU_power" << ";" << "Betta" << ";" << "FIFO" << ";" 
				<< "OPT" << ";" << "NOTPUSH" << ";" << "NOTDEL" << std::endl;

	for (size_t CPU_power = 1; CPU_power <= max_value_CPU_power; ++CPU_power)
	{
		for (double betta = min_value_betta; betta <= max_value_betta; betta += betta_step)
		{
			std::tuple<size_t, size_t, size_t, size_t> test_tuple = Test_done_packets (
											block_size_distribution, buffer_size, CPU_power, betta,
											iteration_number, max_size_block, max_value_in_block);

			std::tie (done_fifo, done_opt, done_notpush, done_notdel) = test_tuple;
			uniform_test<< CPU_power << ";" << betta << ";" << done_fifo << ";" 
						<< done_opt << ";" << done_notpush << ";" << done_notdel << std::endl;
		}
	}
}



void PoissonTest (int max_value_lambda)
{
	const DISTRIBUTION_TYPE block_size_distribution = POISSON;
	const size_t buffer_size = 10;
	const size_t max_value_CPU_power = 10;
	const double min_value_betta = 1;
	const double betta_step = 0.1;
	const double max_value_betta = 3;

	const size_t iteration_number = 3000;

	const size_t max_size_block = 5;
	const size_t max_value_in_block = 7;

	size_t done_fifo = 0;
	size_t done_opt = 0;
	size_t done_notpush = 0;
	size_t done_notdel = 0;

	for (int lambda = 1; lambda <= max_value_lambda; ++lambda)
	{
		std::stringstream ss;
		ss<< "poisson_test_lambda" << lambda << ".csv";

		std::ofstream poisson_test (ss.str());
		poisson_test<< "block_size_distribution = " << "POISSON" << std::endl;
		poisson_test<< "lambda = " << lambda << std::endl;
		poisson_test<< "buffer_size = " << buffer_size << std::endl;
		poisson_test<< "iteration_number = " << iteration_number << std::endl;
		poisson_test<< "CPU_power" << ";" << "Betta" << ";" << "FIFO" << ";" 
					<< "OPT" << ";" << "NOTPUSH" << ";" << "NOTDEL" << std::endl;

		for (size_t CPU_power = 1; CPU_power <= max_value_CPU_power; ++CPU_power)
		{

			for (double betta = min_value_betta; betta <= max_value_betta; betta += betta_step)
			{
				std::tuple<size_t, size_t, size_t, size_t> test_tuple = Test_done_packets (
									block_size_distribution, buffer_size, CPU_power, betta,
									iteration_number, max_size_block, max_value_in_block, lambda);

				std::tie (done_fifo, done_opt, done_notpush, done_notdel) = test_tuple;
				poisson_test<< CPU_power << ";" << betta << ";" << done_fifo << ";" 
							<< done_opt << ";" << done_notpush << ";" << done_notdel << std::endl;
			}
		}
	}
}


void BurstTest ()
{
	DISTRIBUTION_TYPE block_size_distribution = BURST;
	const size_t buffer_size = 10;
	const size_t max_value_CPU_power = 10;
	const double min_value_betta = 1;
	const double betta_step = 0.1;
	const double max_value_betta = 3;

	const size_t iteration_number = 3000;

	const size_t max_size_block = 5;
	const size_t max_value_in_block = 7;

	size_t done_fifo = 0;
	size_t done_opt = 0;
	size_t done_notpush = 0;
	size_t done_notdel = 0;

	std::ofstream burst_test ("burst_test.csv");
	burst_test<< "block_size_distribution = " << "BURST" << std::endl;
	burst_test<< "buffer_size = " << buffer_size << std::endl;
	burst_test<< "max_size_block = " << max_size_block << std::endl;
	burst_test<< "max_value_in_block = " << max_value_in_block << std::endl;
	burst_test<< "iteration_number = " << iteration_number << std::endl;
	burst_test<< "CPU_power" << ";" << "Betta" << ";" << "FIFO" << ";" 
				<< "OPT" << ";" << "NOTPUSH" << ";" << "NOTDEL" << std::endl;

	for (size_t CPU_power = 1; CPU_power <= max_value_CPU_power; ++CPU_power)
	{
		for (double betta = min_value_betta; betta <= max_value_betta; betta += betta_step)
		{
			std::tuple<size_t, size_t, size_t, size_t> test_tuple = Test_done_packets (
											block_size_distribution, buffer_size, CPU_power, betta,
											iteration_number, max_size_block, max_value_in_block);

			std::tie (done_fifo, done_opt, done_notpush, done_notdel) = test_tuple;
			burst_test<< CPU_power << ";" << betta << ";" << done_fifo << ";" 
						<< done_opt << ";" << done_notpush << ";" << done_notdel << std::endl;
		}
	}
}

int main()
{
	UniformTest ();

	int max_value_lambda = 5;
	PoissonTest (max_value_lambda);
	
	BurstTest();

	return 0;
}
