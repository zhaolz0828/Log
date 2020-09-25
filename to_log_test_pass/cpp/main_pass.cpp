#include <main_pass.h>
#include <mutex>

mutex ThreadMutex;  //�̻߳������
test_ test_1;

//ʵ�ֻ���
void ThreadCache()
{
	ThreadMutex.lock(); //ͬ��������
	cout << "\n���濪ʼ����" << endl;
	test_1.BufferStart(test_1.comm_tool.find());
	Sleep(1000);
	ThreadMutex.unlock();  //�������
	cout << "\n������ͣ����" << endl;
	 
}



//��������д����Ӧ�ļ�
void ThreadReadCache()
{
	ThreadMutex.lock();
	//���������ͷŻ���ռ�
	cout << "\n��ʼ��������" << endl;
	deliver_  TextReadCache;
	TextReadCache =test_1.cache.back();

	//ofstream out("C:\\Users\\zhaol\\Desktop\\log.csv"); //�����ļ�	
	ofstream outFile;
	outFile.open("C:\\Users\\zhaol\\Desktop\\log.csv", ios::out);
	outFile << "\nLogData"
		<< "\n Contract.Commodity.CommodityNo: "<<"," << TextReadCache->Contract.Commodity.CommodityNo
		<< "\n Contract.ContractNo1: " << "," << TextReadCache->Contract.ContractNo1
		<< "\n Contract.ContractNo2: " << "," << TextReadCache->Contract.ContractNo2
		<< "\n date time stamp: " << "," << TextReadCache->DateTimeStamp
		<< "\n ask price[0]: " << "," << TextReadCache->QAskPrice[0]
		<< "\n ask qty[0]: " << "," << TextReadCache->QAskQty[0]
		<< endl;


	cout << "\n������������"
		<< "\n Contract.Commodity.CommodityNo: " << TextReadCache->Contract.Commodity.CommodityNo
		<< "\n Contract.ContractNo1: " << TextReadCache->Contract.ContractNo1
		<< "\n Contract.ContractNo2: " << TextReadCache->Contract.ContractNo2
		<< "\n date time stamp: " << TextReadCache->DateTimeStamp
		<< "\n ask price[0]: " << TextReadCache->QAskPrice[0]
		<< "\n ask qty[0]: " << TextReadCache->QAskQty[0]
		<< endl; 
	//�ͷŻ���ռ�
	test_1.cache.pop();
	Sleep(3000);
	ThreadMutex.unlock();
	cout << "\n���������" << endl;
}



int main() {
	cout << "\t���Կ�ʼ" << endl;
   //�ļ����ֿ�ʼ�����ļ�	
	test_1.fileStart(test_1.comm_tool.findfileshare());
	//�߳�����
	thread task01(ThreadCache);
	thread task02(ThreadReadCache);
	task01.detach();
	task02.detach();
	system("pause");
	return 0;
}
