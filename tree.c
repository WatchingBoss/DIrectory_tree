/*
 * Directory tree implemetation
 * Lists contents of directory in tree-like format
 * Author: Smirnov Egor (ActionLS)
 */

/*
 * TODO: create xmalloc and xrealloc functions to checking memory allocation
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

void sort_alphabeticly(int count, char *list[])
{
	for(int i = 0; i <= count; ++i)
		printf("%s\n", list[i]);
}

void read_and_serve_stream(const char *directory)
{
	DIR *dir;
	struct dirent *dp;
	char **temp = xmalloc(sizeof **temp);
	char **list = xmalloc(sizeof **list);
	int count = 0;

	if( !(dir = opendir(directory)) )
		user_error("No such directory: %s", directory);

	while( (dp = readdir(dir)) != NULL)
	{
		if( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") )
			continue;
		if(!print_disappeared && dp->d_name[0] == '.')
			continue;

		list = xrealloc(temp, sizeof **list * (count + 1));
		if(!list)
			system_error("realloc list error");
		else
			temp = list;
		list[count] = xmalloc(strlen(dp->d_name) + 1);
		strcpy(list[count], dp->d_name);
		printf("%d %s\n", count, list[count]);
		++count;
	}
	puts("");
	
	for(int i = 0; i < count; ++i)
		printf("%s\n", list[i]);

//	sort_alphabeticly(count - 1, list);

	free(list);
	free(temp);
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

		read_and_serve_stream(argv[i]);
	}
	if(!defined_path)
		read_and_serve_stream(current_directory() );
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


