/*
	egpNetPeerManager.h
	By Dan Buckstein
	(c) 2017-2018

	Base interface for networked application management. Abstract manager for 
		RakNet peer interface; implements common peer utilities.
	NOTE: THIS IS NOT A GAME STATE; IT IS HIGHER-LEVEL... THINK DECOUPLING!

	Additional contributions by (and date): 

*/

#ifndef __EGPNET_PEERMANAGER_H_
#define __EGPNET_PEERMANAGER_H_


#include "utils/egpThread.h"
#include "utils/egpTimer.h"


#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/BitStream.h"
#include "RakNet/GetTime.h"


// ****TO-DO: connect peer manager to game state


// peer manager
class egpNetPeerManager abstract
{

	// internal utilities
	int InitializePeer(const bool doesConnect, const unsigned short maxInbound, const unsigned short portOffsetInbound);
	int TerminatePeer();
	int ConnectPeer(const char address[16], const unsigned short portOffset);
	int DisconnectPeer();
	int ProcessAllPackets() const;
	void ResetValues();


	// peer management
	// the Raknet peer interface has a LOT of features, including tracking 
	//	connection indices... we need this higher-level interface to know 
	//	how to use these features!
	// e.g.
	//	-get index of IP address and vice versa (maps connection ID to IP)
	//	-get your index on someone else's system
	//	-send single message
	//	-send multiple messages
	RakNet::RakPeerInterface *mp_peer;

	// connection counts for easy access: inbound only and total
	unsigned short m_maxInbound, m_maxConnect;

	// ports used for inbound and outbound connections
	unsigned short m_portIn, m_portOut;

	// networking management with thread
	int m_networkThreadAllowed;
	egpThread m_networkThread[1];

	// thread launch function
	static int NetworkingThread(egpNetPeerManager *mgr);


protected: 

	// enumeration of custom packet identifiers
	enum me_PacketIdentifier
	{
		e_id_packetBegin = ID_USER_PACKET_ENUM,

		// ****TO-DO: implement general identifiers
		// these should be peer-type-agnostic, i.e. either server or client
		// some suggestions: 
	//	e_id_stateInput,	// packet data contains remote input
	//	e_id_stateData,		// packet data contains info about game state
							// etc.

		// end; indicates where specialized managers can start
		e_id_packetEnd
	};


	// ctor
	egpNetPeerManager();


	// packet individual packet; function should not change manager
	//	packet: pointer to packet
	//	packetIndex: index in sequence of processed packets
	// return 0 to stop processing packets
	virtual int ProcessPacket(const RakNet::Packet *const packet, const unsigned int packetIndex) const;


	// packet management utilities: wrappers for functionalities in peer
	// send packet
	//	bs: pointer to bitstream
	//	connectionIndex: index of connected peer (pass -1 for none)
	//	broadcast: if true, sends to all but specified connection; if false, sends to only specified connection
	//	reliable: set reliability of packet
	// return leading message identifier
	int SendPacket(const RakNet::BitStream *bs, const short connectionIndex, const bool broadcast, const bool reliable) const;


	// utility to write time stamps: writes ID_TIMESTAMP and two time stamps
	//	-> only the first stamp will be pre-processed by RakNet on receipt!
	//	bs: pointer to bitstream
	//	t: first time stamp (could be local time)
	//	t0: second time stamp (use creatively)
	// return: number of bytes written
	static int WriteTimeStamp(RakNet::BitStream *bs, const RakNet::Time &t, const RakNet::Time &t0);

	// utility to read/skip time stamps: skip ID_TIMESTAMP and read two time stamps
	//	-> only the first stamp has been pre-processed by RakNet on receipt!
	//	bs: pointer to bitstream
	//	t_out: first time stamp (could be remote's time on local clock)
	//	t0_out: second time stamp (use creatively)
	// return: number of bytes written
	static int ReadTimeStamp(RakNet::BitStream *bs, RakNet::Time &t_out, RakNet::Time &t0_out);

	// utility to write message identifier (avoids common mistake of writing too many bytes)
	//	bs: pointer to bitstream
	//	messageID: message identifier
	// return: 1 if success, 0 if fail
	static int WriteMessageID(RakNet::BitStream *bs, const char &messageID);

	// utility to read/skip message identifier (avoids common mistake of writing too many bytes)
	//	bs: pointer to bitstream
	//	messageID_out: message identifier
	// return: 1 if success, 0 if fail
	static int ReadMessageID(RakNet::BitStream *bs, char &messageID_out);


public: 

	// virtual dtor
	virtual ~egpNetPeerManager();


	// api for starting up networking
	//	doesConnect: peer will attemp to connect to someone, should add connection slot
	//	maxInbound: number of inbound connections allowed
	//	portOffsetInbound: port offset to use if allowing inbound connections (pass 0 for default)
	// return 1 if success, 0 if fail
	virtual int StartupNetworking(const bool doesConnect, const unsigned short maxInbound, const unsigned short portOffsetInbound = 0, const bool threaded = false);

	// api for shutting down networking
	// return 1 if success, 0 if fail
	virtual int ShutdownNetworking();

	// api for connection, if allowed (determined in startup)
	//	address: null-terminated IP address to connect to, formatted as "###.###.###.###"
	//	portOffset: port offset to get port (pass 0 for default)
	// return 1 if success, 0 if fail, -1 for invalid params
	virtual int Connect(const char address[16], const unsigned short portOffset = 0);

	// api for disconnection
	// return 1 if success, 0 if fail, -1 if not connected
	virtual int Disconnect();

	// api for networking update; publicly accessible for non-threaded networking
	// return packet count, 0 if no packets processed or not set up, -1 if threaded (fails)
	virtual int HandleNetworking() const;


	// get port with offset from default for this app
	//	portOffset: added to default to retrieve port (pass 0 for default)
	// return port
	static unsigned short GetPort(const unsigned short portOffset = 0);

};


#endif	// !__EGPNET_PEERMANAGER_H_