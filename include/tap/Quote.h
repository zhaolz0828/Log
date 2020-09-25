#ifndef QUOTE_H
#define QUOTE_H

#include <fetcherDef.h>

#include <SimpleEvent.h>
#include <TapAPIError.h>

#include <comm_tool.h>





using namespace std;

class Quote : public ITapQuoteAPINotify
{
public:
	Quote();
	~Quote();
	
public:
	comm_tool comm_tool;

	ShareMemoryTool sm_tool1;
	TapAPIQuoteWhole data;
	deliver_ deliver_data = &data;


	ShareMemoryTool sm_tool2;
	MockFile mockfile;
	MK mk = &mockfile;


	void SetQuoteAPI(ITapQuoteAPI* api);
	void Login_(KrakenBasicConf info);
	void Run_();
	void TestFile();
	string getstr();
	KrakenBasicConf getBasicConf();
	void DataDeliver(const TapAPIQuoteWhole* info);
	void test_DataDeliver();
	
	void SubscribeQuote(const TapAPIQuoteContractInfo* info);
	void test_SubscribeQuote();
	//void UnSubscribeQuote();

	//合约表
	void QryContractInfo(const TapAPIQuoteCommodityInfo* info);
	//品种编码表
	void QryCommdityInfo();

	
public:
	virtual void TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info);
	virtual void TAP_CDECL OnAPIReady();
	virtual void TAP_CDECL OnDisconnect(TAPIINT32 reasonCode);
	virtual void TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info);
	virtual void TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info);
	virtual void TAP_CDECL OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info);
	virtual void TAP_CDECL OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info);
	virtual void TAP_CDECL OnRtnQuote(const TapAPIQuoteWhole *info);

	
	
private:
	ITapQuoteAPI* m_pAPI;
	TAPIUINT32	m_uiSessionID;
	SimpleEvent m_Event;
	bool		m_bIsAPIReady;
	TAPIUINT32  m_QuoteNum;
};

#endif /* QUOTE_H */

