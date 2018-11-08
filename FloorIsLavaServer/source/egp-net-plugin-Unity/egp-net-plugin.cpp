/*
	EGP Networking: Plugin Interface/Wrapper
	Dan Buckstein
	October 2018

	Main implementation of Unity plugin wrapper.
*/

#include "egp-net-plugin.h"

#include "RakNet\RakPeerInterface.h"
#include <string.h>
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/BitStream.h"
#include "RakNet/RakNetTypes.h"  // MessageID
#include <fstream>
#include <sstream>
#include <string>
#include <io.h>
#include <iostream>
#include <fcntl.h>
#include <tchar.h>

#include "../include/egp-net/fw/NetworkManager.h"


// dummy function for testing
__declspec(dllexport)	// tmp linker flag, forces lib to exist
float lavaRise(float serverLevel)
{
	return (serverLevel + 0.02f);
}


LAVAPLUGIN_SYMBOL NetworkManager *gameState = 0;

enum Messages
{
	CHAT_ID = ID_USER_PACKET_ENUM + 1,
};


int init()
{
	if (gameState == 0)
	{
		gameState = new NetworkManager();
		return 1;
	}
	return 0;
}


int end()
{
	if (gameState != 0)
	{
		delete gameState;
		gameState = 0;
		return 1;
	}
	return 0;
}

int initNetworking(int serverPort)
{
	gameState->init(serverPort);
	return 0;
}

char * getPacket()
{
	return gameState->getPacket();
}


const char * getGUID()
{
	return gameState->getGUID().ToString();
}


void sendNetworkPacket(char * packet, int size, unsigned long long destID)
{
	gameState->sendPacket(packet, size, destID ? RakNet::AddressOrGUID(RakNet::RakNetGUID(destID)) : RakNet::UNASSIGNED_SYSTEM_ADDRESS);
}

void broadcastNetworkPacket(char * packet, int size)
{
	gameState->sendToAll(packet, size);
}

const char* getIP()
{
	return gameState->getIP();
}

