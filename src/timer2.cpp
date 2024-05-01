//This is example of an asynchronous timer

/*
The job of io_context.run() is to run all the asynchronour tasks and handlers 
which were posted to the io_context. This helps in asynchronous work flow as 
it does not disturb the main thread.
*/

#include<asio.hpp>
#include<iostream>

void print(const std::error_code& ec) {
	std::cout << "Hello World\n";
}

int main() {
	std::cout << "Program started\n";
	asio::io_context context;
	asio::steady_timer t(context,asio::chrono::seconds(5));
	t.async_wait(&print);
	std::cout << "Second line - This shows that program is asynchronous\n";
	context.run();
	return 0;
}