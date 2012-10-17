/* Copyright © 2012 Fabian Schuiki, Sandro Sgier */
#include "Connection.h"
#include "Server.h"
#include "../common/Socket.h"
#include <iostream>
#include <stdexcept>

using namespace Database;
using std::cerr;
using std::endl;
using std::runtime_error;


void Server::run(int argc, char *argv[])
{
	//Setup the listening socket for the control connections.
	Socket* listener = Socket::makeListening(8080);
	if (!listener)
		throw runtime_error("unable to create listening socket");

	//Enter the main loop that waits for new connections.
	while (true) {
		Socket* newSocket = listener->accept();
		Connection* c = new Connection(newSocket, this);
		addConnection(c);
		c->start();
	}
}

/** Adds a connection to the server's list of connections. Thread-safe. */
void Server::addConnection(Connection* c)
{
	connections_mutex.lock();
	connections.insert(c);
	connections_mutex.unlock();
}

/** Removes a connection to the server's list of connections. Thread-safe. */
void Server::removeConnection(Connection* c)
{
	connections_mutex.lock();
	connections.erase(c);
	connections_mutex.unlock();
}

void Server::debugChat(Connection *connection, std::stringbuf &buf)
{
	connections_mutex.lock();
	Connections cs = connections;
	connections_mutex.unlock();

	char buffer[1024];
	int length = buf.sgetn(buffer, 1024);

	for (Connections::iterator ic = cs.begin(); ic != cs.end(); ic++) {
		Connection *c = *ic;
		if (c == connection) continue;
		std::cout << "dispatching message from " << connection->getClientName() << std::endl;
		c->write(buffer, length);
	}
}