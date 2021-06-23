#include "main.h"
#include <algorithm>
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
std::string delLastBlanks(std::string str) {
    if (str.length() == 0)
        return str;
    std::string blanks("\f\v\r\t\n ");
    std::map<char, bool> c2out;
    for (size_t i = 0; i < blanks.size(); i++)
    {
        c2out.insert(std::make_pair(blanks[i], true));
    }
    int idx = 0;
    int len = str.length();
    while (idx > -1) {
        idx = -1;
        for (int i = len - 1; i >= 0; i--) {
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
        return str.substr(0, len);
    return str;
}
bool loadFileLines(std::string path,std::vector<std::string>& data) {
    data.clear();
    std::string blanks("\f\v\r\t\n ");
    std::ifstream in(path);
    std::string line = "";
    
    if (in.is_open()) {
        while (getline(in, line))
        {
            std::string str = line;
            if(str.length() > 0)
                str.erase(0, str.find_first_not_of(blanks));
            str = delLastBlanks(str);
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
//int Type = 0;
//std::string des = "描述:";
//std::string curl = "";
//std::string lua = "";

bool handItem(std::map<std::string, std::string> &olditem,std::string key, int Type, std::string des, std::string curl, std::string lua) {
    if (Type < 1 || Type > 2) {
        std::string tip = "未知类型处理类型:";
        tip += key;
        if (MessageBox(NULL, tip.c_str(), "提示", MB_OK) == MB_OK) {
            return false;
        }
    }
    
    if (Type == 1) {
        OPENFILENAME lofe = { 0 };
        lofe.lStructSize = sizeof(lofe);
        lofe.hwndOwner = NULL;
        lofe.hInstance = GetModuleHandle(NULL);
        lofe.lpstrFilter = "All Files\0*.*\0\0";
        lofe.lpstrCustomFilter = NULL;
        char arr[4096] = "";
        lofe.lpstrFile = arr;
        lofe.nMaxFile = 4096;
        std::string title = "选择路径:";
        title += key;
        lofe.lpstrTitle = title.c_str();
        if (GetOpenFileName(&lofe) == true) {
            olditem[key] = std::string(lofe.lpstrFile);
            return true;
        }
    }
    else if (Type == 2) {
        BROWSEINFO browse_info;
        browse_info.hwndOwner = 0;
        browse_info.pidlRoot = 0;
        browse_info.pszDisplayName = 0;
        std::string title = "请选择文件夹";
        title += key;
        browse_info.lpszTitle = title.c_str();
        browse_info.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
        browse_info.lpfn = 0;
        browse_info.lParam = 0;
        browse_info.iImage = 0;

        LPITEMIDLIST item_id_list = SHBrowseForFolder(&browse_info);
        if (item_id_list != 0) {
            char arr[4096] = "";
            if (SHGetPathFromIDList(item_id_list, arr))
            {
                olditem[key] = arr;
                return true;
            }
        }
    }
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
        try
        {
            loadFileLines(inpath, filedatabuff);
            if (filedatabuff.size() == 0)
            {
                std::cout << "no such file:: " << inpath << std::endl;
                std::cout << "Please input the ini file" << std::endl;
                std::cin >> inpath;
            }
        }
        catch (const std::exception& ex)
        {
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
    std::map<std::string, std::string> oldmap = {};
    if (loadFileLines(oldpath, oldinfo)) {
        for (int i = 0; i < oldinfo.size(); i++)
        {
            int idx = oldinfo[i].find("=");
            if (idx != std::string::npos && idx > 4) {
                if (oldinfo[i].substr(0, 2) != "::") {
                    std::string oldkey = oldinfo[i].substr(4, idx);
                    if (oldkey != "name" && oldkey != "version") {
                        std::string oldvalue = oldinfo[i].substr(idx + 1, oldinfo[i].length());
                        oldmap.insert(std::make_pair(oldkey, oldvalue));
                    }
                }
            }
        }
    }
    for (auto i = buff.begin() ; i != buff.end(); i++)
    {
        std::string str = i->first;
        std::string key = "";
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        key = str;
        if (oldmap.find(key) == oldmap.end()) {
            neb::CJsonObject cjson = neb::CJsonObject(i->second);
            int Type = 0;
            std::string des = "描述:";
            std::string curl = "";
            std::string lua = "";
            cjson.Get("type", Type);
            cjson.Get("des", des);
            cjson.Get("curl",curl);
            cjson.Get("lua", lua);
            cjson.Clear();
            handItem(oldmap, key, Type, des, curl, lua);
        }
    }
    std::string str = "::";
    str += name + "\n::";
    str += version + "\n";
    std::string last = "";
    for  (auto i = oldmap.begin(); i != oldmap.end(); i++)
    {
        std::string item = "\nset " + i->first + "=" + i->second;
        str += item;
        last += ";%" + i->first + "%";
    }
    str += "\nset __"+name+"=" + last;
    str += "\n";
    FILE* fp = NULL;
    fopen_s(&fp, oldpath.c_str(), "wb");
    if (fp != NULL) {
        fwrite(str.c_str(), sizeof(char), str.length(), fp);
        fclose(fp);
        fp = NULL;
    }
    else {
        return -1;
    }
    return 0;
}