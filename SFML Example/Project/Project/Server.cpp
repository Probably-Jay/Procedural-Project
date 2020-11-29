#include "Server.h"

Server::Server() : NetworkHandlerBase(),
	listener(),
	listenForConnections(true), numberOfNewClients(0)
{
	timeWhenServerBegan = std::time(NULL);
}

void Server::RunTCP()
{

	cout << "I am server" << endl;
	Handle(listener.listen(serverConnectionPort));

	testclients.push_back(make_unique<TcpSocket>());

	Handle(listener.accept(*testclients[0]));

	cout << "client connected at: " + testclients[0]->getRemoteAddress().toString() + " port " + std::to_string(testclients[0]->getRemotePort()) << endl;

	Packet packet;
	GameDataPacketStruct data;

	Handle((*testclients[0]).receive(packet));

	packet >> data;

	cout << to_string(data.data) << std::endl;

	

}

void Server::RunUDP()
{
	Handle(usocket.bind(serverConnectionPort));

	
}

void Server::ListenForConnections()
{
	cout << "Server: " << serverIP.toString() << ", " << to_string(SERVERPORT) << endl << endl;

	Handle(listener.listen(serverConnectionPort));

	while (listenForConnections)
	{
		auto socketPtr = make_unique<TcpSocket>();
		Handle(listener.accept(*socketPtr));

		HandleNewClientConnection(socketPtr);

		//listenForConnections = false;
		cout << endl << "===Heartbeat===" << endl;
	}
}

void Server::HandleNewClientConnection(std::unique_ptr<sf::TcpSocket>& socketPtr)
{
	cout << "Established connection: ";
	outputSocket(*socketPtr);

	Packet packet;
	Handle(socketPtr->receive(packet));

	cout << "Received packet: "; 

	auto clientData = make_unique<ClientData>();
	packet >> *clientData;

	outputClientData(*clientData);

	if (!clientIsKnown(clientData->clientID)) { // new connection
		clientData->clientID = std::hash<int>{}((long)timeWhenServerBegan + numberOfNewClients++);
		clients[clientData->clientID] = nullptr; // create placeholder for new client
	} // else keep old ID
	else {
		cout << "Recognised reconnect attempt for: ";
		outputClientData(*clients[clientData->clientID]);
	}

	clientData->updateFromSocket(socketPtr);
	
	packet.clear();

	packet << *clientData;

	Handle(clientData->socket->send(packet));

	cout << "Send: ";
	outputClientData(*clientData);

	cout << "Data replied." << endl;

	clients[clientData->clientID].swap(clientData);
	clients.begin()->second->socket->disconnect();
	clients.clear();
	cout << "Client dissconected" << endl << endl;

}

bool Server::clientIsKnown(size_t clientID)
{
	return clients.find(clientID) != clients.end(); // find returns end ittr if key is not in map 
}

void Server::outputClientData(ClientData const& clientData)
{
	NetworkHandlerBase::outputClientData(clientData);
	if(clientData.socket) cout << "Connected to local port: " << to_string(clientData.socket->getLocalPort()) << endl;
}
