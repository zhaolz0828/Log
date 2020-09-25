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
//获取登陆信息
KrakenBasicConf Quote::getBasicConf() {
    KrakenBasicConf info;
    
    string path = comm_tool.GetProgramDir(2) + "\\configuration\\fetcher\\basicConfiguration.csv";
    const char* c_path = path.c_str();
    cout << "基础配置文件路径" << c_path << endl;
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
            case 2://用户
                strcpy(info.UserNo, word.c_str());
                comm_tool.printOnScreen("登陆用户", word.c_str());
                break;
            case 4://密码
                strcpy(info.Password, word.c_str());
                break;
            case 6://IP
                strcpy(info.Address, word.c_str());
                comm_tool.printOnScreen("服务器IP", word.c_str());
                break;
            case 8://交易端口
                info.TradePort = atoi(word.c_str());
                comm_tool.printOnScreen("服务器交易端口", word.c_str());
                break;
            case 10://行情端口
                info.QuotePort = atoi(word.c_str());
                comm_tool.printOnScreen("服务器行情端口", word.c_str());
                break;
            case 12://授权码
                strcpy(info.AuthCode, word.c_str());
                comm_tool.printOnScreen("授权码", word.c_str());
                break;
            case 14://程序版本号
                strcpy(info.AppID, word.c_str());
                comm_tool.printOnScreen("程序版本号", word.c_str());
                break;
           
            }
        }
        counting = counting + 1;
    }
    info.ISModifyPassword = APIYNFLAG_NO;				//是否修改密码
    info.ISDDA = APIYNFLAG_NO;							//是否需要动态验证

    return info;
}
//数据传递
void Quote::DataDeliver(const TapAPIQuoteWhole* info) {

    if (info)
    {
		deliver_data->Contract					=info->Contract;					///<合约
		strcpy(deliver_data->CurrencyNo,info->CurrencyNo);							///<币种编号
		deliver_data->TradingState				=info->TradingState;				///<交易状态。1集合竞价;2集合竞价撮合;3连续交易;4交易暂停;5闭市
		strcpy(deliver_data->DateTimeStamp,info->DateTimeStamp);					///<时间戳
		deliver_data->QPreClosingPrice			=info->QPreClosingPrice;			///<昨收盘价
		deliver_data->QPreSettlePrice			=info->QPreSettlePrice;				///<昨结算价
		deliver_data->QPrePositionQty			=info->QPrePositionQty;				///<昨持仓量
		deliver_data->QOpeningPrice				=info->QOpeningPrice;				///<开盘价
		deliver_data->QLastPrice				=info->QLastPrice;					///<最新价
		deliver_data->QHighPrice				=info->QHighPrice;					///<最高价
		deliver_data->QLowPrice					=info->QLowPrice;					///<最低价
		deliver_data->QHisHighPrice				=info->QHisHighPrice;				///<历史最高价
		deliver_data->QHisLowPrice				=info->QHisLowPrice;				///<历史最低价
		deliver_data->QLimitUpPrice				=info->QLimitUpPrice;				///<涨停价
		deliver_data->QLimitDownPrice			=info->QLimitDownPrice;				///<跌停价
		deliver_data->QTotalQty					=info->QTotalQty;					///<当日总成交量
		deliver_data->QTotalTurnover			=info->QTotalTurnover;				///<当日成交金额
		deliver_data->QPositionQty				=info->QPositionQty;				///<持仓量
		deliver_data->QAveragePrice				=info->QAveragePrice;				///<均价
		deliver_data->QClosingPrice				=info->QClosingPrice;				///<收盘价
		deliver_data->QSettlePrice				=info->QSettlePrice;				///<结算价
		deliver_data->QLastQty					=info->QLastQty;					///<最新成交量
		deliver_data->QBidPrice[0]				=info->QBidPrice[0];				///<买价1档
		deliver_data->QBidQty[0]				=info->QBidQty[0];					///<买量1档
		deliver_data->QAskPrice[0]				=info->QAskPrice[0];				///<卖价1档
		deliver_data->QAskQty[0]				=info->QAskQty[0];					///<卖量1档
		deliver_data->QImpliedBidPrice			=info->QImpliedBidPrice;			///<隐含买价
		deliver_data->QImpliedBidQty			=info->QImpliedBidQty;				///<隐含买量
		deliver_data->QImpliedAskPrice			=info->QImpliedAskPrice;			///<隐含卖价
		deliver_data->QImpliedAskQty			=info->QImpliedAskQty;				///<隐含卖量
		deliver_data->QPreDelta					=info->QPreDelta;					///<昨虚实度
		deliver_data->QCurrDelta				=info->QCurrDelta;					///<今虚实度
		deliver_data->QInsideQty				=info->QInsideQty;					///<内盘量
		deliver_data->QOutsideQty				=info->QOutsideQty;					///<外盘量
		deliver_data->QTurnoverRate				=info->QTurnoverRate;				///<换手率
		deliver_data->Q5DAvgQty					=info->Q5DAvgQty;					///<五日均量
		deliver_data->QPERatio					=info->QPERatio;					///<市盈率
		deliver_data->QTotalValue				=info->QTotalValue;					///<总市值
		deliver_data->QNegotiableValue			=info->QNegotiableValue;			///<流通市值
		deliver_data->QPositionTrend			=info->QPositionTrend;				///<持仓走势
		deliver_data->QChangeSpeed				=info->QChangeSpeed;				///<涨速
		deliver_data->QChangeRate				=info->QChangeRate;					///<涨幅
		deliver_data->QChangeValue				=info->QChangeValue;				///<涨跌值
		deliver_data->QSwing					=info->QSwing;						///<振幅
		deliver_data->QTotalBidQty				=info->QTotalBidQty;				///<委买总量
		deliver_data->QTotalAskQty				=info->QTotalAskQty;				///<委卖总量
		deliver_data->UnderlyContract			=info->UnderlyContract;				///<虚拟合约对应的真实合约

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
//订阅
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
    //释放
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
    //释放
    //delete &qryReq;
    if (iErr != 0)
        cout << "QryContract Error:" << iErr << endl;
    else
        return;
}
//拉取合约列表
void Quote::QryContractInfo(const TapAPIQuoteCommodityInfo* info)
{
    m_uiSessionID = 0;
    TapAPICommodity qryReq;
    memset(&qryReq, 0, sizeof(qryReq));
    memcpy(qryReq.ExchangeNo,info->Commodity.ExchangeNo, sizeof(TAPISTR_10));
    memcpy(qryReq.CommodityNo,info->Commodity.CommodityNo, sizeof(TAPISTR_10));
    qryReq.CommodityType = info->Commodity.CommodityType;
    
    int iErr = m_pAPI->QryContract(&m_uiSessionID, &qryReq);
    //释放？可能会导致内存溢出
    //delete& qryReq;
    if (iErr != 0)
        cout << "QryContract Error:" << iErr << endl;
    else
        return;
}
//拉取服务器合约品种列表
void Quote::QryCommdityInfo()
{
    m_uiSessionID = 0;
    int iErr = m_pAPI->QryCommodity(&m_uiSessionID);
    if (iErr !=0 )
        cout << "QryCommodity Error:" << iErr << endl;
}
//登陆服务器
void Quote::Login_(KrakenBasicConf info) {

    if (NULL == m_pAPI)
    {
        cout << "Error: m_pAPI is NULL." << endl;
        return;
    }
    TAPIINT32 iErr = TAPIERROR_SUCCEED;
    m_uiSessionID = 0;

    TapAPIQuoteLoginAuth stLoginAuth;										//行情登陆认证信息
    memset(&stLoginAuth, 0, sizeof(stLoginAuth));						//初始化 //[stContract 合约编码结构] 
    strcpy(stLoginAuth.UserNo, info.UserNo);						//用户名
    strcpy(stLoginAuth.Password, info.Password);					//密码
    stLoginAuth.ISModifyPassword = APIYNFLAG_NO;						//是否修改密码
    stLoginAuth.ISDDA = APIYNFLAG_NO;									//是否需要动态验证
 //从配置文件读取，设定服务器IP、端口
    iErr = m_pAPI->SetHostAddress(info.Address, info.QuotePort);
    if (TAPIERROR_SUCCEED != iErr) {									//验证服务器IP与端口	
        cout << "SetHostAddress Error:" << iErr << endl;
        cout << "服务器IP或端口设置错误,请检查基础配置文件!" << endl;
        system("pause");
        return;
    }
    iErr = m_pAPI->Login(&stLoginAuth);		//登陆服务器
    if (TAPIERROR_SUCCEED != iErr) {									//验证服务器IP与端口	
        cout << "Login Error:" << iErr << endl;
        system("pause");
        return;
    }
    m_Event.WaitEvent();					//等待APIReady
    if (!m_bIsAPIReady) {
        return;
    }
}

//运行
void Quote::Run_()
{
   //登陆
   //Login_(getBasicConf());
   //创建共享内存
   sm_tool1 = comm_tool.create();
   deliver_data = (deliver_)MapViewOfFile(sm_tool1.MapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
   //拉取各个交易所品种编码表
   //QryCommdityInfo();
   //QryContractInfo();
   cout << "日志内容共享内存部分" << endl;
   test_DataDeliver();
   

   while (true) {
       m_Event.WaitEvent();
   }

}

void Quote::OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo* info)
{
    if(TAPIERROR_SUCCEED == errorCode) 
    {
		cout << "登录成功，等待API初始化..." << endl;
	} 
    else 
    {
		cout << "登录失败，错误码:" << errorCode << endl;
		m_Event.SignalEvent();	
	}
}

void Quote::OnAPIReady()
{
    cout << "API初始化完成" << endl;
	m_bIsAPIReady = true;
	m_Event.SignalEvent();	
}

void Quote::OnDisconnect(TAPIINT32 reasonCode)
{
    cout << "API断开,断开原因:"<<reasonCode << endl;
}
//返回各个交易所品种编码表
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
            //拉取各个品种的合约代码表
            QryContractInfo(info);
        }
     
    }
}
//返回指定品种的所有合约代码
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
            //传递给to_log

            //订阅
            SubscribeQuote(info);
        }
        
    }
}
//订阅结果
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
   
    // 传递，建立folder

    
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
//取消订阅结果
void Quote::OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract* info)
{
    if(info)
        cout << info->Commodity.CommodityNo << "," << info->ContractNo1;
}
//行情返回
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

        //传递给to_log
        
    }
}

void Quote::TestFile()
{
    
    //创建共享内存
    sm_tool2 = comm_tool.createfileshare();
    mk= (MK)MapViewOfFile(sm_tool2.MapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
    cout <<"文件共享内存部分："<< endl;
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
