#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

char fetch_process(char *filename, char *procname);


int main(int argc, char *argv[]) {
  struct dirent *entry;
  DIR *pDir;
  char proc_dir[] = "/proc";
  char proc_id_dir[1024];
  char cmdline[2048];
  char isKernel;

  pDir = opendir(proc_dir);
  if(pDir == NULL) {
    printf("Can't open such directory '%s'\n", argv[1]);
    return 1;
  }

  while((entry = readdir(pDir)) != NULL) {
    if (!isdigit(entry->d_name[0]))
      continue;

      FILE *cmdfile;
      char auxname[128];
      sprintf(proc_id_dir, "/proc/%s/cmdline", entry->d_name);
      isKernel = fetch_process(proc_id_dir, cmdline);
      printf("[%c] %s:%s\n", isKernel, entry->d_name, cmdline);
  }

  closedir(pDir);
  printf("\n[U]ser process | [K]ernel process\n");
  return 0;
}


char fetch_process(char *filename, char *procname) {
  FILE *file_pointer;
  char *line = NULL;
  char *cmp;
  size_t len = 0;
  procname[0] = '\0';

  if(filename)
  file_pointer = fopen(filename,"r");
  if(file_pointer == NULL) {
    printf("Error while opening file '%s'\nExit code 2\n", filename);
    exit(2);
  }

  while(getline(&line, &len, file_pointer) != -1) {
    sprintf(procname, "%s%s", procname, line);
    cmp = line;
  }

  fclose(file_pointer);
  free(line);
  if(!cmp)
    return 'K';
  else
    return 'U';
}
