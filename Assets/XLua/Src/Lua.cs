using System.Runtime.InteropServices;

namespace XLua.LuaDLL
{
    public partial class Lua
    {
        [DllImport(LUADLL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int luaopen_rapidjson(System.IntPtr L);

        [MonoPInvokeCallback(typeof(LuaDLL.lua_CSFunction))]
        public static int LoadRapidJson(System.IntPtr L)
        {
            return luaopen_rapidjson(L);
        }
        
        [DllImport(LUADLL, CallingConvention = CallingConvention.Cdecl)]
        static extern int luaopen_pb(System.IntPtr L);

        [MonoPInvokeCallback(typeof(LuaDLL.lua_CSFunction))]
        public static int LoadPb(System.IntPtr L)
        {
            return luaopen_pb(L);
        }
        
        [DllImport(LUADLL, CallingConvention = CallingConvention.Cdecl)]
        static extern int luaopen_lsqlite3(System.IntPtr L);

        [MonoPInvokeCallback(typeof(LuaDLL.lua_CSFunction))]
        public static int LoadLSQLite(System.IntPtr L)
        {
            return luaopen_lsqlite3(L);
        }

        [DllImport(LUADLL, CallingConvention = CallingConvention.Cdecl)]
        static extern int xluaL_loadbufferStream(System.IntPtr L, byte[] streamBuffer, int size);

        [MonoPInvokeCallback(typeof(LuaDLL.lua_CSFunction))]
        public static int RequireStream(System.IntPtr L, byte[] streamBuffer, int size)
        {
            return xluaL_loadbufferStream(L, streamBuffer, size);
        }
    }
}