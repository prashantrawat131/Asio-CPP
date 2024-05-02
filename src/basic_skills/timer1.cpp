#include<iostream>
#include<asio.hpp>

int main() {
	asio::io_context context;
	std::cout << "Wait for five seconds\n";
	asio::steady_timer t(context,asio::chrono::seconds(5));
	t.wait();
	std::cout << "\nHello World\n";
	return 0;
}