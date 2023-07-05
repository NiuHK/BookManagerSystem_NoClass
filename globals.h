#pragma once
#ifndef globals_H
#define globals_H
#include"Struct.h"
extern int numBooks;//借阅的数量
extern User currentUser;// 全局变量,当前用户
extern Book* books;//图书馆结构体数组头指针
extern string DATA_BASE_PATH;//图书馆地址
extern  string DATA_BASE_PATH_SAVE;//加密
extern string BOAED_PATH;//公告地址
extern string USER_PATH;//用户地址
extern string WRONG_COMMIT;//异常还书记录
extern  string USER_DATA_PATH;//用户数据路径
extern  int  borrowedBooks[100];//借阅的id
extern int bookNumber;//借阅数量	最大借100本书
//extern const int MAX_USERS;//max users
//library数量可为0
#endif 