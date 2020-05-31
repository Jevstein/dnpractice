
/*
 *  jvt_codec.c 
 *  jvt_codec
 *
 *  Created by Jevstein on 2020/05/31 9:23.
 *  Copyright @ 2020year Jevstein. All rights reserved.
 *
 *  内容：crc校验、
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "codec/jvt_crc.h"

void crc_debug()
{
    int data = 0xAB12;
    int crc = 0;
    int data_crc = 0;
    int crc_ret = 0;

    //1.发送端
    printf("--------- 1.对将发送的数据进行CRC编码 ---------\n");
    data_crc = jvt_crc_code_16(data, &crc);
    printf("原始数据:%x\n", data);
    printf("多项式信息:%x\n", GX);
    printf("生成CRC校验码:%x\n", crc);
    printf("带CRC的新数据:%x\n", data_crc);

    //2.接收端
    printf("\n--------- 2.对接收到到数据进行CRC校验 ---------\n");
    crc_ret = jvt_crc_decode_16(data_crc);
    printf("原始信息:%x\n", data_crc);
    printf("多项式信息:%x\n", GX);
    printf("最后模2除结果:%x\n", crc_ret);

    printf((data_crc ^ crc_ret) == 0 ? "\n 传输成功！\n" :
            "\n 传输错误！\n" );
}


int main () {

    // CRC校验
    printf("========= CRC校验 =========\n");
    crc_debug();

    //

    return 0;
}