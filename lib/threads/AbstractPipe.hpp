#ifndef ABSTRACT_PIPE_HPP
#define ABSTRACT_PIPE_HPP

#include "../../main.hpp"

#include <cstdlib>
#include <string>
#include <queue>

namespace Pipeline
{
	template<typename T>
	class AbstractPipe
	{
	public:
		AbstractPipe(const char* str)
		 :m_signal(false), m_name(str) 
		{ }

		virtual ~AbstractPipe()
		{
			std::lock_guard lock(m_mutex);
			if (!m_buf.empty())
				error("Pipe not empty");
		}

		void writeImpl(T& data)
		{
			std::lock_guard lock(m_mutex);
			m_buf.push(std::move(data));
#if DEBUG_PIPE
			std::cout << "Add item\tbuff size "<< m_buf.size() << "\n";
#endif
		}

		bool readImpl(T& data)
		{
			std::lock_guard lock(m_mutex);	
			if (m_buf.empty())
				return false;
			
			data = std::move(m_buf.front());
			m_buf.pop();
#if DEBUG_PIPE
			std::cout << "Remove item\tbuff size "<< m_buf.size() << "\n";
#endif
			return true;
		}

		inline bool isEmpty()
		{
			std::lock_guard lock(m_mutex);
			return m_buf.empty();
		}

		void signal()
		{
			m_signal = true;
		}
		
	private:
		void error(std::string err)
		{
			throw std::runtime_error("["+m_name+"] "+err+"\n");
		}
		std::atomic<bool> m_signal;
		std::string m_name;
		std::mutex m_mutex;
		std::queue<T> m_buf;
	};
}

#endif