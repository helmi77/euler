/*
 * This program takes an integer as input and calculates
 * the first triangle number which has a divisor count
 * that is larger than the specified input.
 *
 * The n-th triangle number is defined as the sum of
 * all integers up to and including n.
 * e.g. 4-th triangle number: 1 + 2 + 3 + 4 = 10
 *
 * The divisors of n are defined as the integers up to
 * and including n, whichevenly divide n.
 * e.g. divisors of 6: 1, 2, 3, 6
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void parse_args(int argc, char *argv[], int *divisors)
{
    int opt;
    while ((opt = getopt(argc, argv, "d:")) != -1)
    {
        switch (opt)
        {
            case 'd':
                *divisors = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -d divisors\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

int get_divisors(int number)
{
    if (number == 1) return 1;

    int i = 2, divisors = 0;
    while (i <= sqrt(number))
    {
        if (number % i == 0)
        {
            ++divisors;
            if (i != (number / i))
            {
                ++divisors;
            }
        }
        ++i;
    }
    return divisors + 2;
}

int main(int argc, char *argv[])
{
    int min_divisors = 0;
    parse_args(argc, argv, &min_divisors);
    if (min_divisors <= 0)
    {
        fprintf(stderr, "Divisors must be a positive integer\n");
        exit(EXIT_FAILURE);
    }

    int divisor_count = 0, triangle_number = 0;
    for (int i = 1; divisor_count <= min_divisors; ++i)
    {
        triangle_number += i;
        divisor_count = get_divisors(triangle_number);
    }

    printf("%d has %d divisors\n", triangle_number, divisor_count);

    return EXIT_SUCCESS;
}
