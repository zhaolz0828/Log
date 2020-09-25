#include <forTestPass.h>
#include<Windows.h>

test_::test_() {

}

test_::~test_() {
		
}

void test_::pass(ShareMemoryTool tool) {

	
	return;
}

void test_::BufferStart(ShareMemoryTool tool) {

	deliver_destination = (deliver_)MapViewOfFile(tool.MapFile, FILE_MAP_READ, 0, 0, BUF_SIZE);
	cout << "ready..." << endl;
	if (deliver_destination)
	{
		//while (1) {
			WaitForSingleObject(tool.L_Event, INFINITE);
			WaitForSingleObject(tool.L_Mutex, INFINITE);
			cache.push(deliver_destination);
			deliver_ Front = cache.front();
			cout << "当前存入缓存的内容是:"
				<< "\n Contract.Commodity.CommodityNo: " << Front->Contract.Commodity.CommodityNo
				<< "\n Contract.ContractNo1: " << Front->Contract.ContractNo1
				<< "\n Contract.ContractNo2: " << Front->Contract.ContractNo2
				<< "\n date time stamp: " << Front->DateTimeStamp
				<< "\n ask price[0]: " << Front->QAskPrice[0]
				<< "\n ask qty[0]: " << Front->QAskQty[0]
				<< endl;

			Sleep(2000);
			ReleaseMutex(tool.L_Mutex);
			
			/*else
			{
				CloseHandle(tool.L_Mutex);
				UnmapViewOfFile(pTrans);
				return;
			}*/
		//}
	}
}
void test_::fileStart(ShareMemoryTool tool) {
	mk = ( MK)MapViewOfFile(tool.MapFile, FILE_MAP_READ, 0, 0, BUF_SIZE);
	cout << "file ready..." << endl;
	//if (mk)
	//{
		//while (1) {
			WaitForSingleObject(tool.L_Event, INFINITE);
			WaitForSingleObject(tool.L_Mutex, INFINITE);
			cout << "文件部分开始:"
				<< "\n bourse: " << mk->bourse.c_str()
				<< "\n number: " << mk->number.c_str()
				<< endl;


			//创建文件,等待缓存写入
			ofstream out("C:\\Users\\zhaol\\Desktop\\log.csv");
			Sleep(2000);
			ReleaseMutex(tool.L_Mutex);

			/*else
			{
				CloseHandle(tool.L_Mutex);
				UnmapViewOfFile(pTrans);
				return;
			}*/
	
}