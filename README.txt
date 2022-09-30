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

2nd use the "./search" command to analyze the directory.
For example, "./search projects" then it will analyze the project directory.
And if you run the program with arguments.
For example, "./search projects -S -s 1000 -t f -f "README 1"
Then it will show like this.
yuc@cs-vulcan-3:~/HW2$ ./search project -S -s 1000 -t f -f "README 1"
      README File size: 0  permission : 100644 Last access: Tue Sep 27 17:09:03 2022

      README File size: 0  perission : 100644 Last access: Tue Sep 27 17:09:24 2022

      README File size: 0  perission : 100644 Last access: Tue Sep 27 17:09:43 2022

      README File size: 0  perission : 100644 Last access: Tue Sep 27 17:08:31 2022
