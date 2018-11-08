/*
	egpNetClientPeerManager.h
	By Dan Buckstein
	(c) 2017-2018

	Specialized peer manager for client.

	Additional contributions by (and date): 

*/

#ifndef __EGPNET_CLIENTPEERMANAGER_H_
#define __EGPNET_CLIENTPEERMANAGER_H_


#include "egp-net/fw/egpNetPeerManager.h"


// client manager
class egpNetClientPeerManager : public egpNetPeerManager
{
protected: 

	// enumeration of client-generated packet identifiers: 
	// (e.g. list things sent by client)
	enum me_ClientPacketIdentifier
	{
		e_id_clientPacketBegin = e_id_packetEnd,

		// ****TO-DO: implement server-pertinent, client-generated identifiers
	//	e_id_cli_requestUsername,		// client trying to register name
	//	e_id_cli_input,					// client sending input signal
										// etc.

		// end
		e_id_clientPacketEnd
	};


	// packet individual packet; function should not change manager
	//	packet: pointer to packet
	//	packetIndex: index in sequence of processed packets
	// return 0 to stop processing packets
	virtual int ProcessPacket(const RakNet::Packet *const packet, const unsigned int packetIndex) const;


public: 

	// ctor
	egpNetClientPeerManager();

	// dtor
	virtual ~egpNetClientPeerManager();

};


#endif	// !__EGPNET_CLIENTPEERMANAGER_H_