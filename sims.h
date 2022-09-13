/*************************************************
 File name: sims.h
 Author: Bunny 		Github: https://github.com/bunny-chz/
 Version: 1.0  
 Date: 2022-08-05
 Description: SIMS  Student Information Manage System    ||  学生信息管理系统
*************************************************/

#ifndef __SIMS_H__
#define __SIMS_H__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"//定义有ERRP，容错输出函数

#define MAX 2
#define NEXT	0
#define PREV	1

//定义函数指针类型
typedef void (llist_op_t)(const void *);
typedef int (llist_cmp_t)(const void *, const void *);

struct node_t{
	//数据域
	void *data;
	//两个指针域
	struct node_t *next;//指向下一个节点地址
	struct node_t *prev;//指向上一个节点地址
};
//账户信息结构体
struct account_info_t{
	char account[50];//账户名称
	char passwd[64];//账户密码
};

//学生信息结构体
struct student_info_t{
	char name[50];//学生姓名
	char sex[7];//学生性别
	int age;//学生年龄
	int id;//学生学号
	int score;//学生学分绩
	int class;//学生班级
};

//抽象数据类型
typedef struct llist_t{
	struct node_t head;//表示数据
	int size;//数据类型
	int count;//数据个数
}LLIST;

char* my_itoa(int num,char* str,int radix);
//声明函数
//初始化
extern LLIST *llist_create(int);
//尾插
extern int llist_append(void *data, LLIST *handle);

//删除
extern void llist_del_front(void *key, llist_cmp_t *cmp, LLIST *handle);
extern void llist_del_all(void *key, llist_cmp_t *cmp, LLIST *handle);

//查找
void *llist_find_front(void *key, llist_cmp_t *cmp, LLIST *handle);
LLIST *llist_find_all(void *key, llist_cmp_t *cmp, LLIST *handle);

//==========sort===========
extern void llist_sort_ascending(LLIST *handle, llist_cmp_t *cmp);
extern void llist_sort_descending(LLIST *handle, llist_cmp_t *cmp);

//文件
extern int llist_store(LLIST *handle, const char *path);
extern LLIST *llist_load(const char *path);
//遍历
void llist_travel(LLIST *handle, llist_op_t *op, int flag);

//销毁
void llist_destroy(LLIST **handle);
//选择账户界面
void select_account_menu();
//学生登录界面
void student_account_login();
//学生菜单界面
void student_operation_menu();
//老师登录注册界面
void teacher_account_login();
//老师菜单界面
void teacher_operation_menu();
//管理员登录界面
void admin_account_login();
//管理员菜单界面
void admin_operation_menu();
//字符串比较函数(账号)
int cmp_account(const void *d1, const void *d2);
//字符串比较函数(密码)
int cmp_passwd(const void *d1, const void *d2);
//字符串比较函数(学生姓名)
int cmp_name(const void *d1, const void *d2);
//整型比较函数(学生年龄)
int cmp_age(const void *d1, const void *d2);
//整型比较函数(学生学号)
int cmp_id(const void *d1, const void *d2);
//整型比较函数(学生成绩)
int cmp_score(const void *d1, const void *d2);
//整型比较函数(学生班级)
int cmp_class(const void *d1, const void *d2);
//在学生信息结构体内整型比较学生成绩，进行排序
int sort_score(const void *d1, const void *d2);
//账户信息遍历函数
void ls_account_info(const void *data);
//管理员端学生信息遍历函数
void ls_handle_student_info_admin(const void *data);
//学生端学生信息遍历函数
void ls_handle_student_info_student(const void *data);
//学生端学生成绩遍历函数
void ls_handle_student_score_student(const void *data);
//保存管理员录入的(初始)账号密码
void add_account_info_admin();
//管理员通过账户名查找账户信息
void find_account_info_admin_by_account();
//管理员通过账户名删除账户信息
void del_account_info_admin_by_account();
//管理员通过账户名称查找并修改账户密码
void modify_account_info_admin_by_account();
//保存管理员录入的学生信息
void add_student_info_admin();
//管理员通过学号删除的学生信息
void del_student_info_admin_by_id();
//管理员通过学号查找学生信息
void find_student_info_admin_by_id();
//管理员查找有关键词的全部学生信息
void find_student_info_admin_all();
//管理员通过学号查找并修改学生信息
void modify_student_info_admin_by_id();
//学生通过学号查找学生本人信息
void find_student_info_student_by_id(int id);
//学生通过学号查找学生本人成绩
void find_student_score_student_by_id(int id);
//学生修改账户密码
void modify_account_info_student_by_account(int id);
//老师通过姓名查找学生信息
void find_student_info_teacher_by_name();
//老师通过学号查找学生信息
void find_student_info_teacher_by_id(int class);
//老师查看同班的全部学生信息
void find_student_info_teacher_same_class(int class);
//老师通过姓名查找并修改学生信息
void modify_student_score_teacher_by_id(int class);
//对学生成绩排序打印
void sort_student_info_student_by_score();
//加载学生信息
void load_student_info_admin();
//加载账户信息
void load_account_info_admin();
//账户登录信息比较
int login_account_info_cmp(const char *path, int *tmp_id);
//选择账户界面
void select_account_menu();
//学生登录界面
void student_account_login();
//学生菜单界面
void student_operation_menu();
//老师登录注册界面
void teacher_account_login();
//老师菜单界面
void teacher_operation_menu();
//管理员登录界面
void admin_account_login();
//管理员菜单界面
void admin_operation_menu();
#endif
