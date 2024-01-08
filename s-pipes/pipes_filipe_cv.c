
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

#define PROCESS_NUM 3


/*

VIDEO EXPLICATIVO

https://www.youtube.com/watch?v=VzCawLzITh0


*/



// int main(int ac, char **av)
// {
//     int pipes[PROCESS_NUM + 1][2]; // criar array de pipes com os fd
//     int pids[PROCESS_NUM]; // criar array de processos para os child
//     int i;
//     int j;
//     int x;
//     int y;
    
//     criar os pipes necessarios 
//     i = -1;
//     while (++i < PROCESS_NUM + 1)
//     {
//         if (pipe(pipes[i]) == -1)
//         {
//             printf("Errro a criar pipes\n");
//             return(1);
//         }
//     }

//     criar os processos necesarios para os child
//     i = -1;
//     while (++i < PROCESS_NUM + 1)
//     {
//         pids[i] = fork();
//         if (pids[i] == -1)
//         {
//             printf("Errro a criar processos\n");
//             return(2);
//         }
//         if (pids[i] == 0)
//         {
//             estamos no child
//             j = -1;
//             while(++j < PROCESS_NUM + 1)
//             {
//                 if (i != j)
//                 {
//                     close(pipes[j][0]);
//                 }
//                 if (i + 1 != j)
//                 {
//                     close(pipes[j][1]);
//                 }
//             }
//             if (read(pipes[i][0], &x, sizeof(int)) == -1)
//             {
//                 printf("Erro ao ler dos fd dos pipes\n");
//                 return (3);
//             }
//             printf("%d recebeu %d\n", i, x);
//             x = x + 10; // damos aqui uma ordem para alterar nos processos (como se usar comandos para usar os valores lidos)
//             if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
//             {
//                 printf("Erro ao escrever nos fd pipes\n");
//                 return (4);
//             }
//             printf("%d enviou %d\n", i, x);
//             agora fechamos os pipes que estiveram a ser usados no loop
//             close(pipes[i][0]);
//             close(pipes[i + 1][1]);
//             return(0);
//         }
//     }
//         o parent process 
//         y = 5;
//         printf("O resultado inicial é: %d\n", y);
//         if (write(pipes[0][1], &y, sizeof(int)) == -1)
//         {
//             {
//                 printf("Erro ao escrever no pipe inicial\n");
//                 return (5);
//             }
//         }
//         if(read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1)
//         {
//                 printf("Erro ao ler do pipe final\n");
//                 return (6);
//         }

//         printf("O resultado final após %d processos é: %d\n", PROCESS_NUM, y);

//         i = -1;
//         while(++i < PROCESS_NUM)
//             wait(NULL);
//         return (0);

// }


int main(int ac, char **av)
{
    int pipes[PROCESS_NUM + 1][2];
    int pids[PROCESS_NUM];
    int i;
    
    // criar os pipes a serem usaqdos pelos processos
    for (i = 0; i < PROCESS_NUM + 1; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            printf("Erro criar pipes\n");
            return (1);
        }
    }
    // criar a lista de processos a serem usados (child process)
    for (i = 0; i < PROCESS_NUM; i++)
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            printf("Erro criar processos\n");
            return (2);
        }

        if (pids[i] == 0)
        {
            // estamos no child process
            for (int j = 0; j < PROCESS_NUM + 1; j++)
            {
                if(i != j)
                    close(pipes[j][0]);
                if (i + 1 != j)
                    close(pipes[j][1]);      
            }
            int x;
            if (read(pipes[i][0], &x, sizeof(int)) == -1)
            {
                printf("Erro ao ler do pipe\n");
                return (3);
            }
            printf("O child %d recebeu %d\n", i, x);
            x = x + 10;
            if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
            {
                printf("Erro ao escrever no pipe\n");
                return (4);
            }
            printf("O child %d enviou %d\n", i, x);
            close(pipes[i][0]);
            close(pipes[i + 1][1]);
            return (0);
        }
    }
    int y = 5;
    printf("O processo inicial é: %d\n", y);
    if (write(pipes[0][1], &y, sizeof(int)) == -1)
    {
        printf("Erro ao escrever no pipe inicial\n");
        return (5);
    }
    if (read(pipes[PROCESS_NUM][0], &y, sizeof(int) == -1))
    {
        printf("Erro ao ler do pipe\n");
        return (4);
    }

    printf("O resultado final é: %d\n", y);

    for (i = 0; i < PROCESS_NUM; i++)
    {
        wait(NULL);
    }
    return (0);
}



