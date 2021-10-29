#include "HttpConn.h"
#include <QDebug>
#include <boost/certify/extensions.hpp>
#include <boost/certify/https_verification.hpp>
#include <sstream>

using namespace std;

/**
 * HttpConn
 */
//构造函数
HttpConn::HttpConn(string Hostname, int Port) :hostname(Hostname), port(to_string(Port))
{
	try
	{
		//查找域名
		auto const results = resolver.resolve(hostname, port);
		
		// 链接找到的域名
		asio::connect(socket, results.begin(), results.end());
	}
	catch (exception e)
	{
		qDebug() << e.what();
	}
}

//创建请求
void HttpConn::Build(string Target, http::verb Method, int Version)
{
	try
	{
		Request = http::request<http::string_body>{ Method, Target, Version };
		Request.set(http::field::host, hostname);
	}
	catch (exception e)
	{
		qDebug() << e.what();
	}
}

//连接
void HttpConn::Connect()
{
	try
	{
		write(socket, Request);
		read(socket, buffer, Response);
	}
	catch (const std::exception& e)
	{
		qDebug() << e.what();
	}
}

//获得返回本体
string HttpConn::GetResponseBody()
{
	std::stringstream StringStream;
	StringStream << Response.body();
	return StringStream.str();
}

/**
 * HttpsConn
 */
//构造函数
HttpsConn::HttpsConn(string Hostname, int Port) :HttpConn(Hostname, Port)
{
	try
	{
		ssl_ctx.set_verify_mode(ssl::context::verify_peer | ssl::context::verify_fail_if_no_peer_cert);
		ssl_ctx.set_default_verify_paths();
		boost::certify::enable_native_https_server_verification(ssl_ctx);
	}
	catch (const std::exception& e)
	{
		qDebug() << e.what();
	}
}

void HttpsConn::Connect()
{
	try
	{
		asio::connect(this->socket, resolver.resolve(hostname, port));
		stream = boost::make_unique<ssl::stream<tcp::socket>>(std::move(this->socket), ssl_ctx);

		// tag::stream_setup_source[]
		boost::certify::set_server_hostname(*stream, hostname);
		boost::certify::sni_hostname(*stream, hostname);
		// end::stream_setup_source[]

		stream->handshake(ssl::stream_base::handshake_type::client);

		http::write(*stream, Request);
		http::read(*stream, buffer, Response);
	}
	catch (const std::exception& e)
	{
		qDebug() << e.what();
	}
}

