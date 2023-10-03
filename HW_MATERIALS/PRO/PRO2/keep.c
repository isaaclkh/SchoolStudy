#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>

void copyFiles(char * local, char * target);
char * givePath(char * ford);
void tracking(char * fileN);
void pathFromDir(char * pname);
int getVersions();
char *trimString(char *str);
int file_is_modified(const char *path, time_t oldMTime);

int main(int argc, char **argv)
{
    if(argc < 2){
        perror("Invalid option : you need to enter option\n options will be\n init, track, versions, untrack, store, restore\n");
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1], "init") == 0){
        // if there is .keep then print that this directory is already has keep structure (if you do not want to have keep, just simply remove .keep)
        // else
        //      create directory as .keep
        //      in that .keep create tracking-files and latest-version
        if (mkdir("./.keep", S_IRWXU | S_IRWXG | S_IRWXO) == -1){
            fprintf(stderr, "KEEP INIT FAIL : Maybe you already keep init\n");
            return EXIT_FAILURE;
        }
        FILE * fp1;
        FILE * fp2;

        fp1 = fopen("./.keep/tracking-files", "w");
        fp2 = fopen("./.keep/latest-version", "w");

        fwrite("0", sizeof(char), 1, fp2);

        fclose(fp1);
        fclose(fp2);
    }

    if(strcmp(argv[1], "track") == 0){
        // if argc < 3 then error invalid option : you need to give the file(s) or directory(ies) for the option
        // else write tracking-files about the file(s) and direcoty(ies)
        if(argc < 3) fprintf(stderr, "INVALID OPTION : you need to give the file(s) or directory(ies) for the option");

        for (int i = 2; i < argc; i++){
            // printf("argv[i] : %s\n", argv[i]);
            tracking(argv[i]);
        }
    }
    if(strcmp(argv[1], "store") == 0){
        // if argc < 3 then error invalid option : you need to give a comment of the storing
        // else
        //      write latest-version(it is in .keep/) in the latest version# (write latest verion# + 1)
        //      create and copy from .keep/tracking-files into version#/tracking-files and write the tracking files
        //      create version#/note and write the comment of the version
        //      copy files from the tracking-files
        //        if the local file is modified earlier than the target file (현재 파일 modified date가 더 이후라면 그러면)
        //              store in verion#/target/ 
        //        else
        //              store in 이전버전#/target
        if(argc < 3){
            fprintf(stderr, "INVALID OPTION : you need to give the comments for storing");
            return EXIT_FAILURE;
        }
        FILE * fp1;
        FILE * fp2;
        FILE * fp3;
        FILE * fp4;
        FILE * fp5;
        char storeName[1080];
        char tracking_file[1080];
        char note[1080];
        char charToInt[5];
        char * line = NULL;
        char original[3000] = {'\0'};
        char target[3000] = {'\0'};
        size_t len = 0;
        ssize_t read;
        int count = 1;

        struct stat trackingFilesMod;
        time_t tmtime;
        time_t lmtime;
        struct stat localFileMod;
        int did=0;
        
        fp1 = fopen("./.keep/tracking-files", "r");
        fp2 = fopen("./.keep/latest-version", "w");
        fp3 = fopen("./.keep/tracking-files", "a");

        // 여기서 tracking-files의 modified일자가 local에서의 modified일자보다 느리다면 do
        // else no change print
        
        fgets(charToInt, 1, fp2);
        int latestVersion = atoi(charToInt);
        latestVersion += 1;

        if(stat("./.keep/tracking-files", &trackingFilesMod) < 0 ){
            fprintf(stderr, "INIT FIRST\n");
            return EXIT_FAILURE;
        }

        tmtime = trackingFilesMod.st_mtime;

        while((read = getline(&line, &len, fp1)) != -1){
            trimString(line);

            if(file_is_modified(line, tmtime)){
                if(did == 0){
                    sprintf(charToInt, "%d", latestVersion);
                    printf("%s", charToInt);
                    fwrite(charToInt, sizeof(char), 1, fp2);
                    strcpy(storeName, "./.keep/");
                    strcat(storeName, charToInt);
                    strcat(storeName, "/");
                    strcpy(note, storeName);
                    strcat(tracking_file, storeName);

                    if (mkdir(storeName, S_IRWXU | S_IRWXG | S_IRWXO) == -1)
                    {
                        fprintf(stderr, "STORE FAIL : \n");
                        return EXIT_FAILURE;
                    }
                    strcat(tracking_file, "tracking-files");
                    fp5 = fopen(tracking_file, "a");
                    strcat(storeName, "target");

                    if (mkdir(storeName, S_IRWXU | S_IRWXG | S_IRWXO) == -1)
                    {
                        fprintf(stderr, "STORE FAIL : \n");
                        return EXIT_FAILURE;
                    }

                    strcat(note, "note");
                    fp4 = fopen(note, "w");
                    fwrite(argv[2], sizeof(char), strlen(argv[2]), fp4);
                    fclose(fp4);

                    strcpy(target, storeName);
                    strcpy(original, line);
                    char * ptr = strtok(original, "/");

                    while(ptr != NULL){
                        ptr = strtok(NULL,"/");
                        count ++;
                    }

                    strcpy(original, line);

                    ptr = strtok(original, "/");
                    for(int i=0; i<count-1; i++) ptr = strtok(NULL,"/");

                    strcpy(original, ptr);
                    strcat(storeName, original);
                    copyFiles(line, storeName);
                    fwrite(target, sizeof(char), 3000, fp5);
                    did ++;
                }
                else{
                    strcpy(storeName, "./.keep/");
                    sprintf(charToInt, "%d", latestVersion);
                    strcat(storeName, charToInt);
                    strcat(storeName, "/");

                    strcat(target, "./.keep/");
                    strcpy(original, line);
                    char *ptr = strtok(original, "/");

                    while (ptr != NULL)
                    {
                        ptr = strtok(NULL, "/");
                        count++;
                    }

                    strcpy(original, line);

                    ptr = strtok(original, "/");
                    for (int i = 0; i < count - 1; i++)
                        ptr = strtok(NULL, "/");

                    strcpy(original, ptr);
                    strcat(storeName, original);
                    copyFiles(line, storeName);
                    fwrite(target, sizeof(char), 3000, fp5);
                }
                fwrite(line, sizeof(char), 3000, fp5);
            }
        }

        
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        fclose(fp5);

        
    }

    if(strcmp(argv[1], "versions") == 0){
        // read .keep/latest-version and print
        if(getVersions() == -1){
            fprintf(stderr, "SOME THING GOT ERROR ON VERSIONS : MAYBE NOTHING WAS STORED\n");
            return EXIT_FAILURE;
        }
    }
    if(strcmp(argv[1], "untrack") == 0){
        // if argc < 3 then error invalid option : you need to give the file(s) or diretory(ies) for the option
        // else
        //      remove file(s) or directory(ies) in the .keep/tracking-files
    }
    if(strcmp(argv[1], "restore") == 0){
        // if argc < 3 then error invalid option : you need to give the version
        // else
        //      remove all the file(s) and directory(ies) in local
        //      copy all the file(s) and directory(ies) in givenversion#/target/
    }
}

