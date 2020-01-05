/*
 *  MyLuaMath.h 
 *  MyLuaMath
 *
 *  Created by Jevstein on 2018/10/17 17:36.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 */

#ifdef __cplusplus
#	define EXTERN_C extern "C"
#else//!__cplusplus
#	define EXTERN_C
#endif//__cplusplus

#ifdef WIN32
#	ifdef MY_EXPORTS
#		define MY_REPORT_API EXTERN_C _declspec(dllexport)
#	else
#		define MY_REPORT_API EXTERN_C _declspec(dllimport)
#	endif
#	define CALLMODE __cdecl //__stdcall
#else//!WIN32
#	define MY_REPORT_API EXTERN_C
#	define CALLMODE
#endif//WIN32

/************************************************************************/
/* º¯ÊýÉùÃ÷                                                             */
/************************************************************************/
int add_func(lua_State* L);
int sub_func(lua_State* L);
int mul_func(lua_State* L);
int div_func(lua_State* L);

