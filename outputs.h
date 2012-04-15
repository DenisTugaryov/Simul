#ifndef OUTPUTS_H
#define OUTPUTS_H

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
			int lambda);

void CPU_power_Output(	PARAMETR parametr,
			size_t buffer_size, BUFFER_TYPE buffer_type,
			DISTRIBUTION_TYPE block_size_distribution,
			size_t iteration_number,
			double betta,
			size_t min_CPU_power, size_t max_CPU_power, size_t CPU_power_step,
			size_t max_value_in_block,
			size_t max_size_block,
			int lambda);

void max_value_in_block_Output( PARAMETR parametr,
			size_t buffer_size, BUFFER_TYPE buffer_type,
			DISTRIBUTION_TYPE block_size_distribution,
			size_t iteration_number,
			double betta, 
			size_t CPU_power, 
			size_t inf_max_value_in_block, size_t sup_max_value_in_block, size_t max_value_in_block_step,
			size_t max_size_block, 
			int lambda);

void max_size_block_Output( PARAMETR parametr,
			size_t buffer_size, BUFFER_TYPE buffer_type,
			DISTRIBUTION_TYPE block_size_distribution,
			size_t iteration_number,
			double betta,
			size_t CPU_power,
			size_t max_value_in_block,
			size_t inf_max_size_block, size_t sup_max_size_block, size_t max_size_block_step,
			int lambda);

void lambda_Output( PARAMETR parametr, size_t buffer_size, BUFFER_TYPE buffer_type,
			DISTRIBUTION_TYPE block_size_distribution,
			size_t iteration_number,
			double betta,
			size_t CPU_power,
			size_t max_value_in_block,
			size_t max_size_block,
			int min_value_lambda, int max_value_lambda, int lambda_step);

#endif // OUTPUTS_H
