#include "TapTradeAPI.h"
#include "TapAPIError.h"
#include "Trade.h"
#include "TradeConfig.h"

#include <iostream>
#include <string.h>
using namespace std;

typedef ITapTradeAPI* (*TCreateTapTradeAPI)(const TapAPIApplicationInfo *appInfo, TAPIINT32 &iResult);
typedef void (*TFreeTapTradeAPI)(ITapTradeAPI *apiObj);
typedef TAPICHAR* (*TGetTapTradeAPIVersion)();
typedef int (*TSetTapTradeAPIDataPath)(const TAPICHAR *path);
typedef int (*TSetTapTradeAPILogLevel)(TAPILOGLEVEL level);

int main(int argc, char* argv[])
{
	if (NULL == G_TapTradeHandle)
	{
#ifdef __linux
		G_TapTradeHandle = dlopen("libTapTradeAPI.so", RTLD_LAZY);
#elif defined WIN32 || defined WIN64
		G_TapTradeHandle = LoadLibrary("TapTradeAPI.dll");
#endif // __linux
	}
	if (NULL == G_TapTradeHandle)
	{
		//����ʧ�ܴ���
		return -1;
	}


	//ȡ��API�İ汾��Ϣ
#ifdef __linux
	TGetTapTradeAPIVersion pFun = (TGetTapTradeAPIVersion)dlsym(G_TapTradeHandle, "GetTapTradeAPIVersion");
	if (NULL == dlerror())
		cout << pFun() << endl;
#elif defined WIN32 || defined WIN64
	TGetTapTradeAPIVersion pFun = (TGetTapTradeAPIVersion)GetProcAddress(G_TapTradeHandle, "GetTapTradeAPIVersion");
	if (NULL != pFun)
		cout << pFun() << endl;
#endif // __linux
	//cout << GetTapTradeAPIVersion() << endl;

#ifdef __linux
	TSetTapTradeAPIDataPath pFunSetPath = (TSetTapTradeAPIDataPath)dlsym(G_TapTradeHandle, "SetTapTradeAPIDataPath");
	if (NULL == dlerror())
	{
		int pathret = pFunSetPath(DEFAULT_KEYPATH);
		if (pathret != 0)
			return -1;
	}
#elif defined WIN32 || defined WIN64
	TSetTapTradeAPIDataPath pFunSetPath = (TSetTapTradeAPIDataPath)GetProcAddress(G_TapTradeHandle, "SetTapTradeAPIDataPath");
	if (NULL != pFunSetPath)
	{
		int pathret = pFunSetPath(DEFAULT_KEYPATH);
		if (pathret != 0)
			return -1;
	}
#endif // __linux

#ifdef __linux
	TSetTapTradeAPILogLevel pFunSetLevel = (TSetTapTradeAPILogLevel)dlsym(G_TapTradeHandle, "SetTapTradeAPILogLevel");
	if (NULL == dlerror())
	{ 
		int levelret = pFunSetLevel(APILOGLEVEL_DEBUG);
		if (levelret != 0)
			return -1;
	}
#elif defined WIN32 || defined WIN64
	TSetTapTradeAPILogLevel pFunSetLevel = (TSetTapTradeAPILogLevel)GetProcAddress(G_TapTradeHandle, "SetTapTradeAPILogLevel");
	if (NULL != pFunSetLevel)
	{ 
		int levelret = pFunSetLevel(APILOGLEVEL_DEBUG);
		if (levelret != 0)
			return -1;
	}
#endif // __linux

	//����APIʵ��
	TAPIINT32 iResult = TAPIERROR_SUCCEED;
	TapAPIApplicationInfo stAppInfo;
	//��Ȩ�����ɲ��API�����˽ӿڲ��䣬���ǲ���֤��Ȩ���ˡ�
	//��־·����֮ǰ����һ�¡�
	//strcpy(stAppInfo.AuthCode, DEFAULT_AUTHCODEDEMO);
	strcpy(stAppInfo.KeyOperationLogPath, DEFAULT_KEYPATH);

	ITapTradeAPI *pAPI = NULL;

#ifdef __linux
	TCreateTapTradeAPI pFunCreate = (TCreateTapTradeAPI)dlsym(G_TapTradeHandle, "CreateTapTradeAPI");
	if(NULL==dlerror())
		pAPI = pFunCreate(&stAppInfo, iResult);
#elif defined WIN32 || defined WIN64
	TCreateTapTradeAPI pFunCreate = (TCreateTapTradeAPI)GetProcAddress(G_TapTradeHandle, "CreateTapTradeAPI");
	if(NULL!=pFunCreate)
		pAPI = pFunCreate(&stAppInfo, iResult);
#endif // __linux


	//ITapTradeAPI *pAPI = CreateTapTradeAPI(&stAppInfo, iResult);
	if (NULL == pAPI){
		cout << "����APIʵ��ʧ�ܣ������룺" << iResult <<endl;
		return -1;
	}

	//�趨ITapTradeAPINotify��ʵ���࣬�����첽��Ϣ�Ľ���
	Trade objTrade;
	pAPI->SetAPINotify(&objTrade);
	

	//�������ԣ��µ�
	objTrade.SetAPI(pAPI);
	int n = objTrade.RunTest();
	

	objTrade.RunFormerFuncs();

	objTrade.RunInsertFuncs();

	objTrade.RunNewFuncs();

	//objTrade.InsertDCEOptionOrder();

	//objTrade.OptionCUAction();

	
	while (true)
	{
#ifdef linux
		sleep(1);
#elif defined WIN32
		Sleep(1000);
#endif // linux

		
	}

	return 0;
}