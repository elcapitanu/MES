#include "inputs.hpp"

KEY::~KEY()
{
#if DEBUG_THR
    cout << "KEY: adeus" << endl;
#endif
}

void KEY::onMain()
{
#if DEBUG_THR
    cout << "KEY: tou vivo" << endl;
#endif

    struct termios t;
    struct termios t_saved;

    // Set terminal to single character mode.
    tcgetattr(fileno(stdin), &t);
    t_saved = t;
    t.c_lflag &= (~ICANON);
    t.c_cc[VTIME] = 0;
    t.c_cc[VMIN] = 1;
    tcsetattr(fileno(stdin), TCSANOW, &t);

    std::streambuf *pbuf = cin.rdbuf();

    while (!stopRequested())
    {
        // Read single characters from cin.
        if (pbuf->sgetc() == EOF)
            input = 0x1b;

        input = pbuf->sbumpc();
    }

    // Restore terminal mode.
    tcsetattr(fileno(stdin), TCSANOW, &t_saved);

    return;
}