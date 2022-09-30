#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

char *filetype(unsigned char type) {
  char *str;
  switch(type) {
  case DT_BLK: str = "block device"; break;
  case DT_CHR: str = "character device"; break;
  case DT_DIR: str = "directory"; break;
  case DT_FIFO: str = "named pipe (FIFO)"; break;
  case DT_LNK: str = "symbolic link"; break;
  case DT_REG: str = "regular file"; break;
  case DT_SOCK: str = "UNIX domain socket"; break;
  case DT_UNKNOWN: str = "unknown file type"; break;
  default: str = "UNKNOWN";
  }
  return str;
}



int subcount = 0;
char subpath[4096] = "./";
char sub[10] = "/";

int Sflag = 0;
int sflag = 0;
int fflag = 0;
int tflag = 0;
char *cvalue = NULL, *strIndex = NULL;
char *Inputsubstring = NULL, *substring = NULL, *strlayer;
int layer ;
int sizeindex = 0;

typedef int MYFUNC(char path[]);

int findDir(char path[]) {
  char prepath[4096] = "";
  char space[4096] = "";
  char exactfile[4096];
  struct dirent *dirent;
  DIR *parentDir;
    parentDir = opendir (path);
    if (parentDir == NULL) {
        printf ("Error opening directory '%s'\nError:%s\n\n", path, strerror(errno));
        exit (-1);
    }

    for (int i = 0; i < subcount; i++){
            strcat(space,"      ");
    }
    while((dirent = readdir(parentDir)) != NULL){
      struct stat buf;

      //printf("path === %s          file === %s\n", path, dirent->d_name);


      strcpy(exactfile,path);
      strcat(exactfile,dirent->d_name);
      //printf("PATH == %s\n",exactfile);

      if (stat(exactfile, &buf) < 0) {
              printf("lstat error\n");
              exit(-1);
          }

      if(strcmp(dirent->d_name,".") != 0 && strcmp(dirent->d_name,"..") != 0){
        //printf("%d  %d  %d\n", Sflag, sflag, fflag);
         //printf("path === %s \n",path);
	if (Sflag == 1){
          if(sflag == 1 ){
            if(buf.st_size <= sizeindex){
              if (fflag == 1){
                if(strstr(dirent->d_name,substring) != NULL && subcount <= layer){
                  if (tflag == 1){
                    if(strcmp(cvalue,"f") == 0){
                        if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                                printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                        }
                    }   
                    else if(strcmp(cvalue,"d") == 0){
                         if (strcmp(filetype(dirent->d_type),"directory") == 0){
                                printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                        }
                    }
                  }
                  else{
                    printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                  }
                }
              }
              else{
                printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
              }

            }
          }

          else if (fflag == 1){
            if(strstr(dirent->d_name,substring) != NULL && subcount <= layer){
              if (tflag == 1){
                if(strcmp(cvalue,"f") == 0){
                    if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                            printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                    }
                }   
                else if(strcmp(cvalue,"d") == 0){
                      if (strcmp(filetype(dirent->d_type),"directory") == 0){
                            printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                    }
                }
              }
              else{
                printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
              }
            }
          }
          
          else if (tflag == 1){
            if(strcmp(cvalue,"f") == 0){
                if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                        printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                }
            }   
            else if(strcmp(cvalue,"d") == 0){
                  if (strcmp(filetype(dirent->d_type),"directory") == 0){
                        printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                }
            }
          }
          else{
            printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
          }

        }


        else if (sflag == 1){
          if (buf.st_size <= sizeindex){
            if (fflag == 1){
              if(strstr(dirent->d_name,substring) != NULL && subcount <= layer){
                if (tflag == 1){
                  if(strcmp(cvalue,"f") == 0){
                    if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                      printf ("%s%s \n",space, dirent->d_name);
                    }
                  }   
                  else if(strcmp(cvalue,"d") == 0){
                    if (strcmp(filetype(dirent->d_type),"directory") == 0){
                      printf ("%s%s \n",space, dirent->d_name);
                    }
                  }
                }
              }
            }
            else if (tflag == 1){
              if(strcmp(cvalue,"f") == 0){
                if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                  printf ("%s%s \n",space, dirent->d_name);
                }
              }   
              else if(strcmp(cvalue,"d") == 0){
                if (strcmp(filetype(dirent->d_type),"directory") == 0){
                  printf ("%s%s \n",space, dirent->d_name);
                }
              }
            }
            else{
              printf ("%s%s \n",space, dirent->d_name);
            }
          }
        }
              

              


        else if (fflag == 1){
          if(strstr(dirent->d_name,substring) != NULL && subcount <= layer){
            if (tflag == 1){
              if(strcmp(cvalue,"f") == 0){
                if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                  printf ("%s%s \n",space, dirent->d_name);
                }
              }   
              else if(strcmp(cvalue,"d") == 0){
                if (strcmp(filetype(dirent->d_type),"directory") == 0){
                  printf ("%s%s \n",space, dirent->d_name);
                }
              }
            }
            else{
                  printf ("%s%s \n",space, dirent->d_name);
            }
          }
        }
            


        else if (tflag == 1){
          if(strcmp(cvalue,"f") == 0){
            if (strcmp(filetype(dirent->d_type),"regular file") == 0){
              printf ("%s%s  \n",space, dirent->d_name);
            }
          }
          else if(strcmp(cvalue,"d") == 0){
            if (strcmp(filetype(dirent->d_type),"directory") == 0){
              printf ("%s%s \n",space, dirent->d_name);
            }
          }
        }



        else
        {
                //printf("defalt\n");
                printf ("%s%s\n",space, dirent->d_name);
        }

        
        if(filetype(dirent->d_type) == "directory"){
          strcpy(prepath,subpath);
	  //printf("PATH == %s\n",prepath);
          strcat(subpath,sub);
          strcat(subpath,dirent->d_name);
          strcat(subpath,sub);
          //printf("%s\n", subpath);
          subcount++;
          opfunc(subpath,findDir);
          strcpy(subpath,prepath);
        }
      }
    }
  subcount--;
  closedir (parentDir);
}

int opfunc(char path[], MYFUNC *f) {
        return findDir(path);
}

int main (int argc, char **argv)
{
  int c;


  opterr = 0;


  while ((c = getopt (argc, argv, "Ss:f:t:")) != -1)
    switch (c)
      {
      case 'S':
        Sflag = 1;
        break;
        break;
      case 's':
        sflag = 1;
        strIndex = optarg;
        sizeindex = atoi(strIndex);
        break;
      case 'f':
        fflag = 1;
        Inputsubstring = optarg;
        //printf("%s\n",Inputsubstring);
        substring = strtok(Inputsubstring," ");
        strlayer = strtok(NULL, " ");
        layer = atoi(strlayer);
        break;
      case 't':
        tflag = 1;
        cvalue = optarg;
        break;
      case '?':
        if (optopt == 't')
          printf ("Option -%c requires an argument.\n", optopt);
        else
          printf ("Unknown option character `\\x%x'.\n",optopt);
        return 1;
      default:
        abort ();
      }

  //printf ("Sflag = %d, sflag = %d, fflag = %d, cvalue = %s\n\n",Sflag, sflag, fflag, cvalue);

   
  if (argv[optind] != NULL){
    strcat(subpath,argv[optind]);
  }

  strcat(subpath,sub);
  //strcpy(prepath,subpath);
  //printf("%s\n",prepath);


  opfunc(subpath,findDir);

  return 0;
}

