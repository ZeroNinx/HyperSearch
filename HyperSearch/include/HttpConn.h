#pragma once
#include <sdkddkver.h>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http/string_body.hpp>

namespace beast = boost::beast;
namespace asio = boost::asio;
namespace ssl = asio::ssl;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

//Http链接
class HttpConn
{
public:
	HttpConn(std::string Hostname, int Port = 80);

	http::request<http::string_body> Request;
	http::response<http::string_body> Response;

public:

	virtual void Build(std::string Target, http::verb Method = http::verb::get, int Version = 11);
	virtual void Connect();
	std::string GetResponseBody();

protected:

	beast::flat_buffer buffer;
	asio::io_context io_ctx;
	tcp::resolver resolver{ io_ctx };
	tcp::socket socket{ io_ctx };

	std::string hostname;
	std::string port;
};

class HttpsConn:public HttpConn
{
public:

	HttpsConn(std::string Hostname, int Port = 443);

public:

	void Connect() override;

private:

	tcp::socket Connect(asio::io_context& ctx, std::string const& hostname);

	ssl::context ssl_ctx{ ssl::context::tls_client };
	std::unique_ptr<ssl::stream<tcp::socket>> stream;
};