void copyFiles(char * local, char * target){
    FILE * fp1, * fp2;
    fp1 = fopen(local, "r");
    fp2 = fopen(target, "w");

    if(!fp1){
        fprintf(stderr, "ERROR openning file : no rights to open the local file : %s", local);
        // return EXIT_FAILURE;
    }

    if(!fp2){
        fprintf(stderr, "ERROR openning file : no rights to create the target file : %s", target);
        // return EXIT_FAILURE;
    }

    char c;

    while((c=fgetc(fp1)) != EOF) fputc(c, fp2);

    fclose(fp1);
    fclose(fp2);
}

void tracking(char * fileN){
    FILE * fp1;
    char * pathname;
    char pwd[1080];

    pathname = (char *)calloc(3000, sizeof(char));
    
    DIR * spdir;
    struct dirent * entry;
    struct stat buff;
    DIR * opentest;

    getcwd(pwd, sizeof(pwd));
    fp1 = fopen("./.keep/tracking-files", "a"); // 파일 끝 덧붙여 쓰기

    if ((spdir = opendir(pwd)) == NULL)
    {
        fprintf(stderr, "ERROR openning current directory : no rights to open the directory or not a directory\ndirectory name: %s\n", pwd);
        return;
    }

    while ((entry = readdir(spdir)) != NULL)
    {
        stat(entry->d_name, &buff);
        if(strcmp(entry->d_name, fileN) == 0){
            switch (buff.st_mode & S_IFMT)
            {
                case S_IFREG:
                    strcpy(pathname, pwd);
                    strcat(pathname, "/");
                    strcat(pathname, entry->d_name);
                    strcat(pathname, "\n");
                    fwrite(pathname, sizeof(char), strlen(pathname), fp1);
                    break;

                case S_IFDIR:
                    strcpy(pathname, pwd);
                    strcat(pathname, "/");
                    strcat(pathname, entry->d_name);
                    pathFromDir(pathname);
                    break;
                default:
                    break;
            }
        }
    }
    free(pathname);
    fclose(fp1);
    closedir(spdir);
}

