#include "sims.h"

/**
* @file fun.c
* @brief 学生信息管理系统函数实现
* @version 1.0
* @author Bunny		Github: https://github.com/bunny-chz/
* @date 2022-08-05
*/


/**学号全局变量*/
int tmp_id;
/**老师班级全局变量*/
int tmp_class = 19001;

//字符串比较函数(账号)
int cmp_account(const void *d1, const void *d2)
{
	return strcmp((char *)d1, ((struct account_info_t *)d2)->account);
}
//字符串比较函数(密码)
int cmp_passwd(const void *d1, const void *d2)
{
	return strcmp((char *)d1, ((struct account_info_t *)d2)->passwd);
}
//字符串比较函数(学生姓名)
int cmp_name(const void *d1, const void *d2)
{
	return strcmp((char *)d1, ((struct student_info_t *)d2)->name);
}
//整型比较函数(学生年龄)
int cmp_age(const void *d1, const void *d2)
{
	return *(int *)d1 - ((struct student_info_t *)d2)->age;
}
//整型比较函数(学生学号)
int cmp_id(const void *d1, const void *d2)
{
	return *(int *)d1 - ((struct student_info_t *)d2)->id;
}
//整型比较函数(学生成绩)
int cmp_score(const void *d1, const void *d2)
{
	return *(int *)d1 - ((struct student_info_t *)d2)->score;
}
//整型比较函数(学生班级)
int cmp_class(const void *d1, const void *d2)
{
	return *(int *)d1 - ((struct student_info_t *)d2)->class;
}
//在学生信息结构体内整型比较学生成绩，进行排序
int sort_score(const void *d1, const void *d2)
{
	return ((struct student_info_t *)d1)->score - ((struct student_info_t *)d2)->score;
}

//账户信息遍历函数
void ls_account_info(const void *data)
{
	struct account_info_t *account_info = (struct account_info_t *)data;
	printf("账号 : %s | 密码 : %s \n", account_info->account, account_info->passwd);
}

//管理员端学生信息遍历函数
void ls_handle_student_info_admin(const void *data)
{
	struct student_info_t *student_info_admin = (struct student_info_t *)data;
	printf("name : %s | sex : %s | age : %d | id : %d | score : %d | class: %d \n", student_info_admin->name, student_info_admin->sex, student_info_admin->age, student_info_admin->id, student_info_admin->score, student_info_admin->class);
}
//学生端学生信息遍历函数
void ls_handle_student_info_student(const void *data)
{
	struct student_info_t *student_info_admin = (struct student_info_t *)data;
	printf("name : %s | sex : %s | age : %d | id : %d | class: %d \n", student_info_admin->name, student_info_admin->sex, student_info_admin->age, student_info_admin->id, student_info_admin->class);
}
//学生端学生成绩遍历函数
void ls_handle_student_score_student(const void *data)
{
	struct student_info_t *student_info_admin = (struct student_info_t *)data;
	printf("name : %s | id : %d | score : %d  ", student_info_admin->name, student_info_admin->id, student_info_admin->score);
}

void llist_travel_score(LLIST *handle, llist_op_t *op, int flag)
{
	int i = 1;
	struct node_t *tail = NULL;

	if (flag == NEXT)
	{
		for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
		{
			op(tail->data);
			printf("|| 排名: %d \n",i);
			i = i + 1;
		}
	}
}

//保存管理员录入的(初始)账号密码
void add_account_info_admin(){
	system("clear");//清屏
	printf("*****************管理员端*******************\n");
	printf("               添加账户信息                 \n");
	printf("                                           \n");
	printf("               1.返回上一级                 \n");
	printf("                 			                \n");
	struct account_info_t account_info;
	LLIST *handle_account_info = NULL;
	//初始化
	handle_account_info = llist_create(sizeof(struct account_info_t));
	ERRP(NULL == handle_account_info, llist_create, goto ERR1);
	handle_account_info = llist_load("./student_account_info.db");
	
	char enter_clear[2];
	//清除回车引发的错误
	fgets(enter_clear, sizeof(enter_clear), stdin);

	//接收输入的(初始)账号
	printf("请输入账号 : ");
	fgets(account_info.account, sizeof(account_info.account), stdin);
	if (account_info.account[strlen(account_info.account) - 1] == '\n')
		account_info.account[strlen(account_info.account) - 1] = '\0';

	//接收注册输入的(初始)密码
	printf("请输入密码 : ");
	fgets(account_info.passwd, sizeof(account_info.passwd), stdin);
	if (account_info.passwd[strlen(account_info.passwd) - 1] == '\n')
		account_info.passwd[strlen(account_info.passwd) - 1] = '\0';
		
	//尾插(初始)账户数据
	ERRP(llist_append(&account_info, handle_account_info) == -1, add_account_info_append, goto ERR2);
	
	llist_store(handle_account_info,"./student_account_info.db");//保存
	llist_travel(handle_account_info, ls_account_info, NEXT);//遍历

	llist_destroy(&handle_account_info);

	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            admin_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;

ERR2:
	llist_destroy(&handle_account_info);
	return ;
ERR1:
	return ;
}

//管理员通过账户名查找账户信息
void find_account_info_admin_by_account(){
	system("clear");//清屏
	printf("*****************管理员端*******************\n");
	printf("               查找账户信息                 \n");
	printf("                                           \n");
	printf("               1.返回上一级                 \n");
	printf("                 			                \n");
	char account[50];
	char enter_clear[2];
	//清除回车引发的错误
	fgets(enter_clear, sizeof(enter_clear), stdin);
	struct account_info_t *find_account_info_result = NULL;
	
	LLIST *handle_account_info_admin = NULL;
	//初始化
	handle_account_info_admin = llist_create(sizeof(struct account_info_t));
	ERRP(NULL == handle_account_info_admin, llist_create, goto ERR1);
	
	handle_account_info_admin = llist_load("./student_account_info.db");
	printf("请输入账号 : ");
	fgets(account, sizeof(account), stdin);
	if (account[strlen(account) - 1] == '\n')
		account[strlen(account) - 1] = '\0';

	find_account_info_result = llist_find_front(&account,cmp_account,handle_account_info_admin);
	if (find_account_info_result == NULL)
	{
	    printf("没有找到！\n");
	}
	else
	{
		ls_account_info(find_account_info_result);
	}
	llist_destroy(&handle_account_info_admin);
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            admin_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
}

