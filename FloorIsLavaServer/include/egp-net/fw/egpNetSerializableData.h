/*
	egpNetSerializableData.h
	By Dan Buckstein
	(c) 2017-2018

	Base class for some pure data or component that can serialize its data to 
		a RakNet bitstream.

	Additional contributions by (and date): 

*/

#ifndef __EGP_NET_SERIALIZABLEDATA_H_
#define __EGP_NET_SERIALIZABLEDATA_H_


#include "RakNet/BitStream.h"


// serializable data
class egpSerializableData
{
public: 
	
	// serialize: defines how the data should be written to the bitstream
	//	bs: pointer to bitstream
	// return number of bytes written
	virtual int Serialize(RakNet::BitStream *bs) const = 0;

	// deserialize: defines how the data should be read from the bitstream
	//	bs: pointer to bitstream
	// return number of bytes read
	virtual int Deserialize(RakNet::BitStream *bs) = 0;

	// virtual dtor
	virtual ~egpSerializableData() {};

};


#endif	// !__EGP_NET_SERIALIZABLEDATA_H_