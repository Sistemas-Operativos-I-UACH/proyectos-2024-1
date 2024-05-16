#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>

char *line = NULL;
long tam=0;

void get_process_cmd(char *filename, char *procname);

int main (int argc, char *argv[]) {
		char proc_dir[] = "/proc";
		char proc_id_dir[255];
		char cmdline[255];
		DIR *pDir;
		struct dirent *entry;

		pDir = opendir (proc_dir);
		if (pDir == NULL) {
			printf ("Cannot open directory '%s'\n", argv[1]);
			return 1;
		}

		// Process each entry.

		while ((entry = readdir(pDir)) != NULL) {
        if ( ! isdigit(entry->d_name[0]) )
          continue;

		        sprintf(proc_id_dir, "/proc/%s", entry->d_name);

			get_process_cmd(proc_id_dir, cmdline);

			printf ("ID %s || Nombre %s || ", entry->d_name, cmdline);

				if(tam==0){
					printf("Es proceso de Kernel\n");
				}

				else{
					printf("Es proceso de Usuario\n");
				}


		}

		// Close directory and exit.
		closedir (pDir);
		return 0;
}


void get_process_cmd(char *filename, char *procname) {
  FILE *fp;
  size_t len = 0;
  procname[0] = '\0';
  char linea[100];
  sprintf(procname,"%s/cmdline",filename);

  // Open file in read-only mode
  fp = fopen(procname,"r");


  // If file opened successfully, then print the contents
  if ( fp == NULL ) {
    printf("Error abriendo archivo %s\n", procname);
    exit(2);
   }

  *procname = '\0';
  while(getline(&line, &len, fp) != -1) {
    sprintf(procname, "%s%s", procname, line);
  }

  tam = ftell(fp);

  //If cmdline is empty change the path to stat
  if(tam==0) {
    fclose(fp);
    procname[0] = '\0';

    sprintf(procname,"%s/stat",filename);
    fp = fopen(procname,"r");
    procname[0] = '\0';

    // Gets line of stat and put the name of the process in procname
    fgets(linea, sizeof(linea),fp);
    sscanf(linea,"%*d (%[^)])",procname);

  }

  free(line);
  fclose(fp);
}

