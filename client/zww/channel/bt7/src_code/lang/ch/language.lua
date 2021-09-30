if App == nil then
	return
end
local Tlang = App:getData("langTab")
local lang = App:getData("lang")
if lang == nil then
	return
end	Tlang["LEVEL_1"] = [[等级_%d]]
	Tlang["RESOURCE_UPDATE_SPEED1"] = [[更新进度(%s/%s,速度%s/每秒)]]
	Tlang["RESOURCE_UPDATE_TIPS1"] = [[用python从数据库中取到数据后，写入excel中做成自动报表，ExcelWrite默认的格式一般来说都比较丑，但workbook提供可以设置自定义格式，简单记录个demo，供初次使用者参考。]]
