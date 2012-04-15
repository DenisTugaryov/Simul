#include <iostream>
#include <tuple>
#include <fstream>

#include "block.h"
#include "buffer.h"
#include "test_for_distribution.h"

enum PARAMETR
{
	BETTA,
	CPU_POWER,
	MAX_VALUE_IN_BLOCK,
	MAX_SIZE_BLOCK,
	LAMBDA
};

void betta_Output(	PARAMETR parametr,
					size_t buffer_size, BUFFER_TYPE buffer_type,
					DISTRIBUTION_TYPE block_size_distribution,
					size_t iteration_number,
					double min_value_betta, double max_value_betta, double betta_step,
					size_t CPU_power,
					size_t max_value_in_block,
					size_t max_size_block, 
					int lambda)
{
	std::ofstream test ("test.txt");
	test<< "buffer_size = " << buffer_size << ";  "
		<< "buffer_type = " << buffer_type << ";  "
		<< "block_size_distribution = " << block_size_distribution << ";  "
		<< "iteration_number = " << iteration_number << ";  "
		<< "parametr = betta" << std::endl;

	size_t done_fifo = 0;
	size_t done_opt = 0;
	size_t done_notpush = 0;
	size_t done_notdel = 0;
	size_t* done_current = 0;

	switch(buffer_type)
	{
		case FIFO: 
		{
			done_current = & done_fifo;
			break;
		}
		case OPT: 
		{
			done_current = & done_opt;
			break;
		}
		case NOTPUSH: 
		{
			done_current = & done_notpush;
			break;
		}
		case NOTDEL: 
		{
			done_current = & done_notdel;
			break;
		}
	}
	for (double betta = min_value_betta; betta <= max_value_betta; betta += betta_step)
	{
		std::tuple<size_t, size_t, size_t, size_t> test_tuple = Test_done_packets(
									block_size_distribution, buffer_size, CPU_power, betta,
									iteration_number, max_size_block, max_value_in_block, lambda);
		std::tie (done_fifo, done_opt, done_notpush, done_notdel) = test_tuple;
		test<< "(" << betta << "," << ((double)done_opt)/(*done_current) << ")" << std::endl;
	}
}


void CPU_power_Output(	PARAMETR parametr,
						size_t buffer_size, BUFFER_TYPE buffer_type,
						DISTRIBUTION_TYPE block_size_distribution,
						size_t iteration_number,
						double betta,
						size_t min_CPU_power, size_t max_CPU_power, size_t CPU_power_step,
						size_t max_value_in_block,
						size_t max_size_block,
						int lambda)
{
	std::ofstream test ("test.txt");
	test<< "buffer_size = " << buffer_size << ";  "
		<< "buffer_type = " << buffer_type << ";  "
		<< "block_size_distribution = " << block_size_distribution << ";  "
		<< "iteration_number = " << iteration_number << ";  "
		<< "parametr = CPU_power" << std::endl;

	size_t done_fifo = 0;
	size_t done_opt = 0;
	size_t done_notpush = 0;
	size_t done_notdel = 0;

	size_t* done_current = 0;

	switch(buffer_type)
	{
		case FIFO: 
		{
			done_current = & done_fifo;
			break;
		}
		case OPT: 
		{
			done_current = & done_opt;
			break;
		}
		case NOTPUSH: 
		{
			done_current = & done_notpush;
			break;
		}
		case NOTDEL: 
		{
			done_current = & done_notdel;
			break;
		}
	}
	for (size_t CPU_power = min_CPU_power; CPU_power <= max_CPU_power; CPU_power += CPU_power_step)
	{
		std::tuple<size_t, size_t, size_t, size_t> test_tuple = Test_done_packets(
									block_size_distribution, buffer_size, CPU_power, betta,
									iteration_number, max_size_block, max_value_in_block, lambda);
		std::tie (done_fifo, done_opt, done_notpush, done_notdel) = test_tuple;
		test<< "(" << CPU_power << "," << ((double)done_opt)/(*done_current) << ")" << std::endl;
	}
}

