/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: song
 *
 * Created on 2018年3月16日, 下午2:10
 */

#include <Quote.h>


int main(int argc, char** argv) 
{
    cout << GetTapQuoteAPIVersion() << endl;
    
    TAPIINT32 iResult = TAPIERROR_SUCCEED;
    TapAPIApplicationInfo stAppInfo;
    //设置日志路径
	strcpy_s(stAppInfo.AuthCode, "");
	strcpy_s(stAppInfo.KeyOperationLogPath, "..\\tapLogFile");
    //创建api实例
    ITapQuoteAPI* pAPI = CreateTapQuoteAPI(&stAppInfo, iResult);
    if (NULL == pAPI)
    {
        cout << "创建API实例失败，错误码：" << iResult <<endl;
        return 0;
    }
    //获取用户信息，登陆服务器
    Quote quote;
    pAPI->SetAPINotify(&quote);
    quote.SetQuoteAPI(pAPI);
    quote.TestFile();
    quote.Run_();
    
    system("pause");
    return 0;
}

