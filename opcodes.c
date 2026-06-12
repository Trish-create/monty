#include "monty.h"

/**
 * op_push - pushes an integer onto the stack
 * @stack: pointer to the top of the stack
 * @line_number: current line number in the bytecode file
 *
 * Description: Like placing a new plate on top of a stack of plates.
 * Validates that the argument is a valid integer first.
 */
void op_push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_node;
	int i = 0;

	/* Validate argument exists and is a valid integer */
	if (!push_arg)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	/* Allow optional leading minus sign */
	if (push_arg[0] == '-')
		i = 1;

	/* Every remaining character must be a digit */
	for (; push_arg[i]; i++)
	{
		if (push_arg[i] < '0' || push_arg[i] > '9')
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
	}

	/* Must have at least one digit (handle bare "-" case) */
	if (push_arg[i == 0 ? 0 : 1] == '\0' && push_arg[0] == '-')
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = atoi(push_arg);
	new_node->prev = NULL;
	new_node->next = *stack;

	/* If stack already has nodes, link back to new top */
	if (*stack)
		(*stack)->prev = new_node;

	*stack = new_node;
}

/**
 * op_pall - prints all values on the stack from top to bottom
 * @stack: pointer to the top of the stack
 * @line_number: current line number (unused but required by signature)
 *
 * Description: Like reading the labels on your stack of plates top-to-bottom.
 * Does nothing if the stack is empty.
 */
void op_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	(void)line_number; /* suppress unused parameter warning */

	current = *stack;
	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
