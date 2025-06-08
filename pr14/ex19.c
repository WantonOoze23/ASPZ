#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

volatile int ticks_handled = 0;
volatile int total_lost_ticks = 0;

void handler(int sig, siginfo_t *si, void *uc) {
    timer_t *tidp = si->si_value.sival_ptr;
    int overrun = timer_getoverrun(*tidp);

    if (overrun == -1) {
        perror("timer_getoverrun");
    } else {
        total_lost_ticks += overrun;
    }

    ticks_handled++;

    for (volatile int i = 0; i < 100000000; ++i);

    printf("Tick %d, Overrun: %d, Total lost: %d\n", ticks_handled, overrun, total_lost_ticks);
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;

    if (sigaction(SIGRTMIN, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    timer_t timerid;
    struct sigevent sev;
    memset(&sev, 0, sizeof(sev));
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &timerid; 

    if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1) {
        perror("timer_create");
        exit(EXIT_FAILURE);
    }

    struct itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 10000000;      // перший тік через 10 мс
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 10000000;   // інтервал 10 мс

    if (timer_settime(timerid, 0, &its, NULL) == -1) {
        perror("timer_settime");
        exit(EXIT_FAILURE);
    }

    // Працюємо 5 секунд
    sleep(5);

    printf("FINISHED: Ticks handled = %d, Total lost ticks = %d\n", ticks_handled, total_lost_ticks);

    return 0;
}
