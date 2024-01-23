#include "sort.h"

int find_max(int *arr, int n);
void counting_sort(int *arr, int n, int exp, int *output);
void radix_sort(int *arr, int n);

/**
 * find_max - Find the maximum value in an array.
 * @arr: The array of integers.
 * @n: The size of the array.
 *
 * Return: The maximum integer in the array.
 */
int find_max(int *arr, int n)
{
    int max = arr[0];

    for (int i = 1; i < n; ++i)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    return max;
}

/**
 * counting_sort - Perform counting sort on the significant digits.
 * @arr: The array of integers.
 * @n: The size of the array.
 * @exp: The current significant digit.
 * @output: The output array to store the sorted elements.
 */
void counting_sort(int *arr, int n, int exp, int *output)
{
    const int RADIX = 10;
    int count[RADIX] = {0};

    for (int i = 0; i < n; ++i)
        count[(arr[i] / exp) % RADIX]++;

    for (int i = 1; i < RADIX; ++i)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; --i)
    {
        output[count[(arr[i] / exp) % RADIX] - 1] = arr[i];
        count[(arr[i] / exp) % RADIX]--;
    }

    for (int i = 0; i < n; ++i)
        arr[i] = output[i];
}

/**
 * radix_sort - Sort an array of integers using LSD Radix Sort.
 * @arr: The array of integers.
 * @n: The size of the array.
 */
void radix_sort(int *arr, int n)
{
    if (arr == NULL || n < 2)
        return;

    int max = find_max(arr, n);
    int *output = malloc(sizeof(int) * n);

    if (output == NULL)
        return;

    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        counting_sort(arr, n, exp, output);
        print_array(arr, n);
    }

    free(output);
}
