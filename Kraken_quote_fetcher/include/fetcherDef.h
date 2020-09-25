#pragma once
#include <TapTradeAPI.h>
#include <TapQuoteAPI.h>
#include <QuoteConfig.h>

struct KrakenBasicConf {
	TAPISTR_20					UserNo;					///< 用户名
	TAPIYNFLAG					ISModifyPassword;		///< 是否修改密码，'Y'表示是，'N'表示否
	TAPISTR_20					Password;				///< 用户密码
	TAPISTR_20					NewPassword;			///< 新密码，如果设置了修改密码则需要填写此字段
	TAPISTR_20					QuoteTempPassword;		///< 行情临时密码
	TAPIYNFLAG					ISDDA;					///< 是否需呀动态认证，'Y'表示是，'N'表示否
	TAPISTR_30					DDASerialNo;			///< 动态认证码
	TAPISTR_50					AuthCode;				///< 授权码
	TAPISTR_30					AppID;					///< 程序版本号
	TAPINoticeIgnoreFlagType	NoticeIgnoreFlag;		///< 忽略推送通知标记
	TAPISTR_20					Address;				///< IP
	TAPIUINT16					QuotePort;				///< 行情端口
	TAPIUINT16					TradePort;				///< 交易端口
};