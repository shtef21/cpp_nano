#ifndef CURR_DIR_
#define CURR_DIR_

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#elif __linux__
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

// set the working directory in the buffer and return its length
int curr_dir(char *buff, int max_len)
{
	char *s = GetCurrentDir(buff, max_len);
	if (!s)
		return 0;
	while (*(++s));
	return s - buff;
}

#endif
