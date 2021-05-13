#include "main.h"
#include <io.h>
#include <direct.h>
#include "CJsonObject.hpp"
#include "shlobj_core.h"
#define VERSION_TOOL "1.0"
void help() {
}
//输入配置参数文件
//不允许换行符
/*
* envPath=a
* version=1.0
* ::和//注释
* 空行自动跳过
* cout=要求配置行数
* name=json
* "name"={des = "",file = false,curl = "如果没有就启用这个方式下载文件http://192.168.2.98:1254/name/abc.exe;edf.ini;hlv.log;..."}
* "name"={des = "",file = true,lua = "handfunction"}
* ....
*/
bool checkKey(std::string name) {
    if (name.length() == 0)
        return false;
    for (int i = 0; i < name.length(); i++)
    {
        char c = name[i];
        if (c < '0' || c > 'z') {
            return false;
        }
        if (c > '9' && c < 'A')
            return false;
        if (c > 'Z' && c < 'a')
            return false;
    }
    return true;
}
bool loadFileLines(std::string path,std::vector<std::string>& data) {
    data.clear();
    std::string blanks("\f\v\r\t\n ");
    std::ifstream in(path);
    std::string line = "";
    std::map<char, bool> c2out;
    for (size_t i = 0; i < blanks.size(); i++)
    {
        c2out.insert(std::make_pair(blanks[i], true));
    }
    if (in.is_open()) {
        while (getline(in, line))
        {
            std::string str = line;
            if(str.length() > 0)
                str.erase(0, str.find_first_not_of(blanks));
            if (str.length() > 0) {
                int idx = 0;
                int len = str.length();
                while (idx > -1) {
                    idx = -1;
                    for (int i = len-1; i >= 0; i--) {
                        if (c2out.find(str[i]) != c2out.end()) {
                            idx = i;
                        }
                        else {
                            break;
                        }
                    }
                    if (idx > -1)
                        len = idx;
                }
                if (len < str.length())
                    str = str.substr(0, len);
            }
            if (str.length() > 1) {
                std::string first = str.substr(0, 2);
                if (first == "//" || first == "::")
                    continue;
            }
            else if (str.length() == 0) {
                continue;
            }
            data.push_back(str);
        }
        in.close();
        return data.size() > 0;
    }
    return false;
}

int createDirectory(std::string path)
{
    int len = path.length();
    char tmpDirPath[256] = { 0 };
    for (int i = 0; i < len; i++)
    {
        tmpDirPath[i] = path[i];
        if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
        {
            if (_access(tmpDirPath, 0) == -1)
            {
                int ret = _mkdir(tmpDirPath);
                if (ret == -1) return ret;
            }
        }
    }
    return 0;
}
int main(int argc, char* argv[]){
	std::cout<<"TOOL_VERSION::" << VERSION_TOOL << std::endl;
	
	for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << std::endl;
	}
    SetConsoleOutputCP(65001);
    std::string line;
    std::vector<std::string> filedatabuff;
    filedatabuff.clear();
    std::string inpath = "";
    if(argc > 1)
        inpath = argv[1];
    std::vector<std::string> oldinfo;
    oldinfo.clear();
    char path[255];
    SHGetSpecialFolderPath(
        NULL,							// 保留
        path,							// 接受文件路径的字符串指针
        CSIDL_APPDATA,			// CSIDL 宏
        TRUE							// 如果文件夹不存在，则不创建文件夹
    );
    std::cout << "path = " << path << std::endl;
    std::string oldpath = path;
    oldpath += "\\checkEnv\\";
    if (createDirectory(oldpath) != 0)
    {
        MessageBox(NULL, "目录创建失败:", "提示", MB_OK);
        return -1;
    }
    while (filedatabuff.size() == 0) {
        if (inpath == "quit")
            return 0;
        std::ifstream in(inpath);
        if (in)
        {
            
            try
            {
                loadFileLines(inpath, filedatabuff);
                if (filedatabuff.size() == 0)
                    return 0;
            }
            catch (const std::exception& ex)
            {
                if (in.is_open())
                    in.close();
                std::cout << line << std::endl;
                std::cout<<ex.what()<<std::endl;
                if (MessageBox(NULL, TEXT("出现异常是否修改文件后重试"), TEXT("提示"), MB_YESNO) == IDNO) {
                    filedatabuff.push_back("error");
                }
                else {
                    filedatabuff.clear();
                }
            }
        }
        else // 没有该文件
        {
            std::cout << "no such file:: "<<inpath << std::endl;
            std::cout << "Please input the ini file" << std::endl;
            std::cin >> inpath;
        }
    }
    std::map<std::string, std::string> buff = {};
    std::string version = "";
    std::string name = "";
    for (size_t i = 0; i < filedatabuff.size(); i++)
    {
        int idx = filedatabuff[i].find("=");
        if (idx == std::string::npos) {
            continue;
        }
        std::string key = filedatabuff[i].substr(0, idx);
        if (checkKey(key) == false) {
            continue;
        }
        std::string value = filedatabuff[i].substr(idx + 1, filedatabuff[i].length());
        if (key == "name") {
            if(checkKey(value))
                name = value;
        }
        else if (key == "version") {
            version = value;
        }
        else {
            //* "name"={des = "",file = false,curl = "如果没有就启用这个方式下载文件http://192.168.2.98:1254/name/abc.exe;edf.ini;hlv.log;..."}
            //"name" = { des = "",file = true,lua = "handfunction" }
            buff.insert(std::make_pair(key, value));
        }
    }
    if (name == "") {
        MessageBox(NULL, "获取名称失败", "提示", MB_OK);
        return -1;
    }
    if (version == "") {
        MessageBox(NULL, "获取版本编号失败", "提示", MB_OK);
        return -1;
    }
    oldpath += name + ".bat";
    if (loadFileLines(oldpath, oldinfo)) {

    }
    system("pause");
}