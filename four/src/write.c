#include <unistd.h>
#include "tlpi_hdr.h"
int main()
{
    if ((write(1, "Here is some data\n", 18)) != 18)
        write(2, "A write error has occurred on file descriptor 1\n",46);

    exit(EXIT_SUCCESS);
}
