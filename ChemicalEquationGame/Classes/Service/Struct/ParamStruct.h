#ifndef __PARAM_H__
#define __PARAM_H__

#include <map>
#include <vector>
#include <string>
#include <sstream>

#include "Log.h"

extern CLog ParamLog;

/*
禁止使用栈指针作为值
可自行释放堆变量的空间
*/
using namespace std;
struct ParamStruct
{
private:
	class ParamValue
	{
	private:
		enum TYPE_PARAM_VALUE
		{
			VALUE,
			POINT
		};
	public:
		//如果是值，创建堆变量存储存储
		//如果是指针，直接保存指针值
		ParamValue( const type_info *type, void *&value );
		~ParamValue( );
	public:
		string GetValueType();

		template< class T >
		T GetValue( T default_value );
		template< class T >
		bool SetValue( T t );

		void ReSetValue();
		string ToString();
	private:
		TYPE_PARAM_VALUE  DistinguishParamValueType();
	private:
		const type_info *m_type;
		void *m_value;
	};
public:
	ParamStruct();
	~ParamStruct();

	template< class T >
	T GetParam( string name, T default_value );

	template< class T >
	bool SetParam( string name, T t );

	const vector< string > &GetParamNames( );
	void clear();

	string ToString();
protected:
	template< class T >
	bool Insert( string name, T t );
	bool Insert( string name, const type_info * value_type_info );
private:
	map< string, ParamValue* > m_params;
	vector< string > m_names;
};

template< class T >
T ParamStruct::ParamValue::GetValue(T default_value)
{
	T t = default_value;
	if( m_type->before( typeid( T ) ) ||  typeid( T ) == *m_type )
	{
		if( m_value != NULL )
		{
			switch ( DistinguishParamValueType() )
			{
			case VALUE:
				t = *(T*)m_value;
				break;

			case POINT:
				t = *(T*)&m_value;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		ParamLog.DebugLog( "获取参数类型错误 变量类型:%s, 获取类型:%s", m_type->name(), typeid(T).name() );
	}
	return t;
}

template< class T >
bool ParamStruct::ParamValue::SetValue(T t)
{
	bool is_set = false;
	if( m_type->before( typeid( T ) ) || *m_type == typeid( T ) )
	{
		if( m_value != NULL )
		{
			delete m_value;
		}
		m_value = new T(t);

		switch ( DistinguishParamValueType() )
		{
		case VALUE://Do Nothting
			break;

		case POINT://取除指针
			{
				void *value = m_value;
				m_value = *(void**) m_value;
				delete value;
				value = NULL;
				break;
			}
		default:
			break;
		}
		is_set = true;
	}
	else
	{
		ParamLog.DebugLog( "设置参数类型错误 变量类型:%s, 设置类型:%s", m_type->name(), typeid(T).name() );
	}
	return is_set;
}

template< class T >
T ParamStruct::GetParam(string name, T default_value)
{
	T t;
	map< string, ParamValue * >::iterator it_map = m_params.find( name );

	if( it_map != m_params.end() )
	{
		t = it_map->second->GetValue<T>( default_value );
	}
	else
	{
		ParamLog.DebugLog("未创建参数%s", name.c_str() );
	}
	return t;
}
template< class T >
bool ParamStruct::SetParam(string name, T t)
{
	bool is_set = false;
	map< string, ParamValue * >::iterator it_map = m_params.find( name );

	if( it_map != m_params.end() )
	{
		is_set = it_map->second->SetValue<T>( t );
	}
	else
	{
		ParamLog.DebugLog("未创建参数%s", name.c_str() );
	}
	return is_set;
}


template< class T >
bool ParamStruct::Insert(string name, T t)
{
	map< string, ParamValue * >::iterator map_it = m_params.find( name );
	string value;

	if( map_it == m_params.end() )
	{
		T *point = new T(t);
		m_params.insert( pair< string, ParamValue* >( name, new ParamValue( &typeid(T), (void *&)point ) ) );
		m_names.push_back( name );
		return true;
	}
	else
	{
		ParamLog.DebugLog( "已经创建参数%s,参数不能重复创建", name.c_str() );
		return false;
	}
}

#endif