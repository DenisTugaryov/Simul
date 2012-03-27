#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <list>

enum DISTRIBUTION_TYPE
{
	CONST,
	UNIFORM,
	NORMAL,
	POISSON
};

class block
{
public:
	size_t block_size;
	std::list<size_t> data;
	size_t max_elem;

	block(size_t size, size_t max_value, DISTRIBUTION_TYPE distribution);
	bool is_empty ();
	void print ();	
};

#endif // _BLOCK_H_
