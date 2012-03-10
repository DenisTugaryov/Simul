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

#include "buffer.h"
#include "block.h"


buffer::buffer (size_t size = 1, BUFFER_TYPE type = FIFO, size_t CPU_power = 1) : 
	buffer_size (size),
	type (type),
	done_packet (0),
	//done_weight (0),
	CPU_power (CPU_power)
{
	//std::cout << "buffer() : done_packet==" << done_packet << std::endl;
}

bool buffer::is_empty ()
{
	return data.empty();
}

size_t buffer::maximum ()
{
	if (is_empty() ) return 0;
	size_t max = *data.begin();
	for (std::list<size_t>::const_iterator it = ++data.begin(); it != data.end(); ++ it)
	{
		if (*it > max) max = *it;
	}
	return max;
	//return std::max_element (data.begin(), data.end());
}

void buffer::delete_left_maximum ()
{
	if (is_empty()) return;
	size_t max = maximum();
	std::list<size_t>::iterator it = data.begin();
	while (*it != max) ++it;
	data.erase (it);
}

void buffer::add_elem_with_del_max (size_t element)
{
	if (!(data.size() < buffer_size))
		{
			if (maximum() > element)
			{
				delete_left_maximum();
				data.push_back(element);
			}
		}
		else	data.push_back(element);
}

void buffer::add_elem (size_t element)
{	
	switch (type)
	{
		case FIFO :
		case NOTDEL :
		{
			add_elem_with_del_max(element);
			break;
		}
		case OPT  : 
		{
			add_elem_with_del_max(element);
			data.sort();
			break;
		}
		case NOTPUSH :
		{
			if (data.size() < buffer_size)
				data.push_back(element);
			else buffer_size = 0;
			break;
		}
	}
}

void buffer::add_block (const block & b)
{
	for (std::list<size_t>::const_iterator it = b.data.begin(); it != b.data.end(); ++ it)
	{
		add_elem(*it);
	}
}

void buffer::print ()
{
	if (is_empty() )
	{
		std::cout<< "buffer is empty" << std::endl;
		return;
	}
	std::cout << "buffer: ";
	for (std::list<size_t>::iterator it = data.begin(); it != data.end(); ++ it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "data.size(): " << data.size() << ";  buffer_size: " 
				<< buffer_size <<  "; done_packet: " << done_packet << std::endl;
}

void buffer::tact (const block & b)
{
	cpu_action ();
	add_block (b);
}

void buffer::cpu_action ()
{
	if (is_empty()) return;
	switch (type)
	{
		case OPT  : 
		case FIFO : 
		case NOTPUSH:
		{
			cpu_action_frontone_extract ();
			break;
		}		
		case NOTDEL :
		{	
			cpu_action_allone_extract ();
			break;
		}
	}
}

void buffer::cpu_action_frontone_extract ()
{
	size_t power = CPU_power;
	for (std::list<size_t>::iterator it = data.begin(); (it != data.end()) && (power != 0); ++it)
	{
		if (*it == 1)
		{
			if (it == data.begin()) 
			{
				data.pop_front();
				++done_packet;
				--power;
			}
		}
		else
		{
			--*it;
			--power;
		}
	}
}

void buffer::cpu_action_allone_extract ()
{
	size_t power = CPU_power;
	size_t counter = 0;
	for (std::list<size_t>::iterator it = data.begin(); (it != data.end()) && (power != 0); ++it)
	{
		if (*it == 1) 
			++counter;
		else
		{
			--*it;
			--power;
		}
	}
	if (counter == buffer_size)
	{
		done_packet += buffer_size;
		data.clear();
	}
}