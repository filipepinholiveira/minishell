/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f03.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:11:26 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/14 17:32:33 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

Alterações:


int	exec_many(t_script *s, char **path) // teste: "cat | cat | ls"
{
	---> linha 154:

	g_exit_status = WIFEXITED(g_exit_status);

	- com esta alteração ao executar "cat | cat | ls" + "ctrl + c" o g_exit_status com echo $? retorna 0, 
	no entanto o sinal "ctrl + c" deveria ter o valor 130! Decidir com o Antonio quanto a este valor. 

}




int	redir(t_token *tk, t_redirection *file)  // teste: "cat < ls" e "cat < ls > ls"
{
	 --> linha 63

	return (return_error(file->name, 1, 1));


int	return_error(const char *msg, int errms, int errbash) --> linha 47:

		if (!errms)
			g_exit_status = errno;

	- com esta alteraçao ao executar "cat < ls" e "cat < ls > ls" o ficheiro nao é econtrado com open, 
	chamando assim o return error e anteriormente o return error definia o g_exit_status pelo errno,
	que ao !open atribui valor 2. o Bash retorna 1. Tal como no ctl + c cujo erro é 130, mas echo $? retorna 0.



}



int	change_dir(char *path, char ***envp) // teste: cd gdhahahad
{

	--> linhas 30, 31, 32

	if (ret == -1)
	{
		write(1, "Minishell: cd: ", 15);
		(return_error(path, 0, 1));
		return (ERROR);
	}


	- com esta alteração ao executar "cd gdhahahad" tenho o retorno 'cd: gdhahahad: No such file or directory'
	quando anteriormente tinha apenas 'gdhahahad: No such file or directory'. Estava "return ((return_error(path, 0, 1)))"
	mas desta forma ao passares errbash o return_error ja nao escreve minishell, e nem sequer teria cd

}

	

int	bi_cd(t_script *s, int n) // teste: cd depois de unset HOME
{
	--> linha 57

	return (return_error("cd: HOME not set", 1, 0));

	-- ao passar errms ele vai escrever Minishell portanto retirei Minishell ao inicio da linha acima
}




int	bi_exit(t_script *s, int n) // teste: exit 42 10
{

	--> linha 74 a 78

	else if (s->cmds[n].argc > 2)
	{
		g_exit_status = exit_error_args("too many arguments\n", 1);
		return (ERROR);
	}


	int	exec_one(t_script *s, char **path)

	--> 112 a 117

	if (id == CMD_EXIT)
	{
		free_array(path, 0);
		if (exec_bi(id, s, 0))
			return (SUCCESS);
	}


	- com esta alteração o exit com 2 ou mais argumentos deixa de dar erros inesperados, nao sai do ms
	e escreve apenas 1 vez 
	
	exit
	Minishell: exit: too many arguments

}
