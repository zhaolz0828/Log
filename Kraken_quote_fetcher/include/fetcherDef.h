#pragma once
#include <TapTradeAPI.h>
#include <TapQuoteAPI.h>
#include <QuoteConfig.h>

struct KrakenBasicConf {
	TAPISTR_20					UserNo;					///< �û���
	TAPIYNFLAG					ISModifyPassword;		///< �Ƿ��޸����룬'Y'��ʾ�ǣ�'N'��ʾ��
	TAPISTR_20					Password;				///< �û�����
	TAPISTR_20					NewPassword;			///< �����룬����������޸���������Ҫ��д���ֶ�
	TAPISTR_20					QuoteTempPassword;		///< ������ʱ����
	TAPIYNFLAG					ISDDA;					///< �Ƿ���ѽ��̬��֤��'Y'��ʾ�ǣ�'N'��ʾ��
	TAPISTR_30					DDASerialNo;			///< ��̬��֤��
	TAPISTR_50					AuthCode;				///< ��Ȩ��
	TAPISTR_30					AppID;					///< ����汾��
	TAPINoticeIgnoreFlagType	NoticeIgnoreFlag;		///< ��������֪ͨ���
	TAPISTR_20					Address;				///< IP
	TAPIUINT16					QuotePort;				///< ����˿�
	TAPIUINT16					TradePort;				///< ���׶˿�
};