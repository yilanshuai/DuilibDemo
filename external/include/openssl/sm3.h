/*  */

#ifndef OPENSSL_HEADER_SM3_H
#define OPENSSL_HEADER_SM3_H

#include <openssl/base.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct {
	unsigned int total[2];
	unsigned int state[8];
	unsigned char buffer[64];
} SM3_CTX;

/* SM3-256. */

/* SM3256_CBLOCK is the block size of SHA-256. */
#define SM3_CBLOCK 64

/* SM3_DIGEST_LENGTH is the length of a SHA-256 digest. */
#define SM3_DIGEST_LENGTH 32

/* SM3_Init initialises |sha| and returns 1. */
OPENSSL_EXPORT int SM3_Init(SM3_CTX *sha);

/* SM3_Update adds |len| bytes from |data| to |sha| and returns 1. */
OPENSSL_EXPORT int SM3_Update(SM3_CTX *sha, const void *data, size_t len);

/* SM3_Final adds the final padding to |sha| and writes the resulting digest
 * to |md|, which must have at least |SM3_DIGEST_LENGTH| bytes of space. It
 * returns one on success and zero on programmer error. */
OPENSSL_EXPORT int SM3_Final(uint8_t *md, SM3_CTX *sha);

/* SM3 writes the digest of |len| bytes from |data| to |out| and returns
 * |out|. There must be at least |SM3_DIGEST_LENGTH| bytes of space in
 * |out|. */
OPENSSL_EXPORT uint8_t *SM3(const uint8_t *data, size_t len, uint8_t *out);

/* SM3_Transform is a low-level function that performs a single, SHA-1 block
 * transformation using the state from |sha| and 64 bytes from |block|. */
OPENSSL_EXPORT void SM3_Transform(SM3_CTX *sha, const uint8_t *data);

OPENSSL_EXPORT int SM3_EndRaw(SM3_CTX *ctx, uint8_t *md);

OPENSSL_EXPORT void SM3_Transform(SM3_CTX *sm3, const uint8_t *data);

#if defined(__cplusplus)
}  /* extern C */
#endif

#endif  /* OPENSSL_HEADER_SM3_H */
