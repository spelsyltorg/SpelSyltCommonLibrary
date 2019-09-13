#include "FileDialog.h"
#include <windows.h>
#include <commdlg.h>
#include <fstream>
#include <iostream>
#include <experimental/filesystem>

#include "Base64.h"

namespace CommonUtilities
{
	std::string GetOpenDialogFilePath(const char * aExtension)
	{
		char CWD[260];
		GetCurrentDirectoryA(260, CWD);

		OPENFILENAMEA ofn;       // common dialog box structure
		char szFile[260];       // buffer for file name
		szFile[0] = '\0';

		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = nullptr;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.lpstrFile[1] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = aExtension;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		// Display the Open dialog box. 
		if( GetOpenFileNameA(&ofn) == TRUE )
		{
			//Make sure it doesn't change the current working directory
			SetCurrentDirectoryA(CWD);

			return std::string(szFile);
		}

		return "";
	}

	std::string GetSaveDialogFilePath(const char* aExtension)
	{
		char CWD[260];
		GetCurrentDirectoryA(260, CWD);

		OPENFILENAMEA ofn;       // common dialog box structure
		char szFile[260];       // buffer for file name

		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = nullptr;
		ofn.lpstrFile = szFile;
		// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
		// use the contents of szFile to initialize itself.
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = aExtension;
		ofn.lpstrDefExt = aExtension;
		ofn.nFilterIndex = 0;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT;

		// Display the Open dialog box. 
		if( GetSaveFileNameA(&ofn) == TRUE )
		{
			//Make sure it doesn't change the current working directory
			SetCurrentDirectoryA(CWD);

			return std::string(szFile).c_str();
		}

		return "";
	}

	bool SaveFile(const std::string& aFilePath, const std::string& aData, bool aEncode)
	{
		std::string writeData;
		if( aEncode )
		{
			writeData = Base64Encode(reinterpret_cast<unsigned char const*>(aData.c_str()), aData.size());
		}
		else
		{
			writeData = aData;
		}

		std::ofstream o(aFilePath);
		if( o.bad() || o.fail() )
		{
			std::cout << "[ERROR] Failed to write file: " << aFilePath << std::endl;
			return false;
		}

		o << writeData;

		return true;
	}
	std::string OpenFile(const std::string& aFilePath, bool aEncoded)
	{
		std::ifstream i(aFilePath);
		if( i.bad() || i.fail() )
		{
			return "";
		}
		std::string fileData((std::istreambuf_iterator<char>(i)), std::istreambuf_iterator<char>());

		std::string returnData;

		if( aEncoded )
		{
			returnData = Base64Decode(fileData);
		}
		else
		{
			returnData = fileData;
		}

		return returnData;
	}
	//void FillArrayWithFiles(CU::FastArray<std::string>& aFileListToFill, const wchar_t * aSearchPath)
	//{
	//	std::experimental::filesystem::path path = std::experimental::filesystem::current_path().append(aSearchPath);
	//	std::experimental::filesystem::directory_iterator dir(path.c_str());
	//	for (auto& file : dir)
	//	{
	//		if (file.path().has_extension())
	//		{
	//			aFileListToFill.Push();
	//			std::wstring wideVersion = file.path().filename();
	//			aFileListToFill.GetLast() = std::string(wideVersion.begin(), wideVersion.end());
	//		}
	//	}
	//}
	//void FillArrayWithFiles(std::vector<std::string>& aFileListToFill, const wchar_t * aSearchPath)
	//{
	//	std::experimental::filesystem::path path = std::experimental::filesystem::current_path().append(aSearchPath);
	//	std::experimental::filesystem::directory_iterator dir(path.c_str());
	//	for (auto& file : dir)
	//	{
	//		if (file.path().has_extension())
	//		{
	//			std::wstring wideVersion = file.path().filename();
	//			aFileListToFill.push_back(std::string(wideVersion.begin(), wideVersion.end()));
	//		}
	//	}
	//}
	//void FillArrayWithFiles(CU::FastArray<std::string>& aFileListToFill, const wchar_t * aSearchPath, const wchar_t * aExtension)
	//{
	//	std::experimental::filesystem::path path = std::experimental::filesystem::current_path().append(aSearchPath);
	//	std::experimental::filesystem::directory_iterator dir(path.c_str());
	//	for (auto& file : dir)
	//	{
	//		if (file.path().has_extension() && file.path().extension() == aExtension)
	//		{
	//			aFileListToFill.Push();
	//			std::wstring wideVersion = file.path().filename();
	//			aFileListToFill.GetLast() = std::string(wideVersion.begin(), wideVersion.end());
	//		}
	//	}
	//}
	//void FillArrayWithFiles(std::vector<std::string>& aFileListToFill, const wchar_t * aSearchPath, const wchar_t * aExtension)
	//{
	//	std::experimental::filesystem::path path = std::experimental::filesystem::current_path().append(aSearchPath);
	//	std::experimental::filesystem::directory_iterator dir(path.c_str());
	//	for (auto& file : dir)
	//	{
	//		if (file.path().has_extension() && file.path().extension() == aExtension)
	//		{
	//			std::wstring wideVersion = file.path().filename();
	//			aFileListToFill.push_back(std::string(wideVersion.begin(), wideVersion.end()));
	//		}
	//	}
	//}
}
