#include"XAudio2DLLSet.h"

/// //////////////////////////////////////////////////////////////////////////
//
// Xaudio2DllUnloadWorkaround_LoadLibraryVersion implementation
//
//////////////////////////////////////////////////////////////////////////

Xaudio2DllUnloadWorkaround_LoadLibraryVersion::Xaudio2DllUnloadWorkaround_LoadLibraryVersion(void)
	:m_hLib(NULL)
{
	//LOG_DEBUG(_T("<<Created>>"));
}


Xaudio2DllUnloadWorkaround_LoadLibraryVersion::~Xaudio2DllUnloadWorkaround_LoadLibraryVersion(void)
{
	ExplicitUnload();
	//(_T("<<Destroyed>>"));
}


void Xaudio2DllUnloadWorkaround_LoadLibraryVersion::Invoke(bool isDebugMode)
{
	// Choose the debug or release version of the XAudio2 DLL.
	REFCLSID clsid = isDebugMode ? __uuidof(XAudio2_Debug) : __uuidof(XAudio2);

	if (RegistryFindDllPath(clsid))
	{
		ExplicitLoad();
	}
	else
	{
		// Nasty. There will be consequences.
		OutputDebugStringA("âÒîçÙÇìKópÇ≈Ç´Ç‹ÇπÇÒÇ≈ÇµÇΩÅB");
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Use the XAudio2 CLSID to find the XAudio2 DLL path in the registry.
// 
//////////////////////////////////////////////////////////////////////////
bool Xaudio2DllUnloadWorkaround_LoadLibraryVersion::RegistryFindDllPath(REFCLSID clsidXaudio2Dll)
{
	// Construct a string representation of the registry key in which the
	// path to the desired XAudio2 COM DLL should be located.

	LPOLESTR szClsid;
	StringFromCLSID(clsidXaudio2Dll, &szClsid);

	std::basic_stringstream<TCHAR> subKey;
	subKey << _T("\\CLSID\\") << szClsid << _T("\\InProcServer32");
	CoTaskMemFree(szClsid);

	bool isDllFound = false; // assume the worst


							 // Open the XAudio2 DLL's COM registry key.

	HKEY hKey;
	LONG ret = RegOpenKeyEx(HKEY_CLASSES_ROOT, subKey.str().c_str(), 0, KEY_READ, &hKey);
	if (ret != ERROR_SUCCESS)
	{
		DWORD err = GetLastError();
		//LOG_WARNING(_T("XAudio2 DLL: find by CLSID: FAILED: GetLastError()=") << err);

		// The key must exist if DirectX is installed!
		assert(ret != ERROR_SUCCESS);
	}
	else
	{
		// Found the registry key. Now read its value: it should be the full
		// path the the XAudio2 COM DLL.

		TCHAR buf[_MAX_PATH];
		DWORD bufSize = sizeof(buf);

		ret = RegQueryValueEx(hKey, NULL, NULL, NULL, (LPBYTE)buf, &bufSize);
		if (ret != ERROR_SUCCESS)
		{
			DWORD err = GetLastError();
			//LOG_WARNING(_T("XAudio2 DLL: path retrieval: FAILED: GetLastError()=") << err);

			// The DLL path must exist if DirectX is installed!
			assert(ret != ERROR_SUCCESS);
		}
		else
		{
			isDllFound = true;
			m_dllFullPath = buf; // Save the path for logging.
			//LOG_DEBUG(_T("XAudio2 DLL: path found: \"") << m_dllFullPath << _T("\""));
		}

		RegCloseKey(hKey);
	}

	return isDllFound;
}


//////////////////////////////////////////////////////////////////////////
//
// Forcibly increment the internal reference count in the XAudio2 DLL by
// explicitly loading it. This is a crude but effective way to prevent
// it being unloading by the COM run time.
// 
//////////////////////////////////////////////////////////////////////////
void Xaudio2DllUnloadWorkaround_LoadLibraryVersion::ExplicitLoad(void)
{
	//StringStreamType logMsg;

	/*if (m_pLogger->IsDebugEnabled())
	{
		logMsg << _T("LoadLibrary: \"") << m_dllFullPath << _T("\": ");
	}*/

	// Load the XAudio2 DLL
	m_hLib = LoadLibrary(m_dllFullPath.c_str());
	if (m_hLib != NULL)
	{
		/*logMsg << _T("SUCCEEDED");
		LOG_DEBUG(logMsg);*/
	}
	else
	{
		DWORD err = GetLastError();
		/*logMsg << _T("FAILED: GetLastError()=") << err;
		LOG_WARNING(logMsg);*/
	}
}


void Xaudio2DllUnloadWorkaround_LoadLibraryVersion::ExplicitUnload(void)
{
	if (m_hLib != NULL)
	{
		//StringStreamType logMsg;

		/*if (m_pLogger->IsDebugEnabled())
		{
			logMsg << _T("FreeLibrary: \"") << m_dllFullPath << _T("\": ");
		}*/

		// Unload the XAudio2 DLL
		if (FreeLibrary(m_hLib))
		{
			/*logMsg << _T("SUCCEEDED");
			LOG_DEBUG(logMsg);*/
		}
		else
		{
			/*DWORD err = GetLastError();
			logMsg << _T("FAILED: GetLastError()=") << err;
			LOG_WARNING(logMsg);*/
		}
	}
}


//////////////////////////////////////////////////////////////////////////