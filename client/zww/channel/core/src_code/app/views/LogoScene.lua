require("cocos.cocos2d.json")

local LogoScene = class("LogoScene", cc.load("mvc").ViewBase)

LogoScene.RESOURCE_FILENAME = "UILogoScene.csb"
LogoScene.eventPools = {}
LogoScene.RESOURCE_BINDING = LogoScene.eventPools
local LOGONORMALMAXTIME = 2
assert(LOGONORMALMAXTIME > 1)
--除了点开开关的情况和出错的情况，这个界面最多2.5 s
function LogoScene.eventPools:on_bug_switch_root(scene,node,touchType)
	--print(tolua.type(scene),tolua.type(node),touchType)
	if touchType == 0 then
		scene.state = 2
		self.startTime = os.time()
	elseif touchType == 1 then
		local pt = node:getTouchMovePosition()
		if pt.x > 50 and pt.x < 150 and pt.y > 80 and pt.y < 180 then
		else
			self.startTime = nil
		end
		dump(pt)
		scene.state = 3
	elseif touchType == 2 then
		if scene.bugLayer:isVisible() then
			scene.state = 1
		else
			if self.startTime and (os.time() - self.startTime) > 3 then
				scene.state = 4
				scene:openSuperSwitchUI(true)
			else
				scene.state = 1
			end
		end
		self.startTime = nil
	else
		scene.state = 1
		self.startTime = nil
	end
	if scene.state == 1 then
		scene:openSuperSwitchUI(false)
	end
end
function LogoScene:getRootWebInfos()

end
function LogoScene:openSuperSwitchUI(open)
	self.bugLayer:setVisible(open)
	if open then
	else
		local rootweb = App:getData("rootweb")
		if rootweb ~= nil then
			--Scene跳转
			self:switchNextScene()
			return
		end
		local params = {
			channeId =Root_Datas.channelId,
			packageName = "sfds",
			pageageVersion = "1.0.1",
			time = os.time()
		}
		local strParam = ""
		for k,v in ipairs(params) do
			strParam = strParam.."&"..k.."="..v
		end
		local rooturlInfos = App:getData("rootUrlInfo")
		if rooturlInfos == nil then
			rooturlInfos = {}
			App:setData("rooturlInfos",rooturlInfos)
		end
		for i,v in ipairs(LOCAL_CONST_URLS) do
			local url = v..strParam
			Log.d("send  "..url)
			local xhr = cc.XMLHttpRequest:new()
			xhr.responseType = cc.XMLHTTPREQUEST_RESPONSE_STRING
			xhr:open("GET", url)
			rooturlInfos[v] = 1
			local function onReadyStateChange()
				Log.d("recv  "..url)
				if xhr.readyState == 4 and(xhr.status >= 200 and xhr.status < 207) then
					rooturlInfos[v] = 2
					local statusString = "Http Status Code:" .. xhr.statusText
					local rootweb = App:getData("rootweb")
					if rootweb ~= nil then
						return
					end
					Log.d("recv data "..xhr.response)
					local data = json.decode(xhr.response)
					App:setData("rootweb",data)
					data.url = v
					if App:getData("sceneName") ~= "LogoScene" or self.state ~= 1 then
						return 
					end
					local useTime = os.time() - self.createTime
					self:runAction(cc.Sequence:create(cc.DelayTime:create(math.max(0,LOGONORMALMAXTIME - useTime)),cc.CallFunc:create(function ()
						if App:getData("sceneName") ~= "LogoScene" then
							return
						end
						if self.state == 1  then--有可能已经跳走了
							self:switchNextScene()
							return
						end
				    end)))
				else
					rooturlInfos[v] = 3
					for i1,v1 in ipairs(LOCAL_CONST_URLS) do
						if rooturlInfos[v1] and rooturlInfos[v1] == 2 then
							return
						end
					end
					Log.d("all rooturlInfos access faile ")
				end
			end
			Log.d(string.format("Http GET: %s", url))
			xhr:registerScriptHandler(onReadyStateChange)
			xhr:send()
		end
		local useTime = os.time() - self.createTime
		self:runAction(cc.Sequence:create(cc.DelayTime:create(math.max(0,LOGONORMALMAXTIME - useTime)),cc.CallFunc:create(function ()
			if self.state == 1 then
				self:switchNextScene()
				return
			end
	    end)))
	end
end
function LogoScene:switchNextScene()
	App:enterScene("AssertsUpdateScene")
end
function LogoScene:pushPoint(pt)
	local idx = #self.vectors
	pt = cc.p(math.ceil(pt.x),math.ceil(pt.y))
	local key = ""..pt.x.."|"..pt.y
	if self.vectorsHashKey[key] then
		return
	end
	if idx == 0 then
		self.vectors[idx+1] = pt
		self.vectorsHashKey[key] = 1
	else
		--如何连续性质的增加？
		local prvePt = self.vectors[idx]
		local off = cc.pSub(pt,prvePt)
		local len = math.ceil(cc.pGetLength(off))
		if len == 0 then
			return
		elseif len == 1 then
			self.vectors[idx+1] = pt
			self.vectorsHashKey[key] = 1
		else
			local normalize = cc.pNormalize(off)
			for i=1,len do
				temp = cc.pMul(off,i)
				local newPt = cc.pAdd(prvePt,temp)
				local pt1 = cc.p(math.ceil(newPt.x),math.ceil(newPt.y))
				local key1 = ""..pt1.x.."|"..pt1.y
				if self.vectorsHashKey[key1] == nil then
					self.vectorsHashKey[key1] = 1
					self.vectors[#self.vectors + 1] = pt1
				end
			end
			self.vectors[#self.vectors + 1] = pt
			self.vectorsHashKey[key] = 1
		end
		
	end
end
function LogoScene:onCreate()

	LogoScene.eventPools.ProxyNode = self
	self.state = 1
    local logo_bg = App:getNodeByName(self.resourceNode_,"logo_bg")
    self.bugLayer = App:getNodeByName(logo_bg,"bugLayer")
    logo_bg:loadTexture("res/prveLogin/loading.jpg")
    self.createTime = os.time()
    self:openSuperSwitchUI(false)
    
	local drawNode = cc.DrawNode:create()
	print(device.platform)
	if device.platform == "windows" then
		drawNode:drawSolidRect(cc.p(50,80), cc.p(150,180), cc.c4f(1.0, 1.0, 0.34, 0.75))
	end
    self:addChild(drawNode)
    self.drawNode = drawNode
    self.vectorsHashKey = {}

end
return LogoScene