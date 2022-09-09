// client.c

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

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

int	checker(const char *str) // 정수인가? 확인해주는 함수.
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == 0) // 숫자만 나온 다음에 끝났다? 0 반환
		return (0);
	else // '0'~'9' 이외값 나왔는데 NULl아니다? -1 반환
		return (-1);
}

void	sigmanager(int pid, char *str)
{
	int		sig; // sig 확인함. 비트 단위로 0인가 1인가...
	int		i;   // 8bit 보내는 거 count 용도
	char	c;   // 문자

	while (*str)
	{
		c = *str;
		kill(pid, SIGUSR2); // 모든 아스키코드는 양수. 첫 비트 무조건 0임
		usleep(30); // server에서 보낸 신호대로 action하고 있는데 바로 client에서 다음 문장 실행하다가 꼬이면
                    // 문자 깨지고 난리남 => usleep으로 대기!!
		i = 7;      // 1bit (0) 보냈으니까 남은 bit는 7
		while (i)
		{
//  sig == 64 == 0100 0000
//  A   == 65 == 0100 0001
// & 비트 연산 =>  0100 0000
// (무조건 하위 6byte, 상위 1byte는 0 되고, 보낼 문자의 상위 2번째 바이트가 1이면 sig가 64 되고 0이면 0된다.)
			sig = c & 64;
			c = c << 1; // 다음 실행 때는 다음 비트 보내야 하므로 왼쪽으로 밀어
			if (sig == 64) // 보낼 비트가 1이면 sig 64 됨
				kill(pid, SIGUSR1); // 보내
			else
				kill(pid, SIGUSR2); // 0이면 얘 보내
			i--;
			usleep(30);             // 보냈으니까 기다려
		}
		str++; // 1bit씩 8번 해서 1byte 다 보냈으면 다음 문자 ㄲ
	}
}

int	main(int argc, char *argv[])
{
// ./client [PID] [string]
// 이렇게  실행해야 됨. 인자 3개여야 함
	if (argc != 3)
	{
		write(1, "error", 5);
		return (0);
	}

// 1번째 인자(pid)는 정수여야 함. (사실 이거 해줄 필요 없음 애초에 PID 맞는지도 client는 구분도 못함 ㅋㅋ)
	if (checker(argv[1]) == -1)
	{
		write(1, "error", 5);
		return (0);
	}
	sigmanager(ft_atoi(argv[1]), argv[2]); // pid, string 보냄
	return (0); // 문자열 출력했으면 나가
}
