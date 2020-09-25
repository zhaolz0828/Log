#include <main_pass.h>
#include <mutex>

mutex ThreadMutex;  //线程互斥对象
test_ test_1;

//实现缓存
void ThreadCache()
{
	ThreadMutex.lock(); //同步数据锁
	cout << "\n缓存开始工作" << endl;
	test_1.BufferStart(test_1.comm_tool.find());
	Sleep(1000);
	ThreadMutex.unlock();  //解除锁定
	cout << "\n缓存暂停工作" << endl;
	 
}



//读出缓存写入相应文件
void ThreadReadCache()
{
	ThreadMutex.lock();
	//读出缓存释放缓存空间
	cout << "\n开始读出缓存" << endl;
	deliver_  TextReadCache;
	TextReadCache =test_1.cache.back();

	//ofstream out("C:\\Users\\zhaol\\Desktop\\log.csv"); //创建文件	
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


	cout << "\n读出缓存数据"
		<< "\n Contract.Commodity.CommodityNo: " << TextReadCache->Contract.Commodity.CommodityNo
		<< "\n Contract.ContractNo1: " << TextReadCache->Contract.ContractNo1
		<< "\n Contract.ContractNo2: " << TextReadCache->Contract.ContractNo2
		<< "\n date time stamp: " << TextReadCache->DateTimeStamp
		<< "\n ask price[0]: " << TextReadCache->QAskPrice[0]
		<< "\n ask qty[0]: " << TextReadCache->QAskQty[0]
		<< endl; 
	//释放缓存空间
	test_1.cache.pop();
	Sleep(3000);
	ThreadMutex.unlock();
	cout << "\n读缓存结束" << endl;
}



int main() {
	cout << "\t测试开始" << endl;
   //文件部分开始创建文件	
	test_1.fileStart(test_1.comm_tool.findfileshare());
	//线程启动
	thread task01(ThreadCache);
	thread task02(ThreadReadCache);
	task01.detach();
	task02.detach();
	system("pause");
	return 0;
}
