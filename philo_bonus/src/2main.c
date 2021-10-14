#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

int	main(void)
{
	sem_t *id;
	size_t	i;

	sem_unlink("fork");
	id = sem_open("fork", O_CREAT, O_RDWR, 5);
	i = 0;
	while (i < 10)
	{
		printf("PRE LOOOOOP\n");
		sem_wait(id);
		printf("LOOOOOP %zu\n", i);
		sem_post(id);
		i++;
	}
}