//管理员通过账户名删除账户信息
void del_account_info_admin_by_account(){
	system("clear");//清屏
	printf("*****************管理员端*******************\n");
	printf("               删除账户信息                 \n");
	printf("                                           \n");
	printf("               1.返回上一级                 \n");
	printf("                 			                \n");
	char account[50];

	char enter_clear[2];
	//清除回车引发的错误
	fgets(enter_clear, sizeof(enter_clear), stdin);

	struct account_info_t *find_account_info_result = NULL;

	LLIST *handle_account_info_admin = NULL;
	//初始化
	handle_account_info_admin = llist_create(sizeof(struct account_info_t));
	ERRP(NULL == handle_account_info_admin, llist_create, goto ERR1);
	
	handle_account_info_admin = llist_load("./student_account_info.db");
	printf("请输入账号 : ");
	fgets(account, sizeof(account), stdin);
	if (account[strlen(account) - 1] == '\n')
		account[strlen(account) - 1] = '\0';

	find_account_info_result = llist_find_front(&account,cmp_account,handle_account_info_admin);
	if (find_account_info_result == NULL)
	{
	    printf("没有这个账户，无法删除！\n");
	}
	else
	{
		llist_del_front(&account,cmp_account,handle_account_info_admin);
		llist_store(handle_account_info_admin,"./student_account_info.db");//保存
		printf("删除操作成功！\n");
	}
	llist_destroy(&handle_account_info_admin);
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            admin_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
}

//管理员通过账户名称查找并修改账户密码
void modify_account_info_admin_by_account(){
	system("clear");//清屏
	printf("*****************管理员端*******************\n");
	printf("             查找修改账户信息               \n");
	printf("                                           \n");
	printf("               1.返回上一级                 \n");
	printf("                 			                \n");
	char account[50];
	char passwd[50];
	char enter_clear[2];
	//清除回车引发的错误
	fgets(enter_clear, sizeof(enter_clear), stdin);
	struct account_info_t *find_account_info_result = NULL;
	LLIST *handle_account_info_admin = NULL;
	//初始化
	handle_account_info_admin = llist_create(sizeof(struct account_info_t));
	
	handle_account_info_admin = llist_load("./student_account_info.db");
	printf("请输入账号 : ");
	fgets(account, sizeof(account), stdin);
	if (account[strlen(account) - 1] == '\n')
		account[strlen(account) - 1] = '\0';

	find_account_info_result = llist_find_front(&account,cmp_account,handle_account_info_admin);
	ls_account_info(find_account_info_result);
	if (find_account_info_result == NULL)
	{
	    printf("没有找到此账户！\n");
	}
	else
	{
	    printf("请输入密码 : ");
		fgets(passwd, sizeof(passwd), stdin);
		if (passwd[strlen(passwd) - 1] == '\n')
			passwd[strlen(passwd) - 1] = '\0';
		memcpy(find_account_info_result->passwd,&passwd,sizeof(passwd));

		ls_account_info(find_account_info_result);
		//尾插(初始)账户数据
		ERRP(llist_append(find_account_info_result, handle_account_info_admin) == -1, add_account_info_append, goto ERR2);
		llist_del_front(&account,cmp_account,handle_account_info_admin);
		llist_store(handle_account_info_admin,"./student_account_info.db");//保存
		printf("修改成功！\n");

	}
	
	llist_destroy(&handle_account_info_admin);
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            admin_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
ERR2:
	llist_destroy(&handle_account_info_admin);
	return ;
}

//保存管理员录入的学生信息
void add_student_info_admin(){
	system("clear");//清屏
	printf("*****************管理员端*******************\n");
	printf("               添加学生信息                 \n");
	printf("                                           \n");
	printf("               1.返回上一级					\n");
	printf("                 			               \n");
	int i;
	int id;//学生学号
	int age;//学生年龄
	int score;//学生学分绩
	int class;//学生班级
	char enter_clear[2];
	//清除回车引发的错误
	fgets(enter_clear, sizeof(enter_clear), stdin);
	
	struct student_info_t student_info_admin;
	LLIST *handle_student_info_admin = NULL;
	//初始化
	handle_student_info_admin = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_admin, llist_create, goto ERR1);
	
	handle_student_info_admin = llist_load("./student_info_admin.db");
	
	//接收输入的学生姓名
	printf("请输入姓名: ");
	fgets(student_info_admin.name, sizeof(student_info_admin.name), stdin);
	if (student_info_admin.name[strlen(student_info_admin.name) - 1] == '\n')
		student_info_admin.name[strlen(student_info_admin.name) - 1] = '\0';

	//接收输入的学生性别
	printf("请输入性别: ");
	fgets(student_info_admin.sex, sizeof(student_info_admin.sex), stdin);
	if (student_info_admin.sex[strlen(student_info_admin.sex) - 1] == '\n')
		student_info_admin.sex[strlen(student_info_admin.sex) - 1] = '\0';

	//接收输入的年龄
	printf("请输入年龄: ");
	scanf("%d",&age);
	student_info_admin.age = age;

	//接收输入的学号
	printf("请输入学号: ");
	scanf("%d",&id);
	student_info_admin.id = id;
	while(1){
		//接收输入的学生学分绩
		printf("请输入学分绩: ");
		scanf("%d",&score);
		if(score >= 0 && score <=100){
		student_info_admin.score = score;
		break;
		}
		else{
			printf("输入的分数有误！请重新输入！\n");
		}
	}
	//接收输入的学生班级
	printf("请输入班级: ");
	scanf("%d",&class);
	student_info_admin.class = class;

	//尾插学生信息数据
	ERRP(llist_append(&student_info_admin, handle_student_info_admin) == -1, add_student_info_admin_append, goto ERR2);
	
	llist_store(handle_student_info_admin,"./student_info_admin.db");//保存
	llist_travel(handle_student_info_admin, ls_handle_student_info_admin, NEXT);//遍历

	llist_destroy(&handle_student_info_admin);
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字: ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            admin_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;

ERR2:
	llist_destroy(&handle_student_info_admin);
	return ;
ERR1:
	return ;
}

