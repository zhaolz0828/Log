#include <system_middleware.h>
#include <comm_struct.h>

#define BUF_SIZE 256

class go_sharememory
{
public:
	go_sharememory();
	~go_sharememory();

	ShareMemoryTool create();
	ShareMemoryTool find();
	
private:

};

