# -*- coding: UTF-8 -*- 
import os;
import random;
import sys;
#还去一些自定义类型扩展 和函数类型的传递
#三个表 父子表  成员变量表 函数表
#跨文件的处理，比如类头文件和成员对象的类型或函数参数类型或父类类的头文件不在一起的时候，跨文件引用
#userdata的支持  
#函数类型支持
#容器的支持
desfilekey2path={}
c2LuaTypeEx = {}
allFunRegisterTables = {}
nowExportClass = ""
def readLuaScriptManageHead():
    f = open("Manages/LuaScriptManage.h","r")
    LuaClasss = []
    if f:
        lines = f.readlines()
        f.close()
        for line in lines:
            if len(line) > 0:
                idx = line.find("ExtensionClassAssistant")
                if idx > 6 and line[0:idx].find("//") == -1 and line[0:idx].find("/*") and line[0:idx].find("#include \"") == 0:
                    linetext = line.replace("\n","")
                    LuaClasss.append(linetext)
    #print(LuaClasss)
    #sys.exit(1)
    return LuaClasss
c2LuaType = {
    "int":"number","long":"number","short":"number","double":"number","float":"number",
    "bool":"boolean",
    "string":"string",
    "std::string":"string"}
def getCTypeLua(CType):
    if CType in c2LuaType:
        return c2LuaType[CType]
    if CType.find("unsigned ") >= 0:
        if CType[10:-1] in c2LuaType:
            return c2LuaType[CType[10:-1]]
    if CType.endswith("*"):
        return "userdata"
    return False
def checkTypes(CType,isFunRet):
    if CType == "void":
        return isFunRet
    return getCTypeLua(CType) != None
def readClassInfo(path,Class):
    operpath = path
    if path.startswith("../"):
        operpath = operpath[3:len(path)]
    f = open(operpath,"r")
    if f:
        lines = f.readlines()
        f.close()
        classLines = []
        classline = -1
        ignore = 0
        curidx = 0
        baseList = []
        funkey = "CPP2LUABACKREGISTERFUN"
        for line in lines:
            idx = line.find("//")
            curidx = curidx + 1
            if ignore > 0:
                ignore = ignore - 1
                continue
            if idx == 0:
                continue
            text = line
            if idx > 0:
                text = line[0:idx-1]
            text = text.strip("\t")
            text = text.strip()
            if text.startswith(funkey):
                text = text[len(funkey)+1:-1]
                text = text.strip("(")
                text = text.strip(")")
                text = text.strip(" ")
                nameparams = text.split(",")
                if not nameparams[0] in c2LuaType:
                    funType = nameparams[0]
                    c2LuaType[funType] = "function"
                    nameparams.remove(funType)
                    c2LuaTypeEx[funType] = {
                        "name":funType,
                        "params":nameparams,
                        "path":path
                    }
                continue
            elif classline < 0:
                keyword = "struct "
                if text.startswith(keyword) == False:
                    keyword = "class "
                    if text.startswith(keyword) == False:
                        continue
                if text.startswith(keyword+Class) == False:
                    continue
                text3 = text
                if text.find("{") == -1:
                    ignore = 0
                    for i in range(curidx,len(lines)):
                        text2 = lines[i]
                        ignore = ignore + 1
                        idx = text2.find("//")
                        if idx > 0:
                            text2 = text2[0:idx-1]
                        idx = text2.find("{")
                        if idx >= 0:
                            break;
                        text = text +" "+ text2
                text = text.strip("\n")
                text = text.strip("\t")
                idx = text.find("BASECLUACLASS")
                if idx >= 0:
                    base = text[idx:len(text)]
                    idx = base.find("(")
                    base = base[idx+1:len(base)]
                    idx = base.find(")")
                    base = base[0:idx]
                    base = base.split(",")
                    for baseitem in base:
                        if len(baseitem) > 1:
                            baseList.append(baseitem)
                classLines.append(text)
                classline = 1
            if classline > 0:
                if text == "CLUACLASSEND":
                    classline = -2
                    break
                if text.find("EXPORTVALSET ") >= 0 or text.find("EXPORTVALGET ") >= 0:
                    classLines.append(text)
                elif text.find("EXPORTFUN ") >= 0 or text.find("EXPORTOBJFUN ") >= 0:
                    #怎么解决多行的问题
                    lcout = text.count('(')
                    rcout = text.count(')')
                    if lcout == rcout:
                        classLines.append(text)
                    elif lcout < rcout:
                        return None
                    else:
                        ignore = 0
                        for i in range(curidx,len(lines)):
                            text2 = lines[i]
                            ignore = ignore + 1
                            idx = text2.find("//")
                            if idx > 0:
                                text2 = text2[0:idx-1]
                            text2 = text2.strip("\t")
                            text2 = text2.strip()
                            rcout1 = text2.count(')')
                            rcout = rcout + rcout1
                            text = text +" "+ text2
                            if(rcout == lcout):
                                break
                        classLines.append(text)

                else:
                    continue
        if classline == -2:
            hasebase = {}
            classHashFlg = {
                "index":{},
                "newindex":{},
                "function":{},
                "name":Class,
                "baseList":[],
                "include":[],
            }
            for baseitem in baseList:
                if not baseitem in hasebase:
                    classHashFlg["baseList"].append(baseitem)
                    hasebase[baseitem] = 1
            for line in classLines:
                text = line
                funtype = 1
                firstkey = "EXPORTFUN"
                idx = text.find(firstkey+" ")
                if idx == -1:
                    funtype = 2
                    firstkey = "EXPORTOBJFUN"
                    idx = text.find(firstkey + " ")
                if idx >= 0:
                    if text.find(">") > 0:
                        continue
                    idx = text.find("(")
                    idx2 = text.rfind(")")
                    text1 = text[0:idx]
                    text2 = text[idx+1:idx2]
                    texttab = text1.split(" ")
                    funItem = {"funtype":funtype}
                    funItem["ret"] = texttab[-2]
                    
                    if checkTypes(funItem["ret"],True) == False:
                        continue

                    funItem["name"] = texttab[-1]
                    
                    if text.find(" static ") >= 0:
                        funItem["static"] = True
                    else:
                        funItem["static"] = False

                    if len(text2) < 5:
                        text2 = ""
                    params = text2.split(",")
                    if len(params) == 1 and len(params[0]) < 3:
                        params = []
                    funItem["param"] = len(params)
                    idx = 1
                    for param in params:
                        param = param.strip()
                        paramnames = param.split(" ")
                        if( checkTypes(paramnames[0],False) == False):
                            funItem = None
                            break
                        funItem[str(idx)] = paramnames[0]                        
                        idx = idx + 1
                    if funItem == None:
                        continue
                    if not funItem["name"] in classHashFlg["function"]:
                        classHashFlg["function"][funItem["name"]] = []
                    
                    classHashFlg["function"][funItem["name"]].append(funItem)
                else:
                    items = text.split(" ")
                    idx = text.find("<")
                    if idx >= 0:
                        continue
                    inValue = False
                    outValue = False
                    static = False
                    ctype = ""
                    name = ""
                    for item in items:
                        if item == "EXPORTVALGET":
                            outValue = True
                        if item == "EXPORTVALSET":
                            inValue = True
                        if items[-1] == item:
                            name = item[0:-1]
                        if items[-2] == item:
                            if checkTypes(item,False) == False:
                                name = None
                                break
                            ctype = item
                        if item == "static":
                            static = True

                    if inValue == False and outValue == False:
                        continue
                    if name == None:
                        continue
                    valueInfo = {"static":static,"name":name,"type":ctype}
                    if inValue:
                        classHashFlg["newindex"][name] = valueInfo
                    if outValue:
                        classHashFlg["index"][name] = valueInfo
            return classHashFlg
