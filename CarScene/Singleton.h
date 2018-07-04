
#pragma once

using namespace std;

template <class T>

//Singleton class
class Singleton
{

public:

	static T* Instance();

private:

	Singleton();
	Singleton(const Singleton&);
};



template <class T> T* Singleton<T>::Instance()
{
	static T* singletonObject = new T();
	return singletonObject;

}