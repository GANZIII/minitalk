#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	put_div(int num, int p, int f)
{
	int		rest;
	char	c;

	if (p == 1)
	{
		rest = num % 10;
		c = rest + '0';
		write(f, &c, 1);
	}
	else
	{
		num /= 10;
		put_div(num, p - 1, f);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	power;
	int	cp;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	cp = n;
	power = 1;
	while (cp > 9)
	{
		cp /= 10;
		power++;
	}
	while (power)
	{
		put_div(n, power, fd);
		power--;
	}
}

void    action(int sig)
{
    static int  byte_len;
    static char c;

    byte_len++;
    c =  c<<1;
    if (sig == SIGUSR1)
        c = c | 1;
    if (byte_len == 8)
    {
        write(1, &c, 1);
        c = 0;
        byte_len = 0;
    }
}

int main(void)
{
    __pid_t pid;

    pid = getpid();
    write(1, "pid: ", 5);
    ft_putnbr_fd(pid, 1);
    signal(SIGUSR1, action);
    signal(SIGUSR2, action);
    while (1)
        pause();
    return (0);
}