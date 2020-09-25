#include <go_sharememory.h>


class goto_log:go_sharememory
{
public:
	goto_log();
	~goto_log();

	go_sharememory sharememory;

	void forTestReadShareMemory(ShareMemoryTool tool);
	void go_folder();
	void go_file();


private:
	
};

