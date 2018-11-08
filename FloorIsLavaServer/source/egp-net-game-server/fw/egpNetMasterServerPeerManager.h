/*
	egpNetMasterServerPeerManager.h
	By Dan Buckstein
	(c) 2017-2018

	Specialized peer manager for master server.

	Additional contributions by (and date): 

*/

#ifndef __EGPNET_MASTERSERVERPEERMANAGER_H_
#define __EGPNET_MASTERSERVERPEERMANAGER_H_


#include "egp-net/fw/egpNetPeerManager.h"


// server manager
class egpNetMasterServerPeerManager : public egpNetPeerManager
{
protected: 

	// enumeration of server-generated packet identifiers
	// (e.g. list things sent by server)
	enum me_MasterServerPacketIdentifier
	{
		e_id_masterserverPacketBegin = e_id_packetEnd,

		// ****TO-DO: implement master server-generated identifiers
	//	e_id_msrv_availableServers,		// master server sending game servers
										// etc.

		// end
		e_id_masterserverPacketEnd
	};


	// packet individual packet; function should not change manager
	//	packet: pointer to packet
	//	packetIndex: index in sequence of processed packets
	// return 0 to stop processing packets
	virtual int ProcessPacket(const RakNet::Packet *const packet, const unsigned int packetIndex) const;


public: 

	// ctor
	egpNetMasterServerPeerManager();

	// dtor
	virtual ~egpNetMasterServerPeerManager();

};


#endif	// !__EGPNET_MASTERSERVERPEERMANAGER_H_