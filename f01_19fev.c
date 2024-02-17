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



Lista de ficheiros e observaçoes quanto ao return_error:

void 100_main.c () 
{

/*#######################################################*/


	char	**envp_init(char **envp)

		if (!ms_envp) -> return_error("", errno, 1); // ja estava
		if (!ms_envp[i]) -> return_error("", errno, 1); // adicionada por mim


#######################################################

	int	ms_loop(t_script *s) 

#######################################################

	int	main(int argc, char **argv, char **envp) 

######################################################

}

void 200_signal.c ()
{

######################################################

void	signal_setter(void) /

#######################################################

void	sig_handler(int signum)

#######################################################

void	sig_handler_fork(int signum)

#######################################################

void	sig_handler_heredoc(int signum)

#######################################################

}

void 300_parser.c ()
{
######################################################

int	parse_commands(t_token *tk, t_command *cmd, int i, int j)

	estava: 	
	
	if (!cmd[i].argv)
		return (1);

	alterei:
	
	if (!cmd[i].argv)
		{
			return_error("", errno, 1); // adicionada Filipe 19fev
			return (ERROR);
		}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

	estava: 

		return (0);

	alterei:

		return (SUCCESS);		


######################################################

int	parser(t_script *s, char **line_buffer)

	if (!*line_buffer)
		return (return_error("readline error\n", 2, 0)); // já estava


	estava: 
	s->cmds = malloc(sizeof(t_command) * s->cmd_count);
	if (!s->cmds || s->cmd_count <= 0)
		return (free_tokens(&tk));

	alterei:

	if (!s->cmds || s->cmd_count <= 0)
	{
		return_error("", errno, 1);
		return (free_tokens(&tk));
	}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

	estava: 

		return (0);

	alterei:

		return (SUCCESS);

#######################################################
}

void 301_parser_syntax.c ()
{

######################################################


int	syntax_error_msg(char *tk_content, int errms, int errsys) -> exemplo a seguir ao recorrer a malloc

	status = return_error(msgr, errms, errsys); // ja estava


######################################################


int	syntax_checker(t_token *tk)

	uso na função de chamada do syntax_error_msg o qual recorre ao return_error


#######################################################

}

void 302_parser_cmd.c ()
{

######################################################

int	cmds_counter(t_token *tk)

#######################################################

}

void 303_parser_argc.c ()
{

######################################################

void	args_counter(t_token *tk, t_script *s)

#######################################################

}

void 304_parser_redir.c ()
{

######################################################


void	fnames_clear(t_command *cmds, int max, t_token *tk)


######################################################


int	redir(t_token *tk, t_redirection *file)

	ret = open(file->name, file->flag, 0644);
	if (ret == -1)
		return (return_error(file->name, 0, 1)); // já estava

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

	nas linhas 48, 59 e 64

		return (0);

	alterado para 

		return (SUCCESS);

#######################################################

}

void 305_parser_heredoc.c ()
{

######################################################

void	fill_heredoc(t_redirection *file)

#######################################################

}

void 400_termios.c ()
{

######################################################

void	termios_getter(struct termios *termios_p)

	err = tcgetattr(STDIN_FILENO, termios_p);
	if (err != 0)
		return_error("tcgetattr() error", err, 1); // já estava tratado

######################################################

void	termios_setter(struct termios *termios_p)

	err = tcsetattr(STDIN_FILENO, TCSAFLUSH, termios_p);
	if (err != 0)
		return_error("tcsetattr() error", err, 1); // já estava tratado

#######################################################

}

void 501_tk_builder.c ()
{

######################################################

void	tk_rm_blank(t_token *head)



######################################################

t_ops	tk_type_getter(const char *s)



######################################################

int	tk_getter(char *str, t_token **tk_lst)

	else if ((*str == '\"' || *str == '\'') && tk_quotes_checker(&str))
			return (ERROR); // nao preciso de fazer return (return_error("", ms_error, basherr)) pq é feito na chamada em tk_builder, certo?

######################################################

int	tk_builder(char **line, t_token **tk, t_script *s)

	if (tk_getter(*line, tk) == ERROR)
	{
		return_error("Syntax Error", 1, 0); 
		return (ERROR); // já estava feito
	}


#######################################################

}

