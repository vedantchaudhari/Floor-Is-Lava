/*
	egpNetPeerManager.cpp
	By Dan Buckstein
	(c) 2017-2018

	Base peer manager implementation.

	Additional contributions by (and date): 

*/

#include "egp-net/fw/egpNetPeerManager.h"


//-----------------------------------------------------------------------------
// private

int egpNetPeerManager::InitializePeer(const bool doesConnect, const unsigned short maxInbound, const unsigned short portOffsetInbound)
{
	// set connection info
	m_maxInbound = maxInbound;
	m_maxConnect = maxInbound + (doesConnect ? 1 : 0);
	m_portIn = maxInbound ? GetPort(portOffsetInbound) : 0;

	// allow thread to run if requested
	m_networkThreadAllowed = 1;

	// allocate peer
	mp_peer = RakNet::RakPeerInterface::GetInstance();

	// enable pinging for accurate delays in time stamps
	mp_peer->SetOccasionalPing(true);

	// open socket if we are accepting connections
	RakNet::SocketDescriptor sd = m_maxInbound ? RakNet::SocketDescriptor(m_portIn, 0) : RakNet::SocketDescriptor();
	mp_peer->Startup(m_maxConnect, &sd, 1);
	mp_peer->SetMaximumIncomingConnections(m_maxInbound);
	
	// done
	return 1;
}

int egpNetPeerManager::TerminatePeer()
{
	// stop and reset thread (if used)
	m_networkThreadAllowed = 0;
	while (m_networkThread->running);
	memset(m_networkThread, 0, sizeof(m_networkThread));

	// can close connections manually with notification
	// (the shutdown function 'supposedly' does this...)
	for (unsigned short i = 0; i < m_maxConnect; ++i)
		mp_peer->CloseConnection(mp_peer->GetSystemAddressFromIndex(i), true);

	// shutdown peer and close all connections
	mp_peer->Shutdown(0);

	// destroy peer
	RakNet::RakPeerInterface::DestroyInstance(mp_peer);

	// reset values
	ResetValues();

	// done
	return 1;
}

int egpNetPeerManager::ConnectPeer(const char address[16], const unsigned short portOffset)
{
	const unsigned short portOut = GetPort(portOffset);
	if (address && *address && portOut != m_portIn)
	{
		// set and connect
		m_portOut = portOut;
		mp_peer->Connect(address, portOut, 0, 0);

		// done
		return 1;
	}

	// invalid param
	return -1;
}

int egpNetPeerManager::DisconnectPeer()
{
	if (m_portOut)
	{
		// reset and close connection
		// assumes outbound connection is always first!
		m_portOut = 0;
		mp_peer->CloseConnection(mp_peer->GetSystemAddressFromIndex(0), true);

		// done
		return 1;
	}

	// not connected
	return -1;
}

int egpNetPeerManager::ProcessAllPackets() const
{
	RakNet::Packet *packet;
	unsigned int i;
	for (packet = mp_peer->Receive(), i = 0;
		packet && ProcessPacket(packet, i);
		mp_peer->DeallocatePacket(packet), packet = mp_peer->Receive(), ++i);

	// done
	return i;
}

void egpNetPeerManager::ResetValues()
{
	mp_peer = 0;
	m_maxInbound = m_maxConnect = 0;
	m_portIn = m_portOut = 0;
}


// thread func
int egpNetPeerManager::NetworkingThread(egpNetPeerManager *mgr)
{
	// ****TO-DO: set local timer for thread
	// 0 is continuous (always ticks)
	egpTimer threadTimer[1] = { 0 };
	egpTimerSet(threadTimer, 0.0);

	// start networing timer
	egpTimerStart(threadTimer);

	// loop
	while (mgr->m_networkThreadAllowed)
		if (egpTimerUpdate(threadTimer))
			mgr->ProcessAllPackets();

	// stop timer
	egpTimerStop(threadTimer);

	// done
	return (threadTimer->ticks);
}


//-----------------------------------------------------------------------------
// protected

// ctor
egpNetPeerManager::egpNetPeerManager()
{
	// reset everything
	ResetValues();

	m_networkThreadAllowed = 0;
	memset(m_networkThread, 0, sizeof(m_networkThread));
}


