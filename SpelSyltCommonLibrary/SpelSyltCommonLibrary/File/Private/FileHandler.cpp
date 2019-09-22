#include "SpelSyltCommonLibrary/File/Public/FileHandler.h"
#include "SpelSyltCommonLibrary/Memory/Public/DataBlob.h"

#include <filesystem>

//------------------------------------------------------------

CL::CBinaryFile::CBinaryFile()
	: FileStream()
	, FileSize(0ull)
{
}

//------------------------------------------------------------

CL::CBinaryFile::~CBinaryFile()
{
	Close();
}

//------------------------------------------------------------

void CL::CBinaryFile::Close()
{
	if (FileStream.is_open())
	{
		FileStream.close();
	}
}

//------------------------------------------------------------

CL::EFileOperationResult CL::CBinaryFile::Write(const SDataBlob& InBlob)
{
	if (!FileStream.is_open())
	{
		return EFileOperationResult::FileNotOpen;
	}

	FileStream.write(InBlob.GetData(), InBlob.GetUsedSize());

	if (FileStream.bad())
	{
		return EFileOperationResult::FileError;
	}

	return EFileOperationResult::Success;
}

//------------------------------------------------------------

CL::EFileOperationResult CL::CBinaryFile::Read(SDataBlob& OutBlob)
{
	if (!FileStream.is_open())
	{
		return EFileOperationResult::FileNotOpen;
	}

	OutBlob.SetSizeInBytes(FileSize);
	FileStream.read(OutBlob.GetData(), FileSize);

	if (FileStream.bad())
	{
		return EFileOperationResult::FileError;
	}

	return EFileOperationResult::Success;
}

//------------------------------------------------------------

CL::EFileResult CL::CBinaryFile::Open(const std::string& InPath, EOpenMode InOpenMode)
{
	if (std::filesystem::exists(InPath))
	{
		FileSize = std::filesystem::file_size(InPath);
	}

	int FileMode = std::ios::binary;
	FileMode |= std::ios::out;
	FileMode |= std::ios::in;

	if (InOpenMode == EOpenMode::WriteAtEnd)
	{
		FileMode |= std::ios::app;
	}
	else if (InOpenMode == EOpenMode::FlushContent)
	{
		FileMode |= std::ios::trunc;
	}

	FileStream.open(InPath, FileMode);

	if (!FileStream.is_open() || FileStream.bad())
	{
		return EFileResult::UnableToOpen;
	}

	return EFileResult::Success;
}

//------------------------------------------------------------
// Begin CFileHandler
//------------------------------------------------------------

CL::CFileHandler::CFileHandler()
	: RootDirectory("")
	, HasRoot(false)
{
}

//------------------------------------------------------------

CL::CFileHandler::CFileHandler(const std::string& InRootDirectory)
	: RootDirectory("")
	, HasRoot(false)
{
	SetRootDirectory(InRootDirectory);
}

//------------------------------------------------------------

void CL::CFileHandler::SetRootDirectory(const std::string& InRootDirectoryPath)
{
	RootDirectory = InRootDirectoryPath;
	HasRoot = true;
}

//------------------------------------------------------------

CL::EFileResult CL::CFileHandler::OpenFile(CBinaryFile& OutFileHandle, const std::string& InPath, EFileMode InFileMode, EOpenMode InOpenMode, bool InOverrideRoot)
{
	const std::string FilePath = InOverrideRoot ? InPath : RootDirectory + InPath;

	if (InFileMode == EFileMode::Open)
	{
		if (!std::filesystem::exists(FilePath))
		{
			return EFileResult::FileNotFound;
		}
	}
	else if (InFileMode == EFileMode::CreateOrReplace)
	{
		if (std::filesystem::exists(FilePath))
		{
			std::filesystem::remove(FilePath);
		}
	}
	//CreateOrOpen is handled through the default case and therefore does not need a special case

	return OutFileHandle.Open(FilePath, InOpenMode);
}

//------------------------------------------------------------

//------------------------------------------------------------

//------------------------------------------------------------