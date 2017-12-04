#pragma once
#include"Sound\Sound.h"
#include<tchar.h>

/// <summary>
/// https://social.msdn.microsoft.com/Forums/vstudio/en-US/1833af9d-7f8c-4f77-a765-f626a3221f91/com-apartments-sta-object-corrupting-an-mta-object?forum=vcgeneral
/// COMの仕様上で起こるXAudio2_7.dllのエラーに対する対処法
/// 外部のライブラリを使用する部分(主にデバッグ部分をコメントアウト)
/// どちらかのクラスを使用すればOKみたい
/// </summary>

//////////////////////////////////////////////////////////////////////////
//
// This class provides a workaround for the incredibly damaging Windows
// bug whereby an IMAPI2 COM object can cause the unintentional unloading
// of the XAudio2 DLL whilst there are still XAudio2 COM objects in use.
// 
// Strategy:
// Keep the XAudio2 DLL in memory to thwart COM's auto-unload function.
// 1. Find the XAudio2 DLL on disk, the same physical DLL containing the
//    registered XAudio COM classes.
// 2. Explicitly load the DLL using LoadLibrary() when the XAudio2 COM
//    objects are created, and only unload the DLL when those COM objects
//    are released.
//    
// Simple, crude but effective. No observed ill effects.
// 
//////////////////////////////////////////////////////////////////////////
class Xaudio2DllUnloadWorkaround_LoadLibraryVersion
{
public:
	Xaudio2DllUnloadWorkaround_LoadLibraryVersion(void);
	virtual ~Xaudio2DllUnloadWorkaround_LoadLibraryVersion(void);

	// Apply this workaround.
	void Invoke(bool isDebugMode);

private:
	// Handle to loaded XAudio2 DLL.
	HMODULE m_hLib;

	// Full path to theXAudio2 DLL.
	std::basic_string<TCHAR> m_dllFullPath;

	bool RegistryFindDllPath(REFCLSID clsidXaudio2Dll);
	void ExplicitLoad(void);
	void ExplicitUnload(void);
};


