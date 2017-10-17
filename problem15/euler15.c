#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void parse_args(int argc, char* argv[], int *grid_size)
{
    int opt = 0;
    while ((opt = getopt(argc, argv, "s:")) != -1)
    {
        switch (opt)
        {
            case 's':
                *grid_size = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -s gridsize\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

void generate_triangle(uintmax_t ***triangle, int height)
{
    for (int i = 0; i < height; ++i)
    {
        int columns = (i == 0) ? 1 : i + 2;
        (*triangle)[i] = malloc(sizeof(uintmax_t) * columns);
        for (int j = 0; j < columns; ++j)
        {
            if (j == 0 || j == columns - 1)
                (*triangle)[i][j] = 1;
            else
            {
                if (i == 1)
                    (*triangle)[i][j] = 2;
                else
                    (*triangle)[i][j] = (*triangle)[i - 1][j - 1] + (*triangle)[i - 1][j];
            }
        }
    }
}

uintmax_t get_paths(uintmax_t **triangle, int row)
{
    return triangle[row][(row + 2) / 2];
}

int main(int argc, char* argv[])
{
    int grid_size = -1;
    parse_args(argc, argv, &grid_size);
    int rows = grid_size * 2;

    if (grid_size <= 0)
    {
        fprintf(stderr, "Grid size must be a positive integer\n");
        exit(EXIT_FAILURE);
    }

    uintmax_t **triangle = malloc(sizeof(uintmax_t*) * rows);
    generate_triangle(&triangle, rows);

    uintmax_t sum = get_paths(triangle, rows - 1);
    printf("%"PRId64"\n", sum);

    for (int i = 0; i < rows; ++i)
    {
        free(triangle[i]);
    }
    free(triangle);

    return EXIT_SUCCESS;
}
