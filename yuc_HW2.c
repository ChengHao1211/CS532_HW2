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
char prepath[4096] = "";
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
              printf("lstat error");
              exit(-1);
          }

      if(strcmp(dirent->d_name,".") != 0 && strcmp(dirent->d_name,"..") != 0){
        //printf("%d  %d  %d\n", Sflag, sflag, fflag);
        if (Sflag == 1){
          if(sflag == 1 ){
            if(buf.st_size <= sizeindex){
              if (fflag == 1){
                if(strstr(dirent->d_name,substring) != NULL && subcount == layer){
                  if (tflag == 1){
                    if(strcmp(cvalue,"f") == 0){
                        if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                                printf ("%s%s File size: %lld  permission  : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                        }
                    }   
                    else if(strcmp(cvalue,"d") == 0){
                         if (strcmp(filetype(dirent->d_type),"directory") == 0){
                                printf ("%s%s File size: %lld  permission  : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                        }
                    }
                  }
                  else{
                    printf ("%s%s File size: %lld  permission  : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                  }
                }
              }
              else{
                printf ("%s%s File size: %lld  permission  : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
              }

            }
          }

          else if (fflag == 1){
            if(strstr(dirent->d_name,substring) != NULL && subcount == layer){
              if (tflag == 1){
                if(strcmp(cvalue,"f") == 0){
                    if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                            printf ("%s%s File size: %lld  permission  : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                    }
                }   
                else if(strcmp(cvalue,"d") == 0){
                      if (strcmp(filetype(dirent->d_type),"directory") == 0){
                            printf ("%s%s File size: %lld  permission  : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                    }
                }
              }
              else{
                printf ("%s%s File size: %lld  permission  : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
              }
            }
          }
          
          else if (tflag == 1){
            if(strcmp(cvalue,"f") == 0){
                if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                        printf ("%s%s File size: %lld  permission  : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                }
            }   
            else if(strcmp(cvalue,"d") == 0){
                  if (strcmp(filetype(dirent->d_type),"directory") == 0){
                        printf ("%s%s File size: %lld  permission  : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                }
            }
          }
          else{
            printf ("%s%s File size: %lld  permission  : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
          }

        }


        else if (sflag == 1){
          if (buf.st_size <= sizeindex){
            if (fflag == 1){
              if(strstr(dirent->d_name,substring) != NULL && subcount == layer){
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
          if(strstr(dirent->d_name,substring) != NULL && subcount == layer){
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

  strcat(subpath,argv[optind]);
  strcat(subpath,sub);
  strcpy(prepath,subpath);
  //strcpy(subpath,"./");


  opfunc(prepath,findDir);

  return 0;
}


/* 
Name: YU Cheng-Hao
BlazerId: yuc
Project #: Homework2
To compile: 
1st make a structure "filetype" to get the exact file type of the file.
such as directory or regular file.

2nd make a function "findDir" to open the directory and analyze the directory. In the code open the directory by using "opendir" and then use the loop to print all files in the directory. If there's a subdirectory then open the function to analyze the subdirectory in the same way. After analyzing the directory use "closedir" to close the directory. 

3rd in the main function use loop and "switch case" to find out which information you are looking for.
If "S" then Sflag becomes 1. Then the "findDir" function will print the size, permissions, and last access time next to the filename.
If "s" then sflag becomes 1. Then the "findDir" function will print file-size less than or equal to the value specified.
If "f" then fflag becomes 1. Then the "findDir" function will print the file name contains the substring and the depth of the file 
relative to the starting directory of the traversal is less than or equal to the depth option.(The starting directory itself has a depth of 0.)
 If "t" with "f" or "d" then tflag becomes 1 and then the "findDir" function will print (1) if it get "f" - list regular files only (2) -t d - list directories only.
And also you can combine the multiple differnt cases.

4th In the makefile I code like this.
mySearch: yuc_HW2.c
        gcc -Wall -o search yuc_HW2.c
	mkdir project
	mkdir project1
	mv project1 project
	touch README
	mv README project/project1
        touch project1.docx
	mv project1.docx project/project1
	mkdir project2
	mv project2 project
	touch README
	mv README project/project2
        touch project2.docx
	mv project1.docx project/project2
	mkdir project3
	mv project3 project
	touch README
	mv README project/project3
        touch project3.docx
	mv project1.docx project/project3
	mkdir project4
	mv project4 project
	touch README
	mv README project/project4
        touch project4.docx
	mv project1.docx project/project4
yuc_HW2.c is my souce code and use "gcc -Wall -o search yuc_HW2.c" to compile the code. Then use "mkdir project" to make a directory "mkdir project1" to make a sub directory "mv project1 project" to move subdirectory to the main directory
"touch README" make a README file "mv README project/project1" move the README file to the subdirectory "touch project1.docx" make a docx file "mv project1.docx project/project1" move the docx file to the subdirectory. 


To run: 
1st use make command to compile my code. After compile the code there's a search.exe file that you can run.

2nd Use the "./search" command to analyze the directory.
For example, "./search projects" then it will analyze the project directory.
And if you run the program with arguments.
For example, "./search projects -S -s 1000 -t f -f "README 1"
Then it will show like this.
yuc@cs-vulcan-3:~/HW2$ ./search project -S -s 1000 -t f -f "README 1"
      README File size: 0  permission : 100644 Last access: Tue Sep 27 17:09:03 2022

      README File size: 0  perission : 100644 Last access: Tue Sep 27 17:09:24 2022

      README File size: 0  perission : 100644 Last access: Tue Sep 27 17:09:43 2022

      README File size: 0  perission : 100644 Last access: Tue Sep 27 17:08:31 2022

*/ 