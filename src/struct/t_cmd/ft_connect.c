#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int ft_connect(void)
{
    char *python_path = "/sgoinfre/goinfre/Perso/zcadinot/script/fc/ft_connect/src/ft_connect.py";
    
    if (access(python_path, F_OK) == -1)
    {
        return 1;
    }
    
    pid_t pid = fork();
    
    if (pid == -1)
    {
        return 1;
    }
    else if (pid == 0)
    {
        // Double fork pour détacher du terminal (technique de démonisation)
        pid_t pid2 = fork();
        
        if (pid2 == -1)
        {
            exit(1);
        }
        else if (pid2 == 0)
        {
            // Petit-fils - devient indépendant
            setsid(); // Crée une nouvelle session
            
            // Redirige les descripteurs standards
            int dev_null = open("/dev/null", O_RDWR);
            if (dev_null != -1)
            {
                dup2(dev_null, STDIN_FILENO);
                dup2(dev_null, STDOUT_FILENO);
                dup2(dev_null, STDERR_FILENO);
                if (dev_null > 2) close(dev_null);
            }
            
            // Exécute le script
            char *args[] = {"python3", python_path, NULL};
            execvp("python3", args);
            exit(1);
        }
        else
        {
            // Premier enfant se termine immédiatement
            exit(0);
        }
    }
    else
    {
        // Parent original
        int status;
        waitpid(pid, &status, 0);
        return 0; // Retourne succès une fois le processus détaché
    }
}