void 502_tk_xpd.c ()
{

######################################################

int	tk_var_xpd_splits_count(char *otk)

	
#######################################################

char	**tk_var_xpd_init(char *otk)

	estava:

			ntks = (char **)malloc(sizeof(char *) * (spl + 1));

	adicionei

			ntks = (char **)malloc(sizeof(char *) * (spl + 1));
			if (!ntks)
			{
				return_error("", errno, 1);
				return (NULL);
			}


#######################################################

char	**tk_var_xpd(char *otk)


#######################################################

char	*tk_env_var_expander(char *otk, t_script *s)

#######################################################

}

void 503_tk_xpd_lst.c ()
{

######################################################

int	var_name_checker(char c)

	
#######################################################

int	var_firstchar(char c)

#######################################################

t_token	*tk_addnew(const char *str, int size, t_token_type type)

	estava:

	if (!tk)
		return (NULL);


	alterei:

	if (!tk)
	{
		return_error("", errno, 1);
		return (NULL);
	}


#######################################################

t_token	*tk_lst_last_getter(t_token *ltk)

	if (!ltk)
		return (NULL); // nap utilizei o return_error pq nao sei se o sistema trata este erro de nao ser passada lista


#######################################################

void	tk_lst_addback(t_token **ltk, t_token *ntk)

#######################################################

}

void 504_tk_xpd_count.c ()
{

######################################################

void	tk_var_xpd_dolar_c(char *otk, int *i)

#######################################################

void	tk_var_xpd_dquote_c(char *otk, int *spl, int *i)

#######################################################

void	tk_var_xpd_squote_c(char *otk, int *i)

#######################################################

void	tk_var_xpd_else_c(char *otk, int *i)

#######################################################

}

void 505_tk_xpd_filler.c ()
{

######################################################

char	*tk_xpd_var_filler(char *ntk, t_script *s)

#######################################################

char	*tk_xpd_filler(char ***ntks, t_script *s)

#######################################################

}

void 506_tk_xpd_split.c ()
{

######################################################

char	*tk_var_xpd_dolar(char *otk, int *i)

#######################################################

void	tk_var_xpd_dquote(char *otk, char ***ntks, int *spl, int *i)

#######################################################

void	tk_var_xpd_squote(char *otk, char ***ntks, int *spl, int *i)

#######################################################

void	tk_var_xpd_else(char *otk, char ***ntks, int *spl, int *i)

#######################################################

}

void 507_tk_quotes.c ()
{

######################################################

int	tk_quotes_checker(char **str)

	if (!(*str))
	{
		(*str) = tmp + ft_strlen(tmp);
		return (ERROR); 
		/*
		pelo que percebi a *str é " e vai procurar na str pela " que falta e 
		retornar ponteiro para essa posiçao, em caso de erro acho que basta o return(ERROR) 
		*/ 
	}

#######################################################

char	*tk_xpd_unquote(char *str)

######################################################

void	tk_trim_spaces(t_token *tk)

######################################################

}

void 600_env.c ()
{

######################################################


#######################################################

}

void 700_exec_start.c ()
{

######################################################


#######################################################

}

void 705_exec_type.c ()
{

######################################################


#######################################################

}

void 710_exec_one.c ()
{

######################################################


#######################################################

}

void 720_exec_many.c ()
{

######################################################


#######################################################

}

void 730_exec_childs.c ()
{

######################################################


#######################################################

}

void 740_exec_redirs.c ()
{

######################################################


#######################################################

}

void 750_exec_heredoc.c ()
{

######################################################


#######################################################

}

void 760_exec_pipes.c ()
{

######################################################


#######################################################

}

void 799_exec_errors.c ()
{

######################################################


#######################################################

}

void 810_bi_echo.c ()
{

######################################################


#######################################################

}

void 820_bi_cd.c ()
{

######################################################


#######################################################

}

void 830_bi_pwd.c ()
{

######################################################


#######################################################

}

void 840_bi_export.c ()
{

######################################################


#######################################################

}

void 850_bi_unset.c ()
{

######################################################


#######################################################

}

void 860_bi_env.c ()
{

######################################################


#######################################################

}

void 870_bi_exit.c ()
{

######################################################


#######################################################

}

void 880_bi_equal.c ()
{

######################################################


#######################################################

}

void 900_free.c ()
{

######################################################


#######################################################

}

void 910_errors.c ()
{

######################################################


#######################################################

}

void 999_debug.c ()
{

######################################################


#######################################################

}
