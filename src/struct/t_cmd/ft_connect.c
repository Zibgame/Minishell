#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int ft_connect(void)
{
    char *python_path = "/sgoinfre/goinfre/Perso/zcadinot/script/fc/ft_connect/src/ft_connect.py";
    
    // Vérifie si le fichier existe
    if (access(python_path, F_OK) == -1)
    {
        fprintf(stderr, "Erreur : Le fichier %s n'existe pas.\n", python_path);
        return 1;
    }
    
    // Vérifie les permissions d'exécution
    if (access(python_path, X_OK) == -1)
    {
        fprintf(stderr, "Erreur : Pas de permission d'exécution pour %s\n", python_path);
        return 1;
    }
    
    // Utilisation de fork/exec pour plus de contrôle
    pid_t pid = fork();
    
    if (pid == -1)
    {
        perror("Erreur fork");
        return 1;
    }
    else if (pid == 0)
    {
        // Processus enfant
        execlp("python3", "python3", python_path, NULL);
        // Si execlp échoue
        perror("Erreur execlp");
        exit(1);
    }
    else
    {
        // Processus parent
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status))
        {
            printf("Script terminé avec le code : %d\n", WEXITSTATUS(status));
            return WEXITSTATUS(status);
        }
        else
        {
            fprintf(stderr, "Script terminé anormalement\n");
            return 1;
        }
    }
}
