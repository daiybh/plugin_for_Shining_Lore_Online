#pragma once
#include "windows.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <string>
struct ConfigItem {
	std::wstring name;
	int    areaOffset=5;
	int    stepOffset_horizontal = 100;
	int    stepOffset_vertical = 100;
	bool     NP=false;
	bool     pickup=false;
	int     pickupTime=1;
	int     last_PickupTime = 0;
	int     cout_pickup = 0;
	bool    attack=false;

	int     last_AttackTime = 0;
	int     mainFunc = 0;
	int     f1Time=1;
	int     f2Time=2;
	int     f3Time=3;
	int     f4Time=4;
	int     f5Time=5;
	int     kTime=5;
	bool    bPressK = false;

	int     cout_f1 = 0;
	int     cout_f2 = 0;
	int     cout_f3 = 0;
	int     cout_f4 = 0;
	int     cout_f5 = 0;
	int     cout_k = 0;
	int     last_f1Time = 0;
	int     last_f2Time = 0;
	int     last_f3Time = 0;
	int     last_f4Time = 0;
	int     last_f5Time = 0;
	int     last_kTime = 0;

	//NLOHMANN_DEFINE_TYPE_INTRUSIVE(ConfigItem, name, areaOffset, NP, pickup, pickupTime, attack, f1Time, f2Time, f3Time, f4Time, f5Time);
};
struct ConfigObjs {
	std::vector<ConfigItem> items;
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE(ConfigObjs, items);
};

class Config {
public:
	static Config getInstance() {
		static Config c;
		return c;
	}
	CString to_string(int v)
	{
		CString x;
		x.Format(L"%d", v);
		return x;
	}
	Config(){
	}
	void save(ConfigItem ci) {
		std::wstring jsonPathA = getJsonPath(ci.name);
		const TCHAR* jsonPath = jsonPathA.c_str();
		const TCHAR* pKey = ci.name.c_str();
		WritePrivateProfileString(pKey, L"areaOffset", to_string(ci.areaOffset), jsonPath);
		WritePrivateProfileString(pKey, L"NP", to_string(ci.NP), jsonPath);
		WritePrivateProfileString(pKey, L"pickup", to_string(ci.pickup), jsonPath);
		WritePrivateProfileString(pKey, L"bPressK", to_string(ci.bPressK), jsonPath);
		WritePrivateProfileString(pKey, L"pickupTime", to_string(ci.pickupTime), jsonPath);
		WritePrivateProfileString(pKey, L"attack", to_string(ci.attack), jsonPath);
		WritePrivateProfileString(pKey, L"mainFun", to_string(ci.mainFunc), jsonPath);
		WritePrivateProfileString(pKey, L"f1Time", to_string(ci.f1Time), jsonPath);
		WritePrivateProfileString(pKey, L"f2Time", to_string(ci.f2Time), jsonPath);
		WritePrivateProfileString(pKey, L"f3Time", to_string(ci.f3Time), jsonPath);
		WritePrivateProfileString(pKey, L"f4Time", to_string(ci.f4Time), jsonPath);
		WritePrivateProfileString(pKey, L"f5Time", to_string(ci.f5Time), jsonPath);		
		WritePrivateProfileString(pKey, L"kTime", to_string(ci.kTime), jsonPath);		


		WritePrivateProfileString(pKey, L"stepOffset_horizontal", to_string(ci.stepOffset_horizontal), jsonPath);
		WritePrivateProfileString(pKey, L"stepOffset_vertical", to_string(ci.stepOffset_vertical), jsonPath);
	}
	void load(ConfigItem &ci) {
		std::wstring jsonPathA = getJsonPath(ci.name);
		const TCHAR* jsonPath = jsonPathA.c_str();
		const TCHAR* pKey = ci.name.c_str();
		ci.areaOffset = GetPrivateProfileInt(pKey,L"areaOffset", ci.areaOffset, jsonPath);
		ci.stepOffset_horizontal = GetPrivateProfileInt(pKey,L"stepOffset_horizontal", ci.stepOffset_horizontal, jsonPath);
		ci.stepOffset_vertical = GetPrivateProfileInt(pKey,L"stepOffset_vertical", ci.stepOffset_vertical, jsonPath);
		ci.NP = GetPrivateProfileInt(pKey,L"NP", ci.NP, jsonPath);
		ci.pickup = GetPrivateProfileInt(pKey,L"pickup", ci.pickup, jsonPath);
		ci.bPressK = GetPrivateProfileInt(pKey,L"bPressK", ci.bPressK, jsonPath);
		ci.pickupTime = GetPrivateProfileInt(pKey,L"pickupTime", ci.pickupTime, jsonPath);
		ci.attack = GetPrivateProfileInt(pKey,L"attack", ci.attack, jsonPath);
		ci.mainFunc = GetPrivateProfileInt(pKey,L"mainFun", ci.mainFunc, jsonPath);
		ci.f1Time = GetPrivateProfileInt(pKey,L"f1Time", ci.f1Time, jsonPath);
		ci.f2Time = GetPrivateProfileInt(pKey,L"f2Time", ci.f2Time, jsonPath);
		ci.f3Time = GetPrivateProfileInt(pKey,L"f3Time", ci.f3Time, jsonPath);
		ci.f4Time = GetPrivateProfileInt(pKey,L"f4Time", ci.f4Time, jsonPath);
		ci.f5Time = GetPrivateProfileInt(pKey,L"f5Time", ci.f5Time, jsonPath);
		ci.kTime = GetPrivateProfileInt(pKey,L"kTime", ci.kTime, jsonPath);
	}
private:
	
	std::wstring getJsonPath(std::wstring name)
	{
		// 获取路径
		wchar_t pszFilePath[MAX_PATH];
		memset(pszFilePath, 0, sizeof(pszFilePath) * sizeof(char));
		GetModuleFileName(NULL, pszFilePath, MAX_PATH);

		PathRemoveFileSpec(pszFilePath);
		//PathAppend(pszFilePath, L"Dll1.dll");

		std::wstring xb(pszFilePath);
		xb += L"\\"+name+L".json";

		return xb;
	}
	
	
};