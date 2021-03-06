/*
 *  mutilprocess.cpp 
 *  mutilprocess
 *
 *  Created by Jevstein on 2018/10/29 15:18.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 */

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <error.h>

#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

#define OPTERRCOLON (1)
#define OPTERRNF (2)
#define OPTERRARG (3)
#define DEFAULT_BIN_NAME "brks"

int optreset = 0;
int optind = 1;
int opterr = 1;
int optopt;

#define LOG_DEBUG printf
#define LOG_INFO  printf
#define LOG_NOTICE  printf
#define LOG_WARN  printf
#define LOG_ERROR printf

//extern int errno;

//static int brks_fprintf(FILE *file, const char *fmt, ...)
//{
//	if (file == NULL)
//		return -1;
//
//	va_list args;
//	va_start(args, fmt);
//	int result = ::vfprintf(file, fmt, args);
//	va_end(args);
//
//	return result;
//}
//
//static int optiserr(int argc, char * const *argv, int oint, const char *optstr, int optchr, int err)
//{
//	if (opterr)
//	{
//		brks_fprintf(stderr, "Error in argument %d, char %d: ", oint, optchr + 1);
//		switch (err)
//		{
//		case OPTERRCOLON:
//			brks_fprintf(stderr, ": in flags\n");
//			break;
//		case OPTERRNF:
//			brks_fprintf(stderr, "option not found %c\n", argv[oint][optchr]);
//			break;
//		case OPTERRARG:
//			brks_fprintf(stderr, "no argument for option %c\n", argv[oint][optchr]);
//			break;
//		default:
//			brks_fprintf(stderr, "unknown\n");
//			break;
//		}
//	}
//	optopt = argv[oint][optchr];
//	return('?');
//}
//
//static int getopt(int argc, char* const *argv, const char *optstr)
//{
//	static int optchr = 0;
//	static int dash = 0; /* have already seen the - */
//
//	char *cp;
//
//	if (optreset)
//		optreset = optchr = dash = 0;
//	if (optind >= argc)
//		return(EOF);
//	if (!dash && (argv[optind][0] != '-'))
//		return(EOF);
//	if (!dash && (argv[optind][0] == '-') && !argv[optind][1])
//	{
//		/*
//		* use to specify stdin. Need to let pgm process this and
//		* the following args
//		*/
//		return(EOF);
//	}
//	if ((argv[optind][0] == '-') && (argv[optind][1] == '-'))
//	{
//		/* -- indicates end of args */
//		optind++;
//		return(EOF);
//	}
//	if (!dash)
//	{
//		assert((argv[optind][0] == '-') && argv[optind][1]);
//		dash = 1;
//		optchr = 1;
//	}
//
//	/* Check if the guy tries to do a -: kind of flag */
//	assert(dash);
//	if (argv[optind][optchr] == ':')
//	{
//		dash = 0;
//		optind++;
//		return(optiserr(argc, argv, optind - 1, optstr, optchr, OPTERRCOLON));
//	}
//	if (!(cp = strchr(optstr, argv[optind][optchr])))
//	{
//		int errind = optind;
//		int errchr = optchr;
//
//		if (!argv[optind][optchr + 1])
//		{
//			dash = 0;
//			optind++;
//		}
//		else
//			optchr++;
//		return(optiserr(argc, argv, errind, optstr, errchr, OPTERRNF));
//	}
//	if (cp[1] == ':')
//	{
//		dash = 0;
//		optind++;
//		if (optind == argc)
//			return(optiserr(argc, argv, optind - 1, optstr, optchr, OPTERRARG));
//		optarg = argv[optind++];
//		return(*cp);
//	}
//	else
//	{
//		if (!argv[optind][optchr + 1])
//		{
//			dash = 0;
//			optind++;
//		}
//		else
//			optchr++;
//		return(*cp);
//	}
//	assert(0);
//	return(0);
//}
//
//static int daemon(int nochdir, int noclose)
//{
//	int fd;
//
//	switch (fork())
//	{
//	case -1:
//		return (-1);
//	case 0:
//		break;
//	default:
//		_exit(0);
//	}
//
//	if (setsid() == -1)
//		return (-1);
//
//	if (!nochdir)
//		(void)chdir("/");
//
//	if (!noclose && (fd = open("/dev/null", O_RDWR, 0)) != -1) {
//		(void)dup2(fd, STDIN_FILENO);
//		(void)dup2(fd, STDOUT_FILENO);
//		(void)dup2(fd, STDERR_FILENO);
//		if (fd > 2)
//			(void)close(fd);
//	}
//
//	return (0);
//}

