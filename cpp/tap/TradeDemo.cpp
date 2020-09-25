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
		//加载失败处理。
		return -1;
	}


	//取得API的版本信息
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

	//创建API实例
	TAPIINT32 iResult = TAPIERROR_SUCCEED;
	TapAPIApplicationInfo stAppInfo;
	//授权码可填可不填，API保持了接口不变，但是不验证授权码了。
	//日志路径与之前保持一致。
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
		cout << "创建API实例失败，错误码：" << iResult <<endl;
		return -1;
	}

	//设定ITapTradeAPINotify的实现类，用于异步消息的接收
	Trade objTrade;
	pAPI->SetAPINotify(&objTrade);
	

	//启动测试，下单
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