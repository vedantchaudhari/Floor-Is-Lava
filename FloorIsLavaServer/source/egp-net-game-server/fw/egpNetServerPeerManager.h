/*
	egpNetServerPeerManager.h
	By Dan Buckstein
	(c) 2017-2018

	Specialized peer manager for server.

	Additional contributions by (and date): 

*/

#ifndef __EGPNET_SERVERPEERMANAGER_H_
#define __EGPNET_SERVERPEERMANAGER_H_


#include "egp-net/fw/egpNetPeerManager.h"


// server manager
class egpNetServerPeerManager : public egpNetPeerManager
{
protected: 

	// enumeration of server-generated packet identifiers
	// (e.g. list things sent by server)
	enum me_ServerPacketIdentifier
	{
		e_id_serverPacketBegin = e_id_packetEnd,

		// ****TO-DO: implement client-pertinent, server-generated identifiers
	//	e_id_srv_routePrivateMessage,	// server delivering a private message
	//	e_id_srv_gameUpdate,			// server sending game update
										// etc.

		// end
		e_id_serverPacketEnd
	};


	// packet individual packet; function should not change manager
	//	packet: pointer to packet
	//	packetIndex: index in sequence of processed packets
	// return 0 to stop processing packets
	virtual int ProcessPacket(const RakNet::Packet *const packet, const unsigned int packetIndex) const;


public: 

	// ctor
	egpNetServerPeerManager();

	// dtor
	virtual ~egpNetServerPeerManager();

};


#endif	// !__EGPNET_SERVERPEERMANAGER_H_