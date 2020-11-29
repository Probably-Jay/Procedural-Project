#pragma once
#include "SFML/Network.hpp"
#include <memory>

struct ClientData
{
	ClientData();
	~ClientData();
	ClientData(ClientData&& other); // move semantics
	void updateFromSocket(std::unique_ptr<sf::TcpSocket> & socketPtr);
	//ClientData();
	size_t clientID;
	sf::IpAddress ip;
	unsigned short port;

friend class Server;
private:
	std::unique_ptr<sf::TcpSocket> socket;

};

inline sf::Packet& operator <<(sf::Packet& packet, const ClientData& data)
{
	return packet << data.clientID << data.ip.toInteger() << data.port;
}

inline sf::Packet& operator >>(sf::Packet& packet, ClientData& data)
{
	sf::Uint32 ip;
	packet >> data.clientID >> ip >> data.port;
	data.ip = sf::IpAddress{ ip };
	return packet;
}

