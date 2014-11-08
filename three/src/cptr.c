// Question: Explain the compiler's errors reported on line 8, 11, and 14
#include <stdio.h>
int main()
{
	int a, b;
	b = a = 7; /* a is an integer */
	const int *aPtr1 = &a; /* aPtr1 is a pointer to an integer of a */
        //*aPtr1 = 9; // trying to modify a constant integer
	//
	int *const aPtr2 = &a; /* aPtr2 is a pointer to an integer of a */
        *aPtr2 = b; // trying to change the pointer location to a constant pointer
        //
        /*const*/ int *const aPtr3 = &a;  /* aPtr2 is a pointer to an integer of a */
        *aPtr3 = 329; // trying to modify a constant again
        //
	return 0;
}
