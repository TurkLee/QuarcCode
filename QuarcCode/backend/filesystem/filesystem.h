#pragma once

#include <Windows.h>
#include <string>
#include <list>
#include <sstream>
#include <ostream>
#include <fstream>
#include <locale>
#include <codecvt>

#include <filesystem>

#include <oleidl.h>

#include "../utilites/utilites.hpp"

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING



struct file
{
	std::string path;
	std::string filename;
	std::string extension;
};

class QuarcFiles
{
public:
	std::string openAndConvertate();
	std::string get_file_extension(const std::string& FileName);
	void OpenFile();

	std::string delimer = "/\\";
	bool dragndrop;

	void SwapDragnDrop()
	{
		dragndrop = !dragndrop;
	}

	bool GetDragnDrop()
	{
		return dragndrop;
	}

public:
	std::list<file> files_map;

	std::string base_name(std::string& path, std::string& delims);
	std::string remove_extension(std::string& filename);
};

extern QuarcFiles qFiles;

class DropManager : public IDropTarget
{
	ULONG AddRef() { return 1; }
	ULONG Release() { return 0; }

	// we handle drop targets, let others know
	HRESULT QueryInterface(REFIID riid, void** ppvObject)
	{
		if (riid == IID_IDropTarget)
		{
			*ppvObject = this;

			return S_OK;
		}

		*ppvObject = NULL;
		return E_NOINTERFACE;
	};

	HRESULT DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
	{
		qFiles.SwapDragnDrop();
		*pdwEffect &= DROPEFFECT_MOVE;
		return S_OK;
	}

	HRESULT DragLeave() { return S_OK; }

	HRESULT DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
	{
		*pdwEffect &= DROPEFFECT_MOVE;
		return S_OK;
	}

	HRESULT Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
	{
		FORMATETC fmte = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
		STGMEDIUM stgm;

		if (SUCCEEDED(pDataObj->GetData(&fmte, &stgm)))
		{
			HDROP hdrop = (HDROP)stgm.hGlobal; // or reinterpret_cast<HDROP> if preferred
			UINT file_count = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);

			for (UINT i = 0; i < file_count; i++)
			{
				TCHAR szFile[MAX_PATH];
				UINT cch = DragQueryFile(hdrop, i, szFile, MAX_PATH);
				if (cch > 0 && cch < MAX_PATH)
				{
					std::wstring szFileStringW = szFile;
					std::string szFileString(szFileStringW.begin(), szFileStringW.end());

					qFiles.files_map.push_back(file{ szFileString, qFiles.base_name(szFileString, qFiles.delimer), qFiles.get_file_extension(szFileString) });
				}
			}

			ReleaseStgMedium(&stgm);
		}


		qFiles.SwapDragnDrop();
		*pdwEffect &= DROPEFFECT_MOVE;
		return S_OK;
	}
};
