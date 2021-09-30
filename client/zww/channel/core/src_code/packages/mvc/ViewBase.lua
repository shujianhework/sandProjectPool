
local ViewBase = class("ViewBase", cc.Node)

function ViewBase:ctor(app, name)
    self:enableNodeEvents()
    self.app_ = app
    self.name_ = name

    -- check CSB resource file
    local res = rawget(self.class, "RESOURCE_FILENAME")
    if res then
        self:createResoueceNode(res)
    end

    local binding = rawget(self.class, "RESOURCE_BINDING")
    if res and binding then
        self:createResoueceBinding(binding)
    end

    if self.onCreate then self:onCreate() end
end

function ViewBase:getApp()
    return self.app_
end

function ViewBase:getName()
    return self.name_
end

function ViewBase:getResourceNode()
    return self.resourceNode_
end

function ViewBase:createResoueceNode(resourceFilename)
    if self.resourceNode_ then
        self.resourceNode_:removeSelf()
        self.resourceNode_ = nil
    end
    dump(cc.FileUtils:getInstance():getSearchPaths())
    self.resourceNode_ = cc.CSLoader:createNode(resourceFilename)
    assert(self.resourceNode_, string.format("ViewBase:createResoueceNode() - load resouce node from file \"%s\" failed", resourceFilename))
    self:addChild(self.resourceNode_)
end

function ViewBase:createResoueceBinding(binding)
    print([[function ViewBase:createResoueceBinding(binding) 1]])
    assert(self.resourceNode_, "ViewBase:createResoueceBinding() - not load resource node")
    local fun = nil
    print([[function ViewBase:createResoueceBinding(binding) 2]])
    fun = function(node)
        print([[function ViewBase:createResoueceBinding(binding) 3]])
        if type(node) == "userdata" then
            local childs = node:getChildren()
            for i, v in ipairs(childs) do
                fun(v)
            end
            if type(node.setTouchEnabled) == "function" then
                print([[function ViewBase:createResoueceBinding(binding) 4]])
                local Type = node:getCallbackType()
                local Name = node:getCallbackName()
                local funCallBack = nil
                if Type ~= "" then
                    funCallBack = function (...)
                        if type(binding[Name]) == "function" then
                            binding[Name](binding,self,...)
                        elseif type(binding.___msgCtrlHand) == "function" then
                            binding:___msgCtrlHand(self,...)
                        end
                    end
                end
                print("ViewBase:crateResou... ",Type,Name,node:getName())
                if Type == "Click" then
                    node:addClickEventListener(funCallBack)
                elseif Type == "Touch" then
                    node:addTouchEventListener(funCallBack)
                elseif Type == "Event" then
                    if node.addCCSEventListener then
                        node:addCCSEventListener(funCallBack)
                    end
                end
            end
        end
    end
    if type(binding) == "table" or type(binding) == "userdata" then
        print([[function ViewBase:createResoueceBinding(binding) 5]])
        fun(self.resourceNode_)
    end
    print([[function ViewBase:createResoueceBinding(binding) 6]])
end

function ViewBase:showWithScene(transition, time, more)
    self:setVisible(true)
    local scene = display.newScene(self.name_)
    scene:addChild(self)
    display.runScene(scene, transition, time, more)
    return self
end

return ViewBase
