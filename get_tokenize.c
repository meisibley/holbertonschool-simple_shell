#include "main.h"
/**
 * get_tokenize - gets the input and tokenizes
 * Description: gets the line and tokenizes it
 * @lineptr: command line
 * Return: command array
 */
char **get_tokenize(char *lineptr)
{
	char *token = NULL, **cmd_arr = NULL;
	const char *delim = " \n";
	int i = 0, ntoken = 0, ct = 0, flag = 0;

	/*takes care of all spaces input*/
	while (lineptr[ct] != '\0' && lineptr[ct] != '\n')
	{
		if (lineptr[ct] == ' ' || lineptr[ct] == '\t' || lineptr[ct] == '\r')
			ct++;
		else
			flag = 1, ct++;
	}
	if (flag == 0)
		return (NULL);
	ntoken = get_num_token(lineptr);
	cmd_arr = malloc(sizeof(char *) * (ntoken + 1)); /*allocate argv*/
	if (cmd_arr == NULL)
	{
		free(cmd_arr);
		return (NULL);
	}
	token = strtok(lineptr, delim); /*store token in argv*/
	while (token)
	{
		cmd_arr[i] = malloc(sizeof(char) * strlen(token) + 1);
		if (cmd_arr[i] == NULL)
		{
			for (i--; i >= 0; i--)
				free(cmd_arr[i]);
			free(cmd_arr[i]);
			return (NULL);
		}
		strcpy(cmd_arr[i], token);
		token = strtok(NULL, delim);
		i++;
	}
	cmd_arr[i] = NULL;
	free(token);
	return (cmd_arr);
}
/**
 * free_tokens - frees the allocated memory for tokens
 * Description: frees memory
 * @cmd_arr: command array
 * Return: void
 */
void free_tokens(char **cmd_arr)
{
	int i;

	if (cmd_arr == NULL)
		return;
	for (i = 0; cmd_arr[i] != NULL; i++)
		free(cmd_arr[i]);
	free(cmd_arr);
}
/**
 * free_location - frees the allocated memory for command line
 * Description: frees memory
 * @actual_com: command line
 * Return: void
 */
void free_location(char *actual_com)
{
	if (actual_com == NULL)
		return;
	free(actual_com);
}