def makeFunName(ClassName,FunName,isLuaSys):
    name = "Ser_AutoLua_"+ClassName+""
    if FunName != None:
        name = name + "_" + FunName
    if isLuaSys:
        name = name + "_luaTable"
    return name
def makeFunNameLine(ClassName,FunName,isLuaSys):
    return "static int " + makeFunName(ClassName,FunName,isLuaSys)+"(lua_State* L)"
def pushLuaTypeStr(ctype,value):
    if ctype in c2LuaType:
        luaType = getCTypeLua(ctype)
        if luaType == "number":
            return "lua_pushnumber(L,"+value+")"
        elif luaType == "boolean":
            return "lua_pushboolean(L,"+value+")"
        elif luaType == "string":
            return "lua_pushstring(L,"+value+")"

    return "this is a error"
def LuaToCTypeStr(ctype,idx,retname):
    if ctype in c2LuaType:
        luaType = getCTypeLua(ctype)
        if luaType == "number":
            return ctype + " " +retname + " = lua_tonumber(L," + str(idx) + ");"
        elif luaType == "boolean":
            return ctype + " " +retname + " = lua_toboolean(L," + str(idx) + ");"
        elif luaType == "string":
            return ctype + " " +retname + " = lua_tostring(L," + str(idx) + ");"
        elif luaType == "userdate":
            if ctype in c2LuaTypeEx:
                return "GETUSERDATA2TYPE(" + ctype + ", "+ retname +", " + str(idx) + ");"
        elif luaType == "function":
            if ctype in c2LuaTypeEx:
                return "auto " + retname + " = lua_tocfunction(L, " + str(idx) + ");"

    return "this is a error"

