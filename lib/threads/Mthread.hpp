#ifndef THREAD_HPP
#define THREAD_HPP

#include <atomic>

#include "../../main.hpp"

namespace Tasks
{	
	//forward declaration
	void* startRoutine(void *object);

	class Thread
	{
	public:
		enum /*__attribute__((__packed__))*/ State
		{
			Creating,
			Deleting,
			Starting,
			Stopping,
			Waiting,
			Stopped,
			Running,
			Idle,
			Dead,
			Detach
		};

		Thread();

		virtual ~Thread();

		void start();

		void stop();

		void join();

		void setPriority(unsigned int priority);

		int getID();

		inline State getState()
		{ return m_state; }
		
	protected:

		inline bool stopRequested()
		{ return m_stopSignal; }

		virtual void onMain() = 0;

		virtual std::string getName() = 0;

		void error(std::string err);

	private:
		friend void* startRoutine(void *object);

		inline void setState(State n_state);

		int m_pid;
		std::atomic<bool> m_stopSignal;
		std::atomic<State> m_state;
		pthread_t m_thread;
		pthread_attr_t m_thread_attr;
	};
}

#endif