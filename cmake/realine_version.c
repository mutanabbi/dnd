// ALERT Include `stdio.h` **BEFORE** the `readline/readline.h`
#include <stdio.h>
#include <readline/readline.h>

int main()
{
    printf("%d.%d", RL_VERSION_MAJOR, RL_VERSION_MINOR);
    return 0;
}
