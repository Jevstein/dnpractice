/*
 *  jvt_bitmap.h 
 *  jvt_bitmap
 *
 *  Created by Jevstein on 2018/7/31 13:52.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  参考：
 * 		https://blog.csdn.net/qq_18108083/article/details/85063072
 * 		https://www.cnblogs.com/li-daphne/p/5549600.html
 * 
 *  位图排序思想：(bitset)
 *
 *    [应用场景]: 关注大量数据，内存不足
 */

#ifndef _JVT_BITMAP_H_
#define _JVT_BITMAP_H_
#include "../jvt_algorithm.h"

//位图排序
void jvt_bitmap_sort(jvt_datas_t *datas);


#endif //_JVT_BITMAP_H_
