#ifndef READ_PIPE_HPP
#define READ_PIPE_HPP

#include "../../main.hpp"

#include "AbstractPipe.hpp"

namespace Pipeline
{
	template<typename T>
	class ReadPipe
	{
	public:
		ReadPipe(AbstractPipe<T>* ptr) 
		 : m_pointer(ptr){};

		~ReadPipe(){};
		
		bool read(T& data)
		{
			return m_pointer->readImpl(data);
		}

		bool isEmpty()
		{
			return m_pointer->isEmpty();
		}
	private:
		AbstractPipe<T>* m_pointer;
	};

	
}

#endif