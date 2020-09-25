#ifndef TRADE_CONFIG_H
#define TRADE_CONFIG_H

#ifdef __linux
#include <unistd.h>
#include <string.h>
#endif // __linux

//����IP��ַ��˿�
#define DEFAULT_IP		(<61.163.243.173<)
#define DEFAULT_PORT	(6160)


#ifdef __linux
#define DEFAULT_KEYPATH (</home/esunny/esunny.tradeapi<)
#elif defined WIN32 || defined WIN64
#define DEFAULT_KEYPATH (<..\\log<)
#endif // __linux

//�û�������
#define DEFAULT_USERNAME	(<<)   //������ʢ��վע��ģ�⽻���˺�
#define DEFAULT_PASSWORD	(<<)
//�µ�
#define DEFAULT_ACCOUNT_NO		(DEFAULT_USERNAME)
#define DEFAULT_EXCHANGE_NO		(<DCE<)
#define DEFAULT_COMMODITY_TYPE	(TAPI_COMMODITY_TYPE_OPTION)
#define DEFAULT_COMMODITY_NO	(<M<)
#define DEFAULT_CONTRACT_NO		(<1807<)
#define DEFAULT_STRIKE_PRICE    (<3000<)
#define DEFAULT_ORDER_TYPE		(TAPI_ORDER_TYPE_OPTION_AUTOEXEC_ABAND)
#define DEFAULT_ORDER_SIDE		(TAPI_SIDE_BUY)
#define DEFAULT_POSITION_EFFECT	(TAPI_PositionEffect_OPEN)
#define DEFAULT_CALLORPUTFLAG   (TAPI_CALLPUT_FLAG_PUT)
#define DEFAULT_ORDER_PRICE		(500)
#define DEFAULT_ORDER_QTY		(10)	


template<size_t size> inline void
APIStrncpy(char(&Dst)[size], const char * source)
{
#ifdef WIN32
	strncpy_s(Dst, source, sizeof(Dst) - 1);
#endif

#ifdef linux
	//�滻��strncpy��׼����������Ŀ��ռ䲻������overflow����
	strncpy(Dst, source, sizeof(Dst) - 1);
#endif

}

inline void APISleep(int secs)
{
#ifdef WIN32
	Sleep(secs * 1000);
#endif

#ifdef linux
	sleep(secs);
#endif // linux

}

#pragma pack(push, 1)
struct InsertOrderStruct
{
	TAPISTR_10					ExchangeNo;						///< ���������
	TAPICommodityType			CommodityType;					///< Ʒ������
	TAPISTR_10					CommodityNo;					///< Ʒ�ֱ�������
	TAPISTR_10					ContractNo;						///< ��Լ1
	TAPISTR_10					StrikePrice;					///< ִ�м۸�1
	TAPICallOrPutFlagType		CallOrPutFlag;					///< ���ſ���1
	TAPISTR_10					ContractNo2;					///< ��Լ2
	TAPISTR_10					StrikePrice2;					///< ִ�м۸�2
	TAPICallOrPutFlagType		CallOrPutFlag2;					///< ���ſ���2
	TAPIOrderTypeType			OrderType;						///< ί������
	TAPITimeInForceType			TimeInForce;					///< ί����Ч����
	TAPISideType				OrderSide;						///< ��������
	TAPIPositionEffectType		PositionEffect;					///< ��ƽ��־1
	TAPIPositionEffectType		PositionEffect2;				///< ��ƽ��־2
	TAPIREAL64					OrderPrice;						///< ί�м۸�1
	TAPIREAL64					OrderPrice2;					///< ί�м۸�2��������Ӧ��ʹ��
	TAPIREAL64					StopPrice;						///< �����۸�
	TAPIUINT32					OrderQty;						///< ί������
	TAPIINT32					RefInt;							///< ���Ͳο�ֵ
	TAPIUINT32					OrderQty2;						///< ί������2
	TAPIYNFLAG					FutureAutoCloseFlag;		    ///< ��Ȩ���ڻ��Ƿ��ԶԳ�
};

#pragma pack(pop)

#endif // TRADE_CONFIG_H
