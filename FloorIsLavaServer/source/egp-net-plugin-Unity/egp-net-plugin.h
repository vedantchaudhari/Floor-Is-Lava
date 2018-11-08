/*
	EGP Networking: Plugin Interface/Wrapper
	Dan Buckstein
	October 2018

	Main interface for plugin. Defines symbols to be exposed to whatever 
		application consumes the plugin. Targeted for Unity but should also 
		be accessible by custom executables (e.g. test app).
*/

#ifndef _EGP_NET_PLUGIN_H_
#define _EGP_NET_PLUGIN_H_

#include "egp-net-plugin-config.h"
#include "Libs.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


	//	startup and shutdown
	LAVAPLUGIN_SYMBOL int init();
	LAVAPLUGIN_SYMBOL int end();

	LAVAPLUGIN_SYMBOL const char* getGUID();

	LAVAPLUGIN_SYMBOL int initNetworking(int serverPort = 60);
	LAVAPLUGIN_SYMBOL char* getPacket();

	LAVAPLUGIN_SYMBOL void sendNetworkPacket(char* packet, int size = 8, unsigned long long destID = 0);

	LAVAPLUGIN_SYMBOL void broadcastNetworkPacket(char* packet, int size = 8);
	LAVAPLUGIN_SYMBOL const char* getIP();
#ifdef __cplusplus
}
#endif // __cplusplus

#endif	// !_EGP_NET_PLUGIN_H_