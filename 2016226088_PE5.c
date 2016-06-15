#include	<stdio.h>
#include	<signal.h>
#include <signal.h>
#include <stdlib.h>
main()
{
	void	f(int);			/* declare the handler	*/
	int	i;
	

	signal( SIGINT, f );		/* install the handler	*/

	for(i=0; i<10; i++ ){		/* do something else	*/
		printf("hello\n");
		sleep(1);
	
}
}

void f(int signum)			/* this function is called */
{
	char c;
	printf("Interrupted! OK to quit(y/n) ? \n");
	scanf("%s", &c);
	if(c=='y')
		exit(0);
	fflush(stdin);
//	printf("OUCH!\n");
}

