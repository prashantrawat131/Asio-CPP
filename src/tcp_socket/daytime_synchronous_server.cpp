#include <ctime>
#include <iostream>
#include <asio.hpp>
#include <string>

using namespace std;

string getTime()
{
    time_t now = time(0);
    return ctime(&now);
}

int main()
{
    try
    {
        asio::io_context context;
        asio::ip::tcp::acceptor acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 13));
        for (;;)
        {
            asio::ip::tcp::socket socket(context);
            acceptor.accept(socket);

            string msg = getTime();
            error_code ignored_error;
            asio::write(socket, asio::buffer(msg), ignored_error);
        }
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}