#include "main.h"

/**
 * get_location - get the path of this command file
 * @command: user inputs command
 *
 * Return: file path
 */
char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path = getenv("PATH");
	if (path)
	{
		path_copy = strdup(path);
		command_length = strlen(command);
		path_token = strtok(path_copy, ":");
		while (path_token != NULL)/*command file is in subdirectory*/
		{
			directory_length = strlen(path_token);
		file_path = malloc(command_length + directory_length + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)/*success*/
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}/*end while loop*/
		free(path_copy);
		if (stat(command, &buffer) == 0)
			return (command);
		return (NULL);
	}
	return (NULL);
}

/**execmd - get a command & find the path to this command & execute it
 * @argv: the arguments include command as the first element
 * Return: nothing
 */
void execmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;

	if (argv)
	{
		/*get the command*/
		command = argv[0];
		/*generate the path to this command before pass it to execve*/
		actual_command = get_location(command);
		if (execve(actual_command, argv, NULL) == -1)
		{
			perror("Error:");
		}
	}
}