def lua2CTypeFunHandler(ctype,retname,useobj):
    
    funstr = "auto luaAutoFun = [&]("
    idx = 0
    for itemType in c2LuaTypeEx[ctype]["params"]:
        if checkTypes(itemType) and (not itemType in c2LuaTypeEx):
            funstr = funstr + itemType
        else:
            funstr = funstr + "this error excontype " + itemType
        funstr = funstr + retname + str(idx)
        idx = idx + 1
        funstr = funstr + ","
    funstr = funstr[0:-1]
    funstr = funstr + "){\n\t\t"
    #a = class1() a:recv(function()end)  b = class1() b:recv(function()end)  存在b覆盖了a，或者不能回调到b
    #funstr = funstr + "

def cTypeConditionStr(ctype,idx):
    luatype = getCTypeLua(ctype)
    if luatype == "number":
        return " lua_type( L,"+str(idx)+") == LUA_TNUMBER"
    elif luatype == "boolean":
        return " lua_type( L,"+str(idx)+") == LUA_TBOOLEAN"
    elif luatype == "string":
        return " lua_type( L,"+str(idx)+") == LUA_TSTRING"
    elif luatype == "userdate":
        return " lua_type( L,"+str(idx)+") == LUA_TUSERDATA"
    elif luatype == "function":
        return " lua_type( L,"+str(idx)+") == LUA_TFUNCTION"
    else:
        return " this error contype " + luatype

def conditionsSort(a,b):
    if len(a[1]) != len(b[1]):
        return len(a[1]) < len(b[1])
    else:
        for i in range(1,len(a[1])):
            if len(a[1][i]) != len(b[1][i]):
                return len(a[1][i]) < len(b[1][i])
        if a[2] != b[2]:
            return len(a[2]) < len(b[2])
        return cmp(a,b)    
    return True

def makeParamChecks(line,start,className):
    types = []
    condition = ""
    params = ""
    paramvalues = ""
    for i in range(0,line["param"]):

        item = line[str(i+1)]
        types.append(item)
        paramname = "auto_"+item+"_"+str(i+1)
        paramname = paramname.replace(" ","")
        paramname = paramname.replace(":","")
        condition = condition + cTypeConditionStr(item,start + i + 1) + " && "
        paramvalues = paramvalues + LuaToCTypeStr(item,start + i + 1,paramname)+"\n\t\t"
        
        if item in c2LuaTypeEx and c2LuaType[item] == "function":
            paramvalues = paramvalues + "GETINSTANCEMANAGE(LuaScriptManage)->saveLuaFun2cpp(obj,\""
            paramvalues = paramvalues + className + "_" + line["name"] + "_" + str(start + i + 1 ) + "_\"," 
            paramvalues = paramvalues + paramname + ");\n\n\t\t";
            paramvalues = paramvalues + item + " " + paramname + "_fun = [](unsigned int objId, ";
            minibackidx = 0
            for typeN in c2LuaTypeEx[item]["params"]:
                paramvalues = paramvalues + typeN + " callback"+str(minibackidx)+" ,"
                minibackidx = minibackidx + 1
            paramvalues = paramvalues[0:-1]
            paramvalues = paramvalues + ") {\n\n"
            paramvalues = paramvalues + "\t\t\tLuaUserDataBase* obj = LuaUserDataBase::getLuaObjectPool(objId);\n"
            paramvalues = paramvalues + "\t\t\tauto c2luaback = GETINSTANCEMANAGE(LuaScriptManage)->getLuaFun2cpp(obj,\""
            paramvalues = paramvalues + className + "_" + line["name"] + "_" + str(start + i + 1 ) + "_\");\n"
            paramvalues = paramvalues + "\t\t\tif ( c2luaback == NULL){\n\t\t\t\tprintf(\"theread id not lua theread or\");\n\t\t\t\treturn;\n\t\t\t}\n"
            minibackidx = 0
            paramvalues = paramvalues + "\t\t\tauto L = GETINSTANCEMANAGE(LuaScriptManage)->getL();\n"
            for typeN in c2LuaTypeEx[item]["params"]:
                paramvalues = paramvalues + "\t\t\t"+pushLuaTypeStr(typeN,"callback"+str(minibackidx))+";\n"
                minibackidx = minibackidx + 1
            paramvalues = paramvalues + "\t\t\treturn ;\n\t\t};\n\n\t\t"
            allFunRegisterTables[className] = 1
            params = params + paramname + "_fun, "
        else:
            params = params + paramname + ", "
        
    return [types,condition,params,paramvalues]
allsortTemp = {}
def tempcmp(a,b):
    a1 = a
    b1 = b
    if len(a1[1]) != len(b1[1]):
        return len(a1[1]) < len(b1[1])
    else:
        for x in xrange(0,len(a1[1])):
            if len(a1[1][x]) != len(b1[1][x]):
                return len(a1[1][x]) < len(b1[1][x])
    return a<b
