#include "UmengConfig.h"

#ifdef UMENG
USING_NS_UM_SOCIAL;
/*
* ����ص�, �ûص�����ĳ����ĳ�Ա������ ����һ����ͨ�ĺ���, ����ʹ�òο�HelloWorldScene������
* @param platform Ҫ������Ŀ��ƽ̨
* @param stCode ������, 200�������ɹ�, 100����ʼ����
* @param errorMsg ����ʧ��ʱ�Ĵ�����Ϣ,androidƽ̨û�д�����Ϣ
*/
void umengShareCallback(int platform, int stCode, string& errorMsg)
{
	if (stCode == 100)
	{
		log("#### HelloWorld ��ʼ����");
	}
	else if (stCode == 200)
	{
		log("#### HelloWorld ����ɹ�");
	}
	else
	{
		log("#### HelloWorld �������");
	}

	log("platform num is : %d.", platform);
}
#endif // UMENG