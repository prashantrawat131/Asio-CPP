#include <functional>
#include <asio.hpp>
#include <iostream>
#include <thread>

class Printer
{
private:
    asio::strand<asio::io_context::executor_type> strand;
    asio::steady_timer timer1;
    asio::steady_timer timer2;
    int count;

public:
    Printer(asio::io_context &io) : strand(asio::make_strand(io)),
                                    timer1(io, asio::chrono::seconds(1)),
                                    timer2(io, asio::chrono::seconds(1)),
                                    count(0)
    {
        std::cout << "Printer constructor called\n";
        timer1.async_wait(std::bind(&Printer::print1, this));
        timer1.async_wait(std::bind(&Printer::print2, this));
    }

    ~Printer()
    {
        std::cout << "Final count is " << count << std::endl;
    }

    void print1()
    {
        if (count < 5)
        {
            std::cout << "Print1: Count is " << count << std::endl;
            ++count;

            timer1.expires_at(timer1.expiry() + asio::chrono::seconds(1));
            timer1.async_wait(asio::bind_executor(strand, std::bind(&Printer::print1, this)));
        }
    }

    void print2()
    {
        if (count < 5)
        {
            std::cout << "Print2: Count is " << count << std::endl;
            ++count;
            timer2.expires_at(timer2.expiry() + asio::chrono::seconds(1));
            timer2.async_wait(asio::bind_executor(strand, std::bind(&Printer::print2, this)));
        }
    }
};

int main()
{
    asio::io_context io;
    Printer printer(io);
    std::thread th([&]
                   { io.run(); });

    return 0;
}