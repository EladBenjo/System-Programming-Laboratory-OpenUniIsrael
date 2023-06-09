#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ENLARGE_SIZE sizeof(struct number)

/*	This program takes in a user input of numbers and makes a set out of it.
 *	Using a struct to track the size of the array in order to reallocate just
 *	as much memory needed.
 *	by Elad Benjo April 4th 2023
 */

/*function prototype*/
struct number;
struct number *get_set();
void print_set(struct number *arr, int arrLength);

/* this struct used to store the integer from users input and mark the last item
	of the array*/
struct number
{
    int x;
    bool last;
};

/* get set is getting the users input and turning it to a 'set' using dynamic
	memory allocating. in order to make legal set it will only store one instance
	of the same number in the set */
struct number *get_set()
{
    int arrLength = 1; /* used as a "pointer" , mostly to enlrage */
    int arraySize = 0; /* used as a "pointer" , as actual pointer in the arr */
    struct number *arr = malloc(ENLARGE_SIZE);
    int num; /* to store users inputs */
    bool match = false; /* is this num already in the set? */

    printf("Insert numbers to create a set:\n");
    while (scanf("%d", &num) != EOF)
    {
    	printf("%d ", num);
        match = false;
        for (int i = 0; i < arraySize; i++)
        {
            if (arr[i].x == num)
            {
                match = true;
                break;
            }
        } /* end of for loop check for duplicates */

        if (!match)
        {
            arrLength++;
            arr = realloc(arr, arrLength * ENLARGE_SIZE);
            arr[arraySize].x = num;
            arr[arraySize].last = true;
            if (arraySize != 0) /* case of first number to insert */
            {
                arr[arraySize-1].last = false;
            }
            arraySize++;
        } /* if it is a new number enlarge array and add it to the end, mark
        	 as last and remove mark from one before it*/
    }

    return arr;
}

/* a simple print function. using the "last" property of 'struct number' it will
	detremine printing space or new line*/
void print_set(struct number *arr, int arrLength)
{
    printf("\nSet contents:\n");
    for (int i = 0; i < arrLength; i++)
    {
        printf("%d", arr[i].x);
        if (arr[i].last == true)
        {
            printf("\n");
        }
        else
        {
            printf(" ");
        }
    }
}

/* the main function ties between get set and print set, it counts the length of
	the array using "last" property of 'struct number' and sending it as an argument
	for print set. */
int main()
{
    struct number *arr = get_set();
    int arrLength = 0;
    while (!arr[arrLength].last)
    {
        arrLength++;
    }
    arrLength++;

    /* Print out the contents of the array*/
    print_set(arr, arrLength);

    free(arr);
    return 0;
}

