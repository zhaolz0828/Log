/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: song
 *
 * Created on 2018��3��16��, ����2:10
 */

#include <Quote.h>


int main(int argc, char** argv) 
{
    cout << GetTapQuoteAPIVersion() << endl;
    
    TAPIINT32 iResult = TAPIERROR_SUCCEED;
    TapAPIApplicationInfo stAppInfo;
    //������־·��
	strcpy_s(stAppInfo.AuthCode, "");
	strcpy_s(stAppInfo.KeyOperationLogPath, "..\\tapLogFile");
    //����apiʵ��
    ITapQuoteAPI* pAPI = CreateTapQuoteAPI(&stAppInfo, iResult);
    if (NULL == pAPI)
    {
        cout << "����APIʵ��ʧ�ܣ������룺" << iResult <<endl;
        return 0;
    }
    //��ȡ�û���Ϣ����½������
    Quote quote;
    pAPI->SetAPINotify(&quote);
    quote.SetQuoteAPI(pAPI);
    quote.TestFile();
    quote.Run_();
    
    system("pause");
    return 0;
}

