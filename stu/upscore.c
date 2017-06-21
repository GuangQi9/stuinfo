#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char stuId[32] = "\0";
	char cno[32] = "\0";
	char grade[32] = "\0";
	int status = 0;

	status = cgiFormString("grade",  grade, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get grade error!\n");
		return 1;
	}

	status = cgiFormString("cno",  cno, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}

	status = cgiFormString("stuId",  stuId, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}


/*	fprintf(cgiOut, "nams = %s, age = %d, stuId = %d, sex = %s, phone = %s, sdept = %s\n", nams, age, stuId, sex, phone, sdept);
*/
//fprintf(cgiOut, "%s\n",);



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
/*fprintf(cgiOut, "nams = %s, age = %d, stuId = %d, sex = %s, phone = %s, sdept = %s\n", nams, atoi(age), atoi(stuId), sex, phone, sdept);*/




	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}




	sprintf(sql, "update score set  grade= %d  where stuId = %d and cno= %d ",  atoi(grade),atoi(stuId),atoi(cno));
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
fprintf(cgiOut, "<br>");


	fprintf(cgiOut, "update student ok!\n");
	mysql_close(db);
	return 0;
}
