#pragma once
#include "NetworkHandlerBase.h"

#include "SFML/Network.hpp"
#include "SFML/Graphics.hpp"

class Client : public NetworkHandlerBase
{
public:
	Client();
	void Connect();
	void RunTCP();
	void RunUDP();

private:

	ClientData myData;
	size_t myID;
	sf::TcpSocket socket;

	UdpSocket usocket;
	//sf::Texture txt;


};

