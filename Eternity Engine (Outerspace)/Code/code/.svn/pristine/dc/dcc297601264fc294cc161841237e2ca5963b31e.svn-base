#include "MySQL.h"
#include <Windows.h>
#include <mysql.h>
#include "ExceptionManager.h"

#pragma comment (lib,"libmysql.lib")

MySQL::MySQL(void)
{
	mLastResult = NULL;
	mIsConnected = false;
	mErrFile = stderr;
	mConnection = mysql_init(NULL);
	if(mConnection==NULL) 
		EXCEPT(ET_InternalError,String("Mysql konnte nicht inizialisiert werden: ")+ mysql_error(mConnection)); 
}

MySQL::~MySQL(void)
{
	if(mIsConnected) mysql_close(mConnection);
}

bool MySQL::connect(const std::string& host, const std::string& user, const std::string& password, const std::string& db, unsigned short port)
{
	unsigned long ip; 
	hostent* he; 
	SOCKADDR_IN addr;
	char* addresse;
	ip = inet_addr(host.c_str());
	if(ip!=INADDR_NONE)
		addr.sin_addr.s_addr=ip; 
	else
	{
		he = gethostbyname(host.c_str());
		if(he)
			memcpy(&(addr.sin_addr),he->h_addr_list[0],4); 
		else
			EXCEPT(ET_InternalError, "'" + host + "' kann nicht aufgelöst werden");
	}
	addresse = inet_ntoa(addr.sin_addr);

	mIsConnected = (mysql_real_connect(mConnection,addresse,user.c_str(),password.c_str(),db.c_str(),port,NULL,0) != NULL);
	if(!mIsConnected) 
		EXCEPT(ET_InternalError,String("MySQL: ")+ mysql_error(mConnection)); 
	return mIsConnected;
}

bool MySQL::query(const std::string& sql)
{
	if(mLastResult) mysql_free_result(mLastResult);
	mLastResult = NULL;
	bool res = (mysql_query(mConnection,sql.c_str()) == 0);
	if(!res) 
		EXCEPT(ET_InternalError,String("MySQL: ")+ mysql_error(mConnection)); 
	mLastResult = mysql_store_result(mConnection);

	return res;
}

my_ulonglong MySQL::getRows(MYSQL_RES* result)
{
	if(!result) result = mLastResult;
	my_ulonglong res;
	res = mysql_affected_rows(mConnection);
	if(res == ((my_ulonglong)-1))
	{
		if(result)
			res = mysql_num_rows(result);
		else
			res = 0;
	}
	return res;
}

MySQL::Result MySQL::getResult(MYSQL_RES* result)
{
	if(!result) result = mLastResult;
	Result res;
	if(mysql_num_rows(result) == 0)
		return res;
	MYSQL_ROW row;
	while(row = mysql_fetch_row(result))
	{
		std::vector<char*> line;
		for(unsigned int i=0;i<mysql_num_fields(result);i++)
			line.push_back(row[i]);
		res.push_back(line);
	}
	return res;
}

MYSQL_RES* MySQL::getMySQLResult()
{
	MYSQL_RES* res = mLastResult;
	mLastResult = NULL;
	return res;
}

void MySQL::FreeResult(MYSQL_RES* result)
{
	mysql_free_result(result);
}

void MySQL::disconnect()
{
	if(mIsConnected)
		mysql_close(mConnection);
	mIsConnected = false;
}

bool MySQL::isConnected()
{
	return mIsConnected;
}

void MySQL::setErrorFile(FILE* file)
{
	mErrFile = file;
}