//管理员通过学号删除的学生信息
void del_student_info_admin_by_id(){
	system("clear");//清屏
	printf("*****************管理员端*******************\n");
	printf("               删除学生信息                 \n");
	printf("                                           \n");
	printf("               1.返回上一级					\n");
	printf("                 			                \n");
	int id;
	struct student_info_t *find_student_info_result = NULL;
	LLIST *handle_student_info_admin = NULL;
	//初始化
	handle_student_info_admin = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_admin, llist_create, goto ERR1);
	
	handle_student_info_admin = llist_load("./student_info_admin.db");
	printf("请输入学号: ");
	scanf("%d",&id);
	find_student_info_result = llist_find_front(&id,cmp_id,handle_student_info_admin);
	if (find_student_info_result == NULL)
	{
	    printf("没有找到这个学号！\n");
	}
	else
	{
	    llist_del_front(&id,cmp_id,handle_student_info_admin);
		printf("删除操作成功！\n");
		llist_store(handle_student_info_admin,"./student_info_admin.db");
	}
	llist_destroy(&handle_student_info_admin);
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            admin_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
}

//管理员通过学号查找学生信息
void find_student_info_admin_by_id(){
	system("clear");//清屏
	printf("*****************管理员端*******************\n");
	printf("               查找学生信息                 \n");
	printf("                                           \n");
	printf("               1.返回上一级                 \n");
	printf("                 			                \n");
	int id;
	struct student_info_t *find_student_info_result = NULL;
	
	LLIST *handle_student_info_admin = NULL;
	//初始化
	handle_student_info_admin = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_admin, llist_create, goto ERR1);
	
	handle_student_info_admin = llist_load("./student_info_admin.db");
	printf("请输入学号: ");
	scanf("%d",&id);

	find_student_info_result = llist_find_front(&id,cmp_id,handle_student_info_admin);
	if (find_student_info_result == NULL)
	{
	    printf("没有找到！\n");
	}
	else
	{
	    ls_handle_student_info_admin(find_student_info_result);
	}
	llist_destroy(&handle_student_info_admin);
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            admin_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
}

//管理员查找有关键词的全部学生信息
void find_student_info_admin_all(){
	int id;
	LLIST *handle_student_info_admin = NULL;
	//初始化
	handle_student_info_admin = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_admin, llist_create, goto ERR1);
	
	handle_student_info_admin = llist_load("./student_info_admin.db");

	scanf("%d",&id);
	
	llist_travel(llist_find_all(&id,cmp_id,handle_student_info_admin),ls_handle_student_info_admin,NEXT);
	llist_destroy(&handle_student_info_admin);
	return ;
ERR1:
	return ;
}

//管理员通过学号查找并修改学生信息
void modify_student_info_admin_by_id(){
	system("clear");//清屏
	char name[50];//学生姓名
	int age;//学生年龄
	int id;//学生学号
	int score;//学生学分绩
	int class;//学生班级
	printf("****************管理员端*******************\n");
	printf("              修改学生信息                 \n");
	printf("                                          \n");
	printf("              1.返回上一级                 \n");
	printf("                 			              \n");
	struct student_info_t *find_student_info_result = NULL;
	
	LLIST *handle_student_info_admin = NULL;
	//初始化
	handle_student_info_admin = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_admin, llist_create, goto ERR1);
	
	handle_student_info_admin = llist_load("./student_info_admin.db");
	printf("请输入要修改学生的学号: ");
	scanf("%d",&id);

	find_student_info_result = llist_find_front(&id,cmp_id,handle_student_info_admin);
	if (find_student_info_result == NULL){
	    printf("没有找到！\n");
		sleep(2);
		system("clear");//清屏
	}
	else{
		system("clear");//清屏
		printf("**************修改学生信息*****************\n");
		printf("                                          \n");
		printf("           请选择以下修改功能              \n");
		printf("   1.修改姓名               4.修改成绩     \n");
		printf("   2.修改年龄               5.修改班级     \n");
		printf("   3.修改学号                              \n");
		printf("                                          \n");
		printf("请输入操作的选项数字:  ");
		int operation_option_modify_student_info;
		scanf("%d",&operation_option_modify_student_info);
		char enter_clear[2];
		//清除回车引发的错误
		fgets(enter_clear, sizeof(enter_clear), stdin);

		if(operation_option_modify_student_info == 1){
			//接收输入的学生姓名
			printf("修改姓名，请输入姓名: ");
			fgets(name, sizeof(name), stdin);
			if (name[strlen(name) - 1] == '\n')
				name[strlen(name) - 1] = '\0';
			memcpy(find_student_info_result->name,&name,sizeof(name));
	    	ls_handle_student_info_admin(find_student_info_result);
			ERRP(llist_append(find_student_info_result, handle_student_info_admin) == -1, add_score_info_append, goto ERR2);
			llist_del_front(&name,cmp_name,handle_student_info_admin);
			llist_store(handle_student_info_admin,"./student_info_admin.db");//保存
			printf("修改成功！\n");
		}
		if(operation_option_modify_student_info == 2){
			printf("修改年龄，请输入年龄: ");
			scanf("%d",&age);
			find_student_info_result->age = age;
	    	ls_handle_student_info_admin(find_student_info_result);
			ERRP(llist_append(find_student_info_result, handle_student_info_admin) == -1, add_score_info_append, goto ERR2);
			llist_del_front(&id,cmp_id,handle_student_info_admin);
			llist_store(handle_student_info_admin,"./student_info_admin.db");//保存
			printf("修改成功！\n");
		}
		if(operation_option_modify_student_info == 3){
			printf("修改学号，请输入学号: ");
			scanf("%d",&id);
			find_student_info_result->id = id;
	    	ls_handle_student_info_admin(find_student_info_result);
			ERRP(llist_append(find_student_info_result, handle_student_info_admin) == -1, add_score_info_append, goto ERR2);
			llist_del_front(&id,cmp_id,handle_student_info_admin);
			llist_store(handle_student_info_admin,"./student_info_admin.db");//保存
			printf("修改成功！\n");
		}
		if(operation_option_modify_student_info == 4){
			while(1){
				
				printf("修改成绩，请输入成绩: ");
				scanf("%d",&score);
				if(score >= 0 && score <=100){
			
				find_student_info_result->score = score;
	    		ls_handle_student_info_admin(find_student_info_result);
				ERRP(llist_append(find_student_info_result, handle_student_info_admin) == -1, add_score_info_append, goto ERR2);
				llist_del_front(&id,cmp_id,handle_student_info_admin);
				llist_store(handle_student_info_admin,"./student_info_admin.db");//保存
				printf("修改成功！\n");
				break;
				}
				else{
			 		printf("输入的分数有误！请重新输入！\n");
				}
			}
		}
		if(operation_option_modify_student_info == 5){
			printf("修改班级，请输入班级: ");
			scanf("%d",&class);
			find_student_info_result->class = class;
	    	ls_handle_student_info_admin(find_student_info_result);
			ERRP(llist_append(find_student_info_result, handle_student_info_admin) == -1, add_score_info_append, goto ERR2);
			llist_del_front(&id,cmp_id,handle_student_info_admin);
			llist_store(handle_student_info_admin,"./student_info_admin.db");//保存
			printf("修改成功！\n");
		}
		sleep(1);
		system("clear");//清屏
	}
	printf("****************管理员端*******************\n");
	printf("              修改学生信息                 \n");
	printf("                                          \n");
	printf("               1.返回上一级                 \n");
	printf("                 			               \n");
	llist_destroy(&handle_student_info_admin);
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            admin_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
ERR2:
	llist_destroy(&handle_student_info_admin);
	return ;
}

