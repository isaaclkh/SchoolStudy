#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

void rePath(DIR * dname);

int main(){
	char pwd[1080];
	DIR * spdir;

	getcwd(pwd, sizeof(pwd));

	if ((spdir = opendir(pwd)) == NULL)
		printf("error\n");

	rePath(spdir);

}

void rePath(DIR * dname){
	char pwd[1080];
	DIR *spdir;
	struct dirent *entry;
	struct stat buff;
	struct tm *t;
	char fpath[3000];

	DIR * dir;

	getcwd(pwd, sizeof(pwd));
	

	while ((entry = readdir(dname)) != NULL)
	{
		stat(entry->d_name, &buff);

		switch (buff.st_mode & S_IFMT)
		{
			case S_IFREG:
				strcpy(fpath, strcat(pwd, entry->d_name));
				printf("%s\n", fpath);
				break;
			case S_IFDIR:
				if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".DS_Store") == 0);

				else{
					dir = opendir(entry->d_name);
					rePath(dir);
				}
				
				break;
			default:
				break;
		}

		// printf("file name : %s ", entry->d_name);
	}

	closedir(dname);
}
