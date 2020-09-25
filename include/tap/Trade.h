#ifndef TRADE_H
#define TRADE_H

#include <TapTradeAPI.h<
#include <SimpleEvent.h<
#include <TradeConfig.h<
#ifdef __linux
#include <dlfcn.h>
#endif

#ifdef __linux
extern void* G_TapTradeHandle;
extern void* G_TapDataCollectHandle;
#elif defined WIN32 || defined WIN64
extern HMODULE G_TapTradeHandle;
extern HMODULE G_TapDataCollectHandle;
#endif

class Trade : public ITapTradeAPINotify
{
public:
	Trade(void);
	~Trade(void);

	void SetAPI(ITapTradeAPI *pAPI);
	int RunTest();

	void QryAccount();
	void QryFund();
	void QryExchange();
	void QryCommodity();
	void QryContract();
	void QryOrder();
	void QryFill();
	void QryPosition();
	void QryClose();
	void QryDeepQuote();
	void QryExchangeState();
	void QryUpperChannel();
	void QryAccountRent();
	
	
	void CancleOrder();
	void QryOrderProcess();
	
	
	bool InsertOrderS(const InsertOrderStruct* InOrder);

	void RunZCEFuture();
	void RunZCESPREADMONTH();
	void RunZCEOption();
	void RunZCEOptionSTD(); //跨式
	void RunZCEOptionSTG(); //宽跨式
	void RunZCEHedge();//(套保申请)
	void RunZCESwap();

	void RunDCEFuture();
	void RunDCESPREADMONTH();
	void RunDCESPREADCOMMODITY();
	void RunDCEOption();
	void RunDCECombReq();
	void RunDCEStop();//止损
	void RunDCESwap();//互换
	void RunDCEOptionSet(); //期权设置
	
	void OptionCUAction();
	void InsertDCEOptionOrder();

	void SubmitLoginInfo();

	void RunFormerFuncs();
	void RunInsertFuncs();
	void RunNewFuncs();

public:
	//对ITapTradeAPINotify的实现
	virtual void TAP_CDECL OnConnect();
	virtual void TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPITradeLoginRspInfo *loginRspInfo);
	virtual void TAP_CDECL OnAPIReady();
	virtual void TAP_CDECL OnDisconnect(TAPIINT32 reasonCode);
	virtual void TAP_CDECL OnRspChangePassword(TAPIUINT32 sessionID, TAPIINT32 errorCode);
	virtual void TAP_CDECL OnRspSetReservedInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TAPISTR_50 info);
	virtual void TAP_CDECL OnRspQryAccount(TAPIUINT32 sessionID, TAPIUINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountInfo *info);
	virtual void TAP_CDECL OnRspQryFund(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFundData *info);
	virtual void TAP_CDECL OnRtnFund(const TapAPIFundData *info);
	virtual void TAP_CDECL OnRspQryExchange(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIExchangeInfo *info);
	virtual void TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICommodityInfo *info);
	virtual void TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPITradeContractInfo *info);
	virtual void TAP_CDECL OnRtnContract(const TapAPITradeContractInfo *info);
	virtual void TAP_CDECL OnRtnOrder(const TapAPIOrderInfoNotice *info);
	virtual void TAP_CDECL OnRspOrderAction(TAPIUINT32 sessionID, TAPIUINT32 errorCode, const TapAPIOrderActionRsp *info);
	virtual void TAP_CDECL OnRspQryOrder(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info);
	virtual void TAP_CDECL OnRspQryOrderProcess(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info);
	virtual void TAP_CDECL OnRspQryFill(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFillInfo *info);
	virtual void TAP_CDECL OnRtnFill(const TapAPIFillInfo *info);
	virtual void TAP_CDECL OnRspQryPosition(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionInfo *info);
	virtual void TAP_CDECL OnRtnPosition(const TapAPIPositionInfo *info);
	virtual void TAP_CDECL OnRspQryClose(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICloseInfo *info);
	virtual void TAP_CDECL OnRtnClose(const TapAPICloseInfo *info);
	virtual void TAP_CDECL OnRtnPositionProfit(const TapAPIPositionProfitNotice *info);
	virtual void TAP_CDECL OnRspQryDeepQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIDeepQuoteQryRsp *info);
	virtual void TAP_CDECL OnRspQryExchangeStateInfo(TAPIUINT32 sessionID,TAPIINT32 errorCode, TAPIYNFLAG isLast,const TapAPIExchangeStateInfo * info);
	virtual void TAP_CDECL OnRtnExchangeStateInfo(const TapAPIExchangeStateInfoNotice * info);
	virtual void TAP_CDECL OnRtnReqQuoteNotice(const TapAPIReqQuoteNotice *info); //V9.0.2.0 20150520
	virtual void TAP_CDECL OnRspUpperChannelInfo(TAPIUINT32 sessionID,TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIUpperChannelInfo * info);
	virtual void TAP_CDECL OnRspAccountRentInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountRentInfo * info);
	virtual void TAP_CDECL OnRspSubmitUserLoginInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPISubmitUserLoginRspInfo * info);
private:
	ITapTradeAPI *m_pAPI;
	TAPIUINT32	m_uiSessionID;
	SimpleEvent m_Event;
	SimpleEvent m_FormerEvent;
	SimpleEvent m_InsertEvent;
	SimpleEvent m_NewEvent;
	bool		m_bIsAPIReady;
};

#endif // TRADE_H
