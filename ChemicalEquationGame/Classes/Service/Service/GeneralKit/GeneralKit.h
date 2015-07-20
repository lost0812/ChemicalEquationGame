#pragma once
#include "iostream"

#define SAFE_DELETE(p){if(p){delete p;p=NULL;}}

template<class T>
class SingleTon
{
public:
  static T* m_Point;
  SingleTon();
public:
  static T* GetInstance();
  virtual ~SingleTon();
};
template<class T>
T* SingleTon<T>::m_Point = NULL;

template<class T>
SingleTon<T>::~SingleTon()
{
  SAFE_DELETE(m_Point);
}

template<class T>
T* SingleTon<T>::GetInstance()
{
  if (!m_Point)
    m_Point = new T;
  return m_Point;
}

template<class T>
SingleTon<T>::SingleTon()
{

}
#define AUTOGETSET(T, V) inline void Set##V(T set){V = set;} \
	inline T Get##V(){return V;}