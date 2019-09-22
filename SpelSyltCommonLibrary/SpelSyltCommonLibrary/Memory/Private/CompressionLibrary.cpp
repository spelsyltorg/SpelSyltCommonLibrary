#include "SpelSyltCommonLibrary/Memory/Public/CompressionLibrary.h"
#include "SpelSyltCommonLibrary/System/Public/EndianHelpers.h"

#include <memory>

//------------------------------------------------------------

bool CL::CCompressor::DataIsCompressed(const SDataBlob& InData)
{
	SHeaderData HeaderData = {};
	ReadHeader(InData, HeaderData);
	return HeaderIndicatesCompression(HeaderData);
}

//------------------------------------------------------------

CL::ECompressionResult CL::CCompressor::CompressData(const SDataBlob& InUncompressedData, SDataBlob& OutCompressedData, ECompressionFormat InFormat)
{
	const uint32_t UncompressedSize = static_cast<uint32_t>(InUncompressedData.GetSize());

	uint32_t EstimatedCompressedSize;
	if (CompressBoundImplementation(UncompressedSize, EstimatedCompressedSize, InFormat) != ECompressionResult::Success)
	{
		return ECompressionResult::FormatError;
	}
	
	uint32_t CompressedSize = EstimatedCompressedSize + sizeof(SHeaderData);

	OutCompressedData.SetSizeInBytes(CompressedSize);

	const char* UncompressedData = InUncompressedData.GetData();

	//We offset the compressed data as we need to leave space for the header without overwriting the actual data
	char* CompressedData = &(OutCompressedData.GetData()[sizeof(SHeaderData)]);

	const ECompressionResult Result = CompressImplementation(
		UncompressedData, 
		UncompressedSize, 
		CompressedData, 
		CompressedSize, 
		InFormat);

	if (Result == ECompressionResult::Success)
	{
		WriteHeader(OutCompressedData, UncompressedSize, InFormat);

		OutCompressedData.SetUsedSizeInBytes(CompressedSize + sizeof(SHeaderData));
	}

	return Result;
}

//------------------------------------------------------------

CL::ECompressionResult CL::CCompressor::UncompressData(const SDataBlob& InCompressedData, SDataBlob& OutUncompressedData)
{
	SHeaderData CompressionHeader = {};
	ReadHeader(InCompressedData, CompressionHeader);

	if (!HeaderIndicatesCompression(CompressionHeader))
	{
		return ECompressionResult::IsUncompressed;
	}

	uint32_t UncompressedSize = CompressionHeader.UncompressedSize;
	const ECompressionFormat Format = static_cast<ECompressionFormat>(CompressionHeader.Format);
	OutUncompressedData.SetSizeInBytes(UncompressedSize);

	const char* CompressedData = &(InCompressedData.GetData()[sizeof(SHeaderData)]);
	const uint32_t CompressedDataSize = static_cast<uint32_t>(InCompressedData.GetUsedSize() - sizeof(SHeaderData));
	
	ECompressionResult Result = UncompressImplementation(
		CompressedData, 
		CompressedDataSize, 
		OutUncompressedData.GetData(), 
		UncompressedSize, 
		Format);

	return Result;
}

//------------------------------------------------------------

void CL::CCompressor::WriteHeader(SDataBlob& InData, const uint32_t InUncompressedSize, ECompressionFormat InUsedFormat)
{
	const bool IsBigEndian = ( GetSystemEndianType() == ESystemEndianType::Big );  

	const uint32_t IdentifierBigEndian = IsBigEndian ? CompressionIdentifier : SwapEndian(CompressionIdentifier);
	const uint32_t UncompressedSizeLittleEndian = IsBigEndian ? SwapEndian(InUncompressedSize) : InUncompressedSize;
	const uint32_t FormatLittleEndian = IsBigEndian ? SwapEndian(static_cast<uint32_t>(InUsedFormat)) : static_cast<uint32_t>(InUsedFormat);

	SHeaderData HeaderData;
	HeaderData.Identifier = IdentifierBigEndian;
	HeaderData.UncompressedSize = UncompressedSizeLittleEndian;
	HeaderData.Format = FormatLittleEndian;

	memcpy_s(InData.GetData(), InData.GetSize(), &HeaderData, sizeof(SHeaderData));
}

//------------------------------------------------------------

void CL::CCompressor::ReadHeader(const SDataBlob& InData, SHeaderData& OutReadHeader)
{
	memcpy_s(&OutReadHeader, sizeof(SHeaderData), InData.GetData(), sizeof(SHeaderData));

	const bool IsLittleEndian = (GetSystemEndianType() == ESystemEndianType::Little);

	OutReadHeader.Identifier = IsLittleEndian ? SwapEndian(OutReadHeader.Identifier) : OutReadHeader.Identifier;
	OutReadHeader.UncompressedSize = IsLittleEndian ? OutReadHeader.UncompressedSize : SwapEndian(OutReadHeader.UncompressedSize);
	OutReadHeader.Format = IsLittleEndian ? OutReadHeader.Format : SwapEndian(OutReadHeader.Format);
}

//------------------------------------------------------------

bool CL::CCompressor::HeaderIndicatesCompression(const SHeaderData& InHeader) const
{
	return InHeader.Identifier == CompressionIdentifier;
}

//------------------------------------------------------------
//Begin all third party compression libraries we support here
//------------------------------------------------------------

CL::ECompressionResult CL::CCompressor::CompressImplementation(
	const void* InUncompressedData, 
	const uint32_t InUncompressedDataSize,
	void* OutCompressedData, 
	uint32_t& InOutCompressedSize,
	ECompressionFormat InFormat)
{
	switch (InFormat)
	{
	case CL::ECompressionFormat::Zlib:
		//Needs impl.
		break;
	}

	return ECompressionResult::FormatError;
}

//------------------------------------------------------------

CL::ECompressionResult CL::CCompressor::UncompressImplementation(
	const void* InCompressedData, 
	const uint32_t InCompressedDataSize,
	void* OutUncompressedData, 
	uint32_t& OutUncompressedSize, 
	ECompressionFormat InFormat)
{
	switch (InFormat)
	{
	case CL::ECompressionFormat::Zlib:
		//Needs impl.
		break;
	default:
		break;
	}

	return ECompressionResult::FormatError;
}

//------------------------------------------------------------

CL::ECompressionResult CL::CCompressor::CompressBoundImplementation(
	const uint32_t InUncompressedDataSize, 
	uint32_t& OutBound,
	ECompressionFormat InFormat)
{
	switch (InFormat)
	{
	case CL::ECompressionFormat::Zlib:
		break;
	default:
		break;
	}

	OutBound = 0;
	return ECompressionResult::FormatError;
}

//------------------------------------------------------------