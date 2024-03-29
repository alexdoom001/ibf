/*
 * FastCGI wrappers and helpers
 *
 */

#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "cgi.h"

int cgi_puts_escaped (const char *s, cgi_req *o)
{
	int ret, n;

	for (; *s != '\0'; ++s)
		switch (*s) {
		case '"':
			if ((ret = FCGX_PutS ("&quot;", o->out)) < 0)
				return -1;

			n += 6;
			break;
		case '&':
			if ((ret = FCGX_PutS ("&amp;", o->out)) < 0)
				return -1;

			n += 5;
			break;
		case '<':
			if ((ret = FCGX_PutS ("&lt;", o->out)) < 0)
				return -1;

			n += 4;
			break;
		case '>':
			if ((ret = FCGX_PutS ("&gt;", o->out)) < 0)
				return -1;

			n += 4;
			break;
		default:
			if ((ret = FCGX_PutChar (*s, o->out)) < 0)
				return -1;

			++n;
			break;
		}

	return n;
}

char *cgi_uri_escape (const char *s)
{
	return s == NULL ? NULL : g_uri_escape_string (s, NULL, FALSE);
}

char **cgi_parse_vars (const char *query)
{
	char **list = g_strsplit (query, "&", 0);
	size_t i;
	char *p;

	for (i = 0; list[i] != NULL; ++i) {
		p = g_uri_unescape_string (list[i], NULL);
		g_free (list[i]);
		list[i] = p;
	}

	return list;
}

void cgi_free_vars (char **list)
{
	g_strfreev (list);
}

const char *cgi_getvar (char **list, const char *name)
{
	if (list == NULL)
		return NULL;

	return FCGX_GetParam (name, list);
}

char **cgi_load_vars (cgi_req *o, char *buf, size_t size)
{
	const char *method;
	const char *p;
	int len;

	if ((method = FCGX_GetParam ("REQUEST_METHOD", o->envp)) == NULL)
		return NULL;

	if (strcmp (method, "GET") == 0) {
		if ((p = FCGX_GetParam ("QUERY_STRING", o->envp)) == NULL)
			return NULL;

		return cgi_parse_vars (p);
	}

	if (strcmp (method, "POST") != 0 ||
	    (p = FCGX_GetParam ("CONTENT_LENGTH", o->envp)) == NULL ||
	    (len = atoi (p)) <= 0 || (len + 1) > size ||
	    cgi_read (buf, len, o) != len)
		return NULL;

	buf[len] = '\0';
	return cgi_parse_vars (buf);
}