static void usage()
{
	const char* usage_name = DEFAULT_BIN_NAME;
	printf("usage: %s [ -d | -v | -c brks.ini | -l log.conf ]\n", usage_name);
	printf("-d: Run in the foreground\n");
	printf("-c brks.ini: Specify a config file\n");
	printf("-l log.conf: Specify a log config file\n");
}

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		usage();
	}

	char ch;
	bool run_in_foreground = false;
	std::string log_file_path = "";
	std::string config_file_path = "";
	while ((ch = getopt(argc, argv, "vdl:c:")) != EOF)
	{
		switch (ch)
		{
		case 'v':
			usage();
			::exit(0);
			break;
		case 'd':
			run_in_foreground = true;
			break;
		case 'l':
			assert(optarg != NULL);// this means we didn't declare getopt options correctly or there is a bug in getopt.
			log_file_path = std::string(optarg);
			break;
		case 'c':
			assert(optarg != NULL);// this means we didn't declare getopt options correctly or there is a bug in getopt.
			config_file_path = std::string(optarg);
			break;
		default:
			break;
		}
	}

	if (!run_in_foreground)
	{
		if (0 != daemon(0, 0))
		{
			//LOG_ERROR("run in daemon failed with error %s", strerror(errno));
			exit(-1);
		}
	}

	//fork multi process
	pid_t processid = 0;
	for (int i = 0; i < 4; i++)
	{
		processid = 0;
		processid = fork();
		if (processid < 0)
		{
			LOG_ERROR("fork child task failed.");
			break;
		}
		else if (processid == 0)  // this is child task
		{
			break;
		}
	}

	if (processid > 0) // this is parent process
	{
		LOG_INFO("parent id is %d", getpid());
		LOG_INFO("brks start successful!");

		// if child process exit with -1 then exit parent process.
		// if child process exit with not -1 then restart child process
		int status = 0;
		while (status == 0)
		{
			pid_t pid = wait(&status);  // parent process block here.
			int exitStatus = WEXITSTATUS(status);
			LOG_INFO("parent process wait return with: pid=%d, status=%d, exitStatus=%d.", pid, status, exitStatus);

			if ((WIFEXITED(status) != 0) && (pid > 0))
			{
				if (exitStatus == -1)
				{
					LOG_ERROR("child process %d cannot normal start so parent should be exit too.", pid);
					exit(-1);
				}
				else
				{
					processid = fork();  // restart an child process.
					if (processid == 0) break;  // break while.
				}
			}

			if (WIFSIGNALED(status)) // child exited on an unhandled signal (maybe a bus error or seg fault)
			{
				processid = fork();  // restart an child process.
				if (processid == 0) break;  // break while.
			}
		}
	}

	if (processid == 0)
	{
		LOG_INFO("this is child process pid=%d", getpid());
		//if (!intf.start(server_socket))
		//{
		//	LOG_ERROR("cannot start child process!");
		//	exit(-1); // if cannot start child process donnot restart server.
		//}
		//LOG_ERROR("child process exit");
	}

	for (;;)
		sleep(1);

	return 0;
}

//compile:
// $ g++ -o ../../bin/mutilprocess mutilprocess.cpp