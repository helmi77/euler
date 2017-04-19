#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int collatz(int start);
int parse_number(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    int number = parse_number(argc, argv);

    int result = 0, longest_chain = 0;
    for (int start = number; start >= 1; --start)
    {
        int chain_length = collatz(start);
        if (chain_length > longest_chain)
        {
            result = start;
            longest_chain = chain_length;
        }
    }
    printf("%d\n", result);

    return EXIT_SUCCESS;
}

int parse_number(int argc, char **argv)
{
    int opt = 0, number_flag = 0, number = 0;
    while ((opt = getopt(argc, argv, "m:")) != -1)
    {
        switch (opt)
        {
            case 'm':
                number_flag = 1;
                number = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -m maximum\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (!number_flag)
    {
        fprintf(stderr, "Usage: %s -m maximum\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return number;
}

int collatz(int start)
{
    int length = 1;
    unsigned long number = start;
    while (number != 1)
    {
        number = (number % 2 == 0) ? number / 2 : 3 * number + 1;
        ++length;
    }
    return length;
}