def iSort_0(data1,back):    
    le = len(data1)
    for x in xrange(0,le):
        maxidx = x
        for y in xrange(x+1,le):
            flg = back(data1[maxidx],data1[y])
            if flg > 0:
                maxidx = y
        if maxidx != x:
            tempValue = data1[maxidx]
            data1[maxidx] = data1[x]
            data1[x] = tempValue
    return data1

def makeClassLuaFuns(classInfo,allincludes):
    ret = {}
    ret["heads"] = []
    ret["heads"].append(makeFunNameLine(classInfo["name"],"index",True)+";")
    for baseincludes in classInfo["include"]:
        allincludes[baseincludes] = 1
    index = makeFunNameLine(classInfo["name"],"index",True)+"{\n\n"
    index = index + "\tGETUSERDATA2TYPE("+classInfo["name"]+", obj, -2);\n"
    index = index + "\tif (lua_type(L,-1) != LUA_TSTRING){\n"
    index = index + "\t\t return 0;\n \t}\n\n"
    index = index + "\tstd::string key = lua_tostring(L, -1);\n"
    
    #先判断函数名称
    for funkey in classInfo["function"]:
        if classInfo["function"][funkey][0]["funtype"] == 2:
            continue
        index = index + "\tif ( key == \""+funkey+"\"){\n"
        index = index + "\t\tlua_pushcfunction(L, "+makeFunName(classInfo["name"],funkey,False)+");\n"
        index = index + "\t\treturn 1;\n\t}\n\n"

        if classInfo["name"] in c2LuaTypeEx:
            allincludes[c2LuaTypeEx[classInfo["name"]]["path"]] = 1
    #再判断静态成员变量
    useValues = {}
    for funkey in classInfo["index"]:
        valueInfo = classInfo["index"][funkey]

        if valueInfo["static"] == True:
            useValues[funkey] = 1
            index = index + "\tif ( key == \""+funkey+"\"){\n"
            index = index + "\t\t" + pushLuaTypeStr( valueInfo["type"] , classInfo["name"] + "::" + funkey ) + ";\n\t\treturn 1;\n\t}\n\n"

        if valueInfo["type"] in c2LuaTypeEx:
            allincludes[c2LuaTypeEx[valueInfo["type"]]["path"]] = 1
    
    index = index + "\tif ( obj == NULL )\n\t\treturn 0;\n"
    for funkey in classInfo["index"]:
        valueInfo = classInfo["index"][funkey]
        if valueInfo["static"] == False:
            useValues[funkey] = 1
            index = index + "\tif ( key == \""+funkey+"\"){\n"
            index = index + "\t\t" + pushLuaTypeStr( valueInfo["type"] , "obj->" + funkey ) + ";\n\t\treturn 1;\n\t}\n\n"
    index = index + "\treturn 0;\n"
    #最后判断成员变量
    index = index + "}"
    ret["index"] = index
    ret["heads"].append(makeFunNameLine(classInfo["name"],"newindex",True)+";")
    newindex = makeFunNameLine(classInfo["name"],"newindex",True)+"{\n\n"
    newindex = newindex + "\tif (lua_type(L,2) != LUA_TSTRING){\n"
    newindex = newindex + "\t\t return 0;\n \t}\n"
    newindex = newindex + "\tstd::string key = lua_tostring(L, 2);\n"
    #newindex = newindex + "\tif( lua_type(L,-2) != LUA_TUSERDATA)\n\t\t return 0;\n"
    newindex = newindex + "\tGETUSERDATA2TYPE("+classInfo["name"]+", obj, 1);\n"
                            #"\t"+classInfo["name"]+"* obj = ( " +classInfo["name"]+"*)lua_touserdata(L, -2);\n"
    for funkey in classInfo["newindex"]:
        valueInfo = classInfo["newindex"][funkey]
        autovalue = "autoval"+funkey
        autovalue = autovalue.replace(" ","")
        autovalue = autovalue.replace(":","")
        newindex = newindex + "\t" + LuaToCTypeStr(valueInfo["type"],"3",autovalue)
        newindex = newindex + "\n\tif ( key == \""+funkey+"\"){\n"
        # luaType =  getCTypeLua(CType)
        if valueInfo["static"] == True:
            newindex = newindex + "\t\t" + classInfo["name"] + "::" + funkey + " = "+ autovalue +";\n\t\treturn 0;\n\t}\n"
        else:
            newindex = newindex + "\t\tobj->" + funkey + " = "+ autovalue +";\n\t\treturn 0;\n\t}\n"

        if valueInfo["type"] in c2LuaTypeEx:
            allincludes[c2LuaTypeEx[valueInfo["type"]]["path"]] = 1

    newindex = newindex + "\treturn 0;\n"
    #最后判断成员变量
    newindex = newindex + "}"
    ret["newindex"] = newindex
    ret["calls"] = []
    for funkey in classInfo["function"]:
        valueInfo = classInfo["function"][funkey]
        if valueInfo[0]["funtype"] == 2:
            continue
        ret["heads"].append(makeFunNameLine(classInfo["name"],funkey,False)+";")
        funvalue = makeFunNameLine(classInfo["name"],funkey,False) + "{\n\n"
        funvalue = funvalue + "\tGETUSERDATA2TYPE("+classInfo["name"]+", obj, 1);\n"
        conditions = []
        for line in valueInfo:
            condition = "\tif ("
            if line["static"] == False:
                condition = condition + "obj != NULL && "
            paramvalues = "\t\t"
            temp = makeParamChecks(line,1,classInfo["name"])
            types = temp[0]
            condition = condition + temp[1]
            params = temp[2][0:-2]
            paramvalues = "\t\t"+temp[3]
            condition = condition + " true ){\n"
            callstr = ""
            if line["static"] == True:
                callstr = classInfo["name"] + "::"
            else:
                callstr = "obj->"
            callstr = callstr + funkey + "(" + params + ")"
            condition = condition + paramvalues
            if line["ret"] == "void":
                condition = condition + callstr + ";\n\t\treturn 0;\n\t}\n"
            else:
                condition = condition + pushLuaTypeStr(line["ret"],callstr)+";\n\t\treturn 1;\n\t}\n"
            conditions.append([condition, types, line["static"]])
        iSort_0(conditions,tempcmp)
        for item in conditions:
            funvalue = funvalue + item[0] + "\n"
        funvalue = funvalue+"\treturn 0;\n}"
        ret["calls"].append(funvalue)
    ret["heads"].append(makeFunNameLine(classInfo["name"],"newobj",True)+";")
    newObj = makeFunNameLine(classInfo["name"],"newobj",True)+"{\n\n"
    newObj = newObj + "\tchar *p = (char*)lua_newuserdata(L, sizeof( " + classInfo["name"] + "));\n\t"
    newObj = newObj + classInfo["name"] + "* ret = NULL;\n"
    if classInfo["instan"]:
        newObj = newObj + "ret error temp= " + classInfo["name"] + "::" + classInfo["newObj"] + "();\n"
    else:
        conditions = []
        for line in classInfo["function"][classInfo["name"]]:
            condition = "\tif ( ret == NULL && "
            paramvalues = "\t\t"
            temp = makeParamChecks(line,0,classInfo["name"])
            types = temp[0]
            condition = condition + temp[1]
            params = temp[2][0:-2]
            paramvalues = "\t\t"+temp[3]
            condition = condition + " true ){\n"

            callstr = "ret = new(p)" + classInfo["name"] + "(" + params + ");\n\t}\n"
            condition = condition + paramvalues
            callstr = condition + callstr
            conditions.append([callstr, types, False])
        iSort_0(conditions,tempcmp)
        for item in conditions:
            newObj = newObj + item[0] + "\n"
    newObj = newObj + "\tif(ret == NULL){\n\t\treturn 0;\n\t}\n"
    newObj = newObj + "\tsetObjectClass(ret, \"" + classInfo["name"] +"\");\n"
    newObj = newObj + "\tlua_getglobal(L, \"Reg_lua_"+classInfo["name"]+"__001\");\n\tlua_setmetatable(L, -2);\n\treturn 1;\n}"
    ret["new"] = newObj
    tabgc = makeFunNameLine(classInfo["name"],"gc",True)+"{\n\n"
    tabgc = tabgc + "\t"+classInfo["name"]+"* obj = (" +classInfo["name"] + "*)lua_touserdata(L,-1);\n\t"
    if ( classInfo["newObj"] == classInfo["name"] ) :
        tabgc = "if(obj != NULL) {\n\t\tdelete obj;\n\t\tobj = NULL;\n\t}"
    tabgc = tabgc + "\n\treturn 0;\n}"
    ret["heads"].append(makeFunNameLine(classInfo["name"],"gc",True)+";")
    ret["gc"] = tabgc
    ret["luaL_Reg"] = "const luaL_Reg Reg_lua_"+classInfo["name"]+"__001 []{\n\t{\"__index\","+makeFunName(classInfo["name"],"index",True)+"},\n\t"
    ret["luaL_Reg"] = ret["luaL_Reg"] + "{\"__newindex\","+makeFunName(classInfo["name"],"newindex",True)+"},\n\t"
    ret["luaL_Reg"] = ret["luaL_Reg"] + "{\"__gc\","+makeFunName(classInfo["name"],"gc",True)+"}\n};"

    ret["newClassParam"] = [makeFunName(classInfo["name"],"newobj",True),classInfo["name"],"Reg_lua_"+classInfo["name"]+"__001",classInfo["basestr"]]
    #print(ret)
    return ret
