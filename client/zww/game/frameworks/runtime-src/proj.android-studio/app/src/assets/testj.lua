_G.PackDyFlg = "25::1625228379"
return {

	CopyFile = function(className,params)
		--public static boolean CopyFile(java.lang.String, java.lang.String, boolean);
		if className == "HashTools"  and type( params ) == "table"  and type( params[1]) == "string"  and type( params[2]) == "string"  and type( params[3]) == "boolean"  then 
			return true,"(Ljava/lang/String;Ljava/lang/String;Z)Z"
		end

		return false
	end,

	getDeviceType = function(className,params)
		--public static java.lang.String getDeviceType();
		if className == "HashTools"  then 
			return true,"()Ljava/lang/String;"
		end

		return false
	end,

	getOperatorName = function(className,params)
		--public static java.lang.String getOperatorName();
		if className == "HashTools"  then 
			return true,"()Ljava/lang/String;"
		end

		return false
	end,

	pingHost = function(className,params)
		--public static boolean pingHost(java.lang.String);
		if className == "HashTools"  and type( params ) == "table"  and type( params[1]) == "string"  then 
			return true,"(Ljava/lang/String;)Z"
		end
		--public static boolean pingHost(java.lang.String, int);
		if className == "HashTools"  and type( params ) == "table"  and type( params[1]) == "string"  and type( params[2]) == "number"  then 
			return true,"(Ljava/lang/String;I)Z"
		end

		return false
	end,

	getosChannel = function(className,params)
		--public static java.lang.String getosChannel();
		if className == "HashTools"  then 
			return true,"()Ljava/lang/String;"
		end

		return false
	end,

	getosVersion = function(className,params)
		--public static java.lang.String getosVersion();
		if className == "HashTools"  then 
			return true,"()Ljava/lang/String;"
		end

		return false
	end,

	testvoid = function(className,params)
		--public static void testvoid(int, int);
		if className == "AppActivity"  and type( params ) == "table"  and type( params[1]) == "number"  and type( params[2]) == "number"  then 
			return true,"(II)V"
		end

		return false
	end,

	isUInt = function(className,params)
		--public static boolean isUInt(java.lang.String);
		if className == "HashTools"  and type( params ) == "table"  and type( params[1]) == "string"  then 
			return true,"(Ljava/lang/String;)Z"
		end

		return false
	end,

	getLocalIpAddress = function(className,params)
		--public static java.lang.String getLocalIpAddress();
		if className == "AppActivity"  then 
			return true,"()Ljava/lang/String;"
		end

		return false
	end,

	getResStr = function(className,params)
		--public static java.lang.String getResStr(int);
		if className == "HashTools"  and type( params ) == "table"  and type( params[1]) == "number"  then 
			return true,"(I)Ljava/lang/String;"
		end

		return false
	end,

	setUnLogHoot = function(className,params)
		--public static boolean setUnLogHoot();
		if className == "HashTools"  then 
			return true,"()Z"
		end

		return false
	end,

	luaSubmitEvent = function(className,params)
		--public static void luaSubmitEvent(java.lang.String, java.lang.String);
		if className == "cocosBase"  and type( params ) == "table"  and type( params[1]) == "string"  and type( params[2]) == "string"  then 
			return true,"(Ljava/lang/String;Ljava/lang/String;)V"
		end

		return false
	end,

	getDeviceCategory = function(className,params)
		--public static java.lang.String getDeviceCategory();
		if className == "HashTools"  then 
			return true,"()Ljava/lang/String;"
		end

		return false
	end,

	testString = function(className,params)
		--public static java.lang.String testString(int);
		if className == "AppActivity"  and type( params ) == "table"  and type( params[1]) == "number"  then 
			return true,"(I)Ljava/lang/String;"
		end
		--public static java.lang.String testString();
		if className == "AppActivity"  then 
			return true,"()Ljava/lang/String;"
		end
		--public static java.lang.String testString(java.lang.String);
		if className == "AppActivity"  and type( params ) == "table"  and type( params[1]) == "string"  then 
			return true,"(Ljava/lang/String;)Ljava/lang/String;"
		end

		return false
	end,

	loadVivo = function(className,params)
		--public static void loadVivo();
		if className == "appBridging"  then 
			return true,"()V"
		end

		return false
	end,

	DeCode = function(className,params)
		--public static java.lang.String DeCode(java.lang.String);
		if className == "HashTools"  and type( params ) == "table"  and type( params[1]) == "string"  then 
			return true,"(Ljava/lang/String;)Ljava/lang/String;"
		end

		return false
	end,

	getTimeArea = function(className,params)
		--public static java.lang.String getTimeArea();
		if className == "HashTools"  then 
			return true,"()Ljava/lang/String;"
		end

		return false
	end,

	getMetaKeyData = function(className,params)
		--public static java.lang.String getMetaKeyData(java.lang.String);
		if className == "HashTools"  and type( params ) == "table"  and type( params[1]) == "string"  then 
			return true,"(Ljava/lang/String;)Ljava/lang/String;"
		end

		return false
	end,

	EnCode = function(className,params)
		--public static java.lang.String EnCode(java.lang.String);
		if className == "HashTools"  and type( params ) == "table"  and type( params[1]) == "string"  then 
			return true,"(Ljava/lang/String;)Ljava/lang/String;"
		end

		return false
	end,

	toHex = function(className,params)
		--public static java.lang.String toHex(java.lang.String);
		if className == "AESEncryptor"  and type( params ) == "table"  and type( params[1]) == "string"  then 
			return true,"(Ljava/lang/String;)Ljava/lang/String;"
		end

		return false
	end,

	getLogsLists = function(className,params)
		--public static void getLogsLists(int);
		if className == "cocosBase"  and type( params ) == "table"  and type( params[1]) == "number"  then 
			return true,"(I)V"
		end

		return false
	end,

	loadQuick = function(className,params)
		--public static void loadQuick();
		if className == "appBridging"  then 
			return true,"()V"
		end

		return false
	end,

	testMuitlsParmas = function(className,params)
		--public static void testMuitlsParmas(int, float, boolean, java.lang.String);
		if className == "AppActivity"  and type( params ) == "table"  and type( params[1]) == "number"  and type( params[2]) == "number"  and type( params[3]) == "boolean"  and type( params[4]) == "string"  then 
			return true,"(IFZLjava/lang/String;)V"
		end

		return false
	end,

	getMBName = function(className,params)
		--public static java.lang.String getMBName();
		if className == "HashTools"  then 
			return true,"()Ljava/lang/String;"
		end

		return false
	end,

	getosType = function(className,params)
		--public static java.lang.String getosType();
		if className == "HashTools"  then 
			return true,"()Ljava/lang/String;"
		end

		return false
	end,

	pIsOppo = function(className,params)
		--public static int pIsOppo();
		if className == "HashTools"  then 
			return true,"()I"
		end

		return false
	end,

	setLogHoot = function(className,params)
		--public static boolean setLogHoot();
		if className == "HashTools"  then 
			return true,"()Z"
		end

		return false
	end,

	readFileAll = function(className,params)
		--public static java.lang.String readFileAll(java.lang.String);
		if className == "HashTools"  and type( params ) == "table"  and type( params[1]) == "string"  then 
			return true,"(Ljava/lang/String;)Ljava/lang/String;"
		end

		return false
	end,

	swtich = function(className,params)
		--public static void swtich(int);
		if className == "cocosBase"  and type( params ) == "table"  and type( params[1]) == "number"  then 
			return true,"(I)V"
		end

		return false
	end,

	clearNativeLog = function(className,params)
		--public static void clearNativeLog(int);
		if className == "cocosBase"  and type( params ) == "table"  and type( params[1]) == "number"  then 
			return true,"(I)V"
		end
		--public static void clearNativeLog();
		if className == "sdkPoolManage"  then 
			return true,"()V"
		end

		return false
	end,

	setOtherBack = function(className,params)
		--public static void setOtherBack(java.lang.String, int);
		if className == "cocosBase"  and type( params ) == "table"  and type( params[1]) == "string"  and type( params[2]) == "number"  then 
			return true,"(Ljava/lang/String;I)V"
		end

		return false
	end,

	fromHex = function(className,params)
		--public static java.lang.String fromHex(java.lang.String);
		if className == "AESEncryptor"  and type( params ) == "table"  and type( params[1]) == "string"  then 
			return true,"(Ljava/lang/String;)Ljava/lang/String;"
		end

		return false
	end,

	getResValueString = function(className,params)
		--public static java.lang.String getResValueString(java.lang.String, java.lang.String);
		if className == "HashTools"  and type( params ) == "table"  and type( params[1]) == "string"  and type( params[2]) == "string"  then 
			return true,"(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;"
		end

		return false
	end,

	isDobule = function(className,params)
		--public static boolean isDobule(java.lang.String);
		if className == "HashTools"  and type( params ) == "table"  and type( params[1]) == "string"  then 
			return true,"(Ljava/lang/String;)Z"
		end

		return false
	end,

	login = function(className,params)
		--public static void login(java.lang.String, int);
		if className == "cocosBase"  and type( params ) == "table"  and type( params[1]) == "string"  and type( params[2]) == "number"  then 
			return true,"(Ljava/lang/String;I)V"
		end

		return false
	end,

	saveLocalFile = function(className,params)
		--public static boolean saveLocalFile();
		if className == "HashTools"  then 
			return true,"()Z"
		end

		return false
	end,

	luaSubmitRoleInfos = function(className,params)
		--public static void luaSubmitRoleInfos(java.lang.String);
		if className == "cocosBase"  and type( params ) == "table"  and type( params[1]) == "string"  then 
			return true,"(Ljava/lang/String;)V"
		end

		return false
	end,
}