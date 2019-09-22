#pragma once
#include <cstdint>
#include <SpelSyltCommonLibrary/Memory/Public/DataBlob.h>

namespace CL
{
	/*
	The SpelSylt compression header is defined as follows:
	|	Endian	|	Size	|	Content		|	Description																								|
	|-----------|-----------|---------------|-----------------------------------------------------------------------------------------------------------|
	|	Big		|	4B		|	"SSCI"		|	"SpelSyltCompressionIdentifier" this is used to determine if a file is compressed using this library	|
	|	Little	|	4B		|	0-n			|	The size of the uncompressed data																		|
	|	Little	|	4B		|	0-n			|	Identifier for the format of the compression															|
	|-----------|-----------|---------------|-----------------------------------------------------------------------------------------------------------|
	*/

	//SSCI as Big endian
	static const int32_t CompressionIdentifier = 0x53534349;

	enum class ECompressionFormat : int32_t
	{
		Invalid,
		Zlib,
		//Add additional formats here
	};

	enum class ECompressionResult
	{
		Success,			//0: Successfully compressed/uncompressed the data
		BufferSizeError,	//1: The buffer provided to store compressed/uncompressed data is too small
		MemoryError,		//2: Not enough memory to perform compress/uncompress operation
		CompressionError,	//3: Error with parameters provided to the compression implementation (may vary depending on format)
		FormatError,		//4: The format does not have any implementation yet
		IsUncompressed,		//5 [Uncompress only]: The data is already uncompressed
	};

	struct SHeaderData
	{
		//Do not reorder these as it will break previously compressed data
		uint32_t Identifier = 0;
		uint32_t UncompressedSize = 0;
		uint32_t Format = 0;
	};

	class CCompressor
	{
	public:
		bool DataIsCompressed(const SDataBlob& InData);
		ECompressionResult CompressData(const SDataBlob& InUncompressedData, SDataBlob& OutCompressedData, ECompressionFormat InFormat);
		ECompressionResult UncompressData(const SDataBlob& InCompressedData, SDataBlob& OutUncompressedData);
	private:
		void WriteHeader(SDataBlob& InData, const uint32_t InUncompressedSize, ECompressionFormat InUsedFormat);
		void ReadHeader(const SDataBlob& InData, SHeaderData& OutReadHeader);
		bool HeaderIndicatesCompression(const SHeaderData& InHeader) const;

		ECompressionResult CompressImplementation(
			const void* InUncompressedData, 
			const uint32_t InUncompressedDataSize,
			void* OutCompressedData, 
			uint32_t& InOutCompressedSize, 
			ECompressionFormat InFormat);

		ECompressionResult UncompressImplementation(
			const void* InCompressedData,
			const uint32_t InCompressedDataSize,
			void* OutUncompressedData,
			uint32_t& OutUncompressedSize,
			ECompressionFormat InFormat);

		ECompressionResult CompressBoundImplementation(
			const uint32_t InUncompressedDataSize,
			uint32_t& OutBound,
			ECompressionFormat InFormat);
	};
}