//学生通过学号查找学生本人信息
void find_student_info_student_by_id(int id){
	system("clear");//清屏
	printf("********************学生端********************\n");
	printf("                加载学生本人信息                \n");
	printf("                		                       \n");
	printf("                   1.返回上级                  \n");
	printf("                 			                   \n");
	struct student_info_t *find_student_info_result = NULL;
	
	LLIST *handle_student_info_student = NULL;
	//初始化
	handle_student_info_student = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_student, llist_create, goto ERR1);
	
	handle_student_info_student = llist_load("./student_info_admin.db");

	find_student_info_result = llist_find_front(&id,cmp_id,handle_student_info_student);
	if (find_student_info_result == NULL)
	{
	    printf("没有找到！\n");
	}
	else
	{
	    ls_handle_student_info_student(find_student_info_result);
	}

	llist_destroy(&handle_student_info_student);
	
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            student_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
}

//学生通过学号查找学生本人成绩
void find_student_score_student_by_id(int id){
	system("clear");//清屏
	printf("********************学生端********************\n");
	printf("                加载学生本人成绩               \n");
	printf("                		                       \n");
	printf("                   1.返回上级                  \n");
	printf("                 			                   \n");
	struct student_info_t *find_student_info_result = NULL;
	
	LLIST *handle_student_info_student = NULL;
	//初始化
	handle_student_info_student = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_student, llist_create, goto ERR1);
	
	handle_student_info_student = llist_load("./student_info_admin.db");

	find_student_info_result = llist_find_front(&id,cmp_id,handle_student_info_student);
	if (find_student_info_result == NULL)
	{
	    printf("没有找到！\n");
	}
	else
	{
	    ls_handle_student_score_student(find_student_info_result);
		printf("\n");
	}

	llist_destroy(&handle_student_info_student);
	
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            student_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
}

//学生修改账户密码
void modify_account_info_student_by_account(int id){
	system("clear");//清屏
	printf("*******************学生端********************\n");
	printf("               查找修改账户信息                \n");
	printf("                                             \n");
	printf("                 1.返回上一级                 \n");
	printf("                 			                 \n");
	char account[50];
	char passwd[50];
	char passwd_new_a[50];
	char passwd_new_b[50];
	my_itoa(id,account,10);
	char enter_clear[2];
	//清除回车引发的错误
	fgets(enter_clear, sizeof(enter_clear), stdin);
	struct account_info_t *find_account_info_result = NULL;
	LLIST *handle_account_info_admin = NULL;
	//初始化
	handle_account_info_admin = llist_create(sizeof(struct account_info_t));
	
	handle_account_info_admin = llist_load("./student_account_info.db");

	find_account_info_result = llist_find_front(&account,cmp_account,handle_account_info_admin);
	if (find_account_info_result == NULL)
	{
	    printf("没有找到你的账户信息！\n");
	}
	else
	{
		while(1){
		printf("请输入原密码 : ");
		fgets(passwd, sizeof(passwd), stdin);
		if (passwd[strlen(passwd) - 1] == '\n')
			passwd[strlen(passwd) - 1] = '\0';
		int account_cmp_result = 1, passwd_cmp_result = 1;//账号和密码的比较结果标记位，默认1为不同，0为相同
		struct node_t *tail = NULL;

		for (tail = handle_account_info_admin->head.next; tail != &handle_account_info_admin->head; tail = tail->next)
		{
			if (cmp_account(account, tail->data) == 0)
			{
			account_cmp_result = 0;
			break;
			}	
		}
	
		if (cmp_passwd(passwd, tail->data) == 0){
			passwd_cmp_result = 0;
		}
	
		if(account_cmp_result == 0 && passwd_cmp_result == 0){
			while(1){
				printf("请输入新密码 : ");
				fgets(passwd_new_a, sizeof(passwd_new_a), stdin);
				if (passwd_new_a[strlen(passwd_new_a) - 1] == '\n')
					passwd_new_a[strlen(passwd_new_a) - 1] = '\0';
				printf("再次输入确认新密码 : ");
				fgets(passwd_new_b, sizeof(passwd_new_b), stdin);
				if (passwd_new_b[strlen(passwd_new_b) - 1] == '\n')
					passwd_new_b[strlen(passwd_new_b) - 1] = '\0';
				if(strcmp(passwd_new_a,passwd_new_b) == 0)
				{
					if(strcmp(passwd,passwd_new_a) == 0){
						printf("新密码不能与旧密码相同！请重新输入！\n");
					}
					else{
					memcpy(find_account_info_result->passwd,&passwd_new_b,sizeof(passwd_new_b));

					ls_account_info(find_account_info_result);
					//尾插(初始)账户数据
					ERRP(llist_append(find_account_info_result, handle_account_info_admin) == -1, add_account_info_append, goto ERR2);
					llist_del_front(&account,cmp_account,handle_account_info_admin);
					llist_store(handle_account_info_admin,"./student_account_info.db");//保存
					printf("修改成功！请重新登录！\n");
					sleep(2);
					select_account_menu();
					break;
					}
				}
				else{
					printf("前后密码不一致，请重新输入！\n");
				}
			}
			break;
		}
		else{
			printf("密码错误！请重新输入！\n");
		}
		}
	}
	
	return ;
ERR1:
	return ;
ERR2:
	llist_destroy(&handle_account_info_admin);
	return ;
}

