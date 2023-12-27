/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7ms_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:00:28 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/27 17:36:12 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 				Splits a string into an array of strings using a delimiter.
/// @param path 		String to be splited
/// @param delimiter 	character used as delimiter
/// @return 			String array containing splited string
char **split_path(char **path, char delimiter)
{
	size_t	count;
	size_t	i;
	size_t	j;
	size_t	start;
	char	*current;
	char	**result;

	// Conta o número de segmentos após a divisão
	count = 0;
	i = 0;

	// Encontrar o número total de segmentos
	while(path[i] != NULL)
	{
		current = path[i];
		while(*current != '\0')
		{
			if (*current == delimiter)
				count++;
			current++;
		}
		i++;
	}
	result = (char **)malloc(sizeof(char *) * (count + 1 +1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	// Loop para dividir cada string no array original
	while (path[i] != NULL) 
	{
		current = path[i];
		start = 0;

    	// Encontrar segmentos na string atual
    	while (*current != '\0') 
		{
			if (*current == delimiter) 
			{
				result[j] = ft_strdup(path[i] + start);
				if (result[j] == NULL) 
					return(NULL);
				j++;
				start = current - path[i] + 1;
			}
        	current++;
    	}

		// Adiciona o último segmento
		result[j] = strdup(path[i] + start);
		if (result[j] == NULL) 
			return(NULL);
		j++;
		i++;

		// Adiciona NULL para indicar o final do novo array
    	result[j] = NULL;
	}
	return (result);
}


/// @brief 				Duplica um descritor de arquivo para outro.
/// @param oldfd		O descritor de arquivo existente que será duplicado.
/// @param newfd		O novo descritor de arquivo que será associado ao oldfd.
/// @return 			Retorna o novo descritor de arquivo se a duplicação for bem-sucedida, ou -1 em caso de erro.
int ft_dup(int oldfd, int newfd) 
{
    if (oldfd == newfd) 
	{
        // Se oldfd e newfd forem iguais, não é necessário fazer nada
        return newfd;
    }

    close(newfd);  // Fecha newfd se já estiver aberto

    // Tenta duplicar oldfd para newfd
    int result = dup2(oldfd, newfd);

    if (result == -1) 
	{
        // Manipulação de erro (opcional)
        perror("Erro ao duplicar o descritor de arquivo");
    }

    return result;
}


/// @brief				Executa comandos encadeados usando pipes. 
/// @param s			Um ponteiro para a estrutura t_script contendo informações sobre os comandos.
/// @param path_env		Um array de strings representando o ambiente do processo.
/// @return				Retorna 0 se a execução for bem-sucedida, ou -1 em caso de erro.
int	pipex(t_script *s, char **path_env)
{
	int		cmd_numb;
	int		pipe_fds[2];
	int		i;
	pid_t	child_pid;
	int		status;

	i = 0;
	cmd_numb = s->cmd_count;
	while(i < cmd_numb - 1)
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("Error creating pipe");
			return (-1);
		}
		child_pid = fork;
		if (child_pid == -1)
		{
			perror("Error creating child process");
			return (-1);
		}
		if (child_pid == 0) // Processo filho
		{
			ft_dup(pipe_fds[1], STDOUT_FILENO);
			close(pipe_fds[0]);
			if (exe)
		}
	}
}
