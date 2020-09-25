#include <go_sharememory.h>

go_sharememory::go_sharememory()
{
}

go_sharememory::~go_sharememory()
{
}

ShareMemoryTool go_sharememory::create() {

	ShareMemoryTool tool;
	tool.MapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		BUF_SIZE,
		"to_log"
		);
	tool.L_Mutex = CreateMutex(NULL, FALSE, "to_log_mutex");
	tool.L_Event = CreateEvent(NULL, FALSE, FALSE, "to_log_event");
	if (tool.MapFile == NULL) cout << "bad MapFile..." << endl;
	else cout << "MapFile created..." << endl;

	return tool;
}

ShareMemoryTool go_sharememory::find() {

	ShareMemoryTool tool;
	tool.MapFile = OpenFileMapping(
		FILE_MAP_READ,
		FALSE,
		"to_log"
		);
	if (tool.MapFile == NULL)
	{
		cout << "share memory not find,2s ag..." << endl;
		Sleep(2000);
		return find();
	}
	else {
		tool.L_Event = OpenEvent(EVENT_ALL_ACCESS, FALSE, "to_log_event");
		tool.L_Mutex = OpenMutex(MUTEX_ALL_ACCESS, TRUE, "to_log_mutex");
		cout << "found..." << endl;
		return tool;
	}
}

