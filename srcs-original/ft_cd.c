#include "../include/minishell.h"

int	cd_command(char **args)
{
	char	*home;

	home = getenv("HOME");
	if (args[1] == NULL)
	{
		if (home == NULL)
		{
			perror("cd");
			return (ERROR);
		}

		if (chdir(home) != 0)
		{
			perror("cd");
			return (ERROR);
		}
	}
	else if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (ERROR);
	}
	return (SUCCESS);
}

// int main() {
// 	char *input = NULL;
// 	size_t input_size = 0;

// 	while (1) {
// 		printf("(Meu Minishell) > ");
// 		getline(&input, &input_size, stdin);

// 		// Quebre a linha de entrada em tokens (por exemplo, usando strtok).

// 		// Verifique se o comando é "cd".
// 		// Se sim, chame a função cd_command com os argumentos apropriados.
// 		// Caso contrário, crie um processo filho para executar o comando.

// 		// Lembre-se de lidar com a liberação de memória e erros apropriadamente.
// 	}

// 	free(input);
// 	return 0;
// }
