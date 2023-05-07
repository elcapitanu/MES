#ifndef MES_HPP
#define MES_HPP

#include "my_time.hpp"
#include "threads/Mthread.hpp"
#include "threads/WritePipe.hpp"

class MES : public Tasks::Thread
{
public:
    MES(Pipeline::AbstractPipe<std::vector<int>> *ptr)
        : m_pipe(ptr)
    {
        orders = 0;
        init_t = initTime(time_now);
        sprintf(message, "OLA :)\n");
    }

    ~MES();

    struct timeval time_now;

    uint64_t init_t;

    uint16_t orders;

    char message[100] = {};

    void addNumberOfOrders(uint16_t number);

private:
    inline std::string getName() override
    {
        return "MES";
    }

    void onMain() override;

    Pipeline::WritePipe<std::vector<int>> m_pipe;
};

#endif