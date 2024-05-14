#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

char fetch_process(char *filename, char *procname);

int main(int argc, char *argv[]) {
  //Inicialización de variables
  struct dirent *entry;
  DIR *pDir;
  char proc_dir[] = "/proc";
  char proc_id_dir[1024];
  char cmdline[1024];
  char isKernel;

  pDir = opendir(proc_dir);
  if(pDir == NULL) {
    printf("Can't open such directory '%s'\n", argv[1]);
    return 1;
  }

  //Revisa cada directorio en /proc y sólo continua el programa si el directorio es numérico
  //Directorios que no son numéricos tampoco son procesos
  while((entry = readdir(pDir)) != NULL) {
    if (!isdigit(entry->d_name[0]))
      continue;

    //Obtiene el nombre del directorio y lo imprime junto a su ID
    sprintf(proc_id_dir, "/proc/%s/cmdline", entry->d_name);
    isKernel = fetch_process(proc_id_dir,cmdline);
    printf("[%c] %s:%s\n", isKernel, entry->d_name, cmdline);
  }

  closedir(pDir);
  printf("\n[U]ser process | [K]ernel process\n");
  return 0;
}


char fetch_process(char *filename, char *procname) {
  //Función para obtener el nombre del proceso
  FILE *file_pointer;
  char *line = NULL;
  char *cmp;
  size_t len = 0;
  procname[0] = '\0';
  char nullstr = (char) 0;

  //Verifica que el nombre proveído no sea nulo y abre el archivo 'cmdline' del proceso
  if(filename)
    file_pointer = fopen(filename,"r");

  //Verifica que el archivo 'cmdline' del proceso exista
  if(file_pointer == NULL) {
    printf("Error while opening file '%s'\nExit code 2\n", filename);
    exit(2);
  }

  //Lee el contendio del archivo línea por línea
  while(getline(&line, &len, file_pointer) != -1) {
    sprintf(procname, "%s%s", procname, line);
  }

  strcpy(cmp,procname);
  fclose(file_pointer);
  free(line);

  //La variable cmp guarda la última línea del archivo
  //Si está vacía regresa 'K' para proceso de kernel, sino 'U' de sistema de usuario
  if(cmp[0]==nullstr)
    return 'K';

  else
    return 'U';
}
