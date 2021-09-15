#pragma once
#include <string>
//²»Ö§³Ö release 32
class zlibManage
{
	static int tempBuffSize;
	static char* tempBuff;
public:
	static int CompressString(const char* in_str, size_t in_len, std::string& out_str, int level);
	static int DecompressString(const char* in_str, size_t in_len, std::string& out_str);
};

