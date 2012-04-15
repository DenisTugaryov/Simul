#ifndef TEST_FOR_DISTRIBUTION
#define TEST_FOR_DISTRIBUTION

#include "block.h"
#include "buffer.h"

std::tuple<size_t, size_t, size_t, size_t> Test_done_packets ( 
								DISTRIBUTION_TYPE block_size_distribution, size_t buffer_size, 
								size_t CPU_power, double betta, size_t iteration_number, 
								size_t max_size_block, size_t max_value_in_block, int lambda = 1);

void UniformTest ();

void PoissonTest (int max_value_lambda);

void BurstTest ();

#endif // TEST_FOR_DISTRIBUTION
