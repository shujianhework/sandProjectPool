
local MyApp = class("MyApp", cc.load("mvc").AppBase)

function MyApp:onCreate()
	App = self
	self._data = {langTab = {}}
    math.randomseed(os.time())
    local sysLangauge = require ("tools.sysLangauge")
    sysLangauge:init()
end
function MyApp:lang(key)
	print([[function MyApp:lang(key) key ]]..key)
	if self._data.langTab[key] then
		return self._data.langTab[key]
	else
		return key
	end
end
function MyApp:setLang(lang)
	self:setData("lang",lang)
end
function MyApp:getLang()
	return self:getData("lang")
end
function MyApp:setData(key,data)
	self._data[key] = data
end
function MyApp:getData( key,data )
	return self._data[key]
end
return MyApp
