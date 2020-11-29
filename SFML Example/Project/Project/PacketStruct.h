#pragma once
#include "SFML/Network.hpp"


struct GameDataPacketStruct
{
	float data;
};

inline sf::Packet& operator <<(sf::Packet& packet, const GameDataPacketStruct& data)
{
	return packet << data.data;
}

inline sf::Packet& operator >>(sf::Packet& packet, GameDataPacketStruct& data)
{
	return packet >> data.data;
}


struct ConnectionPacketStruct
{
	size_t myID;
};

inline sf::Packet& operator <<(sf::Packet& packet, const ConnectionPacketStruct& data)
{
	return packet << data.myID;
}

inline sf::Packet& operator >>(sf::Packet& packet, ConnectionPacketStruct& data)
{
	return packet >> data.myID;
}