

extern int test_dylibutil_main(int, char**);
extern int test_baselog_main(int, char**);

int main(int argc, char **argv)
{
	test_dylibutil_main(argc, argv);
	test_baselog_main(argc,argv);

	return 0;
}
