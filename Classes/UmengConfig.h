#pragma once
#include "AppMacro.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#define UMENG
#endif

#ifdef UMENG
#include "Cocos2dx/Common/CCUMSocialSDK.h"
USING_NS_UM_SOCIAL;
/*
* ����ص�, �ûص�����ĳ����ĳ�Ա������ ����һ����ͨ�ĺ���, ����ʹ�òο�HelloWorldScene������
* @param platform Ҫ������Ŀ��ƽ̨
* @param stCode ������, 200�������ɹ�, 100����ʼ����
* @param errorMsg ����ʧ��ʱ�Ĵ�����Ϣ,androidƽ̨û�д�����Ϣ
*/
void umengShareCallback(int platform, int stCode, string& errorMsg);
#endif // UMENG