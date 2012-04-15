#include <iostream>

#include "block.h"
#include "buffer.h"
#include "test_for_distribution.h"
#include "outputs.h"

PARAMETR Input( size_t & buffer_size, BUFFER_TYPE & buffer_type,
				DISTRIBUTION_TYPE & block_size_distribution,
				size_t & iteration_number,
				double & min_value_betta, double & max_value_betta, double & betta_step,
				size_t & min_CPU_power, size_t & max_CPU_power, size_t & CPU_power_step,
				size_t & inf_max_value_in_block, size_t & sup_max_value_in_block, size_t & max_value_in_block_step,
				size_t & inf_max_size_block, size_t & sup_max_size_block, size_t & max_size_block_step,
				int & min_value_lambda, int & max_value_lambda, int & lambda_step)
{

	PARAMETR parametr = BETTA;

	int type = 0;
	std::cout << "BUFFER TYPES: " << std::endl
				<< "FIFO = 0 " << std::endl
				<< "OPT = 1 " << std::endl
				<< "NOTPUSH = 2 " << std::endl
				<< "NOTDEL = 3 " << std::endl;
	std::cout << "Input <buffer_size> <BUFFER_TYPE>: " << std::endl;
	std::cin >> buffer_size >> type;
	std::cout << std::endl;
	buffer_type = (BUFFER_TYPE) type;

	int block_size_dist = 0;
	std::cout << "BLOCK SIZE DISTRIBUTION: " << std::endl
				<< "UNIFORM = 0 " << std::endl
				<< "POISSON = 1 " << std::endl
				<< "BURST = 2 " << std::endl;
	std::cout << "Input <BLOCK SIZE DISTRIBUTION>: " << std::endl;
	std::cin >> block_size_dist;
	block_size_distribution = (DISTRIBUTION_TYPE) block_size_dist;
	std::cout << std::endl;

	std::cout << "Input <iteration_number>: " << std::endl;
	std::cin >> iteration_number;
	std::cout << std::endl;

	std::cout << "Input <min_value_betta> <max_value_betta> <betta_step>: " << std::endl;
	std::cin >> min_value_betta >> max_value_betta >> betta_step;
	std::cout << std::endl;

	std::cout << "Input <min_CPU_power> <max_CPU_power> <CPU_power_step>: " << std::endl;
	std::cin >> min_CPU_power >> max_CPU_power >> CPU_power_step;
	std::cout << std::endl;
	if (CPU_power_step != 0) parametr = CPU_POWER;

	std::cout << "Input <inf_max_value_in_block> <sup_max_value_in_block> <max_value_in_block_step>: " << std::endl;
	std::cin >> inf_max_value_in_block >> sup_max_value_in_block >> max_value_in_block_step;
	std::cout << std::endl;
	if (max_value_in_block_step != 0) parametr = MAX_VALUE_IN_BLOCK;

	std::cout << "Input <inf_max_size_block> <sup_max_size_block> <max_size_block_step>: " << std::endl;
	std::cin >> inf_max_size_block >> sup_max_size_block >> max_size_block_step;
	std::cout << std::endl;
	if (max_size_block_step != 0) parametr = MAX_SIZE_BLOCK;

	if (block_size_distribution == POISSON)
	{
		std::cout << "Input <min_value_lambda> <max_value_lambda> <lambda_step>: " << std::endl;
		std::cin >> min_value_lambda >> max_value_lambda >> lambda_step;
		std::cout << std::endl;
		if (lambda_step != 0) parametr = LAMBDA;
	}

	return parametr;
}

int main()
{
	size_t buffer_size = 1;
	BUFFER_TYPE buffer_type = FIFO;

	DISTRIBUTION_TYPE block_size_distribution = UNIFORM;
	size_t iteration_number = 3000;

	double min_value_betta = 1;
	double max_value_betta = 1;
	double betta_step = 0;

	size_t min_CPU_power = 1;
	size_t max_CPU_power = 1;
	size_t CPU_power_step = 0;

	size_t inf_max_value_in_block = 0;
	size_t sup_max_value_in_block = 0;
	size_t max_value_in_block_step = 0;

	size_t inf_max_size_block = 1;
	size_t sup_max_size_block = 1;
	size_t max_size_block_step = 0;

	int min_value_lambda = 1;
	int max_value_lambda = 1;
	int lambda_step = 0;

	PARAMETR parametr = Input(buffer_size, buffer_type, block_size_distribution, iteration_number,
		min_value_betta, max_value_betta, betta_step, min_CPU_power, max_CPU_power, CPU_power_step,
		inf_max_value_in_block, sup_max_value_in_block, max_value_in_block_step,
		inf_max_size_block, sup_max_size_block, max_size_block_step, min_value_lambda, max_value_lambda, lambda_step);

	switch (parametr)
	{
		case BETTA:
		{
			betta_Output(parametr, buffer_size, buffer_type, block_size_distribution, iteration_number,
			min_value_betta, max_value_betta, betta_step, min_CPU_power, inf_max_value_in_block,
			inf_max_size_block, min_value_lambda);
			break;
		}
		case CPU_POWER:
		{
			CPU_power_Output(parametr, buffer_size, buffer_type, block_size_distribution, iteration_number,
			min_value_betta, min_CPU_power, max_CPU_power, CPU_power_step, inf_max_value_in_block,
			inf_max_size_block, min_value_lambda);
			break;
		}
		case MAX_VALUE_IN_BLOCK:
		{
			max_value_in_block_Output(parametr, buffer_size, buffer_type, block_size_distribution, iteration_number,
			min_value_betta, min_CPU_power,	inf_max_value_in_block, sup_max_value_in_block, max_value_in_block_step,
			inf_max_size_block, min_value_lambda);
			break;
		}
		case MAX_SIZE_BLOCK:
		{
			max_size_block_Output(parametr, buffer_size, buffer_type, block_size_distribution, iteration_number,
			min_value_betta, min_CPU_power,	inf_max_value_in_block,
			inf_max_size_block, sup_max_size_block, max_size_block_step, min_value_lambda);
			break;
		}
		case LAMBDA:
		{
			lambda_Output(parametr, buffer_size, buffer_type, block_size_distribution, iteration_number,
			min_value_betta, min_CPU_power, inf_max_value_in_block, inf_max_size_block,
			min_value_lambda, max_value_lambda, lambda_step);
			break;
		}
	}
	

	return 0;
}
