#include "register_all_packges.h"
#include "extend_package_define_helper.h"
#include "register_GameDyFuncsVersion_packges.h"
#include "register_Label_packges.h"
int  register_all_packages(lua_State* L) {
	tolua_open(L);

	tolua_module(L, "CheckCpp", 0);
	tolua_beginmodule(L, "CheckCpp");
	register_GameDyFunVersion_packges(L);
	register_Label_packges(L);
	tolua_endmodule(L);
	return 0;
}