// process individual packet
int egpNetPeerManager::ProcessPacket(const RakNet::Packet *const packet, const unsigned int packetIndex) const
{
	// ****TO-DO: implement base class packet processor
	//	-> base class should process only peer-type-agnostic packets, perhaps 
	//		even including RakNet ones such as ID_CONNECTION_REQUEST_ACCEPTED
	//	-> base class should have first dibs at packet

	// done
	return (packetIndex + 1);
}


// send packet using bitstream
int egpNetPeerManager::SendPacket(const RakNet::BitStream *bs, const short connectionIndex, const bool broadcast, const bool reliable) const
{
	if (mp_peer)
	{
		const PacketPriority priorityFlag = IMMEDIATE_PRIORITY;
		const PacketReliability reliableFlag = reliable ? RELIABLE_SEQUENCED : UNRELIABLE_SEQUENCED;
		const RakNet::SystemAddress address = connectionIndex >= 0 ? mp_peer->GetSystemAddressFromIndex(connectionIndex) : RakNet::UNASSIGNED_SYSTEM_ADDRESS;

		// send bitsream
		return mp_peer->Send(bs, priorityFlag, reliableFlag, 0, address, broadcast);
	}
	return 0;
}


// write time stamp
int egpNetPeerManager::WriteTimeStamp(RakNet::BitStream *bs, const RakNet::Time &t, const RakNet::Time &t0)
{
	const unsigned int ret = (sizeof(char) + sizeof(RakNet::Time) * 2);
	if (bs)
	{
		bs->Write((char)ID_TIMESTAMP);
		bs->Write(t);
		bs->Write(t0);
		return ret;
	}
	return 0;
}

// read/skip time stamp
int egpNetPeerManager::ReadTimeStamp(RakNet::BitStream *bs, RakNet::Time &t_out, RakNet::Time &t0_out)
{
	const unsigned int ret = (sizeof(char) + sizeof(RakNet::Time) * 2);
	char tag;
	if (bs)
	{
		bs->Read(tag);
		bs->Read(t_out);
		bs->Read(t0_out);
		return ret;
	}
	return 0;
}

// write message identifier
int egpNetPeerManager::WriteMessageID(RakNet::BitStream *bs, const char &messageID)
{
	if (bs)
	{
		bs->Write(messageID);
		return 1;
	}
	return 0;
}

// read/skip message identifier
int egpNetPeerManager::ReadMessageID(RakNet::BitStream *bs, char &messageID_out)
{
	if (bs)
	{
		bs->Read(messageID_out);
		return 1;
	}
	return 0;
}


//-----------------------------------------------------------------------------
// public

// dtor
egpNetPeerManager::~egpNetPeerManager()
{
	ShutdownNetworking();
}


int egpNetPeerManager::StartupNetworking(const bool doesConnect, const unsigned short maxInbound, const unsigned short portOffsetInbound, const bool threaded)
{
	if (!mp_peer)
	{
		// base class: call common initializer
		const int result = InitializePeer(doesConnect, maxInbound, portOffsetInbound);
		
		// start threaded update if requested
		if (threaded)
			egpCreateThread(m_networkThread, (egpThreadFunc)NetworkingThread, this);

		// done
		return result;
	}
	return 0;
}

int egpNetPeerManager::ShutdownNetworking()
{
	if (mp_peer)
	{
		// base class: call common terminator
		const int result = TerminatePeer();

		// done
		return result;
	}
	return 0;
}

int egpNetPeerManager::Connect(const char address[16], const unsigned short portOffset)
{
	if (mp_peer)
	{
		// base class: call common connect
		const int result = ConnectPeer(address, portOffset);

		// done
		return result;
	}
	return 0;
}

int egpNetPeerManager::Disconnect()
{
	if (mp_peer)
	{
		// base class: call common disconnect
		const int result = DisconnectPeer();

		// done
		return result;
	}
	return 0;
}


// networking update
int egpNetPeerManager::HandleNetworking() const
{
	if (mp_peer)
	{
		// base class: call common processor if not threaded
		const int result = !m_networkThread->handle
			? ProcessAllPackets() : -1;

		// done
		return result;
	}
	return 0;
}


// get port
unsigned short egpNetPeerManager::GetPort(const unsigned short portOffset)
{
	static const unsigned short defaultPort = 1111;
	return (defaultPort + portOffset);
}
