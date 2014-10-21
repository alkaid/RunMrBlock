#include "UmengConfig.h"

#ifdef UMENG
USING_NS_UM_SOCIAL;
/*
* 分享回调, 该回调不是某个类的成员函数， 而是一个普通的函数, 具体使用参考HelloWorldScene的例子
* @param platform 要分享到的目标平台
* @param stCode 返回码, 200代表分享成功, 100代表开始分享
* @param errorMsg 分享失败时的错误信息,android平台没有错误信息
*/
void umengShareCallback(int platform, int stCode, string& errorMsg)
{
	if (stCode == 100)
	{
		log("#### HelloWorld 开始分享");
	}
	else if (stCode == 200)
	{
		log("#### HelloWorld 分享成功");
	}
	else
	{
		log("#### HelloWorld 分享出错");
	}

	log("platform num is : %d.", platform);
}
#endif // UMENG