/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:06:39 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/13 16:47:22 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define MAX_CMDS 7
#define ERROR -1

/// @brief 			Checks what's the command value in enumerator
/// @param argv		The string sent from argv
/// @return			value of cmd enumerator if valid, ERROR if invalid


int main(int ac, char **av, char **envp)
{
        char s[100];

        char *str;
        char ** cmd;
        while (1)
        {
            str = readline("Minishell: ");
            cmd = ft_split(str, ' ');

            if (strcmp(cmd[0], "echo") == 0)
                echo_print(cmd); // FEITO???
            else if (strcmp(cmd[0], "cd") == 0)
                cd_cmd(cmd); // FEITO
            else if (strcmp(cmd[0], "pwd") == 0)
            {
                pwd_print(); // FEITO???
            }
            else if (strcmp(cmd[0], "export") == 0)
                printf("Execute export with no options\n");
            else if (strcmp(cmd[0], "unset") == 0)
                printf("Execute unset with no options\n");
            else if (strcmp(cmd[0], "env") == 0)
            {
                env_print(cmd, envp); // FEITO
            }
            else if (strcmp(cmd[0], "exit") == 0)
            {
                 exit_shell(cmd); // FEITO
            }
            else
                {
            pid_t child_pid = fork();

            if (child_pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if (child_pid == 0)
            {
                // Processo filho
                char *command = get_location(cmd[0]);
                if (command != NULL) {
                    if (execve(command, cmd, NULL) == -1) {
                        perror("Error");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    // Tratar comandos que não existem no caminho especificado
                    printf("%s: command not found\n", cmd[0]);
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                // Processo pai
                wait(NULL);
            }

        }
        }

    return (0);
}




