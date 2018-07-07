/*
 * Directory tree implemetation
 * Lists contents of directory in tree-like format
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h> /* getcwd(); getopt(); */
#include <dirent.h> /* opendir(); readdir(); */

#include "include/tree.h"

#define OPTIONS "af::"

bool print_disappeared = false;

int existing_directory(const char *directory)
{
	DIR *dir;
	if( !(dir = opendir(directory)) )
		return 0;
	closedir(dir);
	return 1;
}

char *current_directory()
{
	static char current_dir[256];
	if( !getcwd(current_dir, sizeof(current_dir)) )
		system_error("getcwd error");
	return current_dir;
}

void print_list()
{

}

void sort_alphabeticly()
{

}

void read_stream(const char *directory)
{
	DIR *dir;
	struct dirent *dp;

	if( !(dir = opendir(directory)) )
		user_error("No such directory: %s", directory);

	int i = 1;
	while( (dp = readdir(dir)) != NULL)
	{
		if( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") )
			continue;
		if(!print_disappeared && dp->d_name[0] == '.')
			continue;
		printf("%d - %s\n", i++, dp->d_name);
	}
}

void read_input(int argc, char *argv[])
{
	bool defined_path = false;

	for(int i = argc - 1; i != 0; --i)
	{
		if(!defined_path && existing_directory(argv[i]) )
			defined_path = true;
			
		if(argv[i][0] == '-')
			continue;

		read_stream(argv[i]);
	}
	if(!defined_path)
		read_stream(current_directory() );
}

int main(int argc, char *argv[])
{
	char option;
	while( (option = getopt(argc, argv, OPTIONS)) > 0 )
	{
		switch(option)
		{
			case 'a':
				print_disappeared = true;
				break;
			case 'f':
				break;
			default:
				break;
		}
	}

	read_input(argc, argv);

	
	exit(EXIT_SUCCESS);
}

void user_error(const char *e, ...)
{
	va_list(args);
	va_start(args, e);
	vprintf(e, args);
	va_end(args);
	printf("\n");
	exit(EXIT_FAILURE);
}

void system_error(const char *e)
{
	perror(e);
	exit(EXIT_FAILURE);
}
