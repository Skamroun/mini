#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av, char **env)
{
	while (*env++)
		printf("%s\n", *env);
}
