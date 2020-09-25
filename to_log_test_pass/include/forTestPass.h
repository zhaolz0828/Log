#include <comm_tool.h>
#include<queue>
class test_ :comm_tool
{
public:
	test_();
	~test_();

	comm_tool comm_tool;

	TapAPIQuoteWhole data;
	deliver_ deliver_destination = &data;

	MockFile Mk;
	MK mk= &Mk;

	void pass(ShareMemoryTool tool);
	void BufferStart(ShareMemoryTool tool);
	void fileStart(ShareMemoryTool tool);
    queue <deliver_> cache;
};

