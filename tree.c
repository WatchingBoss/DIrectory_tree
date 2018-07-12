/*
 * Directory tree implemetation
 * Lists contents of directory in tree-like format
 * Author: Smirnov Egor (ActionLS)
 */

/*
 * TODO: Figer out how free list and temp in right way
 * TODO: Define function to concatinate path name
 * TODO: Make right working vertical lines
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h> /* stat(); */
#include <unistd.h>   /* getcwd(); getopt(); */
#include <dirent.h>   /* opendir(); readdir(); */

#include "include/tree.h"
#include "include/common.h"

#define STRAIGHT_NODE "\u251c\u2500\u2500 "
#define ANGLE_NODE "\u2514\u2500\u2500 "
#define STRAIGHT_LINE "\u2502"

#define OPTIONS "afd::"

/* ===== Start global variable =====*/
bool print_disappeared = false;
bool print_dir_only = false;
bool defined_path = false;
bool first_print_list = true;

size_t amount_of_directories = 0;
size_t amount_of_files = 0;
/* ===== End global variable =====*/

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
			case 'd':
				print_dir_only = true;
				break;
			case 'f':
				break;
			case '?':
				user_error("Unknow option %c", option);
				break;
			default:
				break;
		}
	}

	read_input(argc, argv);

	print_amount();

	exit(EXIT_SUCCESS);
}

void print_tree(int nocpl)
{
	for(int i = 0; i < nocpl; ++i)
	{
		if(i < nocpl - 1)
		{
			printf(" ");
		}
		printf("  ");
	}
}

void print_list(int count, char *list[], const char *directory, int nocpl)
{
	size_t num = nocpl, printed = 0;
	
	if(first_print_list && defined_path)
		printf(ANSI_COLOR_BRIGHT_BLUE"%s"ANSI_COLOR_RESET"\n", directory);
	else if(first_print_list)
		printf(".\n");
	
	for(int i = 0; i <= count; ++i)
	{
		size_t size = strlen(directory) + strlen(list[i]) + 2;
		char total_path[size];
		memset(total_path, 0, sizeof(total_path));
		strncat(total_path, directory, sizeof(total_path) - strlen(total_path));
		strncat(total_path, "/", sizeof(total_path) - strlen(total_path));
		strncat(total_path, list[i], sizeof(total_path) - strlen(total_path));

		if(existing_directory(total_path))
		{
			print_tree(nocpl);

			++amount_of_directories;
			first_print_list = false;
			printf("%s"ANSI_COLOR_BRIGHT_BLUE"%s"ANSI_COLOR_RESET"\n",
				   printed < count ? STRAIGHT_NODE : ANGLE_NODE, list[i]);
			read_and_serve_stream(total_path, num + 1);
			++printed;
		}
		else
		{
			++amount_of_files;
			if(!print_dir_only)
			{
				print_tree(nocpl);

				if(is_executable(total_path))
					printf("%s"ANSI_COLOR_BRIGHT_GREEN"%s"ANSI_COLOR_RESET"\n",
						   printed < count ? STRAIGHT_NODE : ANGLE_NODE, list[i]);
				else
					printf("%s"ANSI_COLOR_WHITE_FILE"%s"ANSI_COLOR_RESET"\n",
						   printed < count ? STRAIGHT_NODE : ANGLE_NODE, list[i]);
				++printed;
			}
		}
	}
}

/*
 * Using bubble sort to sort a case insensitive list of strings in alphabetical order
 */
int greater_stirng(const char *s1, const char *s2)
{
	char str1[strlen(s1) + 1], str2[strlen(s2) + 1];
	strcpy(str1, s1);
	strcpy(str2, s2);
	for(int i = 0; str1[i] != '\0'; ++i)
		str1[i] = tolower(str1[i]);
	for(int i = 0; str2[i] != '\0'; ++i)
		str2[i] = tolower(str2[i]);
	if(strcmp(str1, str2) > 0)
		return 1;
	else
		return 0;
}

void sort_alphabeticly(int count, char *list[], const char *directory, int nocpl)
{
	for(int i = 0; i <= count; ++i)
	{
		int firstIndex = 0, secondIndex = 1;
		while(secondIndex <= count)
		{
			char *firstString = list[firstIndex];
			char *secondString = list[secondIndex];

			if(greater_stirng(firstString, secondString))
			{
				list[firstIndex] = secondString;
				list[secondIndex] = firstString;
			}
			++firstIndex;
			++secondIndex;
		}
	}
	print_list(count, list, directory, nocpl);
}
/* ===== End of sorting =====*/

void read_and_serve_stream(const char *directory, int nocpl)
{
	DIR *dir;
	struct dirent *dp;
	char **temp = NULL, **list = NULL;
	int count = 0;

	if( !(dir = opendir(directory)) )
		user_error("No such directory: %s", directory);

	while( (dp = readdir(dir)) != NULL)
	{
		if( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") )
			continue;
		if(!print_disappeared && dp->d_name[0] == '.')
			continue;

		temp = xrealloc(list, sizeof *temp * (count + 1));
		if(!temp)
			system_error("realloc list error");
		else
			list = temp;
		list[count] = xmalloc(strlen(dp->d_name) + 1);
		strcpy(list[count++], dp->d_name);
	}

	sort_alphabeticly(count - 1, list, directory, nocpl);

	free(list);
}

void read_input(int argc, char *argv[])
{
	for(int i = argc - 1; i != 0; --i)
	{
		if(!defined_path && existing_directory(argv[i]) )
			defined_path = true;
			
		if(argv[i][0] == '-')
			continue;

		read_and_serve_stream(argv[i], 0);
	}
	if(!defined_path)
		read_and_serve_stream(current_directory(), 0);
}

void print_amount()
{
	printf("\n");
	if(amount_of_files > 1)
	{
		printf("%ld files, ", amount_of_files);
		if(amount_of_directories > 1)
			printf("%ld directories", amount_of_directories);
		else if(amount_of_directories == 1)
			printf("%ld directory", amount_of_directories);
	}
	else if(amount_of_files == 1)
		printf("%ld file", amount_of_files);
	else
		printf("Empty directory");
	printf("\n");
}

int is_executable(const char *file)
{
	struct stat sb;
	if(!stat(file, &sb) && sb.st_mode & S_IXUSR)
		return 1;
	return 0;
}

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
