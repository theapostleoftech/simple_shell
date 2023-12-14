<<<<<<< HEAD:shell.c
#include "shell.h"

int main(int ac, char **argv)
{
 char *prompt = "(testshell) $ ";
    char *lineptr = NULL, *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;

    /* declaring void variables */
    (void)ac;

    /* Create a loop for the shell's prompt */
    while (1)
    {
        printf("%s", prompt);
        nchars_read = getline(&lineptr, &n, stdin);
        /* check if the getline function failed or reached EOF or user use CTRL + D */
        if (nchars_read == -1)
        {
            printf("Exiting shell....\n");
            return (-1);
        }

        /* allocate space for a copy of the lineptr */
        lineptr_copy = malloc(sizeof(char) * nchars_read);
        if (lineptr_copy == NULL)
        {
            perror("tsh: memory allocation error");
            return (-1);
        }
        /* copy lineptr to lineptr_copy */
        strcpy(lineptr_copy, lineptr);

        /********** split the string (lineptr) into an array of words ********/
        /* calculate the total number of tokens */
        token = strtok(lineptr, delim);

        while (token != NULL)
        {
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        /* Allocate space to hold the array of strings */
        argv = malloc(sizeof(char *) * num_tokens);

        /* Store each token in the argv array */
        token = strtok(lineptr_copy, delim);

        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;

        /* execute the command */
        execmd(argv);
    }

    /* free up allocated memory */
    free(lineptr_copy);
    free(lineptr);

    return (0);
}
=======
#include "shell.h"

/**
 * display_shell_prompt
 * 
 * Return: void
*/
void display_shell_prompt(void)
{
    printf("($) ");
    fflush(stdout);
}

/**
 * take_instruction
 * 
 * Return: void
*/
char *take_instruction(void) 
{
    char *instruction = NULL;
    size_t buffer_sz = 0;

    if (getline(&instruction, &buffer_sz, stdin) == -1) 
    {
        if (feof(stdin)) 
        {
            free(instruction);
            return (NULL);
        } 
        else 
        {
            perror("getline");
            exit(EXIT_FAILURE);
        }
    }

    return instruction;
}
/**
 * execute_instruction - performs cmdline operations
 * @instruction: tssk to be performed
 * 
 * Return: void
*/
void execute_instruction(char *instruction) 
{
    pid_t s_pid;
    int notify;

    s_pid = fork();

    if (s_pid == 0) 
    {
        char *argv[2];
        argv[0] = instruction;
        argv[1] = NULL;
       
        if (execve(instruction, argv, NULL) == -1) 
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } 
    else if (s_pid < 0) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else 
    {
        do {
            waitpid(s_pid, &notify, WUNTRACED);
        } while (!WIFEXITED(notify) && !WIFSIGNALED(notify));
    }
}

/**
 * main - main function
 * 
 * Return: nothing
*/
int main(void) 
{
    char *instruction;

    while (1) 
    {
        display_shell_prompt();
        instruction = take_instruction();

        if (instruction == NULL) 
        {
            printf("\n");
            break;
        }

        execute_instruction(instruction);
        free(instruction);
    }

    return (EXIT_SUCCESS);
}
>>>>>>> 8467ce53fd43c569152e631175797e09f69edfb5:new/shell.c
