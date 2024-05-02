#include <asio.hpp>
#include <iostream>
#include <array>

using namespace std;

int main()
{
    try
    {
        asio::io_context context;
        asio::ip::tcp::resolver resolver(context);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "daytime");

        asio::ip::tcp::socket socket(context);
        asio::connect(socket, endpoints);

        for (;;)
        {
            array<char, 128> buf;
            error_code ec;

            size_t len = socket.read_some(asio::buffer(buf), ec);
            if (ec == asio::error::eof)
            {
                break;
            }
            else if (ec)
            {
                throw std::system_error(ec);
            }

            cout.write(buf.data(), len);
        }
    }
    catch (exception &e)
    {
        cout << "Error occurred: " << e.what() << endl;
    }
}