#include "main.h"
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
int main(int argc, char* argv[]){
	std::cout<<"TOOL_VERSION::" << VERSION_TOOL << std::endl;
	if (argc <= 2) {
		help();
		return -1;
	}
	for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << std::endl;
	}
    SetConsoleOutputCP(65001);
    std::string line;
    std::vector<std::string> filedatabuff;
    filedatabuff.clear();
    std::string inpath = argv[1];
    std::string blanks("\f\v\r\t\n");
    while (filedatabuff.size() == 0) {
        std::ifstream in(inpath);
        if (in)
        {
            
            try
            {
                filedatabuff.push_back("infile");
                while (getline(in, line))
                {
                    std::string str = line;
                    str.erase(0, str.find_first_not_of(blanks));
                    str.erase(str.find_last_not_of(blanks));
                    if (str.length() > 1) {
                        std::string first = str.substr(0, 2);
                        if (first == "//" || first == "::")
                            continue;
                    }
                    else if (str.length() == 0) {
                        continue;
                    }
                    filedatabuff.push_back(str);
                }
                in.close();
            }
            catch (const std::exception& ex)
            {
                if (in.is_open())
                    in.close();
                std::cout << line << std::endl;
                std::cout<<ex.what()<<std::endl;
                if (MessageBox(NULL, TEXT("出现一场是否修改文件后重试"), TEXT("提示"), MB_YESNO) == IDNO) {
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
    for (size_t i = 1; i < filedatabuff.size(); i++)
    {
        int idx = filedatabuff[i].find("=");
        if (idx == std::string::npos) {
            continue;
        }
        std::string key = filedatabuff[i].substr(0, idx - 1);
        if (checkKey(key) == false) {
            continue;
        }
        std::string value = filedatabuff[i].substr(idx + 1, filedatabuff[i].length());
        if (key == "name") {
            name = value;
        }
        else if (key == "version") {
            value = value;
        }
        else {
            //value 必须是json
        }
    }
    system("pause");
}