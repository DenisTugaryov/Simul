#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <list>

// #include "block.h"

class block;

enum BUFFER_TYPE
{
	FIFO,
	OPT,
	NOTPUSH,
	NOTDEL
};

class buffer
{
public:
	size_t buffer_size;
	const BUFFER_TYPE type;
	std::list<size_t> data;
	size_t done_packet;
	//size_t done_weight;
	const size_t CPU_power;
	const size_t betta;
	size_t deletable;

public:
	buffer (size_t size, BUFFER_TYPE type, size_t CPU_power, size_t betta);
	bool is_empty ();
	size_t maximum ();
	void delete_left_maximum ();
	void add_elem_with_del_max(size_t element);
	void add_elem (size_t element);
	void add_block (const block & b);
	void print ();
	void tact (const block & b);
	void cpu_action ();
	void cpu_action_frontone_extract ();
	void cpu_action_allone_extract ();
	void helper (size_t & counter, size_t & power);
};

#endif // _BUFFER_H_
