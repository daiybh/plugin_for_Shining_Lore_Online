#pragma once
#include "windows.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
struct ConfigItem {
	std::string name;
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

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ConfigItem, name, areaOffset, NP, pickup, pickupTime, attack, f1Time, f2Time, f3Time, f4Time, f5Time);
};
struct ConfigObjs {
	std::vector<ConfigItem> items;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ConfigObjs, items);
};

class Config {
public:
	static Config getInstance() {
		static Config c;
		return c;
	}
	Config(){
	}
	void save(ConfigItem ci) {
		std::string jsonPath = getJsonPath(ci.name);

		WritePrivateProfileStringA(ci.name.c_str(), "areaOffset", std::to_string(ci.areaOffset).c_str(), jsonPath.c_str());
		WritePrivateProfileStringA(ci.name.c_str(), "NP", std::to_string(ci.NP).c_str(), jsonPath.c_str());
		WritePrivateProfileStringA(ci.name.c_str(), "pickup", std::to_string(ci.pickup).c_str(), jsonPath.c_str());
		WritePrivateProfileStringA(ci.name.c_str(), "pickupTime", std::to_string(ci.pickupTime).c_str(), jsonPath.c_str());
		WritePrivateProfileStringA(ci.name.c_str(), "attack", std::to_string(ci.attack).c_str(), jsonPath.c_str());
		WritePrivateProfileStringA(ci.name.c_str(), "mainFun", std::to_string(ci.mainFunc).c_str(), jsonPath.c_str());
		WritePrivateProfileStringA(ci.name.c_str(), "f1Time", std::to_string(ci.f1Time).c_str(), jsonPath.c_str());
		WritePrivateProfileStringA(ci.name.c_str(), "f2Time", std::to_string(ci.f2Time).c_str(), jsonPath.c_str());
		WritePrivateProfileStringA(ci.name.c_str(), "f3Time", std::to_string(ci.f3Time).c_str(), jsonPath.c_str());
		WritePrivateProfileStringA(ci.name.c_str(), "f4Time", std::to_string(ci.f4Time).c_str(), jsonPath.c_str());
		WritePrivateProfileStringA(ci.name.c_str(), "f5Time", std::to_string(ci.f5Time).c_str(), jsonPath.c_str());		
	}
	void load(ConfigItem &ci) {		
		std::string jsonPath = getJsonPath(ci.name);
		ci.areaOffset = GetPrivateProfileIntA(ci.name.c_str(), "areaOffset", ci.areaOffset, jsonPath.c_str());
		ci.NP = GetPrivateProfileIntA(ci.name.c_str(), "NP", ci.NP, jsonPath.c_str());
		ci.pickup = GetPrivateProfileIntA(ci.name.c_str(), "pickup", ci.pickup, jsonPath.c_str());
		ci.pickupTime = GetPrivateProfileIntA(ci.name.c_str(), "pickupTime", ci.pickupTime, jsonPath.c_str());
		ci.attack = GetPrivateProfileIntA(ci.name.c_str(), "attack", ci.attack, jsonPath.c_str());
		ci.mainFunc = GetPrivateProfileIntA(ci.name.c_str(), "mainFun", ci.mainFunc, jsonPath.c_str());
		ci.f1Time = GetPrivateProfileIntA(ci.name.c_str(), "f1Time", ci.f1Time, jsonPath.c_str());
		ci.f2Time = GetPrivateProfileIntA(ci.name.c_str(), "f2Time", ci.f2Time, jsonPath.c_str());
		ci.f3Time = GetPrivateProfileIntA(ci.name.c_str(), "f3Time", ci.f3Time, jsonPath.c_str());
		ci.f4Time = GetPrivateProfileIntA(ci.name.c_str(), "f4Time", ci.f4Time, jsonPath.c_str());
		ci.f5Time = GetPrivateProfileIntA(ci.name.c_str(), "f5Time", ci.f5Time, jsonPath.c_str());
	}
private:
	
	std::string getJsonPath(std::string name)
	{
		// 获取路径
		char pszFilePath[MAX_PATH];
		memset(pszFilePath, 0, sizeof(pszFilePath) * sizeof(char));
		GetModuleFileNameA(NULL, pszFilePath, MAX_PATH);

		// 去除末尾的"\xxx.exe"
		char* pPos = NULL;
		pPos = strrchr(pszFilePath, '\\');
		*pPos = NULL;

		// 给末尾添加上"\"
		if (pszFilePath[strlen(pszFilePath) - 1] != '\\')
			strcat_s(pszFilePath, "\\");
		strcat_s(pszFilePath, name.c_str());
		strcat_s(pszFilePath, ".json");
		return pszFilePath;
	}
	
	
};