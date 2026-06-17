#include "monty.h"

void op_push(stack_t **stack, unsigned int line_number)
{
stack_t *new_node;
int i = 0;

if (!push_arg)
{
fprintf(stderr, "L%u: usage: push integer\n", line_number);
exit(EXIT_FAILURE);
}
if (push_arg[0] == '-')
i = 1;
for (; push_arg[i]; i++)
{
if (push_arg[i] < '0' || push_arg[i] > '9')
{
fprintf(stderr, "L%u: usage: push integer\n", line_number);
exit(EXIT_FAILURE);
}
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
if (*stack)
(*stack)->prev = new_node;
*stack = new_node;
}

void op_pall(stack_t **stack, unsigned int line_number)
{
stack_t *current;

(void)line_number;
current = *stack;
while (current)
{
printf("%d\n", current->n);
current = current->next;
}
}

void op_pint(stack_t **stack, unsigned int line_number)
{
if (!*stack)
{
fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
exit(EXIT_FAILURE);
}
printf("%d\n", (*stack)->n);
}

void op_pop(stack_t **stack, unsigned int line_number)
{
stack_t *tmp;

if (!*stack)
{
fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
exit(EXIT_FAILURE);
}
tmp = *stack;
*stack = (*stack)->next;
if (*stack)
(*stack)->prev = NULL;
free(tmp);
}

void op_swap(stack_t **stack, unsigned int line_number)
{
int tmp;

if (!*stack || !(*stack)->next)
{
fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
tmp = (*stack)->n;
(*stack)->n = (*stack)->next->n;
(*stack)->next->n = tmp;
}

void op_add(stack_t **stack, unsigned int line_number)
{
int sum;

if (!*stack || !(*stack)->next)
{
fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
sum = (*stack)->n + (*stack)->next->n;
(*stack)->next->n = sum;
op_pop(stack, line_number);
}

void op_div(stack_t **stack, unsigned int line_number)
{
int result;

if (!*stack || !(*stack)->next)
{
fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
if ((*stack)->n == 0)
{
fprintf(stderr, "L%u: division by zero\n", line_number);
exit(EXIT_FAILURE);
}
result = (*stack)->next->n / (*stack)->n;
(*stack)->next->n = result;
op_pop(stack, line_number);
}

void op_nop(stack_t **stack, unsigned int line_number)
{
(void)stack;
(void)line_number;
}
