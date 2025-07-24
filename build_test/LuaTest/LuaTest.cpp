#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern "C"
{
#include "lua.h"  
#include "lauxlib.h"  
#include "lualib.h"  
}

int main() {
    // 1. 初始化 Lua
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // 2. 读取二进制文件
    const char* filename = "E:/work/FL_Project/client/Assets/Scripts/ScriptLua/msgpb_combine.bytes";
    FILE* fp = nullptr;
    if (fopen_s(&fp, filename, "rb") != 0 || !fp) {
        printf("无法打开文件: %s\n", filename);
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = (char*)malloc(filesize);
    if (!buffer) {
        printf("内存分配失败\n");
        fclose(fp);
        return 1;
    }
    if (fread(buffer, 1, filesize, fp) != (size_t)filesize) {
        printf("文件读取失败\n");
        free(buffer);
        fclose(fp);
        return 1;
    }
    fclose(fp);

    // 3. 调用 lua_requireStream
    int result = lua_requireStream(L, buffer, (int)filesize);
    free(buffer);

    if (result != 2) {
        printf("lua_requireStream 执行失败，返回值: %d\n", result);
        if (lua_isstring(L, -1)) {
            printf("Lua错误: %s\n", lua_tostring(L, -1));
        }
        lua_close(L);
        return 1;
    }

    // 4. 打印 package.loaded 表中内容
    printf("lua_requireStream 执行成功，package.loaded:\n");
    lua_pushvalue(L, -1); // package.loaded
    lua_pushnil(L);
    while (lua_next(L, -2)) {
        printf("  %s\n", lua_tostring(L, -2));
        lua_pop(L, 1);
    }
    lua_pop(L, 1);

    lua_close(L);
    return 0;
}