/*
 *  strings.cpp 
 *
 *  Created by Jevstein on 2020/01/05 20:09.
 *  Copyright @ 2020year Jevstein. All rights reserved.
 *
 *  Mini CRT(模拟Glibc、MSVC CRT) - string
 * [简介]：
 *      常用的STL实现的string,不仅实现了字符串的一般赋值、取值和重载基本运算符，且拥有强大的模版定制功
 * 能、缓冲，和庞大的继承体系及一系列辅助类。此处简单实现string，不支持模版定制，即仅支持char字符串类型，
 * 不支持自定义分配器，没有basic_string模板类。
 * 
 * [提醒]
 *      string的实现常见于一些面试中，目的是考察面试者对c++类书写的基本功。因为string的诸多特性较为全
 * 面，包含构造、析构、运算符重载、const等。要求面试者细心，正确的同时要考虑条件、边界的判断。
 */
 #include "minicrt++.h"

 namespace std
 {
    string string()
    : length_(0)
    , buffer_(NULL)
    {

    }

    string string(const char* str)
    : length_(strlen(str) + 1)
    , buffer_(NULL)
    {
        buffer_ = new char[length_];
        strcpy(buffer_, str);
    }

    string string(const string& str)
    : length_(str.length_)
    , buffer_(NULL)
    {
        buffer_ = new char[length_];
        strcpy(buffer_, str.c_str());
    }
 }