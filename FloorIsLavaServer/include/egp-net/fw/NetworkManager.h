/*
	EGP Networking Framework
	Dan Buckstein
	October 2018

	Dummy class interface.
*/

#ifndef _EGP_DUMMYCLASS_H_
#define _EGP_DUMMYCLASS_H_

#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"  


class NetworkManager
{
	std::string myIP;
	RakNet::RakPeerInterface *peer;
public:
	~NetworkManager();
	void init(int serverPort = 420);
	char * getPacket();
	void sendPacket(char* packet, int size = 8, RakNet::AddressOrGUID id = RakNet::UNASSIGNED_SYSTEM_ADDRESS);
	RakNet::Packet* getRakNetPacket();
	RakNet::RakNetGUID getGUID();
	void sendToAll(char* packet, int size = 8);
	const char * getIP();
};


#endif	// !_EGP_DUMMYCLASS_H_