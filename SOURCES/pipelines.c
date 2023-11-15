

#include "minishell.h"

/*

Para adicionar suporte a pipes (tubos) em seu minishell, você precisará fazer várias modificações em seu código.
Abaixo estão as alterações sugeridas:

Modifique a função ft_tokenize para detectar pipes:

No loop while, verifique se a linha de entrada contém o caractere de pipe (|). Se encontrar, divida a linha em duas partes:
antes do pipe e após o pipe.
Crie estruturas para representar cada comando:

Você pode criar uma estrutura para representar um comando único, com campos para o nome do comando e seus argumentos.
Também crie uma estrutura para representar uma sequência de comandos conectados por pipes.
Analise as partes antes e depois dos pipes:

Para cada parte, chame a função ft_tokenize para dividir ainda mais a parte em tokens, que serão os argumentos do comando.
Crie um processo filho para cada comando:

Para cada comando em sua sequência de comandos, crie um processo filho com fork.
Em cada processo filho, execute o comando correspondente usando execve.
Conecte os processos filhos com pipes:

Crie pipes antes de executar os comandos e redirecione a saída do comando anterior para a entrada do próximo comando.
Espere pela conclusão de todos os processos filhos:

Use a função wait ou waitpid para aguardar que todos os processos filhos sejam concluídos.
Limpeza:

Certifique-se de liberar memória alocada, fechar os descritores de arquivo dos pipes e realizar outras tarefas de limpeza.
Aqui está uma estrutura de código sugerida que incorpora essas modificações:



*/


// typedef struct Command {
//     char *name;
//     char **args;
// } Command;

// typedef struct Pipeline {
//     Command *commands;
//     int num_commands;
// } Pipeline;

// // Função para liberar a memória alocada para um comando
// void free_command(Command *cmd) {
//     free(cmd->name);
//     if (cmd->args) {
//         for (int i = 0; cmd->args[i]; i++) {
//             free(cmd->args[i]);
//         }
//         free(cmd->args);
//     }
// }

// // Função para liberar a memória alocada para uma sequência de comandos
// void free_pipeline(Pipeline *pipe) {
//     if (pipe->commands) {
//         for (int i = 0; i < pipe->num_commands; i++) {
//             free_command(&pipe->commands[i]);
//         }
//         free(pipe->commands);
//     }
// }

// // Função para executar uma sequência de comandos
// void execute_pipeline(Pipeline *pipe) {
//     int num_pipes = pipe->num_commands - 1;
//     int pipes[2 * num_pipes];

//     for (int i = 0; i < num_pipes; i++) {
//         pipe(pipes + i * 2);
//     }

//     for (int i = 0; i < pipe->num_commands; i++) {
//         pid_t child_pid = fork();

//         if (child_pid == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }

//         if (child_pid == 0) {
//             if (i > 0) {
//                 dup2(pipes[(i - 1) * 2], STDIN_FILENO);
//             }
//             if (i < num_pipes) {
//                 dup2(pipes[i * 2 + 1], STDOUT_FILENO);
//             }

//             for (int j = 0; j < num_pipes * 2; j++) {
//                 close(pipes[j]);
//             }

//             execve(pipe->commands[i].name, pipe->commands[i].args, NULL);
//             perror("execve");
//             exit(EXIT_FAILURE);
//         }
//     }

//     for (int i = 0; i < num_pipes * 2; i++) {
//         close(pipes[i]);
//     }

//     for (int i = 0; i < pipe->num_commands; i++) {
//         wait(NULL);
//     }
// }

// int main(int argc, char *argv[]) {
//     (void) argc;

//     char *prompt = "(Versao teste $) > ";
//     char *lineptr;
//     size_t nbr_tokens = 0;

//     while (1) {
//         printf("%s", prompt);
//         lineptr = readline(prompt);

//         if (lineptr == NULL) {
//             printf("Exiting shell...\n");
//             free(lineptr);
//             break;
//         }

//         Pipeline pipeline;
//         pipeline.num_commands = 0;
//         pipeline.commands = NULL;

//         char *token = strtok(lineptr, "|");

//         while (token != NULL) {
//             Command cmd;
//             cmd.name = strtok(token, " ");

//             char **args = NULL;
//             char *arg = strtok(NULL, " ");
//             int arg_count = 0;

//             while (arg != NULL) {
//                 args = realloc(args, (arg_count + 2) * sizeof(char *));
//                 args[arg_count] = strdup(arg);
//                 args[arg_count + 1] = NULL;
//                 arg = strtok(NULL, " ");
//                 arg_count++;
//             }

//             cmd.args = args;
//             pipeline.commands = realloc(pipeline.commands, (pipeline.num_commands + 1) * sizeof(Command));
//             pipeline.commands[pipeline.num_commands] = cmd;
//             pipeline.num_commands++;
//             token = strtok(NULL, "|");
//         }

//         execute_pipeline(&pipeline);

//         for (int i = 0; i < pipeline.num_commands; i++) {
//             free_command(&pipeline.commands[i]);
//         }

//         free_pipeline(&pipeline);

//         free(lineptr);
//     }

//     return 0;
// }




/*

Este código é um exemplo básico de como você pode implementar pipelines em seu minishell.
Você pode ajustá-lo de acordo com suas necessidades e requisitos específicos.
Certifique-se de incluir verificações de erros e lidar com a limpeza adequada da memória
e dos descritores de arquivo para evitar vazamentos de recursos.

*/
