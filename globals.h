#pragma once
#ifndef globals_H
#define globals_H
#include"Struct.h"
extern int numBooks;//���ĵ�����
extern User currentUser;// ȫ�ֱ���,��ǰ�û�
extern Book* books;//ͼ��ݽṹ������ͷָ��
extern string DATA_BASE_PATH;//ͼ��ݵ�ַ
extern  string DATA_BASE_PATH_SAVE;//����
extern string BOAED_PATH;//�����ַ
extern string USER_PATH;//�û���ַ
extern string WRONG_COMMIT;//�쳣�����¼
extern  string USER_DATA_PATH;//�û�����·��
extern  int  borrowedBooks[100];//���ĵ�id
extern int bookNumber;//��������	����100����
//extern const int MAX_USERS;//max users
//library������Ϊ0
#endif 