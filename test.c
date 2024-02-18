#include <stdio.h>

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
		if (i != 0)
        	printf("ARG [%d] == [%s]\n", i, argv[i]);
    }
    return 0;
}