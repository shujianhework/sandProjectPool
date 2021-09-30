Log = {
	d = function (...)
		release_print(string.format(...))
	end,
}
_G.TXpackage = {}
local srcRequire = require
local TXrequire = function (luapath)
	local ret = srcRequire(luapath)
	_G.TXpackage[luapath] = ret
	return ret
end
require = TXrequire
appexit = function ()
	cc.Director:getInstance():endToLua()
	if cc.PLATFORM_OS_WINDOWS == nil then
		cc.PLATFORM_OS_WINDOWS = 0
		cc.PLATFORM_OS_LINUX   = 1
		cc.PLATFORM_OS_MAC     = 2
		cc.PLATFORM_OS_ANDROID = 3
		cc.PLATFORM_OS_IPHONE  = 4
		cc.PLATFORM_OS_IPAD    = 5
		cc.PLATFORM_OS_BLACKBERRY = 6
		cc.PLATFORM_OS_NACL    = 7
		cc.PLATFORM_OS_EMSCRIPTEN = 8
		cc.PLATFORM_OS_TIZEN   = 9
		cc.PLATFORM_OS_WINRT   = 10
		cc.PLATFORM_OS_WP8     = 11
	end

	local platform = cc.Application:getInstance():getTargetPlatform()
	if platform == cc.PLATFORM_OS_IPHONE or platform == cc.PLATFORM_OS_IPAD or platform == cc.PLATFORM_OS_MAC then
		os.exit()
	end
end
local start = function ()
	cc.FileUtils:getInstance():setPopupNotify(false)
	
	allConstRootPaths = allConstRootPaths or { "" }
	_G.Root_Datas = {
		allConstRootPaths = allConstRootPaths,
		cppVersion = CheckCpp._getCppVersion()
	}
	for i,v in ipairs(allConstRootPaths) do
		cc.FileUtils:getInstance():addSearchPath(v.."/src")
		cc.FileUtils:getInstance():addSearchPath(v.."/res")
	end

	require "config"
	require "cocos.init"

	local str = CheckCpp._getAllFunInfos()
	str = "return "..str
	_G.Root_Datas.CppAllFuns = loadstring(str)()
end
xpcall(start,function ( ... )
	Log.d(...)
	appexit(false)
end)
require("channelMain")
local function main()
    require("app.MyApp"):create():run()
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    Log.d(msg)
    appexit(false)
end
