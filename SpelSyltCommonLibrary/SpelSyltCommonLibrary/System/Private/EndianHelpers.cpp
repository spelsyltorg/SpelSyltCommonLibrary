#include <SpelSyltCommonLibrary/System/Public/EndianHelpers.h>

#include <stdint.h>
#include <intrin.h>

//------------------------------------------------------------

CL::ESystemEndianType CL::GetSystemEndianType()
{
	union
	{
		unsigned int asInt;
		uint32_t asByteArray[4];
	} intVal = {0x01020304};

	return intVal.asByteArray[0] == 1 ? ESystemEndianType::Big : ESystemEndianType::Little;
}

//------------------------------------------------------------

short CL::SwapEndian(const short InSwapSrc)
{
	return _byteswap_ushort(InSwapSrc);
}

//------------------------------------------------------------

unsigned short CL::SwapEndian(const unsigned short InSwapSrc)
{
	return _byteswap_ushort(InSwapSrc);
}

//------------------------------------------------------------

int CL::SwapEndian(const int InSwapSrc)
{
	return _byteswap_ulong(InSwapSrc);
}

//------------------------------------------------------------

unsigned int CL::SwapEndian(const unsigned int InSwapSrc)
{
	return _byteswap_ulong(InSwapSrc);
}

//------------------------------------------------------------

long CL::SwapEndian(const long InSwapSrc)
{
	return _byteswap_ulong(InSwapSrc);
}

//------------------------------------------------------------

unsigned long CL::SwapEndian(const unsigned long InSwapSrc)
{
	return _byteswap_ulong(InSwapSrc);
}

//------------------------------------------------------------

long long CL::SwapEndian(const long long InSwapSrc)
{
	return _byteswap_uint64(InSwapSrc);
}

//------------------------------------------------------------

unsigned long long CL::SwapEndian(const unsigned long long InSwapSrc)
{
	return _byteswap_uint64(InSwapSrc);
}

//------------------------------------------------------------
