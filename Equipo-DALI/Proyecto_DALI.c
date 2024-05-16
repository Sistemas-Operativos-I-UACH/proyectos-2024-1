#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void get_process_cmdline(char *filename, char *procname);
void get_process_name(char *pid, char *procname);

int main(int argc, char *argv[])
{
        struct dirent *entry;
        DIR *pDir;
        char proc_dir[] = "/proc";
        char proc_id_cmdline_dir[255];
        char proc_id_status_dir[255];
        char proc_cmdline[10000];
        char proc_name[255];
        char kernel_string[10] = "";
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

                strcpy(proc_name, "");
                strcpy(kernel_string, "");

                sprintf(proc_id_cmdline_dir, "/proc/%s/cmdline", entry->d_name);
                sprintf(proc_id_status_dir, "/proc/%s/status", entry->d_name);
                get_process_cmdline(proc_id_cmdline_dir, proc_cmdline);
                get_process_name(proc_id_status_dir, proc_name);

                if (strlen(proc_cmdline) == 0)
                {
                        strcpy(kernel_string, "(Kernel)");
                }
                printf("| PID: %s %s| NAME: %s |\n%s\n\n", entry->d_name, kernel_string, proc_name, proc_cmdline);
        }

        closedir(pDir);
        return 0;
}

void get_process_cmdline(char *filename, char *procname)
{
        FILE *fp;
        char *line = NULL;
        size_t len = 0;
        procname[0] = '\0';

        // Open file in read-only mode
        fp = fopen(filename, "r");

        // If file opened successfully, then print the contents
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

void get_process_name(char *filename, char *procname)
{
        FILE *status_file;
        char *line = NULL;
        size_t len = 0;
        procname[0] = '\0';

        // Open file in read-only mode
        status_file = fopen(filename, "r");

        // If file opened successfully, then print the contents
        if (status_file == NULL)
        {
                printf("Error abriendo archivo %s\n", filename);
                exit(2);
        }

        if (getline(&line, &len, status_file) != -1)
        {
                line[strlen(line) - 1] = '\0';
                sprintf(procname, "%s", line + 6);
        }

        fclose(status_file);
        free(line);
}
