/**
 * 来自: https://blog.csdn.net/micx0124/article/details/12746143
 * 
 * 传递文件描述符: parrent向child发送fd，child收到fd后，写入log：“-- Tony Bai”
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
 
#include <sys/socket.h> /* for socketpair */
 
#define MY_LOGO     "-- Tony Bai\r\n"

#define NGX_HAVE_MSGHDR_MSG_CONTROL 1
 
static int send_fd(int fd, int fd_to_send)
{
    struct iovec iov[1];
    struct msghdr msg;
    char    buf[1];

#if (NGX_HAVE_MSGHDR_MSG_CONTROL)
    union {
        struct cmsghdr cm;
        char space[CMSG_SPACE(sizeof(int))];
    } cmsg;

    msg.msg_control = (caddr_t) &cmsg;
    msg.msg_controllen = sizeof(cmsg);

    memset(&cmsg, 0, sizeof(cmsg));

    cmsg.cm.cmsg_len = CMSG_LEN(sizeof(int));
    cmsg.cm.cmsg_level = SOL_SOCKET;
    cmsg.cm.cmsg_type = SCM_RIGHTS;
    memcpy(CMSG_DATA(&cmsg.cm), &fd_to_send, sizeof(int));

    msg.msg_flags = 0;
#else//旧的API
    if (fd_to_send >= 0) {
        msg.msg_accrights = (caddr_t)&fd_to_send;
        msg.msg_accrightslen = sizeof(int);
    } else {
        msg.msg_accrights = (caddr_t)NULL;
        msg.msg_accrightslen = 0;
    }
#endif
 
    msg.msg_name    = NULL;
    msg.msg_namelen = 0;
 
    iov[0].iov_base = buf;
    iov[0].iov_len  = 1;
    msg.msg_iov     = iov;
    msg.msg_iovlen  = 1;
 
    if(sendmsg(fd, &msg, 0) < 0) {
        printf("sendmsg error, errno is %d\n", errno);
        return errno;
    }
 
    return 0;
}
 
static int recv_fd(int fd, int *fd_to_recv)
{
    struct iovec    iov[1];
    struct msghdr   msg;
    char    buf[1];
 
#if (NGX_HAVE_MSGHDR_MSG_CONTROL)
    union {
        struct cmsghdr  cm;
        char            space[CMSG_SPACE(sizeof(int))];
    } cmsg;

    msg.msg_control = (caddr_t) &cmsg;
    msg.msg_controllen = sizeof(cmsg);
#else//旧的API
    msg.msg_accrights = (caddr_t)fd_to_recv;
    msg.msg_accrightslen = sizeof(int);
#endif

    msg.msg_name    = NULL;
    msg.msg_namelen = 0;
 
    iov[0].iov_base = buf;
    iov[0].iov_len  = 1;
    msg.msg_iov     = iov;
    msg.msg_iovlen  = 1;
 
    if (recvmsg(fd, &msg, 0) < 0) {
        return errno;
    }
 
#if (NGX_HAVE_MSGHDR_MSG_CONTROL)
    memcpy(fd_to_recv, CMSG_DATA(&cmsg.cm), sizeof(int));
#else//旧的API
    if(msg.msg_accrightslen != sizeof(int)) {
        *fd_to_recv = -1;
    }
#endif
 
    return 0;
}
 
int x_sock_set_block(int sock, int on)
{
    int val;
    int rv;
 
    val = fcntl(sock, F_GETFL, 0);
    if (on) {
        rv = fcntl(sock, F_SETFL, ~O_NONBLOCK&val);
    } else {
        rv = fcntl(sock, F_SETFL, O_NONBLOCK|val);
    }
 
    if (rv)
        return errno;
 
    return 0;
}
 
int main()
{
    pid_t   pid;
    int     sockpair[2];
    int     rv;
    char    fname[256];
    int     fd;

    rv = socketpair(AF_UNIX, SOCK_STREAM, 0, sockpair);
    if (rv < 0) {
        printf("Call socketpair error, errno is %d\n", errno);
        return errno;
    }

    pid = fork();
    if (pid == 0) {/* in child */
        close(sockpair[1]);

        for ( ; ; ) {
            rv = x_sock_set_block(sockpair[0], 1);
            if (rv != 0) {
                printf("[CHILD]: x_sock_set_block error, errno is %d\n", rv);
                break;
            }

            rv = recv_fd(sockpair[0], &fd);
            if (rv < 0) {
                printf("[CHILD]: recv_fd error, errno is %d\n", rv);
                break;
            }

            if (fd < 0) {
                printf("[CHILD]: child process exit normally!\n");
                break;
            }

            /* 处理fd描述符对应的文件 */
            rv = write(fd, MY_LOGO, strlen(MY_LOGO));
            if (rv < 0) {
                printf("[CHILD]: write error, errno is %d\n", rv);
            } else {
                printf("[CHILD]: append logo successfully\n");
            }
            close(fd);
        }

        exit(0);
    } else {/* in parent */
        for ( ; ; ) {
            memset(fname, 0, sizeof(fname));
            printf("[PARENT]: please enter filename:\n");
            scanf("%s", fname);

            if (strcmp(fname, "exit") == 0) {
                rv = send_fd(sockpair[1], -1);
                if (rv < 0) {
                    printf("[PARENT]: send_fd error, errno is %d\n", rv);
                }
                break;
            }

            fd = open(fname, O_RDWR | O_APPEND | O_CREAT, 0777);
            if (fd < 0) {
                if (errno == ENOENT) {
                    printf("[PARENT]: can't find file '%s'\n", fname);
                    continue;
                }
                printf("[PARENT]: open file error, errno is %d\n", errno);
            }

            rv = send_fd(sockpair[1], fd);
            if (rv != 0) {
                printf("[PARENT]: send_fd error, errno is %d\n", rv);
            }

            close(fd);
        }

        wait(NULL);
    }

    return 0;
}
