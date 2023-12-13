/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpinho-d <fpinho-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:06:35 by fpinho-d          #+#    #+#             */
/*   Updated: 2023/12/05 11:13:58 by fpinho-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../SOURCES/minishell.h"


int arg_countsss(char **cmd)
{
    int count = 0;
    while (cmd[count])
        count++;
    return (count);
}




int echo_print(char **cmd)
{
  //int no_newline = 0;

/*
 echo;
 echo -n;
 echo filipe;
 echo -n filipe;
 echo filipe ...;
 echo -n filipe ...;

contar argumentos, até dois tratar direto; três se o 2º for -n tratar direto; 
três ou mains (sem -n) criar loop para imprimir todos os argumentos

tratar expander



*/
  int arg_nbr = arg_countsss(cmd);

  // printf("Args: %d\n", arg_nbr);
  // printf("cmd[1]: %s\n", cmd[1]);

  if (arg_nbr == 1)
    printf("\n");
  else if ((arg_nbr == 2) && (strcmp(cmd[1], "-n") == 0))
    return(0);
  else if ((arg_nbr == 2) && (strcmp(cmd[1], "-n") != 0))
    printf("%s\n", cmd[1]);
  else if ((arg_nbr == 3) && (strcmp(cmd[1], "-n") == 0))
  {
    //printf("Executar funçao sem quebra de linha para (echo -n 1)\n");
    int i = 2;
    while(i < arg_nbr && cmd)
    {
      ft_putstr_fd(cmd[i], 1);
      //write (1, " ", 1);
      i++;
    }
  }
  else if ((arg_nbr > 3) && (strcmp(cmd[1], "-n") == 0))
  {
    //printf("Executar funçao sem quebra de linha para (echo -n 1 2 3 4)\n");
    int i = 2;
    while(i < arg_nbr && cmd[i])
    {
      ft_putstr_fd(cmd[i], 1);
      if (i + 1 != arg_nbr)
        write (1, " ", 1);
      i++;
    }
  }
  else if ((arg_nbr >= 3) && (strcmp(cmd[1], "-n") != 0))
  {
    //printf("Executar funçao com quebra de linha para (echo 1 2 3 4)\n");
    int i = 1;
    while(i < arg_nbr && cmd[i])
    {
      ft_putstr_fd(cmd[i], 1);
      write (1, " ", 1);
      i++;
    }
    write (1, "\n", 1);
  }
}
