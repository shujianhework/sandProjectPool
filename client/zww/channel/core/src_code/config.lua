-- 0 - disable debug info, 1 - less debug info, 2 - verbose debug info
DEBUG = 2
-- use framework, will disable all deprecated API, false - use legacy API
CC_USE_FRAMEWORK = true
-- show FPS on screen
CC_SHOW_FPS = true
-- disable create unexpected global variable
CC_DISABLE_GLOBAL = false
-- for module display
CC_DESIGN_RESOLUTION = {
    width = 960,
    height = 640,
    autoscale = "FIXED_WIDTH",
    callback = function(framesize)
        local ratio = framesize.width / framesize.height
        if ratio <= 1.34 then
            -- iPad 768*1024(1536*2048) is 4:3 screen
            return {autoscale = "SHOW_ALL"}
        end
    end
}
--部分根信息 不参与更新 基本不变
LOCAL_CONST_URLS = {
    "https://localhost:44351/Pages/startGame.aspx",
    "https://192.168.0.109:44351/Pages/startGame.aspx",
    "http://www.xn--3-y50c.com:44351/Pages/startGame.aspx",
    --"http://www.xn--3-y50c.com:44351/Pages/startGame.aspx",
}