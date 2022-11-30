// main file

#define _BSD_SOURCE  // get getpass() declaration from unistd.h
#define _XOPEN_SOURCE  // get crypt() declaration from unistd.h

#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>

#include <tlpi/tlpi_hdr.h>

int main(int argc, char **argv) {
	long lnmax = sysconf(_SC_LOGIN_NAME_MAX);
	if(-1 == lnmax) lnmax = 256;  // if limit is intermediate make a guess

	char* username = malloc(lnmax);
	if(NULL == username) errExit("malloc");

	printf("Username: ");
	fflush(stdout);
	if(NULL == fgets(username, lnmax, stdin)) exit(EXIT_FAILURE);

	size_t len = strlen(username);
	if('\n' == username[len - 1]) username[len - 1] = '\0';  // remove trailing '\n'

	struct passwd* pwd = getpwnam(username);
	if(NULL == pwd) fatal("couldn't get password record");

	struct spwd* spwd = getspnam(username);
	if(NULL == spwd && EACCES == errno) fatal("no permission to read shadow password file");

	// if there is a shadow password record, Use the shadow password
	if(NULL != spwd) pwd->pw_passwd = spwd->sp_pwdp;  // I'm not seeing any significance of doing this

	char* password = getpass("Password: ");


	// encrypt password and erase cleartext version immediately
	const char* const encrypted = crypt(password, pwd->pw_passwd);

	for(char* p = password; *p != '\0';) *p++ = '\0';

	if(NULL == encrypted) errExit("crypt");

	Boolean authOk = strcmp(encrypted, pwd->pw_passwd) == 0;
	if(!authOk) {
		printf("Incorrect password\n");
		exit(EXIT_FAILURE);
	}

	printf("Successfully authenticated: UID=%d\n", pwd->pw_uid);


	// doing authenticated word

	exit(EXIT_SUCCESS);
}