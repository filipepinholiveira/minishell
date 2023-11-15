

#include "minishell.h"

int cd_command(char **args)
{
    if (args[1] == NULL) {
        // Nenhum diretório fornecido, volte para o diretório inicial do usuário.
        char *home = getenv("HOME");
        if (home == NULL) {
            perror("cd");
            return 1;
        }

        if (chdir(home) != 0) {
            perror("cd");
            return 1;
        }
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
            return 1;
        }
    }
    return 0;
}

// int main() {
//     char *input = NULL;
//     size_t input_size = 0;

//     while (1) {
//         printf("(Meu Minishell) > ");
//         getline(&input, &input_size, stdin);

//         // Quebre a linha de entrada em tokens (por exemplo, usando strtok).

//         // Verifique se o comando é "cd".
//         // Se sim, chame a função cd_command com os argumentos apropriados.
//         // Caso contrário, crie um processo filho para executar o comando.

//         // Lembre-se de lidar com a liberação de memória e erros apropriadamente.
//     }

//     free(input);
//     return 0;
// }
