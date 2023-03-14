#include <unistd.h>
#include <stdio.h>
int main(int argc, char **argv, char **envp) {
    int ret;
    int x = 0;
    printf("-----------------------------------------\n");
    while(argv[x] != NULL)
    {
        printf("argv[%d] -> %s\n", x, argv[x]);
        x++;
    }
    x = 0;
    while(envp[x] != NULL)
    {
        printf("envp[%d] -> %s\n", x, envp[x]);
        x++;
    }
    printf("-----------------------------------------\n");
    ret = execve ("/bin/echo", argv, envp);
/*                 L----> caminho = /bin/ + nome da ft
                                L----> seria tipo as flags e o q vem dps (ex: -n teste)echo
                                      L----> so manda a envp
 */
}