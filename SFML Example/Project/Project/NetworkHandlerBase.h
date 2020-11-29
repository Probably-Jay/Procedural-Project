#pragma once

#include "serverConfig.h"
#include "ErrorHandler.h"
#include "PacketStruct.h"
#include "ClientHandle.h"

#include <memory>
#include <iostream>
#include <functional>
using std::unique_ptr; using std::make_unique;
using std::shared_ptr; using std::make_shared;
using std::cout; using std::cin; using std::endl; 
using std::to_string;
using namespace sf;
class NetworkHandlerBase
{
protected:
	NetworkHandlerBase();
	//virtual void Run() = 0;
	
	//void Die();

	ErrorHandler errorHandler;

	const IpAddress serverIP = IpAddress::LocalHost;;
	const unsigned short serverConnectionPort = SERVERPORT;

	inline void Handle(Socket::Status status, bool die = true) {
		if (status == Socket::Done) { return; }
		else if(die) { errorHandler.Die(); }
	}

	//unsigned long generateClientID()
	virtual void outputClientData(ClientData const & clientData);
	void outputSocket(TcpSocket const & socket);
public:


};