def checkExportNewObj(classInfo):
    allCheckNew = {}
    for funkey in classInfo["function"]:
        funvalue = classInfo["function"][funkey]
        for value in funvalue:
            classInfo["newObj"] = funkey
            if value["funtype"] == 2:
                allCheckNew[funkey] = 1
        if funkey in allCheckNew:
            for value in funvalue:
                if value["funtype"] == 1:
                    return False
        if len(allCheckNew) > 1:
            return False
    if len(allCheckNew) == 0:
        allCheckNew[classInfo["name"]] = 1
        classInfo["function"][classInfo["name"]] = [{"name":classInfo["name"],"param":0,"static":False,"funtype":2}]
    #单例获取，而不是直接构造
    classInfo["instan"] = not (classInfo["name"] in allCheckNew)
    if classInfo["instan"]:
        if len(classInfo["function"][classInfo["newObj"]]) > 1:
            return False
        instanValue = classInfo["function"][classInfo["newObj"]]
        if instanValue[0]["static"] == False:
            return False
    return True

def classInfos2ioStr(allfileInfo,allincludes):
    writefiles = {}
    runcpp = "#include \"../Manages/LuaScriptManage.h\"\n"
    runcpp = runcpp + "#include \"../tools/StringTools.h\"\n"
    runcpp = runcpp + "\n\n\n//以下包含的头文件以及对应实现文件是代码生成工具生成的，本文件也是工具生成\n\n\n"
    runheadfun = ""
    for filename in allfileInfo:
        cpp = ""
        if filename in allincludes:
            cpp = cpp + "#include \""+desfilekey2path[filename] + "\"\n"
            for includeItem in allincludes[filename]:
                cpp = cpp + "#include \""+desfilekey2path[includeItem] + "\"\n"
        else:
            cpp = cpp + "#include \""+desfilekey2path[filename] + "\"\n"
        cpp = cpp + "#include \"ser_autoLua_"+filename+"\"\n"
        cpp = cpp + "\nstatic std::string luaSave2CFunctionName = \"\";\n\n"
        head = "#include \"../Manages/LuaScriptManage.h\"\n"
        runcpp = runcpp + "#include \"ser_autoLua_" + filename + "\"\n"
        head = head + "void ser_autoLua_file_"+filename[0:-2]+"();"
        for value in allfileInfo[filename]:
            for headline in value["heads"]:
                cpp = cpp + headline+"\n"
        cpp = cpp + "\n"
        for value in allfileInfo[filename]:
            cpp = cpp + value["luaL_Reg"] + "\n\n"
        cpp = cpp + "\n"
        cpp = cpp + "void ser_autoLua_file_"+filename[0:-2]+"(){\n\tLuaScriptManage* LSM = GETINSTANCEMANAGE(LuaScriptManage);\n\t"
        cpp = cpp + "luaSave2CFunctionName = LSM->luaSave2CFunctionTableName();\n"
        cpp = cpp + "\tlua_State *L = LSM->getL();\n"
        for value in allfileInfo[filename]:
            cpp = cpp + "\tMAKECLASS2TABLE(" + value["newClassParam"][0] + "," + value["newClassParam"][1] + "," + value["newClassParam"][2]+");\n"
        for value in allfileInfo[filename]:
            print("----------------------")
            print(value["newClassParam"])
            if value["newClassParam"][1] in allFunRegisterTables:
                cpp = cpp + "\tREGISTERCLASS2CODE("+value["newClassParam"][1]+"," + value["newClassParam"][3] + ",true);\n"
            else:
                cpp = cpp + "\tREGISTERCLASS2CODE("+value["newClassParam"][1]+"," + value["newClassParam"][3] + ");\n"

        cpp = cpp + "};\n"
        for value in allfileInfo[filename]:
            #print(value)
            for callfuntext in value["calls"]:
                cpp = cpp + callfuntext+"\n"
            cpp = cpp + value["index"]+"\n"
            cpp = cpp + value["newindex"]+"\n"
            cpp = cpp + value["gc"]+"\n"
            cpp = cpp + value["new"]+"\n"

        writefiles["ser_autoLua_"+filename] = head
        writefiles["ser_autoLua_"+filename[0:-2]+".cpp"] = cpp
        runheadfun = runheadfun + "\tser_autoLua_file_"+filename[0:-2]+"();\n\t"

    runcpp = runcpp + "\nstd::string LuaScriptManage::luaSave2CFunctionTableName(){\n"
    runcpp = runcpp + "\treturn \"sys_lua2csave_funs_table\";\n}"

    runcpp = runcpp + "\nlua_CFunction LuaScriptManage::getLuaFun2cpp(LuaUserDataBase* ludb, std::string saveKey){\n"
    runcpp = runcpp + "\n\tif ( ludb == NULL || ludb->use00Lua00Obj00Hash_Id == 0)\n\t\treturn NULL;\n"
    runcpp = runcpp + "\n\tlua_getglobal(L,this->luaSave2CFunctionTableName().c_str());"
    runcpp = runcpp + "\n\tlua_getfield(L,-1,StringTools::number2Str(ludb->use00Lua00Obj00Hash_Id).c_str());"
    runcpp = runcpp + "\n\tif (lua_type(L, -1) == LUA_TTABLE) {"
    runcpp = runcpp + "\n\t\tlua_getfield(L, -2, saveKey.c_str());"
    runcpp = runcpp + "\n\t\tif (lua_type(L, -1) == LUA_TFUNCTION) {"
    runcpp = runcpp + "\n\t\t\tlua_CFunction fun = lua_tocfunction(L, -1);"
    runcpp = runcpp + "\n\t\t\tlua_pop(L, 1);"
    runcpp = runcpp + "\n\t\t\treturn fun;\n\t\t}"
    runcpp = runcpp + "\n\t\tlua_pop(L, 1);\n\t}"
    runcpp = runcpp + "\n\tlua_pop(L, 1);"
    runcpp = runcpp + "\n\n\treturn NULL;\n}"

    runcpp = runcpp + "\nbool LuaScriptManage::saveLuaFun2cpp(LuaUserDataBase* ludb, std::string saveKey, lua_CFunction luaFun){\n"
    runcpp = runcpp + "\n\tif ( ludb == NULL || ludb->use00Lua00Obj00Hash_Id == 0)\n\t\treturn false;\n"
    runcpp = runcpp + "\n\tlua_getglobal(L,this->luaSave2CFunctionTableName().c_str());"
    runcpp = runcpp + "\n\tlua_getfield(L,-1,StringTools::number2Str(ludb->use00Lua00Obj00Hash_Id).c_str());"
    runcpp = runcpp + "\n\tlua_pushcfunction(L,luaFun);"
    runcpp = runcpp + "\n\tlua_setfield(L,-2,saveKey.c_str());"
    runcpp = runcpp + "\n\n\treturn true;\n}"
