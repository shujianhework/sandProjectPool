
#include "base/CCGameDyFuncsVersion.h"
NS_CC_BEGIN
std::map<char *,char *> GameDyfuncsVersion::funs = {};
char* GameDyfuncsVersionInfoBufss = NULL;
unsigned int GameDyfuncsVersionInfoBufSize = 0;
unsigned int GameDyfuncsVersionInfoBufOffset = 0;

void GameDyfuncsVersion::addFunInfo(std::string name, std::string destr) {
	
	if (destr.length() > 512 || name.length() > 100 || name.length() == 0 || destr.length() == 0) {
		throw char("name or destr len out range");
	}

	if (GameDyfuncsVersionInfoBufSize == 0) {
		GameDyfuncsVersionInfoBufSize = 1024;
		GameDyfuncsVersionInfoBufss = new char[GameDyfuncsVersionInfoBufSize];
		memset(GameDyfuncsVersionInfoBufss, 0, GameDyfuncsVersionInfoBufSize);
	}

	if ((GameDyfuncsVersionInfoBufOffset + name.length() + destr.length() + 3) > GameDyfuncsVersionInfoBufSize) {

		int size = GameDyfuncsVersionInfoBufOffset + name.length() + destr.length() + 512;
		char* p = new char[size];
		memset(p, 0, size);
		memcpy(p, GameDyfuncsVersionInfoBufss, GameDyfuncsVersionInfoBufOffset);
		delete GameDyfuncsVersionInfoBufss;
		GameDyfuncsVersionInfoBufss = p;
		GameDyfuncsVersionInfoBufSize = size;

	}
	if ( funs.find((char*)name.c_str()) != funs.end())
		return;
	char* key = &GameDyfuncsVersionInfoBufss[GameDyfuncsVersionInfoBufOffset];
	memcpy(&GameDyfuncsVersionInfoBufss[GameDyfuncsVersionInfoBufOffset], name.c_str(), name.size());
	key[name.size()] = 0;
	GameDyfuncsVersionInfoBufOffset += name.size()+1;
	char* value = &GameDyfuncsVersionInfoBufss[GameDyfuncsVersionInfoBufOffset];
	memcpy(&GameDyfuncsVersionInfoBufss[GameDyfuncsVersionInfoBufOffset], destr.c_str(), destr.size());
	GameDyfuncsVersionInfoBufOffset += destr.size()+1;
	value[destr.size()] = 0;
	funs.insert(std::make_pair(key,value));

}
std::string GameDyfuncsVersion::getAllFunInfos() {
	
	if (funs.size() == 0)
		return "{}";

	std::string ret = "{\n";
	for (auto item = funs.begin(); item != funs.end(); item++) {

		std::string temp = std::string(item->first) + "=\"" + item->second + "\",\n";
		ret += std::string("\t") + temp;
	}
	return ret + "nil}";
}
void GameDyfuncsVersion::destory()
{
	funs.clear();
	if (GameDyfuncsVersionInfoBufss != NULL) {
		delete GameDyfuncsVersionInfoBufss;
		GameDyfuncsVersionInfoBufss = NULL;
	}
	GameDyfuncsVersionInfoBufSize = 0;
	GameDyfuncsVersionInfoBufOffset = 0;
}
NS_CC_END
