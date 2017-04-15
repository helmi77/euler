#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_matrix(int ***matrix, int *rows, int *cols)
{
    int line_nr = 0, matrix_size = 0;
    char *line = NULL;
    size_t line_len = 0;
    while (getline(&line, &line_len, stdin) >= 0)
    {
        int *arr = NULL, arr_size = 0;

        char *token = NULL;
        while ((token = strsep(&line, " ")) != NULL)
        {
            arr = realloc(arr, sizeof(int) * (arr_size + 1));
            arr[arr_size++] = strtol(token, NULL, 10);
        }
        *matrix = realloc(*matrix, sizeof(int*) * (line_nr + 1));
        *(*matrix + line_nr) = arr;

        ++line_nr;
        *cols = arr_size;
    }
    *rows = line_nr;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int check_row(int *row, int row_size)
{
    int product = 0;
    for (int i = 3; i < row_size; ++i)
    {
        int cur_product = row[i] * row[i - 1] * row[i - 2] * row[i - 3];
        if (cur_product > product)
            product = cur_product;
    }
    return product;
}

int check_col(int **matrix, int col, int col_size)
{
    int product = 0;
    for (int i = 3; i < col_size; ++i)
    {
        int cur_product = matrix[i][col]
            * matrix[i - 1][col]
            * matrix[i - 2][col]
            * matrix[i - 3][col];
        if (cur_product > product)
            product = cur_product;
    }
    return product;
}

int check_left_diagonal(int **matrix, int row_size)
{
    int product = 0;
    for (int i = 3; i < row_size; ++i)
    {
        for (int j = 0; j <= i - 3; ++j)
        {
            int top_product = matrix[i - j][j]
                * matrix[i - j - 1][j + 1]
                * matrix[i - j - 2][j + 2]
                * matrix[i - j - 3][j + 3];
            int bot_product = matrix[row_size - 1 - i + j][row_size - 1 - j]
                * matrix[row_size - 1 - i + j + 1][row_size - 1 - j - 1]
                * matrix[row_size - 1 - i + j + 2][row_size - 1 - j - 2]
                * matrix[row_size - 1 - i + j + 3][row_size - 1 - j - 3];
            if (max(top_product, bot_product) > product)
                product = max(top_product, bot_product);
        }
    }
    return product;
}

int check_right_diagonal(int **matrix, int row_size)
{
    int product = 0;
    for (int i = 0; i < row_size - 3; ++i)
    {
        for (int j = 0; j < row_size - i - 3; ++j)
        {
            int top_product = matrix[i + j][j]
                * matrix[i + j + 1][j + 1]
                * matrix[i + j + 2][j + 2]
                * matrix[i + j + 3][j + 3];
            int bot_product = matrix[row_size - 1 - i - j][row_size - 1 - j]
                * matrix[row_size - 1 - i - j - 1][row_size - 1 - j - 1]
                * matrix[row_size - 1 - i - j - 2][row_size - 1 - j - 2]
                * matrix[row_size - 1 - i - j - 3][row_size - 1 - j - 3];
            if (max(top_product, bot_product) > product)
                product = max(top_product, bot_product);
        }
    }
    return product;
}

int main(int argc, char* argv[])
{
    int **matrix = NULL, rows = 0, cols = 0;
    read_matrix(&matrix, &rows, &cols);

    int product = 0;
    for (int i = 0; i < rows; ++i)
    {
        int row_product = check_row(matrix[i], rows);
        int col_product = check_col(matrix, i, cols);
        if (max(col_product, row_product) > product)
            product = max(col_product, row_product);
    }

    int left_diagonal = check_left_diagonal(matrix, rows);
    int right_diagonal = check_right_diagonal(matrix, rows);
    if (max(left_diagonal, right_diagonal) > product)
        product = max(left_diagonal, right_diagonal);

    printf("%d\n", product);
    return 0;
}
