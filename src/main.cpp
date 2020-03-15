#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/regex.hpp>
#include "ReversePolishNotation.h"

using namespace std;
using namespace boost::asio;

int main()
{
	//cout << "Hello World!" << endl;
	boost::asio::io_service io_service;
	//ip::address::make_address("127.0.0.1")
	auto const address = boost::asio::ip::address::from_string("127.0.0.1");
	ip::tcp::endpoint endpoint{address, 4444};
	ip::tcp::socket socket(io_service);
	ip::tcp::acceptor acceptor{io_service, endpoint};

	acceptor.accept(socket);
	//read
	boost::asio::streambuf buf;
	boost::asio::read_until(socket, buf, "\n" );
	string data = boost::asio::buffer_cast<const char*>(buf.data());
	std::cout << "FLAG+++ server: \n" + data;


	std::size_t size =  data.find("\n");
	std::cout << "Size: " << size << std::endl;
	std::string first_input_line = data.substr(0, size -1);
	std::cout << "Size: " << first_input_line << std::endl;
	//regex
	boost::regex expression("GET /[?]e=%22(.+)%22 HTTP/1.1");
	boost::smatch what;

	bool flag = false;
	if (boost::regex_match(first_input_line, what, expression))
	{
		std::cout << "TRUE" << std::endl;
		for (auto e: what)
		{
			std::cout << e << std::endl;
		}
		flag =true;
	}
	else
	{
		std::cout << "Invalid input format" << std::endl;
	}

	int result = 0;

	if (flag)
	{
		ReversePolishNotation rpn(what.str(1));
		try
		{
			rpn.process();
		}
		catch (const char * msg)
		{
			std::cout << msg << std::endl;
		}
		try
		{
			result = rpn.calculationRPN();
		}
		catch (const char * msg)
		{
			std::cout << msg << std::endl;
		}

		std::cout << "Result:: " << result << std::endl;
		//write
		std::string message(
					"HTTP/1.1 200 OK\n\n"
					"<html><body><h1>" + std::to_string(result) + "</h1></body></html>");
		write(socket, buffer(message));
	}


	return 0;
}
