#pragma once
#include "windows.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
struct ConfigItem {
	CString name;
	int    areaOffset=5;
	int    stepOffset = 100;
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

	int     cout_f1 = 0;
	int     cout_f2 = 0;
	int     cout_f3 = 0;
	int     cout_f4 = 0;
	int     cout_f5 = 0;
	int     last_f1Time = 0;
	int     last_f2Time = 0;
	int     last_f3Time = 0;
	int     last_f4Time = 0;
	int     last_f5Time = 0;

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
		CString jsonPath = getJsonPath(ci.name);

		WritePrivateProfileString(ci.name, L"areaOffset", to_string(ci.areaOffset), jsonPath);
		WritePrivateProfileString(ci.name, L"NP", to_string(ci.NP), jsonPath);
		WritePrivateProfileString(ci.name, L"pickup", to_string(ci.pickup), jsonPath);
		WritePrivateProfileString(ci.name, L"pickupTime", to_string(ci.pickupTime), jsonPath);
		WritePrivateProfileString(ci.name, L"attack", to_string(ci.attack), jsonPath);
		WritePrivateProfileString(ci.name, L"mainFun", to_string(ci.mainFunc), jsonPath);
		WritePrivateProfileString(ci.name, L"f1Time", to_string(ci.f1Time), jsonPath);
		WritePrivateProfileString(ci.name, L"f2Time", to_string(ci.f2Time), jsonPath);
		WritePrivateProfileString(ci.name, L"f3Time", to_string(ci.f3Time), jsonPath);
		WritePrivateProfileString(ci.name, L"f4Time", to_string(ci.f4Time), jsonPath);
		WritePrivateProfileString(ci.name, L"f5Time", to_string(ci.f5Time), jsonPath);		
	}
	void load(ConfigItem &ci) {		
		CString jsonPath = getJsonPath(ci.name);
		ci.areaOffset = GetPrivateProfileInt(ci.name,L"areaOffset", ci.areaOffset, jsonPath);
		ci.NP = GetPrivateProfileInt(ci.name,L"NP", ci.NP, jsonPath);
		ci.pickup = GetPrivateProfileInt(ci.name,L"pickup", ci.pickup, jsonPath);
		ci.pickupTime = GetPrivateProfileInt(ci.name,L"pickupTime", ci.pickupTime, jsonPath);
		ci.attack = GetPrivateProfileInt(ci.name,L"attack", ci.attack, jsonPath);
		ci.mainFunc = GetPrivateProfileInt(ci.name,L"mainFun", ci.mainFunc, jsonPath);
		ci.f1Time = GetPrivateProfileInt(ci.name,L"f1Time", ci.f1Time, jsonPath);
		ci.f2Time = GetPrivateProfileInt(ci.name,L"f2Time", ci.f2Time, jsonPath);
		ci.f3Time = GetPrivateProfileInt(ci.name,L"f3Time", ci.f3Time, jsonPath);
		ci.f4Time = GetPrivateProfileInt(ci.name,L"f4Time", ci.f4Time, jsonPath);
		ci.f5Time = GetPrivateProfileInt(ci.name,L"f5Time", ci.f5Time, jsonPath);
	}
private:
	
	CString getJsonPath(CString name)
	{
		// 获取路径
		wchar_t pszFilePath[MAX_PATH];
		memset(pszFilePath, 0, sizeof(pszFilePath) * sizeof(char));
		GetModuleFileName(NULL, pszFilePath, MAX_PATH);

		PathRemoveFileSpec(pszFilePath);
		//PathAppend(pszFilePath, L"Dll1.dll");

		CString x;
		x.Format(L"%s\\%s.json",pszFilePath, name);
		return x;
	}
	
	
};