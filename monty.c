#define _POSIX_C_SOURCE 200809L
#include "monty.h"

char *push_arg = NULL;

/**
 * free_stack - frees all nodes in the stack
 * @stack: pointer to the top of the stack
 */
void free_stack(stack_t *stack)
{
	stack_t *tmp;

	while (stack)
	{
		tmp = stack->next;
		free(stack);
		stack = tmp;
	}
}

/**
 * get_op_func - finds the function matching the given opcode
 * @opcode: the opcode string
 *
 * Return: pointer to the matching function, or NULL if not found
 */
void (*get_op_func(char *opcode))(stack_t **, unsigned int)
{

instruction_t instructions[] = {
    {"push", op_push},
    {"pall", op_pall},
    {"pint", op_pint},
    {"pop", op_pop},
    {"swap", op_swap},
    {"add", op_add},
    {"div", op_div},
    {"nop", op_nop},
    {NULL, NULL}
}; 
	};
	int i = 0;

	while (instructions[i].opcode)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
			return (instructions[i].f);
		i++;
	}
	return (NULL);
}

/**
 * main - entry point for the Monty interpreter
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned int line_number = 0;
	stack_t *stack = NULL;
	char *opcode, *arg;
	void (*op_func)(stack_t **, unsigned int);

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++;

		/* Strip newline */
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		opcode = strtok(line, " \t");

		/* Skip empty lines and comments */
		if (!opcode || opcode[0] == '#')
			continue;

		arg = strtok(NULL, " \t");
		push_arg = arg; /* make arg accessible to op_push */

		op_func = get_op_func(opcode);
		if (!op_func)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
			free(line);
			free_stack(stack);
			fclose(file);
			exit(EXIT_FAILURE);
		}

		op_func(&stack, line_number);
	}

	free(line);
	free_stack(stack);
	fclose(file);
	return (EXIT_SUCCESS);
}