void pathFromDir(char *dirpath)
{
    FILE * fp1;
    DIR * dir = opendir(dirpath);

    fp1 = fopen("./.keep/tracking-files", "a"); // 파일 끝 덧붙여 쓰기

    if (dir == 0x0)
		return ;

	for (struct dirent * i = readdir(dir) ; i != NULL ; i = readdir(dir)) {
		if (i->d_type != DT_DIR && i->d_type != DT_REG)
			continue ;

		char * filepath = (char *) malloc(strlen(dirpath) + 1 + strlen(i->d_name) + 1) ;
		strcpy(filepath, dirpath) ;
		strcpy(filepath + strlen(dirpath), "/") ;
		strcpy(filepath + strlen(dirpath) + 1, i->d_name) ;

		if (i->d_type == DT_DIR) {
			if (strcmp(i->d_name, ".") != 0 && strcmp(i->d_name, "..") != 0)
                pathFromDir(filepath);
        }
		else if (i->d_type == DT_REG){
            strcat(filepath, "\n");
            fwrite(filepath, sizeof(char), strlen(filepath), fp1);
        }
		free(filepath) ;
	}

    fclose(fp1);
	closedir(dir);
}

int getVersions()
{
    FILE *versionFile;
    char ch;
    char str[20];

    // 파일을 읽기 모드로 열기
    versionFile = fopen(".keep/latest-version", "r");

    // 파일 열기에 실패한 경우
    if (versionFile == NULL) {
        fprintf(stderr, "LATEST VERSION DOES NOT EXIST\n");
        return -1;
    }

    int latestVersion = fgetc(versionFile) - '0';

    for (int i = 1; i <= latestVersion; i++) {
        char str[20];
        sprintf(str, "%d", i);
        char dir[1000];
        strcpy(dir, ".keep/");
        strcat(dir, str);
        strcat(dir, "/note");

        FILE *note = fopen(dir, "r");

        if (note == NULL) {
            fprintf(stderr, "NOTE FILE DOESN'T EXIST %d\n", i);
            return -1;
        }

        printf("%d ", i);

        while ((ch = fgetc(note)) != EOF) {
            printf("%c", ch);
        }
        printf("\n");

        // 파일 닫기
        fclose(note);
    }

    // 파일 닫기
    fclose(versionFile);

    return 0;
}

char * trimString(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '\n')
            str[i] = '\0'; // if there is line feed sign, just make it as the end of the string
    }

    return str; // return the trimmed string
}

int file_is_modified(const char *path, time_t oldMTime)
{
    struct stat file_stat;
    int err = stat(path, &file_stat);
    if (err != 0){
        fprintf(stderr, "NO FILE");
        return -1;
    }
    return file_stat.st_mtime > oldMTime;
}