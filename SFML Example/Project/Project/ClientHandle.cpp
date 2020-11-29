#include "ClientHandle.h"

ClientData::ClientData():
	clientID(-1),
	ip(-1),
	port(-1),
	socket(nullptr)
{
}

ClientData::ClientData(ClientData&& other):
	socket(nullptr)
{
	other.clientID = this->clientID;
	other.ip = this->ip;
	other.port = this->port;
	other.socket.swap(this->socket);
}

ClientData::~ClientData()
{
	if(socket) socket->disconnect();
}

void ClientData::updateFromSocket(std::unique_ptr<sf::TcpSocket> & socketPtr)
{
	socket.swap(socketPtr);
	ip = socket->getRemoteAddress();
	port = socket->getRemotePort();
}
