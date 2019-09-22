#pragma once

namespace CL
{
	struct SDataBlob
	{
	public:
		SDataBlob();
		SDataBlob(const SDataBlob& InOther);

		void SetSizeInBytes(const unsigned long long InSize);
		void SetUsedSizeInBytes(const unsigned long long InUsedSize, bool ShouldShrink = false);

		void AddToBlob(const void* InData, const unsigned long long InDataSize);
		void CopyBlobData(void* InDestination, const unsigned long long InDataSize);

		char* GetData(unsigned long long InOffset = 0ull);
		const char* GetData(unsigned long long InOffset = 0ull) const;
		unsigned long long GetSize() const;
		unsigned long long GetUsedSize() const;

		template<typename T>
		void operator<<(const T& InCopyFrom);

		template<typename T>
		void operator>>(T& InCopyTo);

	private:
		char* Data;
		unsigned long long Size;
		unsigned long long UsedSize;
	};
}

//------------------------------------------------------------

template<typename T>
inline void CL::SDataBlob::operator<<(const T& InCopyFrom)
{
	AddToBlob(&InCopyFrom, sizeof(T));
}

//------------------------------------------------------------

template<typename T>
inline void CL::SDataBlob::operator>>(T& InCopyTo)
{
	CopyBlobData(&InCopyTo, sizeof(T));
}

//------------------------------------------------------------