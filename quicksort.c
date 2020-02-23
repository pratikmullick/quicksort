/* A simple Quicksort Program. Copyright 2019 2020. Pratik Mullick and Richard W. Marinelli. Please read LICENSE.md for further details. */

/* 
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/* 
algorithm quicksort(A, lo, hi) is
    if lo < hi then
    	        p := partition(A, lo, hi)
    	        quicksort(A, lo, p - 1)
    	        quicksort(A, p + 1, hi)

algorithm partition(A, lo, hi) is
    pivot := A[hi]
    i := lo
    for j := lo to hi do
	        if A[j] < pivot then
		            swap A[i] with A[j]
		            i := i + 1
    swap A[i] with A[hi]
    return i
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int reverse = -1;
static int (*scmp)(const char *s1, const char *s2) = strcmp;

static int partition(char **array, int low, int high)	{
	char *pivot = array[high];
	int i = low;
	char *temp;
	int result;
	// fputs(pivot, stdout); exit(1);
	for (int j = low; j <= high; j++)	{
		result = scmp(array[j], pivot);
		result = (result < 0) ? -1 : (result > 0) ? 1 : 0;
		if (result == reverse)	{
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			++i;
			}
		}
	array[high] = array[i];
	array[i] = pivot;
	return i;
	}

static void quicksort(char **array, int low, int high)	{
	int p;
	// printf("quicksort: %d, %d, \n", low, high); exit(1);
	if (low < high)	{
		p = partition(array, low, high);
		quicksort(array, low, p - 1);
		quicksort(array, p + 1, high);
		}
	}



// Read a line with getline. Getline returns the length (l). Use malloc to allocate (l+1) in memory. Copy **lineptr used in getline into the space. Add the pointer
// to the next element in the array.  Read no more than 1000 lines.  Sort the array. Print out the results to stdout.

int main(int argc, char **argv)	{
	// Getline requirements
#if 0
	char lineptr[512];
#else
	char *lineptr = NULL;
#endif
	FILE *stream;
	size_t length = 0;

	// Array requirements
	char *array[1000];
	int idx = 0;

	// Parse switches.
	--argc;
	++argv;
	while (argc > 0)	{
		if (**argv == '-')	{
			char *temp = *argv;
			if (strcmp(temp + 1,"r") == 0)	
				reverse = 1;
			else if (strcmp(temp + 1,"i") == 0)	
				scmp = strcasecmp;
			else	{
				fprintf(stderr, "Incorrect option '%s'\n", temp);
				return 1;
				}
			}
		else
			break;
		--argc; ++argv;
		}
	
	if (argc == 0)	{
		stream = stdin;
		}		
	else if (argc > 1)	{
		fprintf(stderr, "Usage: %s [-i] [-r] [file]\n", argv[0]);
		return 1;
	}
	else if ((stream = fopen(*argv,"r")) == NULL)	{
		fprintf(stderr, "File open error. Filename: %s\n", argv[1]);
		return 1;
	}

	// Getting data into the array.
#if 1
	while ((idx < 1000) && (getline(&lineptr, &length, stream) != -1))	{
		array[idx] = malloc(length + 1);
		strcpy(array[idx], lineptr);
		// fputs(lineptr, stdout);
		idx++;
		}
#else
	while ((fgets(lineptr, sizeof(lineptr), stream) != NULL) && (idx < 1000))	{
		array[idx] = (char *) malloc(strlen(lineptr) + 1);
		// strcpy(array[idx], lineptr);
		// idx++;
		strcpy((array[idx++] = (char *) malloc(sizeof(lineptr))), lineptr);
	}
#endif
	quicksort(array, 0, idx - 1);

	// For Testing.
	for (int i = 0; i <= idx; i++)
		printf("%s", array[i]);

	return 0;
}
