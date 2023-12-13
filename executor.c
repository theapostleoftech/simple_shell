#include "shell.h"
/**
 * execute_command - executes a command
 * @line: the command to execute
 * 
 * Return: void
 */
void execute_command(char *line)
{
    /*char *argv[3];*/
    pid_t s_pid;
    int notify;
    int i;

    char **argv = string_splitter(line, " ");

    if (argv == NULL || argv[0] == NULL)
    {
        fprintf(stderr, "Error: Unable to parse command\n");
        free(argv);
        return;
    }

    if (_strcompare(argv[0], "env") == 0)
    {
        sh_env();
    }

    if (_strcompare(argv[0], "exit") == 0)
    {
        if (argv[1] != NULL)
        {
            sh_exit(argv[1]);
        }
        else
        {
            sh_exit(NULL);
        }
    }

     printf("Command: %s\n", argv[0]);

    if (access(argv[0], F_OK | X_OK) == 0)
    {
        char *message = "Command found in the current directory\n";
        write(STDOUT_FILENO, message, strlen(message));
    }

    else
    {
        pathlist *paths = create_path();
        char *realpath = search_path(paths, argv[0]);

        if (realpath == NULL)
        {
            perror("Error:");
            free_path(paths);
            free(argv);
            return;
        }

        argv[0] = realpath;

        free_path(paths);
    }

    printf("Executing: %s\n", argv[0]);
    printf("Arguments: ");
    for (i = 1; argv[i] != NULL; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");

    s_pid = fork();

    if (s_pid == -1)
    {
        perror("Error:");
        free(argv);
        exit(1);

    }

    if (s_pid == 0)
    {
        if (execve(argv[0], argv, NULL) == -1)
        {
            perror(argv[0]);
        }
        free(argv);
        exit(1);
    }
    else
    {
        do {
            waitpid(s_pid, &notify, WUNTRACED);
        } while (!WIFEXITED(notify) && !WIFSIGNALED(notify));

    }
    free(argv);
}
