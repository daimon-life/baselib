#include "Baselog.h"


extern std::string GetExecuteDir();

CBaseLog* g_pLog;

int test_baselog_main(int argc, char **argv)
{
	g_pLog = new CBaseLog();

	LOG_INIT(std::string(GetExecuteDir() + "test_baselog.log").c_str(), true);
	LOG_INFO("%s", "log info show here ...");
	LOG_WARN("%s", "log warn show here ...");
	LOG_EROR("%s", "log eror show here ...");

	delete g_pLog;
	g_pLog = nullptr;

	return 0;
}
