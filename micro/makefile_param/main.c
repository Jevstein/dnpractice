#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char info[] = STR_INFO;//来自Makefile的宏定义
const char date[] = STR_DATE;//来自Makefile的宏定义

int main()
{
	printf("%s\n", info);
	printf("%s\n", date);
	
#ifdef DEBUG//来自Makefile的宏定义
	printf("DEBUG: YES\n");
#else
	printf("DEBUG: NO\n");
#endif
	
	return 0;
}