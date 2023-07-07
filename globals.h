#pragma once
#pragma warning (disable: 4996)
#ifndef globals_H
#define globals_H
#include"Struct.h"
#include <time.h>
#include <iomanip>
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

#ifdef _WIN32
#include <conio.h>  // 用于Windows环境
#endif

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif



extern int numBooks;//借阅的数量
extern User currentUser;// 全局变量,当前用户
extern Book* books;//图书馆结构体数组头指针
extern string DATA_BASE_PATH;//图书馆地址
extern  string DATA_BASE_PATH_SAVE;//加密
extern string BOAED_PATH;//公告地址
extern string BOAED_PATH_SAVE;//公告地址加密
extern string USER_PATH;//用户地址
extern string USER_PATH_SAVE;//用户地址加密
extern string WRONG_COMMIT;//异常还书记录
extern string WRONG_COMMIT_SAVE;//异常还书记录加密
extern  string USER_DATA_PATH;//用户数据路径
extern  BorrowedBooks  borrowedBooks[100];//借阅的id
extern int bookNumber;//借阅数量	最大借100本书
//library数量可为0

bool AllisNum(string str);//判断字符串是否为数字

#endif 