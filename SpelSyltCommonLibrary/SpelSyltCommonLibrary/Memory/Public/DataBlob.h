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

		char* GetData();
		const char* GetData() const;
		unsigned long long GetSize() const;
		unsigned long long GetUsedSize() const;

	private:
		char* Data;
		unsigned long long Size;
		unsigned long long UsedSize;
	};
}