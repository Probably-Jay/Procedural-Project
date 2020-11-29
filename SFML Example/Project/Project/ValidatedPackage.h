#pragma once
#include "SFML/Network.hpp"
using sf::Packet;
class ValidatedPackage :
	public Packet
{
	virtual const void* onSend(std::size_t& size) {
		const void* sourceData = getData();
		std::size_t sourceSize = getDataSize();

		return applyChecksum(sourceData, sourceSize, &size);
	}

	virtual void onReceive(const void* data, std::size_t size)
	{
		std::size_t dstSize;
		const void* dstData = validateChecksum(data, size, &dstSize); 
		append(dstData, dstSize);
	}

	const void* applyChecksum(const void*& sourceData, size_t sourceSize, size_t* size)
	{
		*size = sourceSize;
		return sourceData;
	}

	const void* validateChecksum(const void*& data, size_t size, size_t * dstSize) {
		*dstSize = size;
		return data;
	}
};

