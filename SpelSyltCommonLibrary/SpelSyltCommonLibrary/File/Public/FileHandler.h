#pragma once
#include <string>
#include <fstream>

namespace CL
{
	struct SDataBlob;

	//------------------------------------------------------------

	enum class EFileResult
	{
		Success,
		FileNotFound,
		UnableToOpen,
	};

	//------------------------------------------------------------

	enum class EFileOperationResult
	{
		Success,
		FileNotOpen,
		FileError,
	};

	//------------------------------------------------------------

	enum class EFileMode
	{
		//Open the file. If it does not exist, fail
		Open,				

		//Open the file if it exists, otherwise create it
		CreateOrOpen,		

		//Replace the file if it exists, otherwise create it
		CreateOrReplace,
	};

	//------------------------------------------------------------

	enum class EOpenMode
	{
		//Remove all contents of the file on open
		FlushContent,

		//Place marker at beginning of file and overwrite as it progresses
		OverwriteContent,

		//Place marker at the end of file and append all written data
		WriteAtEnd,
	};

	//------------------------------------------------------------

	class CBinaryFile
	{
	public:
		friend class CFileHandler;

		CBinaryFile();
		~CBinaryFile();

		void Close();

		EFileOperationResult Write(const SDataBlob& InBlob);
		EFileOperationResult Read(SDataBlob& OutBlob);

	private:
		EFileResult Open(const std::string& InPath, EOpenMode InOpenMode);

		std::fstream FileStream;
		unsigned long long FileSize;
	};

	//------------------------------------------------------------

	class CFileHandler
	{
	public:
		CFileHandler();
		CFileHandler(const std::string& InRootDirectory);
		
		void SetRootDirectory(const std::string& InRootDirectoryPath);

		EFileResult OpenFile(
			CBinaryFile& OutFileHandle, 
			const std::string& InPath, 
			EFileMode InFileMode, 
			EOpenMode InOpenMode, 
			bool InOverrideRoot = false);

	private:
		std::string RootDirectory;
		bool HasRoot;
	};

	//------------------------------------------------------------
}