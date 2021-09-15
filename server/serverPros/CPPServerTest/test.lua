if dump == nil then
	dumps = function ( ... )
		local addrs = {}
		local prve = ""
		local tab = nil
		tab = {["number"] = function (v)
			return ""..v
		end,["string"] = function (v)
			return "[["..v.."]]"
		end,["boolean"] = function (v)
			return v and "true" or "false"
		end,["function"] = function (v)
			return "__func:"..tostring(v)
		end,["userdata"] = function (v)
			return "__user:"..tostring(v)
		end,["table"] = function (vv)
			if addrs[tostring(vv)] == nil then
				addrs[tostring(vv)] = 1
				prve = prve.."\t"
				local ss = "{\n"
				for k,v in pairs(vv) do
					ss = ss..prve.."[\""..tab(k,true).."\"]="
					ss = ss..tab(v)..",\n"
				end
				prve = prve:sub(1,-2)
				ss = ss:sub(1,-2).."\n"..prve.."}"
				return ss
			else
				return "__tab:"..tostring(v)
			end
		end,function (v,flg)
			
		end}
		setmetatable(tab,{__call = function (t,v,flg)
			if flg and type(v) == "string" then
				return v
			end
			return tab[type(v)](v)
		end})
		local param = {...}
		local s = " "
		if #param == 1 then
			if type(param[1]) == "table" then
				return "return "..tab(param[1])
			else
				return tab(param[1])
			end
		elseif #param == 2 and type(param[1]) == "string" and type(param[2]) == "table" then
			return "local "..param[1].." = "..tab(param[2])
		else
			for i,v in pairs(param) do
				s = s..tab(v)..","
			end
			s = s:sub(1,-2)
			return s
		end
	end
	dump = function (...)
		print(dumps(...))
	end
	dump2file = function (path,data)
		local f = io.open(path,"w")
		if f then
			if type(data) ~= "table" then
				f:write(dumps({data}))
			else
				f:write(dumps(data))
			end
			f:close()
		end
	end
	os.srcexecute = os.execute
	os.execute = function ( ... )
		if Debug == true then
			print(...)
		end
		return os.srcexecute(...)
	end
end
dump(Reg_lua_LuaTools1__001)
dump(Reg_lua_LuaTools2__001)
dump(Reg_lua_LuaTools5__001)
-- local a = LuaTools2(23)
-- --a:setName("apple")
-- a.salary = 235.12
-- print(a.salary)
-- a:test002(100,"this is a la ji",23.1)
-- local name = a.name
-- print(name)