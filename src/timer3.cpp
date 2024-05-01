#include<functional>
#include<asio.hpp>
#include<iostream>

void print(asio::steady_timer* timer,int* count) {
	if (*count<5) {
		std::cout << *count << std::endl;
		++(*count);
		timer->expires_at(timer->expiry() + asio::chrono::seconds(1));
		timer->async_wait(std::bind(print, timer, count));
	}
}

int main() {
	std::cout << "Program started\n";
	int count = 0;

	asio::io_context context;
	asio::steady_timer t(context,asio::chrono::seconds(5));
	t.async_wait(std::bind(print,&t,&count));
	
	context.run();
	
	std::cout << "Final count is " << count << std::endl;
	
	return 0;
}