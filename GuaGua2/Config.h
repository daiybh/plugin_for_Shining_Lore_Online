#pragma once
#include "windows.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
struct ConfigItem {
	std::string name;
	int    areaOffset=0;
	bool     NP=false;
	bool     pickup=false;
	int     pickupTime=0;
	bool    attack=false;
	int     f1Time=0;
	int     f2Time=0;
	int     f3Time=0;
	int     f4Time=0;
	int     f5Time=0;

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
		load();	
	}
	void save() {
		nlohmann::json j;
		to_json(j, objs);
		// write prettified JSON to another file
		std::ofstream o(getJsonPath());
		o << std::setw(4) << j << std::endl;
	}
	void load() {
		std::ifstream f(getJsonPath());
		if (f.is_open()) {
			nlohmann::json data = nlohmann::json::parse(f);
			from_json(data, objs);
		}
		else
		{
			save();
		}
	}
	ConfigObjs objs;
private:
	std::string jsonFilePath = "example.json";
	
	std::string GetExePath()
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

		return pszFilePath;
	}
	std::string getJsonPath() {
		return GetExePath() + jsonFilePath;
	}
	
};