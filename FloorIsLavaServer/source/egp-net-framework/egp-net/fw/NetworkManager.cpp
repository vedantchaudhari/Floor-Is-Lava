/*
	EGP Networking Framework
	Dan Buckstein
	October 2018

	Dummy class implementation.
*/
#include <sstream>
#include <string>
#include <fcntl.h>
#include <string.h> 
#include <io.h>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include "egp-net/fw/NetworkManager.h"
NetworkManager::~NetworkManager()
{
	peer->Shutdown(0);
	RakNet::RakPeerInterface::DestroyInstance(peer);
}

void NetworkManager::init(int serverPort)
{


	peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd(serverPort, 0);

	peer->Startup(12, &sd, 1);
	myIP = peer->GetLocalIP(2);

	peer->SetTimeoutTime(90000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);

}

RakNet::RakNetGUID NetworkManager::getGUID() 
{ 
	return peer->GetMyGUID(); 
}
const char * NetworkManager::getIP()
{
	return myIP.c_str();
}
char* NetworkManager::getPacket()
{

	RakNet::Packet *packet;

	packet = peer->Receive();
	if (packet)
	{
		return (char*)packet->data;
	}
	else
	{
		return NULL;
	}


	switch (packet->data[0])
	{
		break;
	case ID_REMOTE_DISCONNECTION_NOTIFICATION:
		printf("Another client has disconnected.\n");
		break;
	case ID_REMOTE_CONNECTION_LOST:
		printf("Another client has lost the connection.\n");
		break;
	case ID_REMOTE_NEW_INCOMING_CONNECTION:
		printf("Another client has connected.\n");
		break;
	case ID_NO_FREE_INCOMING_CONNECTIONS:
		printf("The server is full.\n");
		break;
	case ID_CONNECTION_REQUEST_ACCEPTED:
	{
		system("cls");
	}
	break;
	case ID_NEW_INCOMING_CONNECTION:
	{
		system("cls");
	}
	break;
	case ID_DISCONNECTION_NOTIFICATION:
	{
		printf("We have been disconnected.\n");
	}
	break;
	case ID_CONNECTION_LOST:
		printf("Connection lost.\n");
		break;


	default:
		printf("Message with identifier %i has arrived.\n", packet->data[0]);
		break;
	}
	peer->DeallocatePacket(packet);

}

RakNet::Packet* NetworkManager::getRakNetPacket()
{
	static RakNet::Packet *temp;
	peer->DeallocatePacket(temp);
	temp = peer->Receive();
	if (temp)
	{
		return temp;
	}
	else
	{
		return NULL;
	}
}

void NetworkManager::sendPacket(char * packet, int size, RakNet::AddressOrGUID id)
{
	peer->Send(packet, size, HIGH_PRIORITY, RELIABLE_ORDERED, 0, id, false);
}

void NetworkManager::sendToAll(char * packet, int size)
{
	peer->Send(packet, size, HIGH_PRIORITY, RELIABLE_ORDERED, 0, peer->GetMyGUID(), true);
}

