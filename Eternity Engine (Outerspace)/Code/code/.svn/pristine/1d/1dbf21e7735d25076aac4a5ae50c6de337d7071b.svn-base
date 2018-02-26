#pragma once
#include <vector>
#include <string>
struct st_mysql;
struct st_mysql_res;
typedef st_mysql_res MYSQL_RES;

class MySQL
{
	st_mysql* mConnection;
	st_mysql_res* mLastResult;
	bool mIsConnected;
	FILE* mErrFile;
public:
	typedef std::vector<std::vector<char*>> Result;
#define MySQLFetchResult(itr,row) for(MySQL::Result::iterator itr = res.begin(); itr != res.end(); itr++) { for(std::vector<char*>::iterator row = itr->begin(); row != itr->end(); row++)

	MySQL(void);
	~MySQL(void);
	bool connect(const std::string& host, const std::string& user, const std::string& password, const std::string& db = "", unsigned short port = 3306);
	bool query(const std::string& sql);
	unsigned __int64 getRows(MYSQL_RES* result = NULL);
	Result getResult(MYSQL_RES* result = NULL);
	MYSQL_RES* getMySQLResult();
	void FreeResult(MYSQL_RES* result);
	void disconnect();
	bool isConnected();
	void setErrorFile(FILE* file);

};

