if App == nil then
	return
end
local Tlang = App:getData("langTab")
local lang = App:getData("lang")
if lang == nil then
	return
end	Tlang["LEVEL_1"] = [[Level_%d]]
	Tlang["RESOURCE_UPDATE_SPEED1"] = [[Update progress (%s /%s at %s/sec)]]
	Tlang["RESOURCE_UPDATE_TIPS1"] = [[After getting the data from the database in Python, it is written into Excel to make an automatic report. The default format of excelwrite is generally ugly, but the workbook provides a user-defined format and a simple demo for reference by first-time users.]]
