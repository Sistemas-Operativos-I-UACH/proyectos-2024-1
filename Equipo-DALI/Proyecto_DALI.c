#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void get_process_cmd(char *filename, char *procname);

int main(int argc, char *argv[])
{
        struct dirent *entry;
        DIR *pDir;
        char proc_dir[] = "/proc";
        char proc_id_dir[1000];
        char cmdline[255];
        FILE *fp;

        pDir = opendir(proc_dir);
        if (pDir == NULL)
        {
                printf("Cannot open directory '%s'\n", argv[1]);
                return 1;
        }

        while ((entry = readdir(pDir)) != NULL)
        {
                if (!isdigit(entry->d_name[0]))
                        continue;

                sprintf(proc_id_dir, "/proc/%s/cmdline", entry->d_name);

                get_process_cmd(proc_id_dir, cmdline);

                char *isKernel = "";
                if (strlen(cmdline) == 0)
                {
                        isKernel = "(Kernel)";
                }
                printf("| PID: %s %s|\n%s\n\n", entry->d_name, isKernel, cmdline);
        }

        closedir(pDir);
        return 0;
}

void get_process_cmd(char *filename, char *procname)
{
        FILE *fp;
        char *line = NULL;
        size_t len = 0;
        procname[0] = '\0';

        // Open file in read-only mode
        fp = fopen(filename, "r");

        if (fp == NULL)
        {
                printf("Error abriendo archivo %s\n", filename);
                exit(2);
        }

        while (getline(&line, &len, fp) != -1)
        {
                sprintf(procname, "%s%s", procname, line);
        }

        fclose(fp);
        free(line);
}