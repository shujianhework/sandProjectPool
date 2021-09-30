_G.channel = "develop"
_G.lang = "ch"
local main = cc.FileUtils:getInstance():fullPathForFilename("main.lua")
print(main:len())
if main:len() == 0 then
	main = cc.FileUtils:getInstance():fullPathForFilename("main.luac")
end
print(main:len())
allConstRootPaths = {}

if main:len() == 0 then
	allConstRootPaths = { "core",channel }
	for i,v in ipairs(allConstRootPaths) do
		cc.FileUtils:getInstance():addSearchPath(v.."\\src_code")
		cc.FileUtils:getInstance():addSearchPath(v.."\\res")
		package.path = package.path..";"..v.."src_code"
	end
end
require("main")