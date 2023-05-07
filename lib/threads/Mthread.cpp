#include "Mthread.hpp"

namespace Tasks
{
	Thread::Thread()
		: m_pid(-1), m_stopSignal(false), m_state(Thread::Creating)
	{
		if (pthread_attr_init(&m_thread_attr))
			error("Failed to init thread attributes");
		
		//set schedule at thread creation
		if (pthread_attr_setinheritsched(&m_thread_attr, PTHREAD_EXPLICIT_SCHED))
			error("Failed to set thread schedule attributes");
		
		setState(Thread::Idle);
	}

	Thread::~Thread()
	{
		setState(Thread::Deleting);
		pthread_attr_destroy(&m_thread_attr);
	}

	void Thread::setPriority(unsigned int priority)
	{
		//TODO: change if thread already running ?
		if(pthread_attr_setscope(&m_thread_attr, PTHREAD_SCOPE_PROCESS))
			error("Failed to set thread scope attribute");
		
		if(pthread_attr_setschedpolicy(&m_thread_attr, SCHED_FIFO))
			error("Failed to set thread schedule attribute");

		sched_param param;
		std::memset(&param, 0, sizeof(sched_param));
		param.sched_priority = priority;
		if (pthread_attr_setschedparam(&m_thread_attr, &param))
			error("Failed to set thead priority schedule param attribute");
		
	}

	int Thread::getID()
	{
		return m_pid;
	}


	void Thread::setState(State n_state)
	{	
		//TODO: check if mutex would be faster (force enum to be char?)
		//? is busy-waiting effective here
		m_state = n_state;
	}

	void Thread::start()
	{
		if (pthread_create(&m_thread, &m_thread_attr, startRoutine, this))
			error("Failed to start thread");
		
		setState(Thread::Starting);
		while (m_state != Running)//TODO: use another waiting method
			usleep(100);
#if DEBUG_THR
		std::cout << "["+getName()+"] running\n";
#endif
		
	}

	void Thread::stop()
	{
		setState(Thread::Stopping);
		m_stopSignal = true;
	}

	void Thread::join()
	{
#if DEBUG_THR
		std::cout << "["+getName()+"] asked to stop\n";
#endif
		if (m_state != Stopping && m_stopSignal == false)
			stop();
		
		if(pthread_join(m_thread, 0))
			error("Failed to join thead");
		
	}

	void* startRoutine(void *object)
	{
		Thread* handle = (Thread*)(object);
		pthread_setname_np(pthread_self(), handle->getName().c_str());

		handle->m_pid = gettid();

		handle->setState(Thread::Running);
#if DEBUG_THR
		std::cout << "["+handle->getName()+"] onMain started\n";
#endif
		handle->onMain();
#if DEBUG_THR
		std::cout << "["+handle->getName()+"] onMain returned\n";
#endif
		handle->setState(Thread::Stopped);
		handle->m_pid = -1;

		return nullptr;
	}
	

	void Thread::error(std::string err)
	{
		throw std::runtime_error("["+getName()+"] "+ err + "\n");
	}
}