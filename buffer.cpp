#include <iostream>

#include "buffer.h"
#include "block.h"


buffer::buffer (size_t size = 1, BUFFER_TYPE type = FIFO, size_t CPU_power = 1, double betta = 1) : 
	buffer_size (size),
	type (type),
	done_packet (0),
	//done_weight (0),
	CPU_power (CPU_power),
	betta (betta),
	deletable (0)
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
			if ((maximum() / element) > betta)
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
	for (std::list<size_t>::iterator it = data.begin(); (it != data.end()) && (power > 0); )
	{
		if (*it == 1)
		{
			if (it == data.begin()) 
			{
				data.pop_front();
				++done_packet;
				--power;
				it = data.begin();
			}
			else ++it;
		}
		else
		{
			--*it;
			--power;
			++it;
		}
	}
}

void buffer::cpu_action_allone_extract ()
{
	size_t power = CPU_power;
	size_t counter = 0;
	if (deletable <= 0)
	{
		helper (counter, power);
		if (counter == buffer_size)
		{
			deletable = buffer_size;
		}
	}
	if (deletable > 0)
	{
		for (std::list<size_t>::iterator it = data.begin(); (it != data.end()) && (deletable > 0) && (power > 0); )
		{
			data.pop_front();
			++done_packet;
			--deletable;
			--power;
			it = data.begin();
		}
		helper (counter, power);		
	}
}

void buffer::helper(size_t & ones_counter, size_t & power)
{
	ones_counter = 0;
	for (std::list<size_t>::iterator it = data.begin(); (it != data.end()) && (power > 0); ++it)
	{
		if (*it == 1) 
			++ones_counter;
		else
		{
			--*it;
			--power;
			if (*it == 1) 
			++ones_counter;
		}
	}
}
