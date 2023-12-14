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
        
        if (execve(instruction, NULL, NULL) == -1) 
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
