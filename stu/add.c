#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char nams[32] = "\0";
	char age[16] = "\0";
	char stuId[32] = "\0";
	char sdept[32] = "\0";
	char sex[32] = "\0";
	char phone[32] = "\0";
	char ssate[32] = "\0";
	int status = 0;

	status = cgiFormString("nams",  nams, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get nams error!\n");
		return 1;
	}

	status = cgiFormString("age",  age, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get age error!\n");
		return 1;
	}
	status = cgiFormString("sdept",  sdept, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sdept error!\n");
		return 1;
	}
	status = cgiFormString("sex",  sex, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sex error!\n");
		return 1;
	}
	status = cgiFormString("stuId",  stuId, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}
	status = cgiFormString("phone",  phone, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get phone error!\n");
		return 1;
	}
	status = cgiFormString("ssate",  ssate, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get ssate error!\n");
		return 1;
	}

	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	mysql_options(db,MYSQL_SET_CHARSET_NAME,"utf8");
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}




	strcpy(sql, "create table student( stuId int not null primary key, nams varchar(20) not null, age int not null, sdept int(4) not null , sex char(6) (sex in('男','女')), phone char(15) not null, ssate int not null  ")     ;
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}




	sprintf(sql, "insert into student values(%d, '%s', %d,'%d','%s','%s',%d)", atoi(stuId), nams, atoi(age), atoi(sdept), sex, phone, atoi(ssate));
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add student ok!\n");
	mysql_close(db);
	return 0;
}