void max_value_in_block_Output( PARAMETR parametr, size_t buffer_size, BUFFER_TYPE buffer_type,
			DISTRIBUTION_TYPE block_size_distribution,
			size_t iteration_number,
			double betta, 
			size_t CPU_power, 
			size_t inf_max_value_in_block, size_t sup_max_value_in_block, size_t max_value_in_block_step,
			size_t max_size_block, 
			int lambda)
{
	std::ofstream test ("test.txt");
	test<< "buffer_size = " << buffer_size << ";  "
		<< "buffer_type = " << buffer_type << ";  "
		<< "block_size_distribution = " << block_size_distribution << ";  "
		<< "iteration_number = " << iteration_number << ";  "
		<< "parametr = max_value_in_block" << std::endl;

	size_t done_fifo = 0;
	size_t done_opt = 0;
	size_t done_notpush = 0;
	size_t done_notdel = 0;

	size_t* done_current = 0;

	switch(buffer_type)
	{
		case FIFO: 
		{
			done_current = & done_fifo;
			break;
		}
		case OPT: 
		{
			done_current = & done_opt;
			break;
		}
		case NOTPUSH: 
		{
			done_current = & done_notpush;
			break;
		}
		case NOTDEL: 
		{
			done_current = & done_notdel;
			break;
		}
	}
	for (size_t max_value_in_block = inf_max_value_in_block; max_value_in_block <= sup_max_value_in_block;
														max_value_in_block += max_value_in_block_step)
	{
		std::tuple<size_t, size_t, size_t, size_t> test_tuple = Test_done_packets(
									block_size_distribution, buffer_size, CPU_power, betta,
									iteration_number, max_size_block, max_value_in_block, lambda);
		std::tie (done_fifo, done_opt, done_notpush, done_notdel) = test_tuple;
		test<< "(" << max_value_in_block << "," << ((double)done_opt)/(*done_current) << ")" << std::endl;
	}
}



void max_size_block_Output( PARAMETR parametr,
							size_t buffer_size, BUFFER_TYPE buffer_type,
							DISTRIBUTION_TYPE block_size_distribution,
							size_t iteration_number,
							double betta,
							size_t CPU_power,
							size_t max_value_in_block,
							size_t inf_max_size_block, size_t sup_max_size_block, size_t max_size_block_step,
							int lambda)
{
	std::ofstream test ("test.txt");
	test<< "buffer_size = " << buffer_size << ";  "
		<< "buffer_type = " << buffer_type << ";  "
		<< "block_size_distribution = " << block_size_distribution << ";  "
		<< "iteration_number = " << iteration_number << ";  "
		<< "parametr = max_size_block" << std::endl;

	size_t done_fifo = 0;
	size_t done_opt = 0;
	size_t done_notpush = 0;
	size_t done_notdel = 0;

	size_t* done_current = 0;

	switch(buffer_type)
	{
		case FIFO: 
		{
			done_current = & done_fifo;
			break;
		}
		case OPT: 
		{
			done_current = & done_opt;
			break;
		}
		case NOTPUSH: 
		{
			done_current = & done_notpush;
			break;
		}
		case NOTDEL: 
		{
			done_current = & done_notdel;
			break;
		}
	}
	for (size_t max_size_block = inf_max_size_block; max_size_block <= sup_max_size_block;
													max_size_block += max_size_block_step)
	{
		std::tuple<size_t, size_t, size_t, size_t> test_tuple = Test_done_packets(
									block_size_distribution, buffer_size, CPU_power, betta,
									iteration_number, max_size_block, max_value_in_block, lambda);
		std::tie (done_fifo, done_opt, done_notpush, done_notdel) = test_tuple;
		test<< "(" << max_size_block << "," << ((double)done_opt)/(*done_current) << ")" << std::endl;
	}
}

void lambda_Output( PARAMETR parametr,
			size_t buffer_size, BUFFER_TYPE buffer_type,
			DISTRIBUTION_TYPE block_size_distribution,
			size_t iteration_number,
			double betta,
			size_t CPU_power,
			size_t max_value_in_block,
			size_t max_size_block,
			int min_value_lambda, int max_value_lambda, int lambda_step)
{
	std::ofstream test ("test.txt");
	test<< "buffer_size = " << buffer_size << ";  "
		<< "buffer_type = " << buffer_type << ";  "
		<< "block_size_distribution = " << block_size_distribution << ";  "
		<< "iteration_number = " << iteration_number << ";  "
		<< "parametr = lambda" << std::endl;

	size_t done_fifo = 0;
	size_t done_opt = 0;
	size_t done_notpush = 0;
	size_t done_notdel = 0;

	size_t* done_current = 0;

	switch(buffer_type)
	{
		case FIFO: 
		{
			done_current = & done_fifo;
			break;
		}
		case OPT: 
		{
			done_current = & done_opt;
			break;
		}
		case NOTPUSH: 
		{
			done_current = & done_notpush;
			break;
		}
		case NOTDEL: 
		{
			done_current = & done_notdel;
			break;
		}
	}
	for (int lambda = min_value_lambda; lambda <= max_value_lambda; lambda += lambda_step)
	{
		std::tuple<size_t, size_t, size_t, size_t> test_tuple = Test_done_packets(
									block_size_distribution, buffer_size, CPU_power, betta,
									iteration_number, max_size_block, max_value_in_block, lambda);
		std::tie (done_fifo, done_opt, done_notpush, done_notdel) = test_tuple;
		test<< "(" << lambda << "," << ((double)done_opt)/(*done_current) << ")" << std::endl;
	}
}
