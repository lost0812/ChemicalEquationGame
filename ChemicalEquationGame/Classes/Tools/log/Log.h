#ifndef __LOG_MANGAGE_H__
#define __LOG_MANGAGE_H__

#include <string>
#include <stdarg.h>

using namespace std;

#define DebugLog( format, ... ) LogOut( __FILE__, __FUNCTION__ , __LINE__, format, ##__VA_ARGS__ )
#define ErrorLog( format, ... ) LogErr( __FILE__, __FUNCTION__ , __LINE__, format, ##__VA_ARGS__ )
class CLog
{
public:
	CLog( string file_name );
public:
	void LogOut( char *src_file, char *function, int line, char *format, ... );
	void LogErr( char *src_file, char *function, int line, char *format, ... );

private:
	//获取函数栈中所有函数的参数
	int GetParameterFromFunctionStack( int *first_function_edp_address, char *parameter );

private:
	string m_file_name;
};


#endif