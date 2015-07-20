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

	//��ȡԴ�ļ����ļ���
	string src_file_name;
	src_file_name = src_file;
	src_file_name = src_file_name.substr( src_file_name.find_last_of('\\')+1 );


	//���ɱ������ʽ����buffer
	char buffer[2048];
	va_list list;

	va_start( list, format );
	vsnprintf_s(buffer, sizeof(buffer) - 1,sizeof(buffer) - 1, format, list );
	va_end( list );


	//��ȡʱ��
	char time_buffer[50];
	time_t int_timer = time(NULL);
	tm struct_timer;

	localtime_s( &struct_timer, &int_timer );
	strftime( time_buffer, sizeof( time_buffer ), "%Y-%m-%d %H:%M:%S", &struct_timer );

		
	//��־���
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


	//����̨���
	cout<< time_buffer
		<< " " << src_file_name.c_str()
		<< " " << function
		<< " " << line
		<< " " << buffer << endl;

}


void CLog::LogErr( char *src_file, char *function, int line, char *format, ... )
{
	//��ȡջָ��
	int *stack_address = (int*)(&stack_address);//�����Ӻ����л�ȡ��Ϊ���ٳ�һ�ɺ���Ƕ�ס�


	//��ȡ��ӡ��־��Դ�ļ��ļ���
	string src_file_name;
	src_file_name = src_file;
	src_file_name = src_file_name.substr( src_file_name.find_last_of('\\')+1 );


	//���ɱ������ʽ����buffer
	char buffer[2048];
	va_list list;

	va_start( list, format );
	vsnprintf_s( buffer, sizeof(buffer) - 1,sizeof(buffer) - 1, format, list );
	va_end( list );


	//��ȡ����ջ�����к����Ĳ���
	char parameter[2048] = {'\0'};
	GetParameterFromFunctionStack( stack_address, parameter );


	//��ȡʱ��
	char time_buffer[50];
	time_t int_timer = time(NULL);
	tm struct_timer;

	localtime_s( &struct_timer, &int_timer );
	strftime( time_buffer, sizeof( time_buffer ), "%Y-%m-%d %H:%M:%S", &struct_timer );

		
	//��־���
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


	//����̨���
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

	while( *(int*)(*(int*)(*(int*)((int*)(*last_ebp_stack_address)))) != 0 )//�ų��������ϲ�ĺ�������
	{
		asm_code = (unsigned char*)(*function_execute_address);

		//��ȡ��������
		if( *asm_code == 0x83 )
		{
			arg_size = asm_code[2];//��ȡ��������
			strcat_s( parameter, 2048, "ȫ�ֺ�����" );
		}
		else if( *asm_code == 0x33 )
		{
			arg_size = 0;
			strcat_s( parameter, 2048, "ȫ�ֺ������޲���" );
		}
		else
		{
			return_address = asm_code;
			asm_code -= 5;

			//call ��ת
			call_offset = *(unsigned short*)(asm_code+1);
			call_offset = *return_address == 0xcc?(~call_offset) - 1:(~call_offset) - 4;
			asm_code -= call_offset;

			//jmp ��ת
			call_offset = *(unsigned short*)(asm_code+1) + 5;
			asm_code += call_offset;
			
			//���� ret�����
			while( *asm_code != 0xc2 && *asm_code != 0xc3 )
			{
				asm_code++;
			}
			if( *asm_code == 0xc2 )
			{
				arg_size = asm_code[1];//��ȡ��������
				strcat_s( parameter,2048, "��Ա������" );
			}
			else if( *asm_code == 0xc3 )
			{
				arg_size = 0;
				strcat_s( parameter,2048, "��Ա�������޲���" );
			}

		}

		//�����������
		char temp[100] = {'\0'};
		for( int *arg = function_execute_address+1, i = 0; i < arg_size/4; i++,arg++ )
		{
			sprintf_s( temp, 100, "[%d],", *arg );
			strcat_s( parameter,2048, temp );
		}
		strcat_s( parameter, 2048, "\n" );

		//ѭ������ջ�����к���
		curr_ebp_stack_address = last_ebp_stack_address;
		last_ebp_stack_address = (int*)(*curr_ebp_stack_address);
		function_execute_address = curr_ebp_stack_address+1;
	}
	strcat_s( parameter, 2048, "ȫ�ֺ�����������\n" );


	return 1;
}