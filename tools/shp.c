#define _POSIX_C_SOURCE 200809L
#include "../ftemplate.h"
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

#define PROGNAME "shp"
#define COPYRIGHT_LINE \
    "Copyright (c) 2023 Harkaitz Agirre, harkaitz.aguirre@gmail.com" "\n" \
    ""
#define BUFFER_LENGTH 1024*10


int main (int _argc, char *_argv[]) {

    char          *b               = NULL;
    int            pid             = -1;
    int            p1[2]           = {-1,-1};
    int            p2[2]           = {-1,-1};
    int            echo_fd;
    int            status;
    int            exit_code       = 1;
    int            e;

    b = malloc(BUFFER_LENGTH);
    if (!b/*err*/) goto fail_malloc_errno;
    
    e = pipe(p1);
    if (e==-1/*err*/) goto fail_pipe_errno;
    e = pipe(p2);
    if (e==-1/*err*/) goto fail_pipe_errno;
    
    pid = fork();
    if (pid==-1/*err*/) goto fail_fork_errno;

    if (pid == 0) {
        dup2(p1[0], 0);
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        execl("/bin/sh", "/bin/sh", NULL);
        exit(1);
    }
    echo_fd=p2[1];
    close(p1[0]); p1[0] = -1;
    close(p2[1]); p2[1] = -1;

    while (ftemplate(stdout, stdin, "<shp>", "</shp>", BUFFER_LENGTH, b)) {
        fflush(stdout);
        e = dprintf(p1[1],
                    "%s\n"
                    "echo >&%i\n",
                    b, echo_fd);
        if (e==-1/*err*/) break;
        e = read(p2[0], b, 1);
        if (e!=1/*err*/) break;
        fflush(stdout);
    }
    close(p1[1]); p1[1] = -1;
    
    e = waitpid(pid, &status, 0);
    if (e==-1/*err*/) goto fail_waitpid_errno;
    pid = -1;

    if (WIFEXITED(status)) {
        exit_code = WEXITSTATUS(status);
    }
    
 cleanup:
    if (pid!=-1) {
        kill(SIGINT, pid);
        waitpid(pid, NULL, 0);
    }
    if (p1[0]!=-1) close(p1[0]);
    if (p1[1]!=-1) close(p1[1]);
    if (p2[0]!=-1) close(p2[0]);
    if (p2[1]!=-1) close(p2[1]);
    free(b);
    return exit_code;
 fail_malloc_errno:
    fprintf(stderr, "shp: malloc: %s", strerror(errno));
    goto cleanup;
 fail_pipe_errno:
    fprintf(stderr, "shp: pipe: %s", strerror(errno));
    goto cleanup;
 fail_fork_errno:
    fprintf(stderr, "shp: fork: %s", strerror(errno));
    goto cleanup;
 fail_waitpid_errno:
    fprintf(stderr, "shp: fork: %s", strerror(errno));
    goto cleanup;
    
}
