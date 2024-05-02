#include <functional>
#include <asio.hpp>
#include <iostream>

class Printer
{
private:
    asio::steady_timer timer;
    int count;

public:
    Printer(asio::io_context &io) : timer(io, asio::chrono::seconds(1)), count(0)
    {
        /*
        Inside the printer constructor, we start the asynchronous wait
        operation by calling async_wait() on the timer object.
        */
        std::cout << "Printer constructor called\n";
        timer.async_wait(std::bind(&Printer::print, this));
    }

    ~Printer()
    {
        std::cout << "Final count is " << count << std::endl;
    }

    void print()
    {
        if (count < 5)
        {
            std::cout << "Count is " << count << std::endl;
            ++count;

            /* We start a new asynchronous wait operation each time the previous one completes.
             This way, the print() member function is called every second until count reaches 5.*/
            timer.expires_at(timer.expiry() + asio::chrono::seconds(1));
            timer.async_wait(std::bind(&Printer::print, this));
        }
    }
};

int main()
{
    asio::io_context io;
    Printer printer(io);
    io.run();

    return 0;
}