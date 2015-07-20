#ifndef __PARAM_H__
#define __PARAM_H__

#include <map>
#include <vector>
#include <string>
#include <sstream>

#include "Log.h"

extern CLog ParamLog;

/*
��ֹʹ��ջָ����Ϊֵ
�������ͷŶѱ����Ŀռ�
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
		//�����ֵ�������ѱ����洢�洢
		//�����ָ�룬ֱ�ӱ���ָ��ֵ
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
		ParamLog.DebugLog( "��ȡ�������ʹ��� ��������:%s, ��ȡ����:%s", m_type->name(), typeid(T).name() );
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

		case POINT://ȡ��ָ��
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
		ParamLog.DebugLog( "���ò������ʹ��� ��������:%s, ��������:%s", m_type->name(), typeid(T).name() );
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
		ParamLog.DebugLog("δ��������%s", name.c_str() );
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
		ParamLog.DebugLog("δ��������%s", name.c_str() );
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
		ParamLog.DebugLog( "�Ѿ���������%s,���������ظ�����", name.c_str() );
		return false;
	}
}

#endif