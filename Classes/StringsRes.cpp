#include "StringsRes.h"
#include "R.h"

USING_NS_CC;

// singleton stuff
static StringRes *s_SharedStringRes = nullptr;

StringRes* StringRes::getInstance()
{
	if (!s_SharedStringRes)
	{
		s_SharedStringRes = new (std::nothrow) StringRes();
		CCASSERT(s_SharedStringRes, "FATAL: Not enough memory");
		s_SharedStringRes->init();
	}

	return s_SharedStringRes;
}

StringRes::StringRes()
{
}

StringRes::~StringRes()
{
}

bool StringRes::init()
{
	map = FileUtils::getInstance()->getValueMapFromFile(R::strings_xml);
	return true;
}

const std::string StringRes::getString(const char* key)
{
	return map.at(key).asString();
}
