#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int carry(int num);
int unit_pos(int num);
void sum(int **numbers, size_t arr_len);

size_t read_numbers(int **numbers);
size_t process_line(char *line, int **numbers);

int main(int argc, char *argv[])
{
    int *numbers = NULL;
    size_t arr_len = read_numbers(&numbers);
    sum(&numbers, arr_len);
    for (int i = 0; i < arr_len; ++i)
    {
        printf("%d", numbers[i]);
    }
    printf("\n");

    free(numbers);
    return 0;
}

size_t read_numbers(int **numbers)
{
    size_t line_sz = 0, line_len;
    char *line = NULL;
    while (getline(&line, &line_sz, stdin) >= 0)
    {
        line_len = process_line(line, numbers);
    }
    free(line);
    return line_len;
}

size_t process_line(char *line, int **numbers)
{
    size_t i = 0, line_len = strlen(line);
    if (*numbers == NULL)
        *numbers = calloc(line_len + 1, sizeof(int));

    for (; i < line_len && isdigit(line[i]); ++i)
    {
        int digit = line[i] - '0';
        (*numbers)[i + 1] = (*numbers)[i + 1] + digit;
    }
    return i + 1;
}

void sum(int **numbers, size_t arr_len)
{
    int sum = 0;
    for (int i = arr_len - 1; i >= 1; --i)
    {
        int rem = carry((*numbers)[i]);
        int pos = unit_pos((*numbers)[i]);
        (*numbers)[i] = pos;
        (*numbers)[i - 1] += rem;
    }
}

int unit_pos(int num)
{
    return num % 10;
}
int carry(int num)
{
    return (num - unit_pos(num)) / 10;
}
