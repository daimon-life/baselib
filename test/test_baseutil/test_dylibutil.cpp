#include "DylibUtil.h"

int test_dylibutil_main(int argc, char **argv)
{
	void* hModule = CDylibUtil::LoadDylib("base.dll");
	return 0;
}

