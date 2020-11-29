#pragma once
#include "NetworkHandlerBase.h"
#include <vector>
#include <map>
#include <ctime>
using std::vector; using std::map;
class Server : public NetworkHandlerBase
{
public:
	Server();
	void RunTCP();
	void RunUDP();
	void ListenForConnections();


private:

	void HandleNewClientConnection(std::unique_ptr<sf::TcpSocket>& socketPtr);
	bool clientIsKnown(size_t clientID);
	virtual void outputClientData(ClientData const & clientData);

	bool listenForConnections;
	int numberOfNewClients;
	int timeWhenServerBegan;

	sf::TcpListener listener;
	UdpSocket usocket;
	vector<std::unique_ptr<TcpSocket>> testclients;
	map<size_t, unique_ptr<ClientData>> clients;
};

