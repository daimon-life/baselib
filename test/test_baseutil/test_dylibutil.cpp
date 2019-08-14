#include "DylibUtil.h"

int main(int argc, char **argv)
{
	void* hModule = CDylibUtil::LoadDylib("base.dll");
	return 0;
}
