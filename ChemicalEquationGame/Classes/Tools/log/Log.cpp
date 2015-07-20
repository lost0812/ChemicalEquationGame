#include "Log.h"

#include <fstream>
#include <time.h>
#include <iostream>

CLog::CLog( string file_name )
{
	m_file_name = file_name;
}
	
void CLog::LogOut( char *src_file, char *function, int line, char *format, ... )
{

	//获取源文件的文件名
	string src_file_name;
	src_file_name = src_file;
	src_file_name = src_file_name.substr( src_file_name.find_last_of('\\')+1 );


	//将可变参数格式化到buffer
	char buffer[2048];
	va_list list;

	va_start( list, format );
	vsnprintf_s(buffer, sizeof(buffer) - 1,sizeof(buffer) - 1, format, list );
	va_end( list );


	//获取时间
	char time_buffer[50];
	time_t int_timer = time(NULL);
	tm struct_timer;

	localtime_s( &struct_timer, &int_timer );
	strftime( time_buffer, sizeof( time_buffer ), "%Y-%m-%d %H:%M:%S", &struct_timer );

		
	//日志输出
	ofstream fout( m_file_name.c_str(), ios::app );
	if( fout.is_open() )
	{
		fout << time_buffer
			 << " " << src_file_name.c_str()
			 << " " << function
			 << " " << line
			 << " " << buffer << endl;
		fout.close();
	}


	//控制台输出
	cout<< time_buffer
		<< " " << src_file_name.c_str()
		<< " " << function
		<< " " << line
		<< " " << buffer << endl;

}


void CLog::LogErr( char *src_file, char *function, int line, char *format, ... )
{
	//获取栈指针
	int *stack_address = (int*)(&stack_address);//不在子函数中获取，为了少除一成函数嵌套。


	//获取打印日志的源文件文件名
	string src_file_name;
	src_file_name = src_file;
	src_file_name = src_file_name.substr( src_file_name.find_last_of('\\')+1 );


	//将可变参数格式化到buffer
	char buffer[2048];
	va_list list;

	va_start( list, format );
	vsnprintf_s( buffer, sizeof(buffer) - 1,sizeof(buffer) - 1, format, list );
	va_end( list );


	//获取函数栈中所有函数的参数
	char parameter[2048] = {'\0'};
	GetParameterFromFunctionStack( stack_address, parameter );


	//获取时间
	char time_buffer[50];
	time_t int_timer = time(NULL);
	tm struct_timer;

	localtime_s( &struct_timer, &int_timer );
	strftime( time_buffer, sizeof( time_buffer ), "%Y-%m-%d %H:%M:%S", &struct_timer );

		
	//日志输出
	ofstream fout( m_file_name.c_str(), ios::app );
	if( fout.is_open() )
	{
		fout << time_buffer
				<< " " << src_file_name.c_str()
				<< " " << function
				<< " " << line
				<< " " << buffer << endl
				<< parameter << endl;
		fout.close();
	}


	//控制台输出
	cout<< time_buffer
		<< " " << src_file_name.c_str()
		<< " " << function
		<< " " << line
		<< " " << buffer << endl
		<< parameter << endl;

}


int CLog::GetParameterFromFunctionStack( int *first_function_edp_address, char *parameter )
{
	int *last_ebp_stack_address = *( first_function_edp_address + 4 )== 0? first_function_edp_address + 5 : first_function_edp_address + 1;
	int *curr_ebp_stack_address = (int*)(*(int*)(*last_ebp_stack_address));
	int *function_execute_address = curr_ebp_stack_address+1;

	unsigned char *asm_code;
	unsigned char *return_address;
	unsigned char call_offset;
	int arg_size = 0;

	while( *(int*)(*(int*)(*(int*)((int*)(*last_ebp_stack_address)))) != 0 )//排除主函数上层的函数调用
	{
		asm_code = (unsigned char*)(*function_execute_address);

		//获取参数个数
		if( *asm_code == 0x83 )
		{
			arg_size = asm_code[2];//获取参数个数
			strcat_s( parameter, 2048, "全局函数：" );
		}
		else if( *asm_code == 0x33 )
		{
			arg_size = 0;
			strcat_s( parameter, 2048, "全局函数：无参数" );
		}
		else
		{
			return_address = asm_code;
			asm_code -= 5;

			//call 跳转
			call_offset = *(unsigned short*)(asm_code+1);
			call_offset = *return_address == 0xcc?(~call_offset) - 1:(~call_offset) - 4;
			asm_code -= call_offset;

			//jmp 跳转
			call_offset = *(unsigned short*)(asm_code+1) + 5;
			asm_code += call_offset;
			
			//查找 ret汇编码
			while( *asm_code != 0xc2 && *asm_code != 0xc3 )
			{
				asm_code++;
			}
			if( *asm_code == 0xc2 )
			{
				arg_size = asm_code[1];//获取参数个数
				strcat_s( parameter,2048, "成员函数：" );
			}
			else if( *asm_code == 0xc3 )
			{
				arg_size = 0;
				strcat_s( parameter,2048, "成员函数：无参数" );
			}

		}

		//遍历输出参数
		char temp[100] = {'\0'};
		for( int *arg = function_execute_address+1, i = 0; i < arg_size/4; i++,arg++ )
		{
			sprintf_s( temp, 100, "[%d],", *arg );
			strcat_s( parameter,2048, temp );
		}
		strcat_s( parameter, 2048, "\n" );

		//循环查找栈内所有函数
		curr_ebp_stack_address = last_ebp_stack_address;
		last_ebp_stack_address = (int*)(*curr_ebp_stack_address);
		function_execute_address = curr_ebp_stack_address+1;
	}
	strcat_s( parameter, 2048, "全局函数：主函数\n" );


	return 1;
}