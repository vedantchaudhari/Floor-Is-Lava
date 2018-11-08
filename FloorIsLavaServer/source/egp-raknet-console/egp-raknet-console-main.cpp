/*
	RakNet Console Application
	Prepared by Dan Buckstein
	September 5, 2018

	Simple RakNet application following official tutorials.

	****TO-DO: add your own implementations and comments

	Resources: 
	http://www.jenkinssoftware.com/raknet/manual/tutorialsample1.html
	http://www.jenkinssoftware.com/raknet/manual/tutorialsample2.html
	http://www.jenkinssoftware.com/raknet/manual/tutorialsample3.html

	http://www.raknet.net/raknet/manual/creatingpackets.html
	http://www.raknet.net/raknet/manual/receivingpackets.html
	http://www.raknet.net/raknet/manual/sendingpackets.html
	http://www.raknet.net/raknet/manual/timestamping.html

	Read them for the secrets to success!
	E.g. pointers on pointers ;)
*/


// standard includes
#include <stdio.h>
#include <string.h>


// RakNet includes
#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"


enum GameMessages
{
	ID_CUSTOM_MESSAGE_START = ID_USER_PACKET_ENUM,

	ID_GAME_MESSAGE_1, 
};


#pragma pack(push, 1)

struct GameMessageData
{
	unsigned char typeID;

	// ****TO-DO: implement game message data struct

};

#pragma pack (pop)


// entry function
int main(int const argc, char const *const *const argv)
{
	// buffer
	const unsigned int bufferSz = 512;
	char str[bufferSz];

	// create and return instance of peer interface
	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();

	// global peer settings for this app
	int isServer = 0;
	unsigned short serverPort = 60000;

	// ask user for peer type
	printf("(C)lient or (S)erver?\n");
	fgets(str, bufferSz, stdin);

	// start networking
	if ((str[0] == 'c') || (str[0] == 'C'))
	{
		RakNet::SocketDescriptor sd;
		peer->Startup(1, &sd, 1);

		printf("Enter server IP or hit enter for 127.0.0.1\n");
		fgets(str, bufferSz, stdin);

		if (str[0] == '\n')
		{
			strcpy(str, "127.0.0.1");
		}

		printf("Starting the client.\n");
		peer->Connect(str, serverPort, 0, 0);
	}
	else
	{
		printf("Enter maximum number of clients: \n");
		fgets(str, bufferSz, stdin);

		unsigned int maxClients = atoi(str);
		RakNet::SocketDescriptor sd(serverPort, 0);
		peer->Startup(maxClients, &sd, 1);

		// We need to let the server accept incoming connections from the clients
		printf("Starting the server.\n");
		peer->SetMaximumIncomingConnections(maxClients);
		isServer = 1;
	}


	RakNet::Packet *packet;

	while (1)
	{
		for (
			packet = peer->Receive(); 
			packet; 
			peer->DeallocatePacket(packet), packet = peer->Receive()
			)
		{
			switch (packet->data[0])
			{
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				printf("Another client has disconnected.\n");
				break;
			case ID_REMOTE_CONNECTION_LOST:
				printf("Another client has lost the connection.\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				printf("Another client has connected.\n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				printf("Our connection request has been accepted.\n");
				{
					// Use a BitStream to write a custom user message
					// Bitstreams are easier to use than sending casted structures, 
					//	and handle endian swapping automatically
				//	RakNet::BitStream bsOut;
				//	bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
				//	bsOut.Write("Hello world");
				//	peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

					// ****TO-DO: write and send packet without using bitstream

				}
				break;
			case ID_NEW_INCOMING_CONNECTION:
				printf("A connection is incoming.\n");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("The server is full.\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				if (isServer) {
					printf("A client has disconnected.\n");
				}
				else {
					printf("We have been disconnected.\n");
				}
				break;
			case ID_CONNECTION_LOST:
				if (isServer) {
					printf("A client lost the connection.\n");
				}
				else {
					printf("Connection lost.\n");
				}
				break;

			case ID_GAME_MESSAGE_1:
				printf("DEBUG MESSAGE: received packet ID_GAME_MESSAGE_1.\n");
				{
				//	RakNet::RakString rs;
				//	RakNet::BitStream bsIn(packet->data, packet->length, false);
				//	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
				//	bsIn.Read(rs);
				//	printf("%s\n", rs.C_String());

					// ****TO-DO: read packet without using bitstream

				}
				break;

			default:
				printf("Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}
		}
	}


	// shut down networking by destroying peer interface instance
	RakNet::RakPeerInterface::DestroyInstance(peer);


	// exit
	printf("\n\n");
	system("pause");
	return 0;
}
