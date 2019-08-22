#pragma once
#include <string>
#include <vector>

namespace CommonUtilities
{
	std::string GetOpenDialogFilePath(const char* aExtension);
	std::string GetSaveDialogFilePath(const char* aExtension);
	
	bool SaveFile(const std::string& aFilePath, const std::string& aData, bool aEncode = false);
	std::string OpenFile(const std::string& aFilePath, bool aEncoded = false);

	//void FillArrayWithFiles(CU::FastArray<std::string>& aFileListToFill, const wchar_t* aSearchPath);
	//void FillArrayWithFiles(std::vector<std::string>& aFileListToFill, const wchar_t * aSearchPath);
	//void FillArrayWithFiles(CU::FastArray<std::string>& aFileListToFill, const wchar_t* aSearchPath, const wchar_t* aExtension);
	//void FillArrayWithFiles(std::vector<std::string>& aFileListToFill, const wchar_t * aSearchPath, const wchar_t * aExtension);
}
