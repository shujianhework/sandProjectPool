#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "lua_module_register.h"
#include "register_all_packges.h"
#include "base/CCGameDyFuncsVersion.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX)
#include "ide-support/CodeIDESupport.h"
#endif

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
#include "runtime/Runtime.h"
#include "ide-support/RuntimeLuaImpl.h"
#endif
static char zuiwengtingji[100] = "";
static char ouyangxiu[100] = "";
using namespace CocosDenshion;

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
    const char pass[5] = "thos";
#if WIN32
    log("zuiwentingji = %s,ouyangxiu = %s", zuiwengtingji, ouyangxiu);
#endif
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    RuntimeEngine::getInstance()->end();
#endif

}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
//static int register_all_packages()
//{
//    lua_State *L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
//    /*lua_getglobal(L, "_G");
//    */
//    
//    return 0; //flag for packages manager
//}

bool AppDelegate::applicationDidFinishLaunching()
{
    // set default FPS
    Director::getInstance()->setAnimationInterval(1.0 / 60.0f);

    // register lua module
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);
    register_all_packages(L);
    std::string k;
    std::string p;
    getPasswordStrs(k,p);
    LuaStack* stack = engine->getLuaStack();
    if (k.length() > 0 && p.length() > 0) {
        char p1[300] = "";
        std::string p2 = "";
        short first = p[0] % 8 + 8;
        short last = 255 - (k[0] % 5 + 5);
        for (int i = 0; i < p.length(); i++)
        {
            char c = p[i];
            if (c > first && c < last) {
                sprintf(p1, "%02d", c);
                p2 = p2 + p1;
                if (p2.length() > 250) {
                    break;
                }
            }
        }
        if (p2.length() == 0) {
            p2 = k + p;
        }
        stack->setXXTEAKeyAndSign(p2.c_str(), p2.length(), k.c_str(), k.length());
    }
    //register custom function
    //LuaStack* stack = engine->getLuaStack();
    //register_custom_function(stack->getLuaState());

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0) && CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    auto runtimeEngine = RuntimeEngine::getInstance();
    runtimeEngine->addRuntime(RuntimeLuaImpl::create(), kRuntimeEngineLua);
    runtimeEngine->start();
#else
    if (engine->executeScriptFile("src/main.lua"))
    {
        return false;
    }
#endif

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