//老师通过姓名查找学生信息
void find_student_info_teacher_by_name(){
	char name[50];
	struct student_info_t *find_student_info_result = NULL;
	
	LLIST *handle_student_info_teacher = NULL;
	//初始化
	handle_student_info_teacher = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_teacher, llist_create, goto ERR1);
	
	handle_student_info_teacher = llist_load("./student_info_admin.db");
	printf("请输入姓名: ");
		fgets(name, sizeof(name), stdin);
		if (name[strlen(name) - 1] == '\n')
			name[strlen(name) - 1] = '\0';

	find_student_info_result = llist_find_front(&name,cmp_name,handle_student_info_teacher);
	if (find_student_info_result == NULL)
	{
	    printf("没有找到！\n");
	}
	else
	{
	    ls_handle_student_info_admin(find_student_info_result);
	}
	
	llist_destroy(&handle_student_info_teacher);
	return ;
ERR1:
	return ;
}

//老师通过学号查找学生信息
void find_student_info_teacher_by_id(int class){
	system("clear");
	printf("*********************老师端*******************\n");
	printf("                通过学号查找学生信息            \n");
	printf("                		                       \n");
	printf("                    1.返回上级                  \n");
	printf("                 			                   \n");
	int id;
	struct student_info_t *find_student_info_result = NULL;
	
	LLIST *handle_student_info_teacher = NULL;
	//初始化
	handle_student_info_teacher = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_teacher, llist_create, goto ERR1);
	
	handle_student_info_teacher = llist_load("./student_info_admin.db");
	handle_student_info_teacher = llist_find_all(&class,cmp_class,handle_student_info_teacher);
	printf("请输入学号: ");
	scanf("%d",&id);

	find_student_info_result = llist_find_front(&id,cmp_id,handle_student_info_teacher);
	if (find_student_info_result == NULL)
	{
		
	    printf("没有找到！\n");
	}
	else
	{
		
	    ls_handle_student_info_admin(find_student_info_result);
	}
	llist_destroy(&handle_student_info_teacher);
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            teacher_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
}

//老师查看同班的全部学生信息
void find_student_info_teacher_same_class(int class){
	system("clear");//清屏
	printf("********************老师端*********************\n");
	printf("                  本班学生信息                  \n");
	printf("                		                       \n");
	printf("                   1.返回上级                   \n");
	printf("                 			                   \n");
	LLIST *handle_student_info_teacher = NULL;
	//初始化
	handle_student_info_teacher = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_teacher, llist_create, goto ERR1);
	
	handle_student_info_teacher = llist_load("./student_info_admin.db");
	
	llist_travel(llist_find_all(&class,cmp_class,handle_student_info_teacher),ls_handle_student_info_admin,NEXT);
	llist_destroy(&handle_student_info_teacher);
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            teacher_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
}

//老师通过姓名查找并修改学生信息
void modify_student_score_teacher_by_id(int class){
	system("clear");//清屏
	printf("*********************老师端*********************\n");
	printf("                登记本班学生成绩                \n");
	printf("                		                       \n");
	printf("                    1.返回上级                  \n");
	printf("                 			                   \n");
	int id;
	int score;
	struct student_info_t *find_student_info_result = NULL;
	
	LLIST *handle_student_info_teacher = NULL;
	//初始化
	handle_student_info_teacher = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_teacher, llist_create, goto ERR1);
	
	handle_student_info_teacher = llist_load("./student_info_admin.db");
	handle_student_info_teacher = llist_find_all(&class,cmp_class,handle_student_info_teacher);
	printf("请输入学号 : ");
	scanf("%d",&id);

	find_student_info_result = llist_find_front(&id,cmp_id,handle_student_info_teacher);
	if (find_student_info_result == NULL){
	    printf("没有找到！没有这个学号！\n");
	}
	else{
		while(1){
		printf("请输入要登记的成绩 : ");
		scanf("%d",&score);
		if(score >= 0 && score <=100){
			find_student_info_result->score = score;
			ls_handle_student_info_admin(find_student_info_result);
			ERRP(llist_append(find_student_info_result, handle_student_info_teacher) == -1, add_score_info_append, goto ERR2);
			llist_del_front(&id,cmp_id,handle_student_info_teacher);
			llist_store(handle_student_info_teacher,"./student_info_admin.db");//保存
			printf("修改成功！\n");
			break;
		}
		else{
			 printf("输入的分数有误！请重新输入！\n");
		}
		}
	}
	llist_destroy(&handle_student_info_teacher);
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            teacher_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
ERR2:
	llist_destroy(&handle_student_info_teacher);
	return ;
}
//对学生成绩排序打印
void sort_student_info_student_by_score(){
	system("clear");//清屏
	printf("******************学生端******************\n");
	printf("             加载学生成绩排名             \n");
	printf("                		                  \n");
	printf("                 1.返回上级                \n");
	printf("                 			              \n");
	LLIST *handle_student_info_student = NULL;
	//初始化
	handle_student_info_student = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_student, llist_create, goto ERR1);
	
	handle_student_info_student = llist_load("./student_info_admin.db");
	llist_sort_descending(handle_student_info_student, sort_score);//排序

	llist_travel_score(handle_student_info_student, ls_handle_student_score_student, NEXT);//遍历
	llist_destroy(&handle_student_info_student);
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            student_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
}
//加载学生信息
void load_student_info_admin(){
	system("clear");//清屏
	printf("*****************管理员端*****************\n");
	printf("               加载学生信息               \n");
	printf("                            		  	 \n");
	printf("               1.返回上一级		  		  \n");
	printf("                 			             \n");
	char enter_clear[2];
	//清除回车引发的错误
	fgets(enter_clear, sizeof(enter_clear), stdin);

	LLIST *handle_student_info_admin = NULL;
	//初始化
	handle_student_info_admin = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_student_info_admin, llist_create, goto ERR1);
	
	handle_student_info_admin = llist_load("./student_info_admin.db");

	llist_travel(handle_student_info_admin, ls_handle_student_info_admin, NEXT);//遍历
	llist_destroy(&handle_student_info_admin);
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            admin_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
}
//加载账户信息
void load_account_info_admin(){
	system("clear");//清屏
	printf("*****************管理员端*******************\n");
	printf("               加载账户信息                 \n");
	printf("                                           \n");
	printf("               1.返回上一级                 \n");
	printf("                 			                \n");
	LLIST *handle_account_info_admin = NULL;
	//初始化
	handle_account_info_admin = llist_create(sizeof(struct student_info_t));
	ERRP(NULL == handle_account_info_admin, llist_create, goto ERR1);
	
	handle_account_info_admin = llist_load("./student_account_info.db");

	llist_travel(handle_account_info_admin, ls_account_info, NEXT);//遍历
	llist_destroy(&handle_account_info_admin);
	int operation_option_int;
	while(1)//选项输入容错
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int == 1){
            admin_operation_menu();
            break;
        }
        else if(operation_option_int != 1)
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
ERR1:
	return ;
}

