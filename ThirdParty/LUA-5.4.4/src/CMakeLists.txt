cmake_minimum_required (VERSION 3.8.2)

add_library (LUALIB STATIC 
	lapi.c      lctype.c  lfunc.c   lmathlib.c  loslib.c   ltable.c   lundump.c
	lauxlib.c   ldblib.c  lgc.c     lmem.c      lparser.c  ltablib.c  lutf8lib.c
	lbaselib.c  ldebug.c  linit.c   loadlib.c   lstate.c   ltm.c      lvm.c
	lcode.c     ldo.c     liolib.c  lobject.c   lstring.c  lzio.c
	lcorolib.c  ldump.c   llex.c    lopcodes.c  lstrlib.c
)
target_include_directories (LUALIB PUBLIC ".")

add_executable (LUA lua.c)
target_link_libraries (LUA PUBLIC LUALIB)

add_executable (LUAC luac.c)
target_link_libraries (LUAC PUBLIC LUALIB)
