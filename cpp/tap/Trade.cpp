#include "Trade.h"
#include "TapAPIError.h"
#include <iostream>
#include <string.h>

#ifdef __linux
void* G_TapTradeHandle(NULL);
void* G_TapDataCollectHandle(NULL);
#elif defined WIN32 || defined WIN64
HMODULE G_TapTradeHandle(NULL);
HMODULE G_TapDataCollectHandle(NULL);
#endif

using namespace std;

typedef int(*Tesunny_getsysteminfo)(char* pSystemInfo, int* nLen, int* nVer);

Trade::Trade(void):
	m_pAPI(NULL),
	m_bIsAPIReady(false)
{
	if (NULL == G_TapDataCollectHandle)
	{
#ifdef __linux
		G_TapDataCollectHandle = dlopen("libTapDataCollectAPI.so", RTLD_LAZY);
#elif defined WIN32 || defined WIN64
		G_TapDataCollectHandle = LoadLibrary("TapDataCollectAPI.dll");
#endif // __linux
	}
	if (NULL == G_TapDataCollectHandle)
	{
		//加载失败处理。
	}
}


Trade::~Trade(void)
{
	if (NULL != G_TapTradeHandle)
	{
#ifdef __linux
		dlclose(G_TapTradeHandle);
#elif defined WIN32 || defined WIN64
		FreeLibrary(G_TapTradeHandle);
#endif // __linux

		G_TapTradeHandle = NULL;
	}

	if (NULL != G_TapDataCollectHandle)
	{
#ifdef __linux
		dlclose(G_TapDataCollectHandle);
#elif defined WIN32 || defined WIN64
		FreeLibrary(G_TapDataCollectHandle);
#endif // __linux

		G_TapDataCollectHandle = NULL;
	}
}


void Trade::SetAPI(ITapTradeAPI *pAPI)
{
	m_pAPI = pAPI;
}