//账户登录信息比较
int login_account_info_cmp(const char *path, int *tmp_id){
	char enter_clear[2];
	//清除回车引发的错误
	fgets(enter_clear, sizeof(enter_clear), stdin);
	int account_cmp_result = 1, passwd_cmp_result = 1;//账号和密码的比较结果标记位，默认1为不同，0为相同
	char account[10],passwd[10];

	LLIST *handle_account_info = NULL;
	//初始化
	handle_account_info = llist_create(sizeof(struct account_info_t));
	ERRP(NULL == handle_account_info, llist_create, goto ERR1);
	
	handle_account_info = llist_load(path);
	
	//登录输入账号
	printf("\033[8;16H");
	fgets(account, sizeof(account), stdin);
	if (account[strlen(account) - 1] == '\n')
		account[strlen(account) - 1] = '\0';
	printf("\033[8;16H%s\n",account);
	printf("\033[9;16H");
	
	*tmp_id = atoi(account);

	//登录输入密码
	fgets(passwd, sizeof(passwd), stdin);
	if (passwd[strlen(passwd) - 1] == '\n')
		passwd[strlen(passwd) - 1] = '\0';
	
	printf("\033[9;16H%s\n",passwd);

	struct node_t *tail = NULL;

	for (tail = handle_account_info->head.next; tail != &handle_account_info->head; tail = tail->next)
	{
		if (cmp_account(account, tail->data) == 0)
		{
			account_cmp_result = 0;
			break;
		}	
	}
	
	if (cmp_passwd(passwd, tail->data) == 0){
		passwd_cmp_result = 0;
	}
	
	if(account_cmp_result == 0 && passwd_cmp_result == 0){
		printf("登录成功！\n");
	}
	else{
		printf("登录失败！\n");
		llist_destroy(&handle_account_info);
		return 0;//返回0表示登陆失败
	}

	llist_destroy(&handle_account_info);
	return 1;//返回1表示登录成功
ERR1:
	return ;
}


//选择账户界面
void select_account_menu(){
	system("clear");//清屏
	printf("********************欢迎***********************\n");
	printf("* SIMS  Student Information Manage System     \n");
	printf("*              学生信息管理系统                 \n");
	printf("*             请选择你的账户身份                \n");
	printf("*   1.学生                                     \n");
	printf("*   2.老师                                     \n");
	printf("*   3.管理员                                   \n");
	printf("*   4.退出系统                                 \n");
	printf("***********************************************\n");
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        
        if(operation_option_int == 1){//选择1,进入学生登录界面
			system("clear");//清屏
	 		student_account_login();
			break;
		}
		if(operation_option_int == 2){//选择2,进入老师登录界面
			system("clear");
	 		teacher_account_login();
			break;
		}
		if(operation_option_int == 3){//选择3,进入管理员登录界面
			system("clear");
			admin_account_login();
			break;
		}
		if(operation_option_int == 4){//退出管理系统
			system("clear");
			exit(0);
			break;
		}
        else
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
	return ;
}

//学生登录界面
void student_account_login()
{
	system("clear");
	int login_account_status;
	printf("*********************学生端********************\n");
	printf("*  SIMS   Student Information Manage System   \n");
	printf("*               学生信息管理系统               \n");
	printf("*             请输入你的账号和密码              \n");
    printf("*                    注意！！                  \n");
	printf("*             账号就是你的学号                  \n");
	printf("*  如果你第一次登录,初始密码是：   123456        \n");
	printf("*      账号:                                   \n");
	printf("*      密码:                                   \n");
	printf("***********************************************\n");
	login_account_status = login_account_info_cmp("./student_account_info.db",&tmp_id);
	if(login_account_status == 1){ //登录成功
		student_operation_menu();
	}
	if(login_account_status == 0){
		system("clear");
		printf("账号或密码错误！\n");
		printf("请重新登录！\n");
		sleep(2);
		select_account_menu();//登录失败，跳回账户身份选择界面
	}
}

//学生菜单界面
void student_operation_menu(){
	system("clear");//清屏
	printf("*********************学生端********************\n");
	printf("*  SIMS   Student Information Manage System    \n");
	printf("*                学生信息管理系统               \n");
	printf("*                 请选择你的服务                \n");
    printf("*      1.查找你的学生信息                       \n");
	printf("*      2.查看你的成绩                           \n");
	printf("*      3.查看你的成绩排名                       \n");
	printf("*      4.修改密码                              \n");
	printf("*      5.退出登录                              \n");
	printf("*                                              \n");
	printf("***********************************************\n");
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int > 0 && operation_option_int < 6){
         	switch (operation_option_int)
		{
		case 1:
			find_student_info_student_by_id(tmp_id);//学生通过学号查找学生信息
			break;
		case 2:
			find_student_score_student_by_id(tmp_id);//学生通过学号查找学生成绩
			break;
		case 3:
			sort_student_info_student_by_score();//对学生成绩排序排名打印
			break;
		case 4:
			modify_account_info_student_by_account(tmp_id);//修改学生账户密码
			break;
		case 5:
			select_account_menu();//管理员界面退出登录，回到欢迎界面
			break;
		}    
        }
        else
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
}
//老师登录注册界面
void teacher_account_login(){
	system("clear");
	int login_account_status;
	printf("*********************老师端*********************\n");
	printf("*  SIMS   Student Information Manage System    \n");
	printf("*                 学生信息管理系统               \n");
	printf("*                请输入你的账号密码              \n");
    printf("*                     注意！！                   \n");
	printf("*                账号是你的工号                  \n");
	printf("*   如果你第一次登录,初始密码是：   123456        \n");
	printf("*      账号:                                    \n");
	printf("*      密码:                                    \n");
	printf("************************************************\n");
	login_account_status = login_account_info_cmp("./teacher_account_info.db",&tmp_id);
	if(login_account_status == 1){ //登录成功
		teacher_operation_menu();
	}
	if(login_account_status == 0){
		system("clear");
		printf("账号或密码错误！\n");
		printf("请重新登录！\n");
		sleep(2);
		select_account_menu();//登录失败，跳回账户身份选择界面
	}
}
//老师菜单界面
void teacher_operation_menu(){
	system("clear");
	printf("*********************老师端*********************\n");
	printf("*  SIMS   Student Information Manage System    \n");
	printf("*                学生信息管理系统               \n");
	printf("*                                               \n");
    printf("*        1.查看本班学生信息                      \n");
	printf("*        2.登记学生成绩                          \n");
	printf("*        3.查找指定学生的信息                    \n");
	printf("*        4.退出登录                              \n");
	printf("*                                               \n");
	printf("************************************************\n");
	int operation_option_int;
	while(1)
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int > 0 && operation_option_int < 5){
         	switch (operation_option_int){
				case 1:
					find_student_info_teacher_same_class(tmp_class);//查看同一个班级学生信息
					break;
				case 2:
					modify_student_score_teacher_by_id(tmp_class);//老师通过姓名查找并修改学生成绩
					break;
				case 3:
					find_student_info_teacher_by_id(tmp_class);//老师通过学号查找学生信息
					break;
				case 4:
					select_account_menu();//管理员界面退出登录，回到欢迎界面
					break;
			}   
        }
        else
        {
            printf("没有这个选项！请重新输入！\n");
        }
    }
}

//管理员登录界面
void admin_account_login(){
	system("clear");
	int login_account_status;
	printf("*******************管理员端********************\n");
	printf("*                                             \n");
	printf("* SIMS   Student Information Manage System    \n");
	printf("*                                             \n");
	printf("*             请输入管理员账号密码              \n");
	printf("*                                             \n");
	printf("*                                             \n");
	printf("*      账号:                                   \n");
	printf("*      密码:                                   \n");
	printf("***********************************************\n");
	login_account_status = login_account_info_cmp("./admin_account_info.db",&tmp_id);
	if(login_account_status == 1){
		admin_operation_menu();
	}
	if(login_account_status == 0){
		system("clear");
		printf("账号或密码错误！\n");
		printf("请重新登录！\n");
		sleep(2);
		select_account_menu();//登录失败，跳回账户身份选择界面
	}
}

//管理员菜单界面
void admin_operation_menu(){
	system("clear");//清屏
	printf("*****************管理员端**********************\n");
	printf("*              学生信息管理系统                 \n");
	printf("*  SIMS   Student Information Manage System    \n");
	printf("*                                              \n");
	printf("*             请选择要进行的操作                 \n");
	printf("*                                              \n");
    printf("*   1.加载学生信息         6.加载账户信息        \n");
    printf("*   2.添加学生信息         7.添加账户信息        \n");
    printf("*   3.删除学生信息         8.删除账户信息        \n");
    printf("*   4.修改学生信息         9.修改账户信息        \n");
	printf("*   5.查找学生信息         10.查找账户信息       \n");
	printf("*               11.退出登录                     \n");
	printf("***********************************************\n");
	
	int operation_option_int;
	while(1)  //选择选项容错
    {
		printf("请输入操作的选项数字:  ");
        scanf("%d",&operation_option_int);
        if(operation_option_int > 0 && operation_option_int < 12){
        switch (operation_option_int)
		{
			case 1:
				load_student_info_admin();//管理员界面加载学生信息函数
				break;
			case 2:
				add_student_info_admin();//管理员界面添加学生信息函数
				break;
			case 3:
				del_student_info_admin_by_id();//管理员界面删除学生信息函数
				break;
			case 4:
				modify_student_info_admin_by_id();//管理员界面修改学生信息函数
				break;
			case 5:
				find_student_info_admin_by_id();//管理员界面查找学生信息函数
				break;
			case 6:
				load_account_info_admin();//管理员界面加载账户信息函数
				break;
			case 7:
				add_account_info_admin();//管理员界面添加账户信息函数
				break;
			case 8:
				del_account_info_admin_by_account();//管理员界面删除账户信息函数
				break;
			case 9:
				modify_account_info_admin_by_account();//管理员界面修改账户信息函数
				break;
			case 10:
				find_account_info_admin_by_account();//管理员界面查找账户信息函数
				break;
			case 11:
				select_account_menu();//管理员界面退出登录，回到欢迎界面
				break;
        	}
		}
        else{
            printf("没有这个选项！请重新输入！\n");
        }
    }
}

//整形转字符型
char* my_itoa(int num,char* str,int radix)
{
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";//索引表
    unsigned unum;//存放要转换的整数的绝对值,转换的整数可能是负数
    int i=0,j,k;//i用来指示设置字符串相应位，转换之后i其实就是字符串的长度；转换后顺序是逆序的，有正负的情况，k用来指示调整顺序的开始位置;j用来指示调整顺序时的交换。
 
    //获取要转换的整数的绝对值
    if(radix==10&&num<0)//要转换成十进制数并且是负数
    {
        unum=(unsigned)-num;//将num的绝对值赋给unum
        str[i++]='-';//在字符串最前面设置为'-'号，并且索引加1
    }
    else unum=(unsigned)num;//若是num为正，直接赋值给unum
 
    //转换部分，注意转换后是逆序的
    do
    {
        str[i++]=index[unum%(unsigned)radix];//取unum的最后一位，并设置为str对应位，指示索引加1
        unum/=radix;//unum去掉最后一位
 
    }while(unum);//直至unum为0退出循环
 
    str[i]='\0';//在字符串最后添加'\0'字符，c语言字符串以'\0'结束。
 
    //将顺序调整过来
    if(str[0]=='-') k=1;//如果是负数，符号不用调整，从符号后面开始调整
    else k=0;//不是负数，全部都要调整
 
    char temp;//临时变量，交换两个值时用到
    for(j=k;j<=(i-1)/2;j++)//头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1
    {
        temp=str[j];//头部赋值给临时变量
        str[j]=str[i-1+k-j];//尾部赋值给头部
        str[i-1+k-j]=temp;//将临时变量的值(其实就是之前的头部值)赋给尾部
    }
 
    return str;//返回转换后的字符串
 
}