# lua_CFunction LuaScriptManage::getLuaFun2cpp(LuaUserDataBase* ludb, std::string saveKey)
# {
#     if (ludb == NULL || ludb->use00Lua00Obj00Hash_Id == 0)
#         return NULL;

#     lua_getglobal(L, this->luaSave2CFunctionTableName().c_str());
#     lua_getfield(L, -1, StringTools::number2Str(ludb->use00Lua00Obj00Hash_Id).c_str());
#     if (lua_type(L, -1) == LUA_TTABLE) {
#         lua_getfield(L, -2, saveKey.c_str());
#         if (lua_type(L, -1) == LUA_TFUNCTION) {
#             lua_CFunction fun = lua_tocfunction(L, -1);
#             lua_pop(L, 1);
#             return fun;
#         }
#         lua_pop(L, 1);
#     }
#     lua_pop(L, 1);
#     return NULL;
# }
    runcpp = runcpp + "\nvoid LuaScriptManage::auto_register_all_Class(){\n\n"
    runcpp = runcpp + "\tauto LSM = GETINSTANCEMANAGE(LuaScriptManage);\n"
    runcpp = runcpp + "\tauto L = LSM->getL();\n"
    runcpp = runcpp + "\tlua_getglobal(L,\"_G\");\n"
    runcpp = runcpp + "\tlua_newtable(L);\n"
    runcpp = runcpp + "\tlua_pushstring(L,LSM->luaSave2CFunctionTableName().c_str());\n"
    runcpp = runcpp + "\tlua_rawseti(L, -2, 0);\n"
    runcpp = runcpp + runheadfun + "\n}"
    writefiles["ser_auto_reg_LuaScriptManage.cpp"] = runcpp
    return writefiles
