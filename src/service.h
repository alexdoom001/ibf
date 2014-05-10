/*
 * Service helper
 *
 */

#ifndef SERVICE_H
#define SERVICE_H

int service_start (const char *fmt, ...);
int service_stop (const char *pidfile, unsigned timeout);

#endif  /* SERVICE_H */
