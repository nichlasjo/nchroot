////===============================================
//// Name        : nchroot.c
//// Author      : Nichlas Johansson
//// Version     : 0.92
//// Copyright   : BSD 2 Clause.
//// Description : nchroot in C, Ansi-style
////===============================================

#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <pwd.h>

    // Detach function
void detach() {
     umount("/proc");
     }

static int childFunc(void *arg) {

     char **argv = arg;

    // Mount proc
     mount("proc", "proc", "proc",
             MS_RDONLY | MS_NOSUID | MS_NODEV | MS_NOEXEC,
	     NULL );
    // Exec
if (argv[2]!=NULL) {
     execvp(argv[2], &argv[2]);
     }
else {
     execlp("sh", "sh", NULL);
     // Run detach on exit
     atexit(detach);
     }
return(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {

     (void)argc;
     pid_t pid;
     int ret;
     long page_size = sysconf(_SC_PAGESIZE);
     void *stack = malloc(page_size) + page_size;
     chdir(argv[1]);
     chroot(".");
     // Print usage
if (argv[1]==NULL) {
     fprintf(stderr, "Usage: %s [chrootdir] cmd \n", argv[0]);
     }
     // Flag declaration, [insert getopt plz]
     int flags;
     flags = CLONE_NEWPID | CLONE_NEWIPC | CLONE_NEWNS |
             CLONE_FILES | CLONE_NEWUTS | CLONE_NEWCGROUP;
     // Childprocess with new PID/IPC/NS/ACL/UTS namespace
     pid = clone(childFunc, stack, flags | SIGCHLD, argv);
    // Wait for the child to terminate
while (waitpid(pid, &ret, 0) < 0 && errno == EINTR) {
     continue;
     return WIFEXITED(ret)?WEXITSTATUS(ret):EXIT_FAILURE;
     free(stack);
     }
}
