#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int rmdir_r(const char* path)
{
	DIR *dirp = NULL;
	struct dirent *dir = NULL;
	struct stat stat_buf;
	int ret;
	int dir_empty = 1;
	char subpath[256] = {'\0'};
	
	if (!path)
	{
		printf("input path err\n");
		return -1;
	}
	printf("path: %s\n", path);
	
	if (lstat(path, &stat_buf) < 0)
	{
		printf("lstat path: %s failed\n", path);
		return -1;
	}
	if (!S_ISDIR(stat_buf.st_mode)) /* not a dir */
	{
		ret = unlink(path);
		if (ret)
		{
			printf("unlink %s failed\n", path);
		}
		return ret;
	}

	dirp = opendir(path);
	if (!dirp)
	{
		printf("open dir:%s failed\n", path);
		return -1;
	}

	while ((dir = readdir(dirp)))
	{
		if (strncmp(dir->d_name, ".", sizeof(dir->d_name)) == 0 ||
			strncmp(dir->d_name, "..", sizeof(dir->d_name)) == 0)
		{
			continue;	
		}
		
		snprintf(subpath, sizeof(subpath), "%s/%s", path, dir->d_name);
		printf("subpath: %s\n", subpath);

		dir_empty = ~rmdir_r(subpath);
	}

	if (closedir(dirp) < 0)
	{
		printf("closedir %s failed.\n", path);
	}

	if (dir_empty)
	{
		ret = remove(path);
	}

	return ret;
}

#ifdef TEST
int main(int argc, char **argv)
{
	rmdir_r(argv[1]);
	return 0;
}
#endif