def writeAllAutoFile(files):

    if os.path.exists("server_auto") == False:
        os.mkdir("server_auto")

    for name in files:
        f = open(os.path.join("server_auto",name),"w")
        if f:
            f.write(files[name])
            f.close()
def classTree2onlyLine(allClassInfo):
    onlyClassInfo = {}
    idx = 0

    for key in allClassInfo:
        value = allClassInfo[key]
        if not "baseClass" in value:
            value["baseClass"] = {}
    while len(allClassInfo) > 0 and idx < 1024000: 
        idx = idx + 1
        removekeys = []
        for key in allClassInfo:
            value = allClassInfo[key]
            
            if len(value["baseList"]) == 0:
                onlyClassInfo[key] = value
                removekeys.append(key)
        
        for key in allClassInfo:
            if key in removekeys:
                continue
            value = allClassInfo[key]
            removeFlg = True
            removeBases = []
            for baseitem in value["baseList"]:
                if not (baseitem in allClassInfo):
                    removeBases.append(baseitem)
                    continue
                if not baseitem in onlyClassInfo:
                    removeFlg = False
                    continue
                for baseIndexKey in onlyClassInfo[baseitem]["index"]:

                    if not (baseIndexKey) in value["index"]:
                        value["index"][baseIndexKey] = onlyClassInfo[baseitem]["index"][baseIndexKey]

                for baseIndexKey in onlyClassInfo[baseitem]["newindex"]:
                    if not (baseIndexKey) in value["newindex"]:
                        value["newindex"][baseIndexKey] = onlyClassInfo[baseitem]["newindex"][baseIndexKey]

                for baseIndexKey in onlyClassInfo[baseitem]["function"]:
                    if not (baseIndexKey) in value["function"] and onlyClassInfo[baseitem]["newObj"] != baseIndexKey:
                        value["function"][baseIndexKey] = onlyClassInfo[baseitem]["function"][baseIndexKey]
                
                if ( baseitem in onlyClassInfo ) and ("path" in onlyClassInfo[baseitem]):
                    value["include"].append(onlyClassInfo[baseitem]["path"])
                value["baseClass"][baseitem] = 1
                for k1 in onlyClassInfo[baseitem]["baseClass"]:
                    value["baseClass"][k1] = 1
                removeBases.append(baseitem)

            if removeFlg == False:
                for key1 in removeBases:
                    value["baseList"].remove(key1)
            else:
                onlyClassInfo[key] = value
                removekeys.append(key)
        for key in removekeys:
            allClassInfo.pop(key)
    if idx >= 1024000:
        return None
    #将base 转成str
    for key in onlyClassInfo:
        value = onlyClassInfo[key]
        basestr = "{"
        for basekey in value["baseClass"]:
            basestr = basestr + "\"" + basekey+"\", "
        if len(value["baseClass"]) > 0:
            basestr = basestr[0:-2] 
        basestr = basestr + "}"
        value["basestr"] = basestr
        value["baseClass"] = None
    return onlyClassInfo