//初始化
LLIST *llist_create(int size)
{
	LLIST *handle = NULL;

	handle = (LLIST *)malloc(sizeof(LLIST));
	ERRP(NULL == handle, malloc handle, goto ERR1);

	handle->size = size;
	handle->count = 0;
	handle->head.data = NULL;
	handle->head.next = &handle->head;
	handle->head.prev = &handle->head;
	return handle;
ERR1:
	return NULL;
}
//尾插
int llist_append(void *data, LLIST *handle)
{
	struct node_t *new = NULL;

	new = (struct node_t *)malloc(sizeof(struct node_t));
	ERRP(new == NULL, malloc node, goto ERR1);

	new->data = (void *)malloc(handle->size);
	ERRP(new->data == NULL, malloc node data, goto ERR2);

	memcpy(new->data, data, handle->size);

	
	//1 先写外来的new
	// 2 谁长写谁
	new->next = &handle->head;
	new->prev = handle->head.prev;
	handle->head.prev->next = new;
	handle->head.prev = new;
	handle->count++;

	return 0;
ERR2:
	free(new);
ERR1:
	return -1;
}

//从头删除某个数据
void llist_del_front(void *key, llist_cmp_t *cmp, LLIST *handle)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(key, tail->data) == 0)
		{
			tail->next->prev = tail->prev;
			tail->prev->next = tail->next;
			free(tail->data);
			free(tail);
			handle->count--;
			return ;
		}
	}
}

//删除所有
void llist_del_all(void *key, llist_cmp_t *cmp, LLIST *handle)
{
	struct node_t *tail = NULL;
	struct node_t *save = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = save)
	{
		save = tail->next;
		if (cmp(key, tail->data) == 0)
		{
			
			tail->next->prev = tail->prev;
			tail->prev->next = tail->next;
			free(tail->data);
			free(tail);
			handle->count--;
		}
	}
}

//查找
void *llist_find_front(void *key, llist_cmp_t *cmp, LLIST *handle)
{
	struct node_t *tail = NULL;

	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (cmp(key, tail->data) == 0)
		{
			return tail->data;
		}
	}
	return NULL;
}
//查找有关键词的全部数据
LLIST *llist_find_all(void *key, llist_cmp_t *cmp, LLIST *handle)
{
	struct node_t *tail = NULL;
	LLIST *ind = NULL;

	ERRP((ind = llist_create(handle->size)) == NULL, llist_create, goto ERR1);

	for (tail = handle->head.prev; tail != &handle->head; tail = tail->prev)
	{
		if (cmp(key, tail->data) == 0)
		{
			llist_append(tail->data, ind);
		}
	}
	return ind;
ERR1:
	return NULL;
}
//升序排序
void llist_sort_asending(LLIST *handle, llist_cmp_t *cmp)
{
	struct node_t *val1, *val2;
	void *tmp = NULL;

	tmp = (void *)malloc(handle->size);
	for (val1 = handle->head.next; val1 != &handle->head; val1 = val1->next)
	{
		for (val2 = val1->next; val2 != &handle->head; val2 = val2->next)
		{
			if (cmp(val1->data, val2->data) > 0)
			{
                /*
				 *tmp = val1->data;
				 *val1->data = val2->data;
				 *val2->data = tmp;
                 */

				memcpy(tmp, val1->data, handle->size);
				memcpy(val1->data, val2->data, handle->size);
				memcpy(val2->data, tmp, handle->size);
			}
		}
	}
}
//降序排序
void llist_sort_descending(LLIST *handle, llist_cmp_t *cmp){
	struct node_t *val1, *val2;
	void *tmp = NULL;

	tmp = (void *)malloc(handle->size);
	for (val1 = handle->head.next; val1 != &handle->head; val1 = val1->next)
	{
		for (val2 = val1->next; val2 != &handle->head; val2 = val2->next)
		{
			if (cmp(val1->data, val2->data) < 0)
			{
                /*
				 *tmp = val1->data;
				 *val1->data = val2->data;
				 *val2->data = tmp;
                 */

				memcpy(tmp, val1->data, handle->size);
				memcpy(val1->data, val2->data, handle->size);
				memcpy(val2->data, tmp, handle->size);
			}
		}
	}
}

//==============file save============
int llist_store(LLIST *handle, const char *path)
{
	FILE *fp = NULL;
	struct node_t *tail = NULL;


	//1 打开文件
	fp = fopen(path, "w");
	ERRP(NULL == fp, fopen, goto ERR1);

	//2 现保存数据类型和个数
	ERRP(fwrite(&handle->size, sizeof(handle->size), 1, fp) != 1, fwrite size, goto ERR2);


	ERRP(fwrite(&handle->count, sizeof(handle->count), 1, fp) != 1, fwrite count, goto ERR2);

	//3 保存数据
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		fwrite(tail->data, handle->size, 1, fp);
	}

	fclose(fp);
	return 0;
ERR2:
	fclose(fp);
ERR1:
	return -1;
}
//文件加载
LLIST *llist_load(const char *path)
{
	FILE *fp = NULL;
	LLIST *handle = NULL;
	int size, count;
	int i;
	void *tmp = NULL;

	// 1 打开文件
	fp = fopen(path, "r");
	ERRP(fp == NULL, fopen, goto ERR1);
	
	//2 获取数据类型和个数
	ERRP(fread(&size, sizeof(size), 1, fp) != 1, fread size, goto ERR2);
	ERRP(fread(&count, sizeof(count), 1, fp) != 1, fread count, goto ERR2);

	

	//初始化handle
	handle = llist_create(size);
	ERRP(NULL == handle, llist_create, goto ERR2);
	
	tmp = (void *)malloc(handle->size);
	ERRP(NULL == tmp, malloc tmp, goto ERR3);

	for (i = 0; i < count; i++)
	{
		ERRP(fread(tmp, size, 1, fp) != 1, fread data, goto ERR4);	

		/*llist_appfront(tmp, handle);*/
		llist_append(tmp, handle);
	}
	
	free(tmp);
	fclose(fp);
	return handle;

ERR4:
	free(tmp);
ERR3:
	llist_destroy(&handle);
ERR2:
	fclose(fp);
ERR1:
	return NULL;
}
//链表遍历
void llist_travel(LLIST *handle, llist_op_t *op, int flag)
{
	struct node_t *tail = NULL;

	if (flag == NEXT)
	{
		for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
		{
			op(tail->data);
		}
	}
}
//销毁
void llist_destroy(LLIST **handle)
{
	struct node_t *tail = NULL;
	struct node_t *save = NULL;
	for (tail  = (*handle)->head.next; tail != &((*handle)->head); tail = save)
	{
		save = tail->next;
		free(tail->data);
		tail->data = NULL;
		free(tail);
		tail = NULL;
	}

	free(*handle);
	*handle = NULL;
}
