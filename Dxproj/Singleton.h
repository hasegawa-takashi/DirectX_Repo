#pragma once

// https://qiita.com/narumi_/items/b205e59e7fc81695f380


template <typename T>
class CSingleton
{
public:
	static inline T& Getintance()
	{
		static T _instance;
		return _instance;
	}

protected:
	CSingleton() {}
	virtual ~CSingleton() 
	{
		int _a = 0;
	}

private:
	void operator = (const CSingleton& obj) {}
	CSingleton(const CSingleton &obj) {}

};
