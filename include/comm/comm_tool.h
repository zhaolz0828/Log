#include <system_middleware.h>
#include <comm_struct.h>

#define BUF_SIZE 256
class comm_tool
{
public:
	comm_tool();
	~comm_tool();

	string GetProgramDir(int target);
	void printOnScreen(string title, string content);

	//share memory 
	ShareMemoryTool create();
	ShareMemoryTool find();
	ShareMemoryTool createfileshare();
	ShareMemoryTool findfileshare();
};

