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
#include <conio.h>  // ����Windows����
#endif

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif



extern int numBooks;//���ĵ�����
extern User currentUser;// ȫ�ֱ���,��ǰ�û�
extern Book* books;//ͼ��ݽṹ������ͷָ��
extern string DATA_BASE_PATH;//ͼ��ݵ�ַ
extern  string DATA_BASE_PATH_SAVE;//����
extern string BOAED_PATH;//�����ַ
extern string BOAED_PATH_SAVE;//�����ַ����
extern string USER_PATH;//�û���ַ
extern string USER_PATH_SAVE;//�û���ַ����
extern string WRONG_COMMIT;//�쳣�����¼
extern string WRONG_COMMIT_SAVE;//�쳣�����¼����
extern  string USER_DATA_PATH;//�û�����·��
extern  BorrowedBooks  borrowedBooks[100];//���ĵ�id
extern int bookNumber;//��������	����100����
//library������Ϊ0

bool AllisNum(string str);//�ж��ַ����Ƿ�Ϊ����

#endif 