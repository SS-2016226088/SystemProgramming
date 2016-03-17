#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

void showtime(long);
void show_info(struct utmp *);
void whoami(struct utmp *);

int main(int argc, char** argv)
{
        if (argc == 3){
                struct utmp utbuf;
                int utmpfd;
                if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
                        perror(UTMP_FILE);
                        return 1;
                }

                while( read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf))

                      whoami(&utbuf);

                close(utmpfd);
        }

        else if (argc == 2){
                struct utmp utbuf;
                int utmpfd;
                if ((utmpfd = open(argv[1], O_RDONLY)) == -1){
                        perror(UTMP_FILE);
                        return 1;
                }

                while( read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf))
                        show_info(&utbuf);

                close(utmpfd); // part b
        }
        else{
                struct utmp utbuf;
                int utmpfd;
                if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
                        perror(UTMP_FILE);

                        return 1;
                }

                while( read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf))
                        show_info(&utbuf);

                close(utmpfd);
        }

        return 0;
}

void show_info(struct utmp *utbufp)
{
        if (utbufp->ut_type != USER_PROCESS)
                return;

        printf("%-8.8s",utbufp->ut_name);
        printf(" ");
        printf("%-8.8s",utbufp->ut_line);
        printf(" ");
        showtime(utbufp->ut_time);


    printf("\nTYPE:  %d\t",utbufp->ut_type);
        printf("PID:  %d \n",utbufp->ut_pid);
        printf("ID:  %-8.8s\t",utbufp->ut_id);
        printf("USER:  %-8.8s\n",utbufp->ut_user);

        printf("HOST:  %-8.8s\t",utbufp->ut_host);

        int ip[4];
        ip[0] = utbufp->ut_addr_v6[0] & 0xFF;
        ip[1] = (utbufp->ut_addr_v6[0] >> 8) & 0xFF;
        ip[2] = (utbufp->ut_addr_v6[0] >> 16) & 0xFF;
        ip[3] = (utbufp->ut_addr_v6[0] >> 24) & 0xFF;
        printf("IP ADDRESS:  %d.%d.%d.%d\n",ip[0],ip[1],ip[2],ip[3]);

        printf("EXIT E-TERM:  %d  \tE-EXIT:  %d\n",utbufp->ut_exit.e_termination,utbufp->ut_exit.e_exit);
        printf("SESSION ID:  %i \n",(int) utbufp->ut_session);

        printf("\n");
}

void showtime(long timeval)
{
    char *cp;
        cp = ctime(&timeval);

        printf("%12.12s",cp+4);
}

void whoami(struct utmp *utbufp)
{
        if (utbufp->ut_type != USER_PROCESS)
                return;
        if (!strcmp(utbufp->ut_name,getenv("LOGNAME")))
        {
                printf("%-8.8s",utbufp->ut_name);
                printf(" ");
                printf("%-8.8s",utbufp->ut_line);
                printf(" ");
                showtime(utbufp->ut_time);

                #ifdef SHOWHOST
                if (utbufp->ut_host[0] != '\0')
                        printf(" (%s)",utbufp->ut_host);
                #endif

                                                     

                printf("\n");
        }
}


