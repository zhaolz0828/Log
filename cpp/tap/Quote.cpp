#include <Quote.h>



Quote::Quote():m_pAPI(NULL),m_bIsAPIReady(false)
{
    m_uiSessionID = 0;
    m_QuoteNum = 0;
}

Quote::~Quote()
{}

void Quote::SetQuoteAPI(ITapQuoteAPI* api)
{
    m_pAPI = api;
}
//��ȡ��½��Ϣ
KrakenBasicConf Quote::getBasicConf() {
    KrakenBasicConf info;
    
    string path = comm_tool.GetProgramDir(2) + "\\configuration\\fetcher\\basicConfiguration.csv";
    const char* c_path = path.c_str();
    cout << "���������ļ�·��" << c_path << endl;
    ifstream infile(c_path);
    if (!infile) {
        cout << "cant find file" << endl;
    }
    string word;
    int counting = 1;
    while (getline(infile, word, ','))
    {
        if (counting % 2 == 0)
        {
            switch (counting)
            {
            case 2://�û�
                strcpy(info.UserNo, word.c_str());
                comm_tool.printOnScreen("��½�û�", word.c_str());
                break;
            case 4://����
                strcpy(info.Password, word.c_str());
                break;
            case 6://IP
                strcpy(info.Address, word.c_str());
                comm_tool.printOnScreen("������IP", word.c_str());
                break;
            case 8://���׶˿�
                info.TradePort = atoi(word.c_str());
                comm_tool.printOnScreen("���������׶˿�", word.c_str());
                break;
            case 10://����˿�
                info.QuotePort = atoi(word.c_str());
                comm_tool.printOnScreen("����������˿�", word.c_str());
                break;
            case 12://��Ȩ��
                strcpy(info.AuthCode, word.c_str());
                comm_tool.printOnScreen("��Ȩ��", word.c_str());
                break;
            case 14://����汾��
                strcpy(info.AppID, word.c_str());
                comm_tool.printOnScreen("����汾��", word.c_str());
                break;
           
            }
        }
        counting = counting + 1;
    }
    info.ISModifyPassword = APIYNFLAG_NO;				//�Ƿ��޸�����
    info.ISDDA = APIYNFLAG_NO;							//�Ƿ���Ҫ��̬��֤

    return info;
}
//���ݴ���
void Quote::DataDeliver(const TapAPIQuoteWhole* info) {

    if (info)
    {
		deliver_data->Contract					=info->Contract;					///<��Լ
		strcpy(deliver_data->CurrencyNo,info->CurrencyNo);							///<���ֱ��
		deliver_data->TradingState				=info->TradingState;				///<����״̬��1���Ͼ���;2���Ͼ��۴��;3��������;4������ͣ;5����
		strcpy(deliver_data->DateTimeStamp,info->DateTimeStamp);					///<ʱ���
		deliver_data->QPreClosingPrice			=info->QPreClosingPrice;			///<�����̼�
		deliver_data->QPreSettlePrice			=info->QPreSettlePrice;				///<������
		deliver_data->QPrePositionQty			=info->QPrePositionQty;				///<��ֲ���
		deliver_data->QOpeningPrice				=info->QOpeningPrice;				///<���̼�
		deliver_data->QLastPrice				=info->QLastPrice;					///<���¼�
		deliver_data->QHighPrice				=info->QHighPrice;					///<��߼�
		deliver_data->QLowPrice					=info->QLowPrice;					///<��ͼ�
		deliver_data->QHisHighPrice				=info->QHisHighPrice;				///<��ʷ��߼�
		deliver_data->QHisLowPrice				=info->QHisLowPrice;				///<��ʷ��ͼ�
		deliver_data->QLimitUpPrice				=info->QLimitUpPrice;				///<��ͣ��
		deliver_data->QLimitDownPrice			=info->QLimitDownPrice;				///<��ͣ��
		deliver_data->QTotalQty					=info->QTotalQty;					///<�����ܳɽ���
		deliver_data->QTotalTurnover			=info->QTotalTurnover;				///<���ճɽ����
		deliver_data->QPositionQty				=info->QPositionQty;				///<�ֲ���
		deliver_data->QAveragePrice				=info->QAveragePrice;				///<����
		deliver_data->QClosingPrice				=info->QClosingPrice;				///<���̼�
		deliver_data->QSettlePrice				=info->QSettlePrice;				///<�����
		deliver_data->QLastQty					=info->QLastQty;					///<���³ɽ���
		deliver_data->QBidPrice[0]				=info->QBidPrice[0];				///<���1��
		deliver_data->QBidQty[0]				=info->QBidQty[0];					///<����1��
		deliver_data->QAskPrice[0]				=info->QAskPrice[0];				///<����1��
		deliver_data->QAskQty[0]				=info->QAskQty[0];					///<����1��
		deliver_data->QImpliedBidPrice			=info->QImpliedBidPrice;			///<�������
		deliver_data->QImpliedBidQty			=info->QImpliedBidQty;				///<��������
		deliver_data->QImpliedAskPrice			=info->QImpliedAskPrice;			///<��������
		deliver_data->QImpliedAskQty			=info->QImpliedAskQty;				///<��������
		deliver_data->QPreDelta					=info->QPreDelta;					///<����ʵ��
		deliver_data->QCurrDelta				=info->QCurrDelta;					///<����ʵ��
		deliver_data->QInsideQty				=info->QInsideQty;					///<������
		deliver_data->QOutsideQty				=info->QOutsideQty;					///<������
		deliver_data->QTurnoverRate				=info->QTurnoverRate;				///<������
		deliver_data->Q5DAvgQty					=info->Q5DAvgQty;					///<���վ���
		deliver_data->QPERatio					=info->QPERatio;					///<��ӯ��
		deliver_data->QTotalValue				=info->QTotalValue;					///<����ֵ
		deliver_data->QNegotiableValue			=info->QNegotiableValue;			///<��ͨ��ֵ
		deliver_data->QPositionTrend			=info->QPositionTrend;				///<�ֲ�����
		deliver_data->QChangeSpeed				=info->QChangeSpeed;				///<����
		deliver_data->QChangeRate				=info->QChangeRate;					///<�Ƿ�
		deliver_data->QChangeValue				=info->QChangeValue;				///<�ǵ�ֵ
		deliver_data->QSwing					=info->QSwing;						///<���
		deliver_data->QTotalBidQty				=info->QTotalBidQty;				///<ί������
		deliver_data->QTotalAskQty				=info->QTotalAskQty;				///<ί������
		deliver_data->UnderlyContract			=info->UnderlyContract;				///<�����Լ��Ӧ����ʵ��Լ

        ReleaseMutex(sm_tool1.L_Mutex);
        SetEvent(sm_tool1.L_Event);
    }
    else {
        cout << "quote info is null." << endl;
        return;
    }

}
void Quote::test_DataDeliver() {

    system("pause");

    TapAPIContract test_contract;
    test_contract.CallOrPutFlag1 = TAPI_CALLPUT_FLAG_NONE;
    test_contract.CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE;
    strcpy(test_contract.Commodity.CommodityNo, DEFAULT_COMMODITY_NO);
    test_contract.Commodity.CommodityType = DEFAULT_COMMODITY_TYPE;
    strcpy(test_contract.Commodity.ExchangeNo, DEFAULT_EXCHANGE_NO);
    strcpy(test_contract.ContractNo1, DEFAULT_CONTRACT_NO);
    strcpy(test_contract.ContractNo2, DEFAULT_CONTRACT_NO2);
    strcpy(test_contract.StrikePrice1, "1");
    strcpy(test_contract.StrikePrice2, "2");

    deliver_data->Contract = test_contract;
    strcpy(deliver_data->CurrencyNo, "1");
    deliver_data->TradingState = 1;
    strcpy(deliver_data->DateTimeStamp, "111111111111");
    deliver_data->QPreClosingPrice = 2;
    deliver_data->QPreSettlePrice = 3;
    deliver_data->QPrePositionQty = 4;
    deliver_data->QOpeningPrice = 5;
    deliver_data->QLastPrice = 6;
    deliver_data->QHighPrice = 7;
    deliver_data->QLowPrice = 8;
    deliver_data->QHisHighPrice = 9;
    deliver_data->QHisLowPrice = 10;
    deliver_data->QLimitUpPrice = 11;
    deliver_data->QLimitDownPrice = 12;
    deliver_data->QTotalQty = 13;
    deliver_data->QTotalTurnover = 14;
    deliver_data->QPositionQty = 15;
    deliver_data->QAveragePrice = 16;
    deliver_data->QClosingPrice = 17;
    deliver_data->QSettlePrice = 18;
    deliver_data->QLastQty = 19;
    deliver_data->QBidPrice[0] = 20;
    deliver_data->QBidQty[0] = 21;
    deliver_data->QAskPrice[0] = 22;
    deliver_data->QAskQty[0] = 23;
    deliver_data->QImpliedBidPrice = 24;
    deliver_data->QImpliedBidQty = 25;
    deliver_data->QImpliedAskPrice = 26;
    deliver_data->QImpliedAskQty = 27;
    deliver_data->QPreDelta = 28;
    deliver_data->QCurrDelta = 29;
    deliver_data->QInsideQty = 30;
    deliver_data->QOutsideQty = 31;
    deliver_data->QTurnoverRate = 32;
    deliver_data->Q5DAvgQty = 33;
    deliver_data->QPERatio = 34;
    deliver_data->QTotalValue = 35;
    deliver_data->QNegotiableValue = 36;
    deliver_data->QPositionTrend = 37;
    deliver_data->QChangeSpeed = 38;
    deliver_data->QChangeRate = 39;
    deliver_data->QChangeValue = 40;
    deliver_data->QSwing = 41;
    deliver_data->QTotalBidQty = 42;
    deliver_data->QTotalAskQty = 43;
    deliver_data->UnderlyContract = test_contract;

    ReleaseMutex(sm_tool1.L_Mutex);
    SetEvent(sm_tool1.L_Event);
    cout << "deliver finish." << endl;
}
//����
void Quote::SubscribeQuote(const TapAPIQuoteContractInfo* info)
{
    m_uiSessionID = 0;
    TapAPIContract qryReq;
    memset(&qryReq, 0, sizeof(qryReq));
    memcpy(&qryReq.Commodity.ExchangeNo, info->Contract.Commodity.ExchangeNo, sizeof(TAPISTR_10)); 
    memcpy(&qryReq.Commodity.CommodityNo, info->Contract.Commodity.CommodityNo, sizeof(TAPISTR_10));
    memcpy(&qryReq.ContractNo1, info->Contract.ContractNo1, sizeof(TAPISTR_10));
    qryReq.Commodity.CommodityType = info->Contract.Commodity.CommodityType;
    if (qryReq.Commodity.CommodityType == 'S')
    {
        memcpy(&qryReq.ContractNo2, info->Contract.ContractNo2, sizeof(TAPISTR_10));
    }
    qryReq.CallOrPutFlag1 = 'N';
    qryReq.CallOrPutFlag2 = 'N';
    
    int iErr = m_pAPI->SubscribeQuote(&m_uiSessionID, &qryReq);
    //�ͷ�
    //delete &qryReq;
    if (iErr != 0)
        cout << "QryContract Error:" << iErr << endl;
    else
        return;
}
void Quote::test_SubscribeQuote() {
    m_uiSessionID = 0;
    TapAPIContract qryReq;
    memset(&qryReq, 0, sizeof(qryReq));
    memcpy(&qryReq.Commodity.ExchangeNo, DEFAULT_EXCHANGE_NO, sizeof(TAPISTR_10));
    memcpy(&qryReq.Commodity.CommodityNo, DEFAULT_COMMODITY_NO, sizeof(TAPISTR_10));
    memcpy(&qryReq.ContractNo1, DEFAULT_CONTRACT_NO, sizeof(TAPISTR_10));
    qryReq.Commodity.CommodityType = DEFAULT_COMMODITY_TYPE;
    if (qryReq.Commodity.CommodityType == 'S')
    {
        //memcpy(&qryReq.ContractNo2, info->Contract.ContractNo2, sizeof(TAPISTR_10));
    }
    qryReq.CallOrPutFlag1 = 'N';
    qryReq.CallOrPutFlag2 = 'N';

    int iErr = m_pAPI->SubscribeQuote(&m_uiSessionID, &qryReq);
    //�ͷ�
    //delete &qryReq;
    if (iErr != 0)
        cout << "QryContract Error:" << iErr << endl;
    else
        return;
}
//��ȡ��Լ�б�
void Quote::QryContractInfo(const TapAPIQuoteCommodityInfo* info)
{
    m_uiSessionID = 0;
    TapAPICommodity qryReq;
    memset(&qryReq, 0, sizeof(qryReq));
    memcpy(qryReq.ExchangeNo,info->Commodity.ExchangeNo, sizeof(TAPISTR_10));
    memcpy(qryReq.CommodityNo,info->Commodity.CommodityNo, sizeof(TAPISTR_10));
    qryReq.CommodityType = info->Commodity.CommodityType;
    
    int iErr = m_pAPI->QryContract(&m_uiSessionID, &qryReq);
    //�ͷţ����ܻᵼ���ڴ����
    //delete& qryReq;
    if (iErr != 0)
        cout << "QryContract Error:" << iErr << endl;
    else
        return;
}
//��ȡ��������ԼƷ���б�
void Quote::QryCommdityInfo()
{
    m_uiSessionID = 0;
    int iErr = m_pAPI->QryCommodity(&m_uiSessionID);
    if (iErr !=0 )
        cout << "QryCommodity Error:" << iErr << endl;
}
//��½������
void Quote::Login_(KrakenBasicConf info) {

    if (NULL == m_pAPI)
    {
        cout << "Error: m_pAPI is NULL." << endl;
        return;
    }
    TAPIINT32 iErr = TAPIERROR_SUCCEED;
    m_uiSessionID = 0;

    TapAPIQuoteLoginAuth stLoginAuth;										//�����½��֤��Ϣ
    memset(&stLoginAuth, 0, sizeof(stLoginAuth));						//��ʼ�� //[stContract ��Լ����ṹ] 
    strcpy(stLoginAuth.UserNo, info.UserNo);						//�û���
    strcpy(stLoginAuth.Password, info.Password);					//����
    stLoginAuth.ISModifyPassword = APIYNFLAG_NO;						//�Ƿ��޸�����
    stLoginAuth.ISDDA = APIYNFLAG_NO;									//�Ƿ���Ҫ��̬��֤
 //�������ļ���ȡ���趨������IP���˿�
    iErr = m_pAPI->SetHostAddress(info.Address, info.QuotePort);
    if (TAPIERROR_SUCCEED != iErr) {									//��֤������IP��˿�	
        cout << "SetHostAddress Error:" << iErr << endl;
        cout << "������IP��˿����ô���,������������ļ�!" << endl;
        system("pause");
        return;
    }
    iErr = m_pAPI->Login(&stLoginAuth);		//��½������
    if (TAPIERROR_SUCCEED != iErr) {									//��֤������IP��˿�	
        cout << "Login Error:" << iErr << endl;
        system("pause");
        return;
    }
    m_Event.WaitEvent();					//�ȴ�APIReady
    if (!m_bIsAPIReady) {
        return;
    }
}

