// Question: (1) Why your program is aborted? 
#include <stdio.h>
int main()
{
	int a;
 	int *aPtr;
        // never initialzied the pointer.
        aPtr = &a;
        *aPtr = 5;
	printf("The address of a is %p"
		"\nThe value of aPtr is %p", &a, *aPtr);

	return 0;
}
