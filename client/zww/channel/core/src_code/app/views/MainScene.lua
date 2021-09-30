
local MainScene = class("MainScene", cc.load("mvc").ViewBase)
MainScene.RESOURCE_FILENAME = "UIMainScene.csb"
MainScene.eventPools = {}
MainScene.RESOURCE_BINDING = MainScene.eventPools
--mainScene = new MainScene()
function MainScene.eventPools:___msgCtrlHand(mainScene,...)
    print("aaaa  ",...)
end
function MainScene.eventPools:onMsgHandler(mainScene,node)
    if node.edit then
        local text = node.edit:getString()
        if node:getName() == "Button_1" then
            local first = text:sub(1,4)
            if first == "cmd:" then
                local strnext = text:sub(5,-1)
                local idx = strnext:find(" ")
                if idx then
                    local ikeys = strnext:sub(1,idx-1)
                    if #ikeys > 0 then
                        self:__cmdsHandlers(ikeys,strnext:sub(idx+1,-1))
                    end
                end
            end
        end
    end
end
function MainScene.eventPools:__netHandler(ip,port)
end
function MainScene.eventPools:__cmdsHandlers(ikey,value)
    
end
local serverflg = true
function MainScene:start()
    local socket = require("socket")
    print(socket._VERSION);
    local host = "127.0.0.1"  
    local port = 10001;  
    self.G_SOCKETTCP = socket.tcp()  
    if serverflg then
        local n,e = self.G_SOCKETTCP:bind(host,port,5)
        self.G_SOCKETTCP:settimeout(5)
        self.G_SOCKETTCP:listen()
    else
        local n,e = self.G_SOCKETTCP:connect(host, port)  
        print("connect return:",n,e)  
        self.G_SOCKETTCP:settimeout(0)  
    end
    self:startServer()
end
function MainScene:socketClose()  
    self.G_SOCKETTCP:close()  
end  
function MainScene:socketSend(sendStr)  
    self.G_SOCKETTCP:send(sendStr)  
end 
function MainScene:socketReceive()  
    if serverflg then
        local client,err = self.G_SOCKETTCP:accept()
        if client then
            --client:send("sdfsdfdsf")
            self.list:onEventHandle("accept",client)
        else
            print(err)
        end
    else
        local response, receive_status=self.G_SOCKETTCP:receive()  
        print("receive return:",response or "nil" ,receive_status or "nil")  
        if receive_status ~= "closed" then  
            if response then  
                print("Receive Message:"..response) 
            end  
        else  
            print("Service Closed!")
        end 
    end
end 
function MainScene:startServer()
    local delay = 0  
    local function receiveHandler(dt)  
        delay = delay + dt  
        if delay > 0.1 then  
            self:socketReceive()  
            delay= 0
        end  
    end
    self:scheduleUpdateWithPriorityLua(receiveHandler,1)
    if serverflg == false then
        self:socketSend("asdf")
    end
end
function MainScene:onCreate()
    MainScene.eventPools.ProxyNode = self
    local edit = App:getNodeByName(self.resourceNode_,"TextField_2")    
    local send = App:getNodeByName(self.resourceNode_,"Button_2")
	
	local label = cc.Label:create()
	label:setPosition(cc.p(send:getPositionX(),send:getPositionY()+20))
	label:setString("sdfsdfsdxcvxcvxc")
	CheckCpp.setOtherFontFlg(label,1)
	print(CheckCpp.isUnderline(label))
	print(CheckCpp.isItalic(label))
	print(CheckCpp.isStrikeOut(label))
	label:setColor(cc.c3b(255,23,0))
	label:setSystemFontSize(30) 
	self:addChild(label)
	
    send.edit = edit
    local layer = send:getParent()
    edit = App:getNodeByName(self.resourceNode_,"TextField_1")  
    send = App:getNodeByName(self.resourceNode_,"Button_1")
    send.edit = edit
	if true then
		return
	end
    layer:retain()
    layer:removeFromParent()
    local list = App:getNodeByName(self.resourceNode_,"ListView_1")
    list.viewData = {}
    list.viewModels = {layer}
    list.__updatadata = false
    self.list = list
    list.datas = {}
    self.list.onEventHandle = function (list,...)
        self:ServerProxy(...)
    end
    self.list:scheduleUpdateWithPriorityLua(function ()
        self.list:onEventHandle("update")
    end,1)
    self:start()
end
function MainScene:ServerProxy(name,...)
    local exparam = {...}
    if name == "update" then
        if self.list.__updatadata then
            self.list.__updatadata = false
            for i,v in ipairs(self.list.viewData) do
                if v.view == nil then
                    local item = v.view:clone()
                    item:setName(v.key)
                    self.list:addChild(item)
                    item:runAction(cc.RepeatForever:create(cc.CallFunc:create(function ()
                        local response, receive_status=self.G_SOCKETTCP:receive()  
                        print("receive return:",response or "nil" ,receive_status or "nil")  
                        if receive_status ~= "closed" then  
                            if response then  
                                print("Receive Message:"..response) 
                                self:runAction(cc.Sequence:create(cc.CallFunc:create(function ()
                                    self:ServerProxy("update")
                                end)))
                                v.f:write(response.."\n")
                            end
                        else  
                            print("Service Closed!")
                            v.f:close()
                            v.f = nil
                            v.net:close()
                            item:removeFromParent()
                        end 
                    end)))
                end
            end
        end
    elseif name == "accept" then
        local randkey = ""..os.time().."|"..math.random(1,10000)
        self.list.__updatadata = true
        self.list.viewData[#self.list.viewData + 1] = {key = randkey,net = exparam[1],view = nil,f = nil}
        -- self:runAction(cc.Sequence:create(cc.DelayTime:create(0.25), cc.CallFunc:create(function ( ... )
        -- end)))
    end
end
return MainScene