void Trade::QryAccount()
{
	m_uiSessionID = 0;
	TapAPIAccQryReq qryReq;
	memset(&qryReq, 0, sizeof(TapAPIAccQryReq));

	APIStrncpy(qryReq.AccountNo, "");

	int iErr = m_pAPI->QryAccount(&m_uiSessionID, &qryReq);
	if (iErr != 0)
	{
		cout << "QryAccount Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::QryFund()
{
	m_uiSessionID = 0;
	TapAPIFundReq qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	int iErr = m_pAPI->QryFund(&m_uiSessionID, &qryReq);
	if (iErr != 0)
	{
		cout << "QryFund Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::QryExchange()
{
	m_uiSessionID = 0;

	int iErr = m_pAPI->QryExchange(&m_uiSessionID);
	if (iErr != 0)
	{
		cout << "QryExchange Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::QryCommodity()
{
	m_uiSessionID = 0;

	int iErr = m_pAPI->QryCommodity(&m_uiSessionID);
	if (iErr != 0)
	{
		cout << "QryCommodity Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::QryContract()
{
	m_uiSessionID = 0;
	TapAPICommodity qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	strcpy(qryReq.ExchangeNo, "ZCE");
	qryReq.CommodityType = TAPI_COMMODITY_TYPE_SPREAD_MONTH;
	int iErr = m_pAPI->QryContract(&m_uiSessionID, &qryReq);
	if (iErr != 0)
	{
		cout << "QryContract Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::QryDeepQuote()
{
	m_uiSessionID = 0;
	TapAPIContract qryReq;
	memset(&qryReq, 0, sizeof(TapAPIContract));

	strcpy(qryReq.Commodity.ExchangeNo, "SHFE");
	qryReq.Commodity.CommodityType = 'F';
	strcpy(qryReq.Commodity.CommodityNo, "CU");

	strcpy(qryReq.ContractNo1, "1703");
	qryReq.CallOrPutFlag1 = 'N';
	qryReq.CallOrPutFlag2 = 'N';

	int iErr = m_pAPI->QryDeepQuote(&m_uiSessionID, &qryReq);
	if (iErr != 0)
	{
		cout << "QryDeepQuote Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::QryFill()
{
	m_uiSessionID = 0;
	TapAPIFillQryReq qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	qryReq.StreamID = 0;
	int iErr = m_pAPI->QryFill(&m_uiSessionID, &qryReq);
	if (iErr != 0)
	{
		cout << "QryFill Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::QryOrder()
{
	m_uiSessionID = 0;
	TapAPIOrderQryReq APIOrderQryReq;
	memset(&APIOrderQryReq, 0, sizeof(APIOrderQryReq));
	APIOrderQryReq.OrderQryType = TAPI_ORDER_QRY_TYPE_UNENDED;
	int iErr = m_pAPI->QryOrder(&m_uiSessionID, &APIOrderQryReq);
	if (iErr != 0)
	{
		cout << "QryOrder Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::QryPosition()
{
	m_uiSessionID = 0;
	TapAPIPositionQryReq qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	//strcpy(qryReq.AccountNo, "1002");
	int iErr = m_pAPI->QryPosition(&m_uiSessionID, &qryReq);
	if (iErr != 0)
	{
		cout << "QryPosition Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::QryClose()
{
	m_uiSessionID = 0;
	TapAPICloseQryReq qryReq;
	memset(&qryReq, 0, sizeof(qryReq));

	int iErr = m_pAPI->QryClose(&m_uiSessionID, &qryReq);
	if (iErr != 0)
	{
		cout << "QryClose Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::QryExchangeState()
{
	m_uiSessionID = 0;
	TapAPIExchangeStateInfoQryReq qryReq;
	memset(&qryReq, 0, sizeof(qryReq));

	int iErr = m_pAPI->QryExchangeStateInfo(&m_uiSessionID, &qryReq);
	if (iErr != 0)
	{
		cout << "QryExchangeStateInfo Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::QryUpperChannel()
{
	m_uiSessionID = 0;
	TapAPIUpperChannelQryReq qryReq;
	memset(&qryReq, 0, sizeof(qryReq));

	int iErr = m_pAPI->QryUpperChannel(&m_uiSessionID, &qryReq);
	if (iErr != 0)
	{
		cout << "QryUpperChannel Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::QryAccountRent()
{
	m_uiSessionID = 0;
	TapAPIAccountRentQryReq APIAccountRentQryReq;
	memset(&APIAccountRentQryReq, 0, sizeof(APIAccountRentQryReq));
	strcpy(APIAccountRentQryReq.AccountNo, DEFAULT_ACCOUNT_NO);
	//strcpy(APIAccountRentQryReq.ExchangeNo, "ZCE");
	//strcpy(APIAccountRentQryReq.CommodityNo, "SR");
	int iErr = m_pAPI->QryAccountRent(&m_uiSessionID, &APIAccountRentQryReq);
	if (iErr != 0)
	{
		cout << "QryAccountRent Error:" << iErr << endl;
		return;
	}

	m_FormerEvent.WaitEvent();
}

void Trade::OptionCUAction()
{
	TAPIINT32 iErr = TAPIERROR_SUCCEED;

	//下单
	TapAPINewOrder stNewOrder;
	memset(&stNewOrder, 0, sizeof(stNewOrder));

	strcpy(stNewOrder.AccountNo, DEFAULT_ACCOUNT_NO);
	strcpy(stNewOrder.ExchangeNo, DEFAULT_EXCHANGE_NO);
	stNewOrder.CommodityType = DEFAULT_COMMODITY_TYPE;
	strcpy(stNewOrder.CommodityNo, DEFAULT_COMMODITY_NO);
	strcpy(stNewOrder.ContractNo, DEFAULT_CONTRACT_NO);
	strcpy(stNewOrder.StrikePrice, DEFAULT_STRIKE_PRICE);
	stNewOrder.CallOrPutFlag = TAPI_CALLPUT_FLAG_CALL;
	strcpy(stNewOrder.ContractNo2, "");
	strcpy(stNewOrder.StrikePrice2, "");
	stNewOrder.CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE;
	stNewOrder.OrderType = TAPI_ORDER_TYPE_FUTURE_AUTO_CLOSE;
	stNewOrder.OrderSource = TAPI_ORDER_SOURCE_ESUNNY_API;
	stNewOrder.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	strcpy(stNewOrder.ExpireTime, "");
	stNewOrder.IsRiskOrder = APIYNFLAG_NO;

	stNewOrder.OrderSide = TAPI_SIDE_NONE;

	stNewOrder.PositionEffect = DEFAULT_POSITION_EFFECT;
	stNewOrder.PositionEffect2 = TAPI_PositionEffect_NONE;
	strcpy(stNewOrder.InquiryNo, "");
	stNewOrder.HedgeFlag = TAPI_HEDGEFLAG_T;
	stNewOrder.OrderPrice = DEFAULT_ORDER_PRICE;
	stNewOrder.OrderPrice2;
	stNewOrder.StopPrice;
	stNewOrder.OrderQty = 1;
	stNewOrder.OrderMinQty;
	stNewOrder.MinClipSize;
	stNewOrder.MaxClipSize;
	stNewOrder.RefInt = 3;
	stNewOrder.RefString;
	stNewOrder.TacticsType = TAPI_TACTICS_TYPE_NONE;
	stNewOrder.TriggerCondition = TAPI_TRIGGER_CONDITION_NONE;
	stNewOrder.TriggerPriceType = TAPI_TRIGGER_PRICE_NONE;
	stNewOrder.AddOneIsValid = APIYNFLAG_NO;
	stNewOrder.OrderQty2;
	stNewOrder.HedgeFlag2 = TAPI_HEDGEFLAG_NONE;
	stNewOrder.MarketLevel = TAPI_MARKET_LEVEL_0;
	stNewOrder.FutureAutoCloseFlag = APIYNFLAG_NO; // V9.0.2.0 20150520

	m_uiSessionID = 0;
	iErr = m_pAPI->InsertOrder(&m_uiSessionID, &stNewOrder);

	if (TAPIERROR_SUCCEED != iErr) {
		cout << "InsertOrder Error:" << iErr << endl;
		return;
	}
}

int Trade::RunTest()
{
	if(NULL == m_pAPI) {
		cout << "Error: m_pAPI is NULL." << endl;
		return -1;
	}

	TAPIINT32 iErr = TAPIERROR_SUCCEED;


	//设定服务器IP、端口
	iErr = m_pAPI->SetHostAddress(DEFAULT_IP, DEFAULT_PORT);
	if(TAPIERROR_SUCCEED != iErr) {
		cout << "SetHostAddress Error:" << iErr <<endl;
		return iErr;
	}

	//登录服务器
	TapAPITradeLoginAuth stLoginAuth;
	memset(&stLoginAuth, 0, sizeof(stLoginAuth));
	strcpy(stLoginAuth.UserNo, DEFAULT_USERNAME);
	strcpy(stLoginAuth.Password, DEFAULT_PASSWORD);

	//新增两个字段，用户客户授权管理。
	//这两个字段都有后台配置。
	APIStrncpy(stLoginAuth.AuthCode, "esunny_gathertradeapi");
	APIStrncpy(stLoginAuth.AppID, "esunny_tradeapi_9.0.3.12");

	stLoginAuth.ISModifyPassword = APIYNFLAG_NO;
	stLoginAuth.ISDDA = APIYNFLAG_NO;
	iErr = m_pAPI->Login(&stLoginAuth);
	if(TAPIERROR_SUCCEED != iErr) {
		cout << "Login Error:" << iErr <<endl;
		return iErr;
	}
	
	//等待APIReady
	m_Event.WaitEvent();
	if (!m_bIsAPIReady){
		return -1;
	}

	return 0;
}

void TAP_CDECL Trade::OnConnect()
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspLogin( TAPIINT32 errorCode, const TapAPITradeLoginRspInfo *loginRspInfo )
{
	if(TAPIERROR_SUCCEED == errorCode) {
		cout << "登录成功，等待API初始化..." << endl;

	} else {
		cout << "登录失败，错误码:" << errorCode << endl;
		m_Event.SignalEvent();	
	}
}

void TAP_CDECL Trade::OnAPIReady()
{
	cout << "API初始化完成" << endl;
	m_bIsAPIReady = true;
	m_Event.SignalEvent();	
}

void TAP_CDECL Trade::OnDisconnect( TAPIINT32 reasonCode )
{
	cout << "API断开,断开原因:"<<reasonCode << endl;
}

void TAP_CDECL Trade::OnRspChangePassword( TAPIUINT32 sessionID, TAPIINT32 errorCode )
{
	//cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspSetReservedInfo( TAPIUINT32 sessionID, TAPIINT32 errorCode, const TAPISTR_50 info )
{
	//cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQryAccount( TAPIUINT32 sessionID, TAPIUINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountInfo *info )
{
	if (info)
		cout << info->AccountNo << "," << info->AccountType << "," << info->AccountState << "," << info->AccountShortName << endl;

	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRspQryFund( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFundData *info )
{
	if(info)
		cout << info->AccountNo << "," << info->FloatingPL << endl;

	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRtnFund( const TapAPIFundData *info )
{
	//cout << __FUNCTION__ << " is called." << endl;
	//cout << info->AccountNo << "," << info->FloatingPL << endl;
}

void TAP_CDECL Trade::OnRspQryExchange( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIExchangeInfo *info )
{
	if (info)
		cout << info->ExchangeNo << "," << info->ExchangeName << endl;

	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRspQryCommodity( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICommodityInfo *info )
{
	if (info)
		cout << info->ExchangeNo << "," << info->CommodityType << "," << info->CommodityNo << endl;

	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRspQryContract( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPITradeContractInfo *info )
{
	if(info)
		cout << info->ExchangeNo << "," << info->CommodityType << "," << info->CommodityNo << "," << info->ContractNo1 << "/" << info->ContractNo2 << endl;

	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRtnContract( const TapAPITradeContractInfo *info )
{
//	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRtnOrder( const TapAPIOrderInfoNotice *info )
{
	if(NULL == info){
		return;
	}

	if (info->ErrorCode != 0) {
		cout << "服务器返回了一个关于委托信息的错误：" << info->ErrorCode << endl;
	} else {
		if (info->OrderInfo) {
			
			if (0 != info->OrderInfo->ErrorCode)
			{
				cout << "报单失败，"
					<< "错误码:" << info->OrderInfo->ErrorCode << ",SessionID:" << info->SessionID << ",RefInt" << info->OrderInfo->RefInt << ","
					<< "委托编号:" << info->OrderInfo->OrderNo
					<< endl;
			}
			else
			{
				cout << "报单成功，"
					<< "状态:" << info->OrderInfo->OrderState << ",SessionID:" << info->SessionID << ",RefInt" << info->OrderInfo->RefInt << ","
					<< "委托编号:" << info->OrderInfo->OrderNo << ",OrderQty:" << info->OrderInfo->OrderQty << ",CancleQty:" << info->OrderInfo->OrderCanceledQty
					<< ",MatchQty:" << info->OrderInfo->OrderMatchQty << ",OrderSystemNo:" << info->OrderInfo->OrderSystemNo
					<< endl;
			}
		}
	}
}

void TAP_CDECL Trade::OnRspOrderAction( TAPIUINT32 sessionID, TAPIUINT32 errorCode, const TapAPIOrderActionRsp *info )
{
	//cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQryOrder( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info )
{
	if (info != NULL)
	{
		cout << info->AccountNo << "," << info->CommodityNo << "," << info->ContractNo <<"," << info->OrderState << endl;
	}

	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRspQryOrderProcess( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQryFill(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFillInfo *info)
{
	if (info)
		cout << info->AccountNo << " ," << info->ExchangeNo << " ," << info->CommodityNo << " ," << info->MatchStreamID << endl;

	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRtnFill( const TapAPIFillInfo *info )
{
	//cout << __FUNCTION__ << " is called." << endl;
	//cout << info->ExchangeMatchNo << "," << info->MatchNo << "," << endl;
}

void TAP_CDECL Trade::OnRspQryPosition( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionInfo *info )
{
	if (info)
		cout << info->AccountNo << info->ExchangeNo << info->CommodityType << info->CommodityNo << info->ContractNo << info->PositionNo << endl;

	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRtnPosition( const TapAPIPositionInfo *info )
{
//	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQryClose( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICloseInfo *info )
{
	if (info)
		cout << info->AccountNo << "," << info->ExchangeNo << "," << info->CommodityNo << ","
		<< info->ContractNo << "," << info->OpenOrderNo << "," << info->CloseOrderNo << endl;

	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRtnClose( const TapAPICloseInfo *info )
{
//	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRtnPositionProfit( const TapAPIPositionProfitNotice *info )
{
//	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQryDeepQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIDeepQuoteQryRsp *info)
{
	if (info)
		cout << info->Contract.Commodity.ExchangeNo << "," << info->Contract.Commodity.CommodityNo << "," << info->DeepQuote.Side << "," << info->DeepQuote.Qty << "," << info->DeepQuote.Price << endl;
	
	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRspQryExchangeStateInfo(TAPIUINT32 sessionID,TAPIINT32 errorCode, TAPIYNFLAG isLast,const TapAPIExchangeStateInfo * info)
{
	if (info)
		cout << info->ExchangeNo << "," << info->CommodityType << "," << info->CommodityNo << endl;

	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRtnExchangeStateInfo(const TapAPIExchangeStateInfoNotice * info)
{
	cout << __FUNCTION__ << " is called." << endl;
	cout << info->ExchangeStateInfo.ExchangeNo << "," << info->ExchangeStateInfo.CommodityType << "," << info->ExchangeStateInfo.CommodityNo << endl;
}

void TAP_CDECL Trade::OnRtnReqQuoteNotice(const TapAPIReqQuoteNotice *info)
{
	if (info)
	{
		cout << __FUNCTION__ << " is called." << info->ContractNo << info->CallOrPutFlag << info->StrikePrice << " " << info->InquiryNo << endl;
	}
}

void TAP_CDECL Trade::OnRspUpperChannelInfo(TAPIUINT32 sessionID,TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIUpperChannelInfo * info)
{
	if (info)
		cout << info->UpperChannelNo << "," << info->UpperNo << "," << info->UpperUserNo << endl;

	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRspAccountRentInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountRentInfo * info)
{
	if (info)
		cout << info->AccountNo << "," << info->ExchangeNo << "," << info->CommodityType << "," << info->CommodityNo
		<< "," << info->ContractNo << endl;

	if(isLast == 'Y')
	{
		cout << __FUNCTION__ << " is done." << endl;
		m_FormerEvent.SignalEvent();
	}
}

void TAP_CDECL Trade::OnRspSubmitUserLoginInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPISubmitUserLoginRspInfo * info)
{
	if (isLast == 'Y')
	{
		if (info)
			cout << info->UserNo << "," << info->ErrorCode << "," << info->ErrorText << endl;
	}
}

bool Trade::InsertOrderS(const InsertOrderStruct* InOrder)
{
	if (!m_bIsAPIReady) { return false; }
	TapAPINewOrder stNewOrder;
	memset(&stNewOrder, 0, sizeof(stNewOrder));
	APIStrncpy(stNewOrder.AccountNo, DEFAULT_ACCOUNT_NO);
	APIStrncpy(stNewOrder.ExchangeNo, InOrder->ExchangeNo);
	stNewOrder.CommodityType = InOrder->CommodityType;
	APIStrncpy(stNewOrder.CommodityNo, InOrder->CommodityNo);

	APIStrncpy(stNewOrder.ContractNo, InOrder->ContractNo);
	APIStrncpy(stNewOrder.StrikePrice, InOrder->StrikePrice);
	stNewOrder.CallOrPutFlag = InOrder->CallOrPutFlag;
	APIStrncpy(stNewOrder.ContractNo2, InOrder->ContractNo2);
	APIStrncpy(stNewOrder.StrikePrice2, InOrder->StrikePrice2);
	stNewOrder.CallOrPutFlag2 = InOrder->CallOrPutFlag2;

	stNewOrder.OrderType = InOrder->OrderType;		
	stNewOrder.OrderSource = TAPI_ORDER_SOURCE_ESUNNY_API;
	stNewOrder.TimeInForce = InOrder->TimeInForce;
	APIStrncpy(stNewOrder.ExpireTime, "");
	stNewOrder.IsRiskOrder = APIYNFLAG_NO;
	stNewOrder.OrderSide = InOrder->OrderSide;
	stNewOrder.PositionEffect = InOrder->PositionEffect;
	stNewOrder.PositionEffect2 = InOrder->PositionEffect2;
	APIStrncpy(stNewOrder.InquiryNo, "");
	stNewOrder.HedgeFlag = TAPI_HEDGEFLAG_T;
	stNewOrder.OrderPrice = InOrder->OrderPrice; 	
	stNewOrder.OrderPrice2 = InOrder->OrderPrice2;
	stNewOrder.StopPrice = InOrder->StopPrice;
	stNewOrder.OrderQty = InOrder->OrderQty;//  DEFAULT_ORDER_QTY-----1手;			
	stNewOrder.OrderMinQty;
	stNewOrder.MinClipSize;
	stNewOrder.MaxClipSize;
	stNewOrder.RefInt = InOrder->RefInt;
	stNewOrder.RefString;
	stNewOrder.TacticsType = TAPI_TACTICS_TYPE_NONE;
	stNewOrder.TriggerCondition = TAPI_TRIGGER_CONDITION_NONE;
	stNewOrder.TriggerPriceType = TAPI_TRIGGER_PRICE_NONE;
	stNewOrder.AddOneIsValid = APIYNFLAG_NO;
	stNewOrder.OrderQty2 = InOrder->OrderQty2;
	stNewOrder.HedgeFlag2 = TAPI_HEDGEFLAG_NONE;
	stNewOrder.MarketLevel = TAPI_MARKET_LEVEL_0;
	stNewOrder.FutureAutoCloseFlag = APIYNFLAG_NO; // V9.0.2.0 20150520
	/////////////////////////////////////////////////////////////////////////////////

	int iErr = m_pAPI->InsertOrder(&m_uiSessionID, &stNewOrder);
	if (TAPIERROR_SUCCEED != iErr) { return false; }
	else { return true; }
}

void Trade::InsertDCEOptionOrder()
{
	if (!m_bIsAPIReady){ return; }
	TapAPINewOrder stNewOrder;
	memset(&stNewOrder, 0, sizeof(stNewOrder));
	strcpy(stNewOrder.AccountNo, DEFAULT_ACCOUNT_NO);
	strcpy(stNewOrder.ExchangeNo, DEFAULT_EXCHANGE_NO);
	stNewOrder.CommodityType = DEFAULT_COMMODITY_TYPE;
	strcpy(stNewOrder.CommodityNo, DEFAULT_COMMODITY_NO);
	strcpy(stNewOrder.ContractNo, DEFAULT_CONTRACT_NO);
	strcpy(stNewOrder.StrikePrice, DEFAULT_STRIKE_PRICE);
	stNewOrder.CallOrPutFlag = DEFAULT_CALLORPUTFLAG;
	strcpy(stNewOrder.ContractNo2, "");
	strcpy(stNewOrder.StrikePrice2, "");
	stNewOrder.CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE;

	stNewOrder.OrderType = DEFAULT_ORDER_TYPE;		
	stNewOrder.OrderSource = TAPI_ORDER_SOURCE_ESUNNY_API;
	stNewOrder.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	strcpy(stNewOrder.ExpireTime, "");
	stNewOrder.IsRiskOrder = APIYNFLAG_NO;
	stNewOrder.OrderSide = DEFAULT_ORDER_SIDE;				
	stNewOrder.PositionEffect = DEFAULT_POSITION_EFFECT;  //开仓  TAPI_PositionEffect_COVER--平仓 TAPI_PositionEffect_COVER_TODAY-平今仓
	stNewOrder.PositionEffect2 = TAPI_PositionEffect_NONE;
	strcpy(stNewOrder.InquiryNo, "");
	stNewOrder.HedgeFlag = TAPI_HEDGEFLAG_T;
	stNewOrder.OrderPrice = DEFAULT_ORDER_PRICE;  //DEFAULT_ORDER_PRICE---市价单;		
	stNewOrder.OrderPrice2;
	stNewOrder.StopPrice;
	stNewOrder.OrderQty = DEFAULT_ORDER_QTY;//  DEFAULT_ORDER_QTY-----1手;			
	stNewOrder.OrderMinQty;
	stNewOrder.MinClipSize;
	stNewOrder.MaxClipSize;
	stNewOrder.RefInt;
	stNewOrder.RefString;
	stNewOrder.TacticsType = TAPI_TACTICS_TYPE_NONE;
	stNewOrder.TriggerCondition = TAPI_TRIGGER_CONDITION_NONE;
	stNewOrder.TriggerPriceType = TAPI_TRIGGER_PRICE_NONE;
	stNewOrder.AddOneIsValid = APIYNFLAG_NO;
	stNewOrder.OrderQty2;
	stNewOrder.HedgeFlag2 = TAPI_HEDGEFLAG_NONE;
	stNewOrder.MarketLevel = TAPI_MARKET_LEVEL_0;
	stNewOrder.FutureAutoCloseFlag = APIYNFLAG_NO; // V9.0.2.0 20150520
	/////////////////////////////////////////////////////////////////////////////////

	int iErr = m_pAPI->InsertOrder(&m_uiSessionID, &stNewOrder);
	if (TAPIERROR_SUCCEED != iErr) { return; }
	else { return; }
}


void Trade::RunFormerFuncs()
{
	cout << "QryAccount" << endl;
	QryAccount();

	cout << "QryFund" << endl;
	QryFund();

	cout << "QryExchange" << endl;
	QryExchange();

	cout << "QryCommodity" << endl;
	QryCommodity();

	cout << "QryContract" << endl;
	QryContract();

	cout << "QryOrder" << endl;
	QryOrder();

	cout << "QryFill" << endl;
	QryFill();

	cout << "QryPosition" << endl;
	QryPosition();

	cout << "QryClose" << endl;
	QryClose();

	cout << "QryDeepQuote" << endl;
	QryDeepQuote();

	cout << "QryExchangeState" << endl;
	QryExchangeState();

	cout << "QryUpperChannel" << endl;
	QryUpperChannel();

	cout << "QryAccountRent" << endl;
	QryAccountRent();
}

void Trade::RunZCEFuture()
{
	cout << "郑商所期货限价：" << endl;
	InsertOrderStruct ZCEFuture;
	memset(&ZCEFuture, 0, sizeof(ZCEFuture));
	APIStrncpy(ZCEFuture.ExchangeNo, "ZCE");
	ZCEFuture.CommodityType = 'F';
	APIStrncpy(ZCEFuture.CommodityNo, "SR");
	APIStrncpy(ZCEFuture.ContractNo, "905");
	ZCEFuture.CallOrPutFlag = 'N';
	ZCEFuture.CallOrPutFlag2 = 'N';
	ZCEFuture.OrderType = TAPI_ORDER_TYPE_LIMIT;
	ZCEFuture.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	ZCEFuture.OrderSide = 'B';
	ZCEFuture.PositionEffect = TAPI_PositionEffect_OPEN;
	ZCEFuture.PositionEffect2 = 'N';
	ZCEFuture.OrderPrice = 4920;
	ZCEFuture.OrderQty = 1;
	ZCEFuture.RefInt = 1;
	ZCEFuture.FutureAutoCloseFlag = 'N';

	InsertOrderS(&ZCEFuture);
	APISleep(2);

	cout << "郑商所期货限价FAK：" << endl;
	ZCEFuture.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	ZCEFuture.RefInt = 2;
	InsertOrderS(&ZCEFuture);
	APISleep(2);

	cout << "郑商所期货限价FOK：" << endl;
	ZCEFuture.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	ZCEFuture.RefInt = 3;
	InsertOrderS(&ZCEFuture);
	APISleep(2);

	cout << "郑商所期货市价：" << endl;
	ZCEFuture.OrderType = TAPI_ORDER_TYPE_MARKET;
	ZCEFuture.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	ZCEFuture.OrderPrice = 0;
	ZCEFuture.RefInt = 4;
	InsertOrderS(&ZCEFuture);
	APISleep(2);

	cout << "郑商所期货市价FAK：" << endl;
	ZCEFuture.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	ZCEFuture.RefInt = 5;
	InsertOrderS(&ZCEFuture);
	APISleep(2);

	cout << "郑商所期货市价FOK：" << endl;
	ZCEFuture.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	ZCEFuture.RefInt = 6;
	InsertOrderS(&ZCEFuture);
	APISleep(2);
}

void Trade::RunZCESPREADMONTH()
{
	cout << "郑商所跨期限价：" << endl;
	InsertOrderStruct ZCEMonth;
	memset(&ZCEMonth, 0, sizeof(ZCEMonth));
	APIStrncpy(ZCEMonth.ExchangeNo, "ZCE");
	ZCEMonth.CommodityType = TAPI_COMMODITY_TYPE_SPREAD_MONTH;
	APIStrncpy(ZCEMonth.CommodityNo, "SR");
	APIStrncpy(ZCEMonth.ContractNo, "905");
	APIStrncpy(ZCEMonth.ContractNo2, "909");
	ZCEMonth.CallOrPutFlag = 'N';
	ZCEMonth.CallOrPutFlag2 = 'N';
	ZCEMonth.OrderType = TAPI_ORDER_TYPE_LIMIT;
	ZCEMonth.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	ZCEMonth.OrderSide = 'B';
	ZCEMonth.PositionEffect = TAPI_PositionEffect_OPEN;
	ZCEMonth.PositionEffect2 = 'N';
	ZCEMonth.OrderPrice = -10;
	ZCEMonth.OrderQty = 1;
	ZCEMonth.RefInt = 11;
	ZCEMonth.FutureAutoCloseFlag = 'N';

	InsertOrderS(&ZCEMonth);
	APISleep(2);

	cout << "郑商所跨期限价FAK：" << endl;
	ZCEMonth.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	ZCEMonth.RefInt = 12;
	//InsertOrderS(&ZCEMonth);
	APISleep(2);


	/*
	郑商所不支持FOK
	cout << "郑商所跨期限价FOK：" << endl;
	ZCEMonth.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	ZCEMonth.RefInt = 13;
	InsertOrderS(&ZCEMonth);
	APISleep(2);*/

	/*
	郑商所组合合约不支持市价单。
	cout << "郑商所跨期市价：" << endl;
	ZCEMonth.OrderType = TAPI_ORDER_TYPE_MARKET;
	ZCEMonth.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	ZCEMonth.OrderPrice = 0;
	ZCEMonth.RefInt = 14;
	InsertOrderS(&ZCEMonth);
	APISleep(2);

	cout << "郑商所跨期市价FAK：" << endl;
	ZCEMonth.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	ZCEMonth.RefInt = 15;
	InsertOrderS(&ZCEMonth);
	APISleep(2);

	cout << "郑商所跨期市价FOK：" << endl;
	ZCEMonth.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	ZCEMonth.RefInt = 16;
	InsertOrderS(&ZCEMonth);
	APISleep(2);*/
}

void Trade::RunZCEOption()
{
	cout << "郑商所期权限价：" << endl;
	InsertOrderStruct ZCEOption;
	memset(&ZCEOption, 0, sizeof(InsertOrderStruct));
	APIStrncpy(ZCEOption.ExchangeNo, "ZCE");
	ZCEOption.CommodityType = TAPI_COMMODITY_TYPE_OPTION;
	APIStrncpy(ZCEOption.CommodityNo, "SR");
	APIStrncpy(ZCEOption.ContractNo, "905");
	ZCEOption.CallOrPutFlag = 'C';
	APIStrncpy(ZCEOption.StrikePrice, "4200");
	ZCEOption.CallOrPutFlag2 = 'N';
	ZCEOption.OrderType = TAPI_ORDER_TYPE_LIMIT;
	ZCEOption.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	ZCEOption.OrderSide = 'B';
	ZCEOption.PositionEffect = TAPI_PositionEffect_OPEN;
	ZCEOption.PositionEffect2 = 'N';
	ZCEOption.OrderPrice = 780;
	ZCEOption.OrderQty = 1;
	ZCEOption.RefInt = 21;
	ZCEOption.FutureAutoCloseFlag = 'N';

	InsertOrderS(&ZCEOption);
	APISleep(2);

	cout << "郑商所期权限价FAK：" << endl;
	ZCEOption.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	ZCEOption.RefInt = 22;
	InsertOrderS(&ZCEOption);
	APISleep(2);

	cout << "郑商所期权限价FOK：" << endl;
	ZCEOption.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	ZCEOption.RefInt = 23;
	InsertOrderS(&ZCEOption);
	APISleep(2);

	cout << "郑商所期权市价：" << endl;
	ZCEOption.OrderType = TAPI_ORDER_TYPE_MARKET;
	ZCEOption.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	ZCEOption.OrderPrice = 0;
	ZCEOption.RefInt = 24;
	InsertOrderS(&ZCEOption);
	APISleep(2);

	cout << "郑商所期权市价FAK：" << endl;
	ZCEOption.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	ZCEOption.RefInt = 25;
	InsertOrderS(&ZCEOption);
	APISleep(2);

	cout << "郑商所期权市价FOK：" << endl;
	ZCEOption.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	ZCEOption.RefInt = 26;
	InsertOrderS(&ZCEOption);
	APISleep(2);
}

void Trade::RunZCEOptionSTD()
{
	cout << "郑商所期权跨式限价：" << endl;
	InsertOrderStruct qryReq;
	memset(&qryReq, 0, sizeof(InsertOrderStruct));
	APIStrncpy(qryReq.ExchangeNo, "ZCE");
	qryReq.CommodityType = TAPI_COMMODITY_TYPE_STD;
	APIStrncpy(qryReq.CommodityNo, "SR");
	APIStrncpy(qryReq.ContractNo, "909");
	qryReq.CallOrPutFlag = 'C';
	APIStrncpy(qryReq.StrikePrice, "4300");
	APIStrncpy(qryReq.ContractNo2, "909");
	qryReq.CallOrPutFlag2 = 'P';
	APIStrncpy(qryReq.StrikePrice2, "4300");
	qryReq.OrderType = TAPI_ORDER_TYPE_LIMIT;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderSide = 'B';
	qryReq.PositionEffect = TAPI_PositionEffect_OPEN;
	qryReq.PositionEffect2 = 'N';
	qryReq.OrderPrice = 80;
	qryReq.OrderQty = 1;
	qryReq.RefInt = 31;
	qryReq.FutureAutoCloseFlag = 'N';

	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所期权跨式限价FAK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	qryReq.RefInt = 32;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所期权跨式限价FOK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	qryReq.RefInt = 33;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所期权跨式市价：" << endl;
	qryReq.OrderType = TAPI_ORDER_TYPE_MARKET;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderPrice = 0;
	qryReq.RefInt = 34;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所期权跨式市价FAK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	qryReq.RefInt = 35;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所期权跨式市价FOK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	qryReq.RefInt = 36;
	InsertOrderS(&qryReq);
	APISleep(2);
}

void Trade::RunZCEOptionSTG()
{
	cout << "郑商所期权宽跨式限价：" << endl;
	InsertOrderStruct qryReq;
	memset(&qryReq, 0, sizeof(InsertOrderStruct));
	APIStrncpy(qryReq.ExchangeNo, "ZCE");
	qryReq.CommodityType = TAPI_COMMODITY_TYPE_STG;
	APIStrncpy(qryReq.CommodityNo, "SR");
	APIStrncpy(qryReq.ContractNo, "909");
	qryReq.CallOrPutFlag = 'C';
	APIStrncpy(qryReq.StrikePrice, "4300");
	APIStrncpy(qryReq.ContractNo2, "909");
	qryReq.CallOrPutFlag2 = 'P';
	APIStrncpy(qryReq.StrikePrice2, "4200");
	qryReq.OrderType = TAPI_ORDER_TYPE_LIMIT;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderSide = 'B';
	qryReq.PositionEffect = TAPI_PositionEffect_OPEN;
	qryReq.PositionEffect2 = 'N';
	qryReq.OrderPrice = 600;
	qryReq.OrderQty = 1;
	qryReq.RefInt = 41;
	qryReq.FutureAutoCloseFlag = 'N';

	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所期权宽跨式限价FAK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	qryReq.RefInt = 42;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所期权宽跨式限价FOK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	qryReq.RefInt = 43;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所期权宽跨式市价：" << endl;
	qryReq.OrderType = TAPI_ORDER_TYPE_MARKET;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderPrice = 0;
	qryReq.RefInt = 44;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所期权宽跨式市价FAK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	qryReq.RefInt = 45;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所期权宽跨式市价FOK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	qryReq.RefInt = 46;
	InsertOrderS(&qryReq);
	APISleep(2);
}

void Trade::RunZCEHedge()
{
	cout << "郑商所套保申请" << endl;
	InsertOrderStruct qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	APIStrncpy(qryReq.ExchangeNo, "ZCE");
	qryReq.CommodityType = TAPI_COMMODITY_TYPE_FUTURES;
	APIStrncpy(qryReq.CommodityNo, "SR");
	APIStrncpy(qryReq.ContractNo, "905");
	qryReq.CallOrPutFlag = 'N';
	APIStrncpy(qryReq.StrikePrice, "");
	APIStrncpy(qryReq.ContractNo2, "");
	qryReq.CallOrPutFlag2 = 'N';
	APIStrncpy(qryReq.StrikePrice2, "");
	qryReq.OrderType = TAPI_ORDER_TYPE_HEDGE;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderSide = 'B';
	qryReq.PositionEffect = TAPI_PositionEffect_OPEN;
	qryReq.PositionEffect2 = 'N';
	qryReq.OrderPrice = 2550;
	qryReq.OrderQty = 1;
	qryReq.RefInt = 111;
	qryReq.FutureAutoCloseFlag = 'N';

	InsertOrderS(&qryReq);
}

void Trade::RunZCESwap()
{
	cout << "郑商所互换" << endl;
	InsertOrderStruct qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	APIStrncpy(qryReq.ExchangeNo, "ZCE");
	qryReq.CommodityType = TAPI_COMMODITY_TYPE_SPREAD_MONTH;
	APIStrncpy(qryReq.CommodityNo, "AP");
	APIStrncpy(qryReq.ContractNo, "805");
	qryReq.CallOrPutFlag = 'N';
	APIStrncpy(qryReq.StrikePrice, "");
	APIStrncpy(qryReq.ContractNo2, "809");
	qryReq.CallOrPutFlag2 = 'N';
	APIStrncpy(qryReq.StrikePrice2, "");
	qryReq.OrderType = TAPI_ORDER_TYPE_SWAP;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderSide = 'B';
	qryReq.PositionEffect = TAPI_PositionEffect_OPEN;
	qryReq.PositionEffect2 = 'N';
	qryReq.OrderPrice = 20;
	qryReq.OrderQty = 1;
	qryReq.RefInt = 121;
	qryReq.FutureAutoCloseFlag = 'N';

	InsertOrderS(&qryReq);
}

void Trade::RunDCEFuture()
{
	cout << "大商所期货限价：" << endl;
	InsertOrderStruct qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	APIStrncpy(qryReq.ExchangeNo, "DCE");
	qryReq.CommodityType = 'F';
	APIStrncpy(qryReq.CommodityNo, "M");
	APIStrncpy(qryReq.ContractNo, "1809");
	qryReq.CallOrPutFlag = 'N';
	qryReq.CallOrPutFlag2 = 'N';
	qryReq.OrderType = TAPI_ORDER_TYPE_LIMIT;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderSide = 'B';
	qryReq.PositionEffect = TAPI_PositionEffect_OPEN;
	qryReq.PositionEffect2 = 'N';
	qryReq.OrderPrice = 2400;
	qryReq.OrderQty = 1;
	qryReq.RefInt = 51;
	qryReq.FutureAutoCloseFlag = 'N';

	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所期货限价FAK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	qryReq.RefInt = 52;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所期货限价FOK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	qryReq.RefInt = 53;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所期货市价：" << endl;
	qryReq.OrderType = TAPI_ORDER_TYPE_MARKET;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderPrice = 0;
	qryReq.RefInt = 54;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所期货市价FAK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	qryReq.RefInt = 55;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所期货市价FOK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	qryReq.RefInt = 56;
	InsertOrderS(&qryReq);
	APISleep(2);
}

void Trade::RunDCESPREADMONTH()
{
	cout << "大商所跨期限价：" << endl;
	InsertOrderStruct qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	APIStrncpy(qryReq.ExchangeNo, "DCE");
	qryReq.CommodityType = TAPI_COMMODITY_TYPE_SPREAD_MONTH;
	APIStrncpy(qryReq.CommodityNo, "M");
	APIStrncpy(qryReq.ContractNo, "1807");
	APIStrncpy(qryReq.ContractNo2, "1809");
	qryReq.CallOrPutFlag = 'N';
	qryReq.CallOrPutFlag2 = 'N';
	qryReq.OrderType = TAPI_ORDER_TYPE_LIMIT;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderSide = 'B';
	qryReq.PositionEffect = TAPI_PositionEffect_OPEN;
	qryReq.PositionEffect2 = 'N';
	qryReq.OrderPrice = 300;
	qryReq.OrderQty = 1;
	qryReq.RefInt = 61;
	qryReq.FutureAutoCloseFlag = 'N';

	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所跨期限价FAK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	qryReq.RefInt = 62;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所跨期限价FOK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	qryReq.RefInt = 63;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所跨期市价：" << endl;
	qryReq.OrderType = TAPI_ORDER_TYPE_MARKET;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderPrice = 0;
	qryReq.RefInt = 64;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所跨期市价FAK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	qryReq.RefInt = 65;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所跨期市价FOK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	qryReq.RefInt = 66;
	InsertOrderS(&qryReq);
	APISleep(2);
}

void Trade::RunDCESPREADCOMMODITY()
{
	cout << "大商所跨品种限价：" << endl;
	InsertOrderStruct qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	APIStrncpy(qryReq.ExchangeNo, "DCE");
	qryReq.CommodityType = TAPI_COMMODITY_TYPE_SPREAD_COMMODITY;
	APIStrncpy(qryReq.CommodityNo, "A&M");
	APIStrncpy(qryReq.ContractNo, "1809");
	APIStrncpy(qryReq.ContractNo2, "1809");
	qryReq.CallOrPutFlag = 'N';
	qryReq.CallOrPutFlag2 = 'N';
	qryReq.OrderType = TAPI_ORDER_TYPE_LIMIT;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderSide = 'B';
	qryReq.PositionEffect = TAPI_PositionEffect_OPEN;
	qryReq.PositionEffect2 = 'N';
	qryReq.OrderPrice = 1000;
	qryReq.OrderQty = 1;
	qryReq.RefInt = 71;
	qryReq.FutureAutoCloseFlag = 'N';

	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所跨品种限价FAK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	qryReq.RefInt = 72;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所跨品种限价FOK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	qryReq.RefInt = 73;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所跨品种市价：" << endl;
	qryReq.OrderType = TAPI_ORDER_TYPE_MARKET;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderPrice = 0;
	qryReq.RefInt = 74;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所跨品种市价FAK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	qryReq.RefInt = 75;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "郑商所跨品种市价FOK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	qryReq.RefInt = 76;
	InsertOrderS(&qryReq);
	APISleep(2);
}

void Trade::RunDCEOption()
{
	cout << "大商所期权限价：" << endl;
	InsertOrderStruct qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	APIStrncpy(qryReq.ExchangeNo, "DCE");
	qryReq.CommodityType = TAPI_COMMODITY_TYPE_OPTION;
	APIStrncpy(qryReq.CommodityNo, "M");
	APIStrncpy(qryReq.ContractNo, "1809");
	qryReq.CallOrPutFlag = 'C';
	APIStrncpy(qryReq.StrikePrice, "2200");
	qryReq.CallOrPutFlag2 = 'N';
	qryReq.OrderType = TAPI_ORDER_TYPE_LIMIT;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderSide = 'B';
	qryReq.PositionEffect = TAPI_PositionEffect_OPEN;
	qryReq.PositionEffect2 = 'N';
	qryReq.OrderPrice = 233;
	qryReq.OrderQty = 1;
	qryReq.RefInt = 81;
	qryReq.FutureAutoCloseFlag = 'N';

	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所期权限价FAK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	qryReq.RefInt = 82;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所期权限价FOK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	qryReq.RefInt = 83;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所期权市价：" << endl;
	qryReq.OrderType = TAPI_ORDER_TYPE_MARKET;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderPrice = 0;
	qryReq.RefInt = 84;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所期权市价FAK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FAK;
	qryReq.RefInt = 85;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所期权市价FOK：" << endl;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_FOK;
	qryReq.RefInt = 86;
	InsertOrderS(&qryReq);
	APISleep(2);
}

void Trade::RunDCECombReq()
{
	cout << "大商所期货组合申请：" << endl;
	InsertOrderStruct qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	APIStrncpy(qryReq.ExchangeNo, "DCE");
	qryReq.CommodityType = TAPI_COMMODITY_TYPE_FUTURE_LOCK;
	APIStrncpy(qryReq.CommodityNo, "M");
	APIStrncpy(qryReq.ContractNo, "1809");
	qryReq.CallOrPutFlag = 'N';
	APIStrncpy(qryReq.StrikePrice, "");
	APIStrncpy(qryReq.ContractNo2, "1809");
	qryReq.CallOrPutFlag2 = 'N';
	APIStrncpy(qryReq.StrikePrice2, "");
	qryReq.OrderType = TAPI_ORDER_TYPE_COMB;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderSide = 'B';
	qryReq.PositionEffect = TAPI_PositionEffect_OPEN;
	qryReq.PositionEffect2 = 'N';
	qryReq.OrderPrice = 233;
	qryReq.OrderPrice2 = 240;
	qryReq.OrderQty = 1;
	qryReq.RefInt = 91;
	qryReq.FutureAutoCloseFlag = 'N';

	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所期货组合拆分申请：" << endl;
	qryReq.OrderType = TAPI_ORDER_TYPE_UNCOMB;
	InsertOrderS(&qryReq);
	APISleep(2);
}

void Trade::RunDCEStop()
{
	cout << "大商所期货买限价止损" << endl;
	InsertOrderStruct qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	APIStrncpy(qryReq.ExchangeNo, "DCE");
	qryReq.CommodityType = TAPI_COMMODITY_TYPE_FUTURES;
	APIStrncpy(qryReq.CommodityNo, "M");
	APIStrncpy(qryReq.ContractNo, "1809");
	qryReq.CallOrPutFlag = 'N';
	APIStrncpy(qryReq.StrikePrice, "");
	APIStrncpy(qryReq.ContractNo2, "");
	qryReq.CallOrPutFlag2 = 'N';
	APIStrncpy(qryReq.StrikePrice2, "");
	qryReq.OrderType = TAPI_ORDER_TYPE_STOP_LIMIT;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderSide = 'B';
	qryReq.PositionEffect = TAPI_PositionEffect_OPEN;
	qryReq.PositionEffect2 = 'N';
	qryReq.OrderPrice = 2550;
	qryReq.StopPrice = 2500; //买限价止损，限价必须大于止损价
	qryReq.OrderQty = 1;
	qryReq.RefInt = 101;
	qryReq.FutureAutoCloseFlag = 'N';

	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所期货卖限价止损" << endl;
	qryReq.OrderSide = 'S';
	qryReq.OrderPrice = 2450;
	qryReq.StopPrice = 2500; //卖限价止损，限价必须小于止损价
	qryReq.RefInt = 101;

	InsertOrderS(&qryReq);
	APISleep(2);
}

void Trade::RunDCESwap()
{
	cout << "大商所互换" << endl;
	InsertOrderStruct qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	APIStrncpy(qryReq.ExchangeNo, "DCE");
	qryReq.CommodityType = TAPI_COMMODITY_TYPE_SPREAD_MONTH;
	APIStrncpy(qryReq.CommodityNo, "M");
	APIStrncpy(qryReq.ContractNo, "1805");
	qryReq.CallOrPutFlag = 'N';
	APIStrncpy(qryReq.StrikePrice, "");
	APIStrncpy(qryReq.ContractNo2, "1809");
	qryReq.CallOrPutFlag2 = 'N';
	APIStrncpy(qryReq.StrikePrice2, "");
	qryReq.OrderType = TAPI_ORDER_TYPE_SWAP;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderSide = 'B';
	qryReq.PositionEffect = TAPI_PositionEffect_OPEN;
	qryReq.PositionEffect2 = 'N';
	qryReq.OrderPrice = 20;
	qryReq.OrderQty = 1;
	qryReq.RefInt = 121;
	qryReq.FutureAutoCloseFlag = 'N';

	InsertOrderS(&qryReq);
}

void Trade::RunDCEOptionSet()
{
	cout << "大商所期权自对冲：" << endl;
	InsertOrderStruct qryReq;
	memset(&qryReq, 0, sizeof(qryReq));
	APIStrncpy(qryReq.ExchangeNo, "DCE");
	qryReq.CommodityType = TAPI_COMMODITY_TYPE_OPTION;
	APIStrncpy(qryReq.CommodityNo, "M");
	APIStrncpy(qryReq.ContractNo, "1809");
	qryReq.CallOrPutFlag = 'C';
	APIStrncpy(qryReq.StrikePrice, "2200");
	qryReq.CallOrPutFlag2 = 'N';
	qryReq.OrderType = TAPI_ORDER_TYPE_OPTION_AUTO_CLOSE;
	qryReq.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
	qryReq.OrderSide = 'B';
	qryReq.PositionEffect = 'N';
	qryReq.PositionEffect2 = 'N';
	qryReq.OrderQty = 1;
	qryReq.RefInt = 121;
	qryReq.FutureAutoCloseFlag = 'N';

	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所履约自对冲：" << endl;
	qryReq.OrderType = TAPI_ORDER_TYPE_FUTURE_AUTO_CLOSE;
	InsertOrderS(&qryReq);
	APISleep(2);

	cout << "大商所取消自动行权：" << endl;
	qryReq.OrderType = TAPI_ORDER_TYPE_OPTION_AUTOEXEC_ABAND;
	InsertOrderS(&qryReq);
}

void Trade::RunInsertFuncs()
{
	cout << "测试现有业务订单：" << endl;

	RunZCEFuture();
	APISleep(2);
//	RunZCESPREADMONTH();
//	APISleep(2);
//	RunZCEOption();
//	APISleep(2);
//	RunZCEOptionSTD();
//	APISleep(2);
//	RunZCEHedge();
//	APISleep(2);
//	RunZCESwap();
//	APISleep(2);
//
//	RunDCEFuture();
//	APISleep(2);
//	RunDCESPREADMONTH();
//	APISleep(2);
//	RunDCESPREADCOMMODITY();
//	APISleep(2);
//	RunDCEOption();
//	APISleep(2);
//	RunDCECombReq();
//	APISleep(2);
//	RunDCEStop();
//	APISleep(2);
//	RunDCESwap();
//	APISleep(2);
//	RunDCEOptionSet();
//	APISleep(2);
}

void Trade::SubmitLoginInfo()
{
	TAPIINT32 iErr = TAPIERROR_SUCCEED;

	TapAPISubmitUserLoginInfo UserLoginInfo;
	memset(&UserLoginInfo, 0, sizeof(TapAPISubmitUserLoginInfo));

	char pInfo[501] = { 0 };
	int nLen = 0, nVer = 0, ret = -10;
#ifdef __linux
	Tesunny_getsysteminfo pFun = (Tesunny_getsysteminfo)dlsym(G_TapDataCollectHandle, "esunny_getsysteminfo");
	if (NULL == dlerror())
		ret = pFun(pInfo, &nLen, &nVer);
#elif defined WIN32 || defined WIN64
	Tesunny_getsysteminfo pFun = (Tesunny_getsysteminfo)GetProcAddress(G_TapDataCollectHandle, "esunny_getsysteminfo");
	if (NULL != pFun)
		ret = pFun(pInfo, &nLen, &nVer);
#endif // __linux  
	//int ret = esunny_getsysteminfo(pInfo, &nLen, &nVer);
	if (ret != 0)
	{
		cout << ret << endl;
		return;
	}

	memcpy(UserLoginInfo.UserNo, "1005", sizeof(UserLoginInfo.UserNo));
	memcpy(UserLoginInfo.GatherInfo, pInfo, sizeof(UserLoginInfo.GatherInfo));
	memcpy(UserLoginInfo.ClientLoginIP, "192.168.23.205", sizeof(UserLoginInfo.ClientLoginIP));
	UserLoginInfo.ClientLoginPort = 35552;
	memcpy(UserLoginInfo.ClientLoginDateTime, "2019-03-11 14:49:52", sizeof(UserLoginInfo.ClientLoginDateTime));
	memcpy(UserLoginInfo.ClientAppID, "esunny_epolestar_9.0.3.12", sizeof(UserLoginInfo.ClientAppID));
	UserLoginInfo.AuthKeyVersion = nVer;

	m_uiSessionID = 0;
	iErr = m_pAPI->SubmitUserLoginInfo(&m_uiSessionID, &UserLoginInfo);
	if (TAPIERROR_SUCCEED != iErr) {
		cout << "SubmitUserLoginInfo Error:" << iErr << endl;
		return;
	}
}

void Trade::RunNewFuncs()
{
	SubmitLoginInfo();
}