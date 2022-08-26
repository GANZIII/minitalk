#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int	num;
	int	i;
	int	sign;

	num = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (sign * num);
}

void    sigmanager(int pid, char *str)
{
    int   sig;
    int     i;
    char    c;

    while(*str)
    {
        c = *str;
        kill(pid, SIGUSR2);
        usleep(500); 
        i = 7;
        while (i)
        {
            sig = c & 64;
            c = c<<1;
            if (sig == 64)
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            i--;
            usleep(100);
        }
        str++;
    }
    
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        write(1, "error", 5);
        return (0);
    }
    sigmanager(ft_atoi(argv[1]), argv[2]);
    while (1)
        pause();
    return (0);
}