#include <comm_tool.h>

comm_tool::comm_tool() {

}

comm_tool::~comm_tool() {

}

string comm_tool::GetProgramDir(int target)
{
	char exeFullPath[MAX_PATH];			// Full path 
	string strPath = "";
	int pos;
	int strata = 0;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = (string)exeFullPath;		// Get full path of the file 
	while (strata < target)
	{
		pos = strPath.find_last_of('\\', strPath.length());
		strPath = strPath.substr(0, pos);
		strata++;
	}
	return strPath;						// Return the directory without the file name 
}

void comm_tool::printOnScreen(string title, string content) {
	cout << "[" << title << "] : " << content << endl;
}

ShareMemoryTool comm_tool::create() {

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

ShareMemoryTool comm_tool::find() {

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
ShareMemoryTool comm_tool::createfileshare() {

	ShareMemoryTool tool;
	tool.MapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		BUF_SIZE,
		"to_logfile"
	);
	tool.L_Mutex = CreateMutex(NULL, FALSE, "to_log_mutexfile");
	tool.L_Event = CreateEvent(NULL, FALSE, FALSE, "to_log_eventfile");
	if (tool.MapFile == NULL) cout << "bad MapFile..." << endl;
	else cout << "file MapFile created..." << endl;

	return tool;
}

ShareMemoryTool comm_tool::findfileshare() {

	ShareMemoryTool tool;
	tool.MapFile = OpenFileMapping(
		FILE_MAP_READ,
		FALSE,
		"to_logfile"
	);
	if (tool.MapFile == NULL)
	{
		cout << "fileshare memory not find,2s ag..." << endl;
		Sleep(2000);
		return findfileshare();
	}
	else {
		tool.L_Event = OpenEvent(EVENT_ALL_ACCESS, FALSE, "to_log_eventfile");
		tool.L_Mutex = OpenMutex(MUTEX_ALL_ACCESS, TRUE, "to_log_mutexfile");
		cout << "found fileshare..." << endl;
		return tool;
	}
}