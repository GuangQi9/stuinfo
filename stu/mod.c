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
	char sex[32] = "\0";
	char phone[32] = "\0";
	char sdept[32] = "\0";
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

	status = cgiFormString("stuId",  stuId, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}
	status = cgiFormString("sex",  sex, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sex error!\n");
		return 1;
	}
	status = cgiFormString("phone",  phone, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get phone error!\n");
		return 1;
	}

	status = cgiFormString("sdept",  sdept, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sdept error!\n");
		return 1;
	}





/*	fprintf(cgiOut, "nams = %s, age = %d, stuId = %d, sex = %s, phone = %s, sdept = %s\n", nams, age, stuId, sex, phone, sdept);
*/

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


	sprintf(sql, "update student set nams='%s', age= %d ,  sex = '%s' , phone = '%s' , sdept = '%s' where stuId = %d ", nams, atoi(age),  sex, phone, sdept,atoi(stuId));
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	fprintf(cgiOut, "update student ok!\n");
	mysql_close(db);
	return 0;
}
