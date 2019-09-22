#include "SpelSyltCommonLibrary/Memory/Public/DataBlob.h"

#include <cassert>
#include <memory>

//------------------------------------------------------------

CL::SDataBlob::SDataBlob()
	: Data(nullptr)
	, Size(0ull)
	, UsedSize(0ull)
{
}

//------------------------------------------------------------

CL::SDataBlob::SDataBlob(const SDataBlob& InOther)
	: Data(nullptr)
	, Size(0ull)
	, UsedSize(0ull)
{
	SetSizeInBytes(InOther.Size);
	SetUsedSizeInBytes(InOther.UsedSize);
	AddToBlob(InOther.Data, Size);
}

//------------------------------------------------------------

void CL::SDataBlob::SetSizeInBytes(const unsigned long long InSize)
{
	if (Data)
	{
		delete[Size] Data;
		Data = nullptr;
	}

	Data = new char[InSize];
	Size = InSize;
}

//------------------------------------------------------------

void CL::SDataBlob::SetUsedSizeInBytes(const unsigned long long InUsedSize, bool ShouldShrink)
{
	UsedSize = InUsedSize;

	if (ShouldShrink)
	{
		char* NewBuffer = new char[UsedSize];
		memcpy_s(NewBuffer, UsedSize, Data, UsedSize);
		delete[Size] Data;

		Data = NewBuffer;
		Size = UsedSize;
	}
}

//------------------------------------------------------------

void CL::SDataBlob::AddToBlob(const void* InData, const unsigned long long InDataSize)
{
	assert(InDataSize <= Size && "Can not add data of bigger size than blob size to data blob");
	memcpy_s(Data, Size, InData, InDataSize);
	UsedSize = InDataSize;
}

//------------------------------------------------------------

void CL::SDataBlob::CopyBlobData(void* InDestination, const unsigned long long InDataSize)
{
	memcpy_s(InDestination, InDataSize, Data, InDataSize);
}

//------------------------------------------------------------

char* CL::SDataBlob::GetData(unsigned long long InOffset)
{
	return &Data[InOffset];
}

//------------------------------------------------------------

const char* CL::SDataBlob::GetData(unsigned long long InOffset) const
{
	return &Data[InOffset];
}

//------------------------------------------------------------

unsigned long long CL::SDataBlob::GetSize() const
{
	return Size;
}

//------------------------------------------------------------

unsigned long long CL::SDataBlob::GetUsedSize() const
{
	return UsedSize;
}

//------------------------------------------------------------