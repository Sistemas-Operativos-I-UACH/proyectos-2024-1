#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void get_process_cmd(char *filename, char **procname);

int main() {
    struct dirent *entry;
    DIR *pDir;
    char proc_dir[] = "/proc";
    char proc_id_dir[255];
    char *cmdline = NULL;

    pDir = opendir(proc_dir);
    if (pDir == NULL) {
        printf("No se pudo abrir el directorio '%s'\n", proc_dir);
        return 1;
    }

    while ((entry = readdir(pDir)) != NULL) {
        if (!isdigit(entry->d_name[0]))
            continue;

        snprintf(proc_id_dir, sizeof(proc_id_dir), "/proc/%s/cmdline", entry->d_name);

        get_process_cmd(proc_id_dir, &cmdline);
        printf("%s:%s\n", entry->d_name, cmdline);

        free(cmdline);
    }

    closedir(pDir);
    return 0;
}

void get_process_cmd(char *filename, char **procname) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error abriendo archivo %s\n", filename);
        exit(2);
    }

    // Leer solo el primer fragmento del cmdline (el nombre del proceso)
    if ((read = getline(&line, &len, fp)) != -1) {
        // Remover el último carácter de nueva línea si existe
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';
        
        *procname = strdup(line); // Almacenar el nombre del proceso
    } else {
        *procname = strdup("No disponible");
    }

    fclose(fp);
    free(line);
}
