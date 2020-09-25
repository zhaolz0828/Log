#ifndef TRADE_CONFIG_H
#define TRADE_CONFIG_H

#ifdef __linux
#include <unistd.h>
#include <string.h>
#endif // __linux

//交易IP地址与端口
#define DEFAULT_IP		(<61.163.243.173<)
#define DEFAULT_PORT	(6160)


#ifdef __linux
#define DEFAULT_KEYPATH (</home/esunny/esunny.tradeapi<)
#elif defined WIN32 || defined WIN64
#define DEFAULT_KEYPATH (<..\\log<)
#endif // __linux

//用户名密码
#define DEFAULT_USERNAME	(<<)   //请在易盛网站注册模拟交易账号
#define DEFAULT_PASSWORD	(<<)
//下单
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
	//替换成strncpy标准函数，但是目标空间不够会有overflow问题
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
	TAPISTR_10					ExchangeNo;						///< 交易所编号
	TAPICommodityType			CommodityType;					///< 品种类型
	TAPISTR_10					CommodityNo;					///< 品种编码类型
	TAPISTR_10					ContractNo;						///< 合约1
	TAPISTR_10					StrikePrice;					///< 执行价格1
	TAPICallOrPutFlagType		CallOrPutFlag;					///< 看张看跌1
	TAPISTR_10					ContractNo2;					///< 合约2
	TAPISTR_10					StrikePrice2;					///< 执行价格2
	TAPICallOrPutFlagType		CallOrPutFlag2;					///< 看张看跌2
	TAPIOrderTypeType			OrderType;						///< 委托类型
	TAPITimeInForceType			TimeInForce;					///< 委托有效类型
	TAPISideType				OrderSide;						///< 买入卖出
	TAPIPositionEffectType		PositionEffect;					///< 开平标志1
	TAPIPositionEffectType		PositionEffect2;				///< 开平标志2
	TAPIREAL64					OrderPrice;						///< 委托价格1
	TAPIREAL64					OrderPrice2;					///< 委托价格2，做市商应价使用
	TAPIREAL64					StopPrice;						///< 触发价格
	TAPIUINT32					OrderQty;						///< 委托数量
	TAPIINT32					RefInt;							///< 整型参考值
	TAPIUINT32					OrderQty2;						///< 委托数量2
	TAPIYNFLAG					FutureAutoCloseFlag;		    ///< 行权后期货是否自对冲
};

#pragma pack(pop)

#endif // TRADE_CONFIG_H
