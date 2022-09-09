// server.c

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// putnbr에 딸린 함수
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


// pid(숫자) 출력하는 애
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


// signal의 handler
// client로부터 1bit씩 받는다.
// 1 == SIGUSR1 / 0 == SIGUSR2
void	action(int sig)
{
	static int	bit_len; // 1byte == 8bits 몇 bit 받았나.. 세는 용도.
                          // action 함수 8번 돌면서 값 증가해야 하니까, static!
	static char	c;        // 1bit 씩 8번 저장해서 1byte짜리 문자 하나 만들어야 함 => static!
                          // 처음 호출될 때 c = 0 = 0000 0000
	bit_len++;

// A == 65 == 01000000
// 0 -> 1 -> 0 -> 0 -> 0 -> 0 -> 0 -> 0 순서로 받는다.
// 1 받으면 c++ 하고, 0 받으면 아무 것도 안한다. 다음 호출 때 왼쪽으로 밀고 다음 비트 받는다. ㅇㅋ?

	c = c << 1; // 왼쪽으로 밀기 (처음 호출 땐.. 아무 일도 안일어남)
	if (sig == SIGUSR1)
		c++;
	if (bit_len == 8) // 8 bit 받아서 문자 하나 완성
	{
		write(1, &c, 1); // 쓰고
		c = 0; // 초기화
		bit_len = 0; // 하기
	}
}

int	main(void)
{
	__pid_t	pid;

	pid = getpid();
	write(1, "pid: ", 5);
	ft_putnbr_fd(pid, 1); // pid 출력하시고
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	while (1)
		pause();  // 신호 대기한다. 영원히~
	return (0);
}
