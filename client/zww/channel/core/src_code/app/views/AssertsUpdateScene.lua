local AssertsUpdateScene = class("AssertsUpdateScene", cc.load("mvc").ViewBase)
AssertsUpdateScene.RESOURCE_FILENAME = "UIupdateResourceScene.csb"
AssertsUpdateScene.eventPools = {}
AssertsUpdateScene.RESOURCE_BINDING = AssertsUpdateScene.eventPools

function AssertsUpdateScene:initUpdateLoading()
	
    local loadingLayer = App:getNodeByName(self.resourceNode_,"loadingLayer")
	local tipsText = App:getNodeByName(self.resourceNode_,"tipsTexts")
    local speedText = App:getNodeByName(self.resourceNode_,"speedState")
	local loadingBar = App:getNodeByName(loadingLayer,"loading")

    loadingBar:setScale9Enabled(true)
    loadingBar:setCapInsets(cc.rect(0, 0, 0, 0))
    local width = display.width*0.8
    local startOffx = display.width*(1-0.8)/2
    local height = 25
    loadingBar:setContentSize(cc.size(width,height))
    local posy = loadingBar:getPositionY()
    loadingBar:setPercent(85)

	--srcLoading
	local bg = ccui.ImageView:create("prveLogin/loadingUnder.png")
	bg:setScale9Enabled(true)
    bg:setCapInsets(cc.rect(0, 0, 0, 0))
    bg:setPosition(cc.p(display.width/2,posy-2))
    bg:setLocalZOrder(loadingBar:getLocalZOrder()-1)
    bg:setContentSize(cc.size(width+8,height + 8))

    loadingBar:getParent():addChild(bg)
    
    local gifnode = CheckCpp.gifbase:create("prveLogin/animation.gif",false)
    loadingBar:getParent():addChild(gifnode)
    local gifsize = gifnode:getSize()
    self.loading = {setPercent = function (a,percent)
        if percent == nil and type(a) == "number" then
            percent = a
        end
    	loadingBar:setPercent(percent)
        if gifnode then
            percent = loadingBar:getPercent()
            gifnode:setPosition(cc.p(width / 100 * percent+startOffx,posy+gifsize.height/2))
        end
    end,setText = function (a,text)
        if text == nil and type(a) == "string" then
            text = a
        end
    	speedText:setString(text)
    end,getText = function ()
    	return speedText:getString()
    end,getPercent = function ()
    	return loadingBar:getPercent()
    end}
    self.loading.setText(App:lang("UPDATE_SCENE_STATE_UPDATE_2"))
    self.loading.setPercent(90)
    
end
function AssertsUpdateScene:checkOnPermission()
end
function AssertsUpdateScene:initTask()
    self.task = {}
    --权限检查
    self.task[#self.task + 1] = {name = "permission",title = App:lang("UPDATE_CHECK_PERMISSION"),onBack = self.checkOnPermission,wait =true,percent = 5}
    --检查根网络是否正常正常返回
    self.task[#self.task + 1] = {name = "rootNet",title = App:lang("UPDATE_ROOT_NET"),onBack = self.checkRootNet,percent = 5}
    --zip obb 等系列检查
    self.task[#self.task + 1] = {name = "unzip",title = App:lang("UPDATE_ZIP_UNPACKHANDER"),onBack = self.zipUnPackHander,wait = false,percent = 5}
    --download pass check update
    self.task[#self.task + 1] = {name = "downloadCheck",title = App:lang("UPDATE_DOWNINFO_GET"),wait = "rootNet",onBack = self.downLoadPrveCheck,percent = 15}
    --download
    self.task[#self.task + 1] = {name = "downloading",title = App:lang("UPDATE_DOWNING"),wait = "downloadCheck",onBack = self.downLoading,percent = 65}
    --checkDownload
    self.task[#self.task + 1] = {name = "downloadCheckFile",title = App:lang("UPDATE_DOWNINGFILECHECKS"),wait = "downloadCheck",onBack = self.downLoadingCheck,percent = 15}
    --useNewFiles
    self.task[#self.task + 1] = {name = "useNewFiles",title = App:lang("UPDATE_USERNEWFILE"),wait = false,onBack = self.reloadFiles}
    --跳转场景到登录
    self.task[#self.task + 1] = {name = "switchScene",title = App:lang("UPDATE_ENTER_LOGIN"),wait = false,onBack = self.switchScene}
end
function AssertsUpdateScene:update()
    
end
function AssertsUpdateScene:onCreate()
    
	AssertsUpdateScene.eventPools.ProxyNode = self
    local logo_bg = App:getNodeByName(self.resourceNode_,"logo_bg")
    self:initUpdateLoading()
    self:initTask()
end
return AssertsUpdateScene