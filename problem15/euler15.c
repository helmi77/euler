#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void parse_args(int argc, char* argv[], int *grid_size)
{
    *grid_size = -1;

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

int** generate_triangle(int height)
{
    int **triangle = malloc(sizeof(int) * height);
    // TODO: Populate the triangle rows up to height
    return triangle;
}

int main(int argc, char* argv[])
{
    int grid_size = -1;
    parse_args(argc, argv, &grid_size);
    if (grid_size < 0)
    {
        fprintf(stderr, "Usage: %s -s gridsize\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int **triangle = generate_triangle(grid_size);

    for (int i = 0; i < grid_size; ++i)
    {
        free(triangle[i]);
    }
    free(triangle);

    return EXIT_SUCCESS;
}
