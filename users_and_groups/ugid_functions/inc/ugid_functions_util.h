// header file
#ifndef _GUARD_UGID_FUNCTIONS_UTIL_H_
#define _GUARD_UGID_FUNCTIONS_UTIL_H_

#include <tlpi/tlpi_hdr.h>

char* userNameFromId(uid_t uid);

uid_t userIdFromName(const char* name);

char* groupNameFromId(gid_t gid);

gid_t groupIdFromName(const char* name);

#endif