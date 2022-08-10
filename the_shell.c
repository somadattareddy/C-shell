#include "prints_prompt.h"

int main()
{
    shell_pid = getpid();
    print_prompt();
    return 0;
}