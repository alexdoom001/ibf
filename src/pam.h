/*
 * PAM login helper
 *
 */

#ifndef PAM_H
#define PAM_H

#include <security/pam_appl.h>

int pam_login (const char *group, const char *user, const char *pass);

#endif  /* PAM_H */
