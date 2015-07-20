#include "ParamStruct.h"

CLog ParamLog("Param.log");

ParamStruct::ParamValue::ParamValue( const type_info *type, void *&value )
{
	m_type = type;
	m_value = value;

	if( value != NULL )
	{
		switch ( DistinguishParamValueType() )
		{
		case VALUE://Do Nothting
			break;

		case POINT://取除指针
			m_value = *(void**) m_value;
			delete value;
			value = NULL;
			break;
		default:
			break;
		}
	}
};

ParamStruct::ParamValue::~ParamValue()
{
	if( m_value != NULL )
	{
		delete m_value;
		m_value = NULL;
	}
};

std::string ParamStruct::ParamValue::GetValueType()
{
	return m_type->name();
}

void ParamStruct::ParamValue::ReSetValue()
{
	if( m_value != NULL )
	{
		delete m_value;
		m_value = NULL;
	}
}

std::string ParamStruct::ParamValue::ToString()
{
	stringstream  ss;
	string        value_type_name = m_type->name();
	if( m_value == NULL )
	{
		ss << 0;
	}
	else if( value_type_name == "bool" || value_type_name == "bool *" )
	{
		ss << *(bool *)m_value;
	}
	else if( value_type_name == "char" || value_type_name == "char *" )
	{
		ss << *(char*)m_value;
	}
	else if( value_type_name == "short" || value_type_name == "short *" )
	{
		ss << *(short*)m_value;
	}
	else if( value_type_name == "int" || value_type_name == "int *" )
	{
		ss << *(int*)m_value;
	}
	else if( value_type_name == "long" || value_type_name == "long *" )
	{
		ss << *(long*)m_value;
	}
	else if( value_type_name == "float" || value_type_name == "float *" )
	{
		ss << *(float*)m_value;
	}
	else if( value_type_name == "double" || value_type_name == "double *" )
	{
		ss << *(double*)m_value;
	}
	else if( value_type_name == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >"
		|| value_type_name == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > *" )
	{
		ss << *(string*)m_value;
	}
	else if( value_type_name == "unsigned char" || value_type_name == "unsigned char *" )
	{
		ss << *(unsigned char*)m_value;
	}
	else if( value_type_name == "unsigned short" || value_type_name == "unsigned short *" )
	{
		ss << *(unsigned short*)m_value;
	}
	else if( value_type_name == "unsigned int" || value_type_name == "unsigned int *" )
	{
		ss << *(unsigned int*)m_value;
	}
	else if( value_type_name == "unsigned long" || value_type_name == "unsigned long *" )
	{
		ss << *(unsigned long*)m_value;
	}
	else if( m_type->before( typeid( ParamStruct ) ) )
	{
		ss << ((ParamStruct*)m_value)->ToString();
	}
	else
	{
		ss << "unknown" <<',' << (int)m_value;
	}

	return ss.str();
}

ParamStruct::ParamValue::TYPE_PARAM_VALUE  ParamStruct::ParamValue::DistinguishParamValueType()
{
	string value_name = m_type->name();
	TYPE_PARAM_VALUE type;

	if( value_name.at(value_name.find_last_not_of(' ')) != '*' )//值
	{
		type = VALUE;
	}
	else
	{
		type = POINT;
	}
	return type;
}



ParamStruct::ParamStruct()
{

}

ParamStruct::~ParamStruct()
{

}

const vector< string > & ParamStruct::GetParamNames()
{
	return m_names;
}


void ParamStruct::clear()
{
	map< string, ParamValue * >::iterator map_it = m_params.begin();
	for( ; map_it != m_params.end(); map_it++ )
	{
		map_it->second->ReSetValue();
	}
}

string ParamStruct::ToString()
{
	string buffer;

	map< string, ParamValue* >::iterator map_it = m_params.begin();

	buffer += '[';
	for( ; map_it != m_params.end(); map_it++ )
	{
		buffer += "\n[";
		buffer += map_it->first;
		buffer += "(";
		buffer += map_it->second->GetValueType();
		buffer += "):";
		buffer += map_it->second->ToString();
		buffer += "]";
	}
	buffer += "\n]";

	return buffer;
}

bool ParamStruct::Insert(string name, const type_info * value_type_info)
{
	map< string, ParamValue * >::iterator map_it = m_params.find( name );
	string value;

	if( map_it == m_params.end() )
	{
		void *point = NULL;
		m_params.insert( pair< string, ParamValue* >( name, new ParamValue( value_type_info, point ) ) );
		m_names.push_back( name );
		return true;
	}
	else
	{
		ParamLog.DebugLog( "已经创建参数%s,参数不能重复创建", name.c_str() );
		return false;
	}
}


