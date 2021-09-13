#define GAMECPPVERSION_TOOLSTR "0.0.0.0"
#ifndef __BASE_CCGAMEDYFUNCSVERSION_H__
#define __BASE_CCGAMEDYFUNCSVERSION_H__
#include "platform/CCPlatformMacros.h"
#include <string>
#include <map>

/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN

/**
 * Ref is used for reference count management. If a class inherits from Ref,
 * then it is easy to be shared in different places.
 * @js NA
 */
class CC_DLL GameDyfuncsVersion
{
	static std::map<char *,char *> funs;
public:

	static std::string getGameCppVersion() {
		//年月日ip索引 //后边用工具生成
		return GAMECPPVERSION_TOOLSTR;
	}
	//if (destr.length() > 512 || name.length() > 100 || name.length() == 0 || destr.length() == 0) false
	static void addFunInfo(std::string name, std::string destr);
	static std::string getAllFunInfos();
	static void destory();
};

NS_CC_END
#endif // __BASE_CCGAMEDYFUNCSVERSION_H__
