#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024

char fetch_process(const char *filename, char *procname);

int main() {
    DIR *dir;
    struct dirent *entry;
    char proc_dir[] = "/proc";
    char proc_id_dir[MAX_PATH_LENGTH];
    char cmdline[MAX_PATH_LENGTH];
    char isKernel;

    if ((dir = opendir(proc_dir)) == NULL) {
        fprintf(stderr, "Error: No se puede abrir el directorio '%s'\n", proc_dir);
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!isdigit(entry->d_name[0]))
            continue;

        snprintf(proc_id_dir, MAX_PATH_LENGTH, "/proc/%s/cmdline", entry->d_name);
        isKernel = fetch_process(proc_id_dir, cmdline);
        printf("[%c] %s:%s\n", isKernel, entry->d_name, cmdline);
    }

    closedir(dir);
    printf("\n[U]ser process | [K]ernel process\n");
    return 0;
}

char fetch_process(const char *filename, char *procname) {
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if ((file = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error: No se puede abrir el archivo '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    procname[0] = '\0'; // Inicializar procname como una cadena vacía

    while ((read = getline(&line, &len, file)) != -1) {
        strncat(procname, line, read);
    }

    fclose(file);
    free(line);

    // Comprobar si el archivo cmdline está vacío, si es así, es un proceso del kernel
    return (procname[0] == '\0') ? 'K' : 'U';
}
