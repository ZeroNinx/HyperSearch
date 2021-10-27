#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>

class HttpConn
{
public:
	HttpConn(std::string host, std::string port);

	boost::beast::http::request< boost::beast::http::string_body> request;
	boost::beast::flat_buffer buf;
	boost::beast::http::response<boost::beast::http::string_body> response;


	void build(boost::beast::http::verb method, std::string target, int version);
	void connect();

private:

	boost::asio::io_service io_se;
	boost::asio::ip::tcp::resolver resolver{ io_se };
	boost::asio::ip::tcp::socket socket{ io_se };


	std::string host = "";
	std::string port = "";
	std::string target = "";
};