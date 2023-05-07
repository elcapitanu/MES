#ifndef WRITE_PIPE_HPP
#define WRITE_PIPE_HPP


#include "AbstractPipe.hpp"


namespace Pipeline
{
	template<typename T>
	class WritePipe
	{
	public:
		WritePipe(AbstractPipe<T>* ptr)
		 : m_pointer(ptr)
		{};

		~WritePipe(){};
		
		void write(T& data)
		{
			m_pointer->writeImpl(data);
		}

		bool isEmpty()
		{
			return m_pointer->isEmpty();
		}

		void signal()
		{
			m_pointer->signal();
		}
	private:
		AbstractPipe<T>* m_pointer;
	};

}

#endif