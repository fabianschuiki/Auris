/* Copyright © 2012 Fabian Schuiki, Sandro Sgier */
#pragma once
#include <gc_cpp.h>
#include <iostream>
#include <sstream>
#include <common/Mutex.h>
#include <common/HTTP/Response.h>
#include <common/HTTP/Request.h>

class Socket;

namespace Database
{
	class Server;

	class Connection : public gc
	{
		Socket *socket;
		Server *server;

		std::string inputBuffer;
		std::string outputBuffer;
		Mutex outputBuffer_lock;
		bool closeAfterWrite;

	public:
		Connection(Socket *socket, Server *server);

		void start();
		void run();

		void received();
		void write(const char *data, unsigned int length);
		void close();

		void write(HTTP::Response &r);
		void write(HTTP::Request &r);
		void write(const std::string &s);

		const std::string& getClientName();
	};
}