//����
void Quote::Run_()
{
   //��½
   //Login_(getBasicConf());
   //���������ڴ�
   sm_tool1 = comm_tool.create();
   deliver_data = (deliver_)MapViewOfFile(sm_tool1.MapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
   //��ȡ����������Ʒ�ֱ����
   //QryCommdityInfo();
   //QryContractInfo();
   cout << "��־���ݹ����ڴ沿��" << endl;
   test_DataDeliver();
   

   while (true) {
       m_Event.WaitEvent();
   }

}

void Quote::OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo* info)
{
    if(TAPIERROR_SUCCEED == errorCode) 
    {
		cout << "��¼�ɹ����ȴ�API��ʼ��..." << endl;
	} 
    else 
    {
		cout << "��¼ʧ�ܣ�������:" << errorCode << endl;
		m_Event.SignalEvent();	
	}
}

void Quote::OnAPIReady()
{
    cout << "API��ʼ�����" << endl;
	m_bIsAPIReady = true;
	m_Event.SignalEvent();	
}

void Quote::OnDisconnect(TAPIINT32 reasonCode)
{
    cout << "API�Ͽ�,�Ͽ�ԭ��:"<<reasonCode << endl;
}
//���ظ���������Ʒ�ֱ����
void Quote::OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo* info)
{
    if(info)
    {
        if (errorCode != 0) {
            cout << "__FUNCTION__ .ERROR:" << errorCode << endl;
        }
        else
        {
            cout << info->Commodity.ExchangeNo << "," << info->Commodity.CommodityType << "," << info->Commodity.CommodityNo << "," << info->ContractSize << endl;
            //��ȡ����Ʒ�ֵĺ�Լ�����
            QryContractInfo(info);
        }
     
    }
}
//����ָ��Ʒ�ֵ����к�Լ����
void Quote::OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo* info)
{
    if (info) {
        if (errorCode != 0) {
            cout << "__FUNCTION__ .ERROR:" << errorCode << endl;
        }
        else {
            cout << info->Contract.Commodity.ExchangeNo << ","
                << info->Contract.Commodity.CommodityType << ","
                << info->Contract.Commodity.CommodityNo
                << info->Contract.ContractNo1 << "&"
                << info->Contract.ContractNo2 << " . "
                << info->LastTradeDate << endl;
            //���ݸ�to_log

            //����
            SubscribeQuote(info);
        }
        
    }
}
//���Ľ��
void Quote::OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole* info)
{
    if (info) {
        cout << info->Contract.Commodity.ExchangeNo << ","
            << info->Contract.Commodity.CommodityType << ","
            << info->Contract.Commodity.CommodityNo
            << info->Contract.ContractNo1 << "&"
            << info->Contract.ContractNo2 << ".sub"
            << endl;
    }
   
    // ���ݣ�����folder

    
    /*cout << info->Contract.Commodity.ExchangeNo << "|" << info->Contract.Commodity.CommodityType << "|" << info->Contract.Commodity.CommodityNo << "|"
             << info->Contract.ContractNo1 << "|" << info->Contract.CallOrPutFlag1 << "|" << info->Contract.StrikePrice1 << "|"
             << info->Contract.ContractNo2 << "|" << info->Contract.CallOrPutFlag2 << "|" << info->Contract.StrikePrice2 << "|"
             << " CurrencyNo:" << info->CurrencyNo << " TradingState:" << info->TradingState << " DateTimeStamp:" << info->DateTimeStamp;
    if(info->QPreClosingPrice > 0)
        cout << " QPreClosingPrice:" << info->QPreClosingPrice;
    if(info->QPreClosingPrice > 0)
        cout << " QPreSettlePrice:" << info->QPreSettlePrice;
    if(info->QPrePositionQty > 0)
        cout << " QPrePositionQty:" << info->QPrePositionQty;
    if(info->QOpeningPrice > 0)
        cout << " QOpeningPrice:" << info->QOpeningPrice;
    if(info->QLastPrice > 0)
        cout << " QLastPrice:" << info->QLastPrice;
    if(info->QHighPrice > 0)
        cout << " QHighPrice:" << info->QHighPrice;
    if(info->QLowPrice > 0)
        cout << " QLowPrice:" << info->QLowPrice;
    if(info->QHisHighPrice > 0)
        cout << " QHisHighPrice:" << info->QHisHighPrice;
    if(info->QHisLowPrice > 0)
        cout << " QHisLowPrice:" << info->QHisLowPrice;
    if(info->QLimitUpPrice > 0)
        cout << " QLimitUpPrice:" << info->QLimitUpPrice;
    if(info->QLimitDownPrice > 0)
        cout << " QLimitDownPrice:" << info->QLimitDownPrice;
    if(info->QTotalQty > 0)
        cout << " QTotalQty:" << info->QTotalQty;
    if(info->QTotalTurnover > 0)
        cout << " QTotalTurnover:" << info->QTotalTurnover;
    if(info->QPositionQty > 0)
        cout << " QPositionQty:" << info->QPositionQty;
    if(info->QAveragePrice > 0)
        cout << " QAveragePrice:" << info->QAveragePrice;
    if(info->QClosingPrice > 0)
        cout << " QClosingPrice:" << info->QClosingPrice;
    if(info->QSettlePrice > 0)
        cout << " QSettlePrice:" << info->QSettlePrice;
    if(info->QLastQty > 0)
        cout << " QLastQty:" << info->QLastQty;
    if(info->QBidPrice[0] > 0)
        cout << " QBidPrice[0]:" << info->QBidPrice[0];
    if(info->QBidQty[0] > 0)
        cout << " QBidQty[0]:" << info->QBidQty[0];
    if(info->QAskPrice[0] > 0)
        cout << " QAskPrice[0]:" << info->QAskPrice[0];
    if(info->QAskQty[0] > 0)
        cout << " QAskQty[0]:" << info->QAskQty[0];
    if(info->QImpliedBidPrice > 0)
        cout << " QImpliedBidPrice:" << info->QImpliedBidPrice;
    if(info->QImpliedBidQty > 0)
        cout << " QImpliedBidQty:" << info->QImpliedBidQty;
    if(info->QImpliedAskPrice > 0)
        cout << " QImpliedAskPrice:" << info->QImpliedAskPrice;
    if(info->QImpliedAskQty > 0)
        cout << " QImpliedAskQty:" << info->QImpliedAskQty;
    if(info->QPreDelta > 0)
        cout << " QPreDelta:" << info->QPreDelta;
    if(info->QCurrDelta > 0)
        cout << " QCurrDelta:" << info->QCurrDelta;
    if(info->QInsideQty > 0)
        cout << " QInsideQty:" << info->QInsideQty;
    if(info->QOutsideQty > 0)
        cout << " QOutsideQty:" << info->QOutsideQty;
    if(info->QTurnoverRate > 0)
        cout << " QTurnoverRate:" << info->QTurnoverRate;
    if(info->Q5DAvgQty > 0)
        cout << " Q5DAvgQty:" << info->Q5DAvgQty;
    if(info->QPERatio > 0)
        cout << " QPERatio:" << info->QPERatio;
    if(info->QTotalValue > 0)
        cout << " QTotalValue:" << info->QTotalValue;
    if(info->QNegotiableValue > 0)
        cout << " QNegotiableValue:" << info->QNegotiableValue;
    if(info->QPositionTrend > 0)
        cout << " QPositionTrend:" << info->QPositionTrend;
    if(info->QChangeSpeed > 0)
        cout << " QChangeSpeed:" << info->QChangeSpeed;
    if(info->QChangeRate > 0)
        cout << " QChangeRate:" << info->QChangeRate;
    if(info->QChangeValue > 0)
        cout << " QChangeValue:" << info->QChangeValue;
    if(info->QSwing > 0)
        cout << " QSwing:" << info->QSwing;
    if(info->QTotalBidQty > 0)
        cout << " QTotalBidQty" << info->QTotalBidQty;
    if(info->QTotalAskQty > 0)
        cout << " QTotalAskQty:" << info->QTotalAskQty;
    
    cout << ";"<< endl;*/
}
//ȡ�����Ľ��
void Quote::OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract* info)
{
    if(info)
        cout << info->Commodity.CommodityNo << "," << info->ContractNo1;
}
//���鷵��
void Quote::OnRtnQuote(const TapAPIQuoteWhole* info)
{
    DataDeliver(info);
    if (info) {

        cout << info->Contract.Commodity.ExchangeNo << ","
            << info->Contract.Commodity.CommodityType << ","
            << info->Contract.Commodity.CommodityNo
            << info->Contract.ContractNo1 << "&"
            << info->Contract.ContractNo2 << "."
            << info->QAskPrice
            << endl;

        //���ݸ�to_log
        
    }
}

void Quote::TestFile()
{
    
    //���������ڴ�
    sm_tool2 = comm_tool.createfileshare();
    mk= (MK)MapViewOfFile(sm_tool2.MapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
    cout <<"�ļ������ڴ沿�֣�"<< endl;
    mk->bourse= getstr().c_str();
    mk->number = "0100001";
    system("pause");
    ReleaseMutex(sm_tool2.L_Mutex);
    SetEvent(sm_tool2.L_Event);
    cout << "TestFile deliver finish." << endl;

   /* while (true) {
        m_Event.WaitEvent();
    }*/

}
string Quote::getstr()
{
    return "eeerr";
}
