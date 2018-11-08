/*
	egpNetSerializableDataExample.cpp
	By Dan Buckstein
	(c) 2017-2018

	Source for simple serializable data component.

	Additional contributions by (and date): 

*/

#include "egp-net/fw/egpNetSerializableDataExample.h"


egpSerializableDataExample::egpSerializableDataExample(const int someInt, const float someFlt, const double someDbl, const unsigned int dynArrayLen)
{
	// ****TO-DO: 
	// init internal data
	data.dummyInt = someInt;
	data.dummyFlt = someFlt;
	data.dummyDbl = someDbl;

	dummyIntArrayLen = dynArrayLen;
	dummyIntArraySz = dynArrayLen * sizeof(int);
	dummyIntArray = dynArrayLen ? new int[dynArrayLen] : 0;
}

egpSerializableDataExample::~egpSerializableDataExample()
{
	// ****TO-DO: 
	// dealloc pointer based things OWNED BY THIS
	// DO NOT DELETE THINGS IF THEY ARE OWNED AND MANAGED ELSEWHERE!!!
	if(dummyIntArray)	
	delete[] dummyIntArray;
}

int egpSerializableDataExample::Serialize(RakNet::BitStream *bs) const
{
	// ****TO-DO: 
	// stuff all data owned by this into array
	// do so in a way that it could be read back again
	if (bs)
	{
		//calc data size
		unsigned int totalSz = 0;
			
		totalSz += sizeof(data);
		bs->Write(data);

		totalSz += sizeof(dummyIntArraySz);
		bs->Write(dummyIntArraySz);

		if (dummyIntArraySz)
		{
			totalSz += dummyIntArraySz;
			bs->Write((char *)dummyIntArray, dummyIntArraySz);
		}
		//done
		return totalSz;
	}
	return 0;
}

int egpSerializableDataExample::Deserialize(RakNet::BitStream *bs)
{
	// ****TO-DO: 
	// fundamentally the opposite of serialize
	// read things back in the same order they would be written
	// do allocations and deallocations as needed
	if (bs)
	{
		unsigned int totalSz = 0;

		totalSz += sizeof(data);

		bs->Read(data);

		unsigned int tmpSz;
		totalSz += sizeof(tmpSz);
		bs->Read(tmpSz);
	
		if (dummyIntArraySz != tmpSz)
		{
			delete[] dummyIntArray;
			dummyIntArraySz = tmpSz;
			dummyIntArrayLen = tmpSz / sizeof(int);
			dummyIntArray = tmpSz ? new int[tmpSz] : 0;
		}

		if (dummyIntArraySz)
		{
			totalSz += dummyIntArraySz;
			bs->Read((char*)dummyIntArray, dummyIntArraySz);

		}


		//done
		return totalSz;
	}
	return 0;
}
