#include "NetworkHandlerBase.h"

NetworkHandlerBase::NetworkHandlerBase() : errorHandler()
{
}

void NetworkHandlerBase::outputClientData(ClientData const & clientData)
{
	cout << "Client: " << clientData.clientID << ": IP: " << clientData.ip.toString() << ", port: " << to_string(clientData.port) << endl;
}

void NetworkHandlerBase::outputSocket(TcpSocket const& socket)
{
	cout << "socket on loal port: "<< socket.getLocalPort()<<" remote address: " << socket.getRemoteAddress() << ", port: " << socket.getRemotePort() << endl;
}

