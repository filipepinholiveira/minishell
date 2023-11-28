/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/28 16:17:18 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/// @brief 				Shows the function name and status
/// @param func_name	Name of the function
/// @param status		Status of the function
/// @return				Status of the function
int	show_func(const char *func_name, int status)
{
	if (MY_DEBUG)
	{
		if (status == ERROR)
			printf("%s(X)%s %s : ERROR%s\n",SYLW, SRED, func_name, SWHT);
		else if (status == SUCCESS)
			printf("%s(X)%s %s : SUCCESS%s\n",SYLW, SGRN, func_name, SWHT);
		else if (status == MY_START)
			printf("%s(>)%s %s : START%s\n",SYLW, SYLW, func_name, SWHT);
	}
	return (status);
}

/// @brief 			Checks if the number of arguments is valid
/// @param argc		Number of arguments
/// @return			SUCCESS if valid, ERROR if invalid
int	invalid_argc(int argc)
{
	show_func(__func__, MY_START);
	if (argc == 1)
	{
		printf("\t%s : Invalid number of arguments : %d\n",__func__, argc);
		return (show_func(__func__, ERROR));
	}
	else
	{
		printf("\t%s : Valid number of arguments:%d\n",__func__,  argc);
	}
	return (show_func(__func__, SUCCESS));
}

int invalid_char(char *str, char *c)
{
	int	i;
	int	k;

	k = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == *c)
			k++;
	}
	if (k % 2 != 0)
	{
		printf("\t%s : Invalid quotes : k(%c) = %d\n", __func__, *c, k);
		return (show_func(__func__, ERROR));
	}
	else
	{
		printf("\t%s : Valid quotes\n", __func__);
		return (show_func(__func__, SUCCESS));
}
}

/// @brief 				Checks if the quotes are valid
/// @param cmdline		Command line
/// @return				SUCCESS if valid, ERROR if invalid
int invalid_quotes(char **cmdline)
{
	int i;
	int j;
	int k;

	show_func(__func__, MY_START);
	i = -1;
	while (cmdline[++i] != NULL)
	{
		if (invalid_char(cmdline[i], "\""))
			return (show_func(__func__, ERROR));
		if (invalid_char(cmdline[i], "\'"))
			return (show_func(__func__, ERROR));
	}
	return (show_func(__func__, SUCCESS));
}

/// @brief 			Checks if the argument is valid
/// @param argv		Argument
/// @return			SUCCESS if valid, ERROR if invalid
int	invalid_argv(char **argv)
{
	show_func(__func__, MY_START);
	printf("\t%s : argv[0] : %s\n",__func__, argv[0]);
	if (argv[0] == NULL)
	{
		printf("\t%s : Invalid argument\n", __func__);
		return (show_func(__func__, ERROR));
	}
	else
	{
		printf("\t%s : Valid argument : %s\n", __func__, argv[0]);
		if (invalid_quotes(argv))
			return (show_func(__func__, ERROR));
	}
	return (show_func(__func__, SUCCESS));
}

// int parse_shell(char **cmdline)
// {
// 	while (*cmdline != NULL)
// 	{
// 		if (invalid_quotes(cmdline))
// 			return (ERROR);
// 		*cmdline = ft_tokenize(*cmdline);
// 	}
// }


//static init_all(char **)



// int	main(int argc, char **argv)
// {
// 	if (invalid_argc(argc) || invalid_argv(argv))
// 		return (ERROR);
// 	return (init_all(argv));
// }


int	main(int argc, char **argv)
{
	// char		*prompt = "(Versao teste $) > ";
	// char		*lineptr = NULL;
	// const char	*exit_shell = "exit";
	// size_t		nbr_tokens = 0;
	//t_cmd		pcmd;

//	(void)ac;
//	(void)av;

	if (invalid_argc(argc) || invalid_argv(++argv))
	{
		return (-1);
	}
	int i = -1;
	while (argv[++i])
		printf("\t%s : argv[0]:%s\n",__func__, argv[i]);
	return (0);
}

// void continue_main_here(void)
// {
// 	//	init_shell();
// 	while (1)
// 	{
// 		printf("%s", prompt);
// 		lineptr = readline(lineptr);
// 		if (lineptr == NULL)
// 		{
// 			printf("Exiting shell...\n");
// 			free ((char *)lineptr);
// 			return (-1);
// 		}
// 		else if (ft_strncmp(lineptr, exit_shell, ft_strlen(exit_shell)) == 0) //tratamento temporario do exit, ja que exit é um command a ser executado e nao
// 		{
// 			printf("Exiting shell...\n");
// 			free ((char *)lineptr);
// 			return (-1);
// 		}
// 		while(lineptr != NULL)
// 		{
// 			lineptr = ft_tokenize(lineptr, &nbr_tokens);
// 		}
// 	}
// 	free((char *)lineptr);
// 	free((char *) exit_shell);
// 	return (0);
// }
