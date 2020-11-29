#include "Client.h"

Client::Client() : NetworkHandlerBase(),
myData(),myID(-1)
{
	//sf::TcpListener list;
	
}

void Client::Connect()
{

	cout << "Attempting to connect..." << endl;
	Handle(socket.connect(serverIP, serverConnectionPort));

	cout << "Connected!"; outputSocket(socket); cout << endl << "Sending data..." << endl;

	Packet packet;

	packet << myData; // if we have never connected, this ID will be set to -1
	Handle(socket.send(packet));

	cout << "Data sent"<< endl;

	packet.clear();

	Handle(socket.receive(packet));
	packet >> myData;
	
	outputClientData(myData);

	//socket.disconnect();
	

}


void Client::RunTCP()
{
	//socket.setBlocking(true);
	//Handle(socket.connect(serverIP, serverConnectionPort));

	GameDataPacketStruct data = { 35 };
	Packet packet;
	packet << data;

//	Handle(socket.send(packet));


}
void Client::RunUDP()
{
	GameDataPacketStruct data = { 35 };
	Packet packet;
	packet << data;
	Handle(usocket.send(packet, serverIP, serverConnectionPort));

}
	//socket()