def AnalysisInclude(LuaClasss):
    if( len(LuaClasss) > 0):
        allfileInfo = {}
        allClassInfo = {}
        for ClassLine in LuaClasss:
            idx1 = ClassLine.find("ExtensionClassAssistant(")
            idx2 = ClassLine.find(")",idx1+1)
            if idx1 < 0 or idx2 < 0:
                continue
            ExportLuaClassName = ClassLine[idx1+24:idx2]
            ExportLuaClassNameList = ExportLuaClassName.split(",")
            idx1 = ClassLine.find("\"",5)
            idx3 = ClassLine.find("\"",idx1+1,idx2)
            if idx1 < 0 or idx3 < 0:
                continue
            path = ClassLine[idx1+1:idx3]
            for className in ExportLuaClassNameList:
                luaClassName = className.replace(" ","")
                classInfo = readClassInfo(path,luaClassName)
                if checkExportNewObj(classInfo) == False:
                    print("--------------",classInfo)
                    return None
                if not luaClassName in c2LuaType:
                    c2LuaType[luaClassName] = "userdate"
                    c2LuaTypeEx[luaClassName] = {"name":luaClassName,"path":path}
                allClassInfo[luaClassName] = classInfo
                dir,file=os.path.split(path)
                classInfo["path"] = path
                classInfo["despath"] = file
                desfilekey2path[file] = path
                if not file in allfileInfo:
                    allfileInfo[file] = []
        #需要将树形结构变成一维结构
        onlyClassInfo = classTree2onlyLine(allClassInfo)
        allincludes = {}
        print(c2LuaType)
        for className in onlyClassInfo:
            if not classInfo["path"] in allincludes:
                allincludes[classInfo["path"]] = {classInfo["path"]:1}
            classInfo = onlyClassInfo[className]
            classStr = makeClassLuaFuns(classInfo,allincludes[classInfo["path"]])

            allfileInfo[classInfo["despath"]].append(classStr)
        ioDirs = classInfos2ioStr(allfileInfo,allincludes)
        
        return ioDirs

def deleteAllAutoFile(path):
    
    if os.path.isdir(path):
        for root,dirs,files in os.walk(path):
            for file in files:
                os.remove(os.path.join(root,file))
        os.rmdir(path)

def run():
    deleteAllAutoFile("server_auto")
    LuaClasss = readLuaScriptManageHead()
    if(len(LuaClasss) > 0):
        writefiles = AnalysisInclude(LuaClasss)
        if writefiles == None:
            return;
        print(len(writefiles))
        writeAllAutoFile(writefiles)

run()