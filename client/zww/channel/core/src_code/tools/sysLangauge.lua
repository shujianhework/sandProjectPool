local sysLangauge = {}
function sysLangauge:init()
	local languageNames = require "languageNames"
	local ret = cc.UserDefault:getInstance():getStringForKey("lang")
	local languageCout = 0
    if languageNames[ret] == nil then

    	for k,v in pairs(languageNames) do
    		languageCout = languageCout + 1
    	end
    else
    	languageCout = 1
    end

    assert(languageCout > 0,"缺少支持的语言")
    local lang = ""
    if languageCout > 1 then
    	--获取系统语言
    	local lang_code = cc.Application:getInstance():getCurrentLanguageCode()
        lang = require("languageSys2Ini")(lang_code)
    elseif ret == nil or ret == "" then

        lang = next(languageNames)
    else
        lang = ret
    end
    
    cc.UserDefault:getInstance():setStringForKey("lang",lang)
    self:setLang(lang)
end
function sysLangauge:setLang(lang)
    local lang1 = App:getLang()
    print(">>>>>>>>>>>>>>>>>",lang,debug.traceback())
    App:setLang(lang)
    require "tools.prveLoginLanguage"
    --怎么切换游戏内语言
    

end
return sysLangauge