#pragma once
#include "AppMacro.h"

USING_NS_CC;

class StringRes
{
public:
	static StringRes* getInstance();
	virtual ~StringRes();
	virtual bool init();
	const std::string getString(const char* key);
private:
	StringRes();
	ValueMap map;
};