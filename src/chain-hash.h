/*
 * Vyatta Chain Hash
 *
 */

#ifndef CHAIN_HASH_H
#define CHAIN_HASH_H  1

void init_chain_hash (void);

/*
 * NOTE: Hash buffer size MUST equal 28.
 */
int get_chain_hash (const char *scope, const char *name, const char *type,
		    char *hash);

#endif  /* CHAIN_HASH_H */
