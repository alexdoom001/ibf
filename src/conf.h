/*
 * Configuration Interface
 *
 */

#ifndef CONF_H
#define CONF_H

#include <stddef.h>

struct conf *conf_alloc (const char *root);
void conf_free (struct conf *o);

struct conf *conf_clone (struct conf *o, ...);

int conf_get (struct conf *o, char *buf, size_t size);
int conf_rewind (struct conf *o);

#endif  /* CONF_H */
