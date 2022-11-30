// c file for "ugid_functions_util.h"

#include "../inc/ugid_functions_util.h"

#include <pwd.h>
#include <grp.h>
#include <ctype.h>

char* userNameFromId(uid_t uid) {
	struct passwd *pwd;

	pwd = getpwuid(uid);
	return (NULL == pwd) ? NULL : pwd->pw_name;
}

uid_t userIdFromName(const char* name) {
	struct passwd *pwd;
	if(NULL == name || *name == '\0') return -1;

	char* endptr = NULL;
	uid_t u = strtol(name, &endptr, 10);
	if('\0' == *endptr) return u;  // that means you passed a number as string

	pwd = getpwnam(name);
	if(NULL == pwd) return -1;

	return pwd->pw_uid;
}

char* groupNameFromId(gid_t gid) {
	struct group *grp;

	grp = getgrgid(gid);
	return (NULL == grp) ? NULL : grp->gr_name;
}

gid_t groupIdFromName(const char* name) {
	struct group* grp;

	char* endptr = NULL;
	if(NULL == name || '\0' == *name) return -1;

	gid_t g = strtol(name, &endptr, 10);
	if('\0' == *endptr) return g;

	grp = getgrnam(name);
	if(NULL == grp) return -1;

	return grp->gr_gid;
}