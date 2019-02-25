/*
 *proc_exit.h: 2019-02-25 created by qudreams
 * show the process-exit-notifier in kernel
 */

#ifndef PROC_EXIT_H
#define PROC_EXIT_H

int kproc_exit_init(void);
void kproc_exit_uninit(void);

#endif
