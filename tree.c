/*
 * Directory tree implemetation
 * Lists contents of directory in tree-like format
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* getcwd(); */
#include <dirent.h> /* opendir(); */

#include "include/tree.h"

int existing_directory(const char *directory)
{
	DIR *dir;
	if( (dir = opendir(directory) ) == NULL)
		return 0;
	closedir(dir);
	return 1;
}

char *current_directory()
{
	static char current_dir[256];
	getcwd(current_dir, sizeof(current_dir));
	return current_dir;
}

void print_list()
{

}

void sort_alphabetic()
{

}

void read_stream(const char *directory)
{
	
}

void read_input(int argc, char *argv[])
{
	bool defined_path = false;

	for(int i = argc - 1; i != 0; --i)
	{
		if(!defined_path && existing_directory(argv[i]) )
			defined_path = true;
			
		if(!strcmp(argv[i], "-f"))
			continue;

		read_stream(argv[i]);
	}

	if(!defined_path)
		read_stream(current_directory() );
}

int main(int argc, char *argv[])
{
	read_input(argc, argv);

	
	exit(EXIT_SUCCESS);
}

/*

Algorithm:
1. Read input to program
2. Loop #1:
1) Read strem from first directory
2) Sort names in alphabetical order
3) Print names of files
4) If file is directory
Use loop #1
5) 


dir1
    | file1
    | dir1
        | dir1
    | dir2
        | dir1
    | dir3
        | dir1

*/
