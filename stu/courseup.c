#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char cno[32] = "\0";
	char cname[32] = "\0";
	char credit[32] = "\0";
	char fclass[32] = "\0";
	int status = 0;

	status = cgiFormString("credit",  credit, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get credit error!\n");
		return 1;
	}

	status = cgiFormString("cno",  cno, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}

	status = cgiFormString("cname",  cname, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cname error!\n");
		return 1;
	}
	status = cgiFormString("fclass",  fclass, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get fclass error!\n");
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




	sprintf(sql, "update course set  cname= '%s',credit= %d,fclass= '%s'  where cno= %d ",  cname,atoi(credit),fclass,atoi(cno));
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
fprintf(cgiOut, "<br>");


	fprintf(cgiOut, "update course ok!\n");
	mysql_close(db);
	return 0;
}
