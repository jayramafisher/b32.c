
/**
 * `decode.c' - b32
 *
 * copyright (c) 2016 jay rama fisher
 * copyright (c) 2014 joseph werle
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "b32.h"


unsigned char *
b32_decode (const char *src, size_t len) {
  return b32_decode_ex(src, len, NULL);
}

unsigned char *
b32_decode_ex (const char *src, size_t len, size_t *decsize) {
  int i = 0;
  int j = 0;
  int l = 0;
  size_t size = 0;
  unsigned char *dec = NULL;
  unsigned char buf[5];
  unsigned char tmp[8];

  // alloc
  dec = (unsigned char *) malloc(0);
  if (NULL == dec) { return NULL; }

  // parse until end of source
  while (len--) {
    // break if char is `=' or not base32 char
    if ('=' == src[j]) { break; }
    if (!(isalnum(src[j]) || '+' == src[j] || '/' == src[j])) { break; }

    // read up to 8 bytes at a time into `tmp'
    tmp[i++] = src[j++];

    // if 8 bytes read then decode into `buf'
    if (8 == i) {
      // translate values in `tmp' from table
      for (i = 0; i < 8; ++i) {
        // find translation char in `b32_table'
        for (l = 0; l < 32; ++l) {
          if (tmp[i] == b32_table[l]) {
            tmp[i] = l;
            break;
          }
        }
      }

      // decode
      buf[0] = (tmp[0] << 3) + ((tmp[1] & 0x1c) >> 2);
      buf[1] = ((tmp[1] & 0x03) << 6) + (tmp[2] << 1) + ((tmp[3] & 0x10) >> 4);
      buf[2] = ((tmp[3] & 0x0f) << 4) + ((tmp[4] & 0x1e) >> 1);
      buf[3] = ((tmp[4] & 0x01) << 7) + (tmp[5] << 2) + ((tmp[6] & 0x18) >> 3);
      buf[4] = ((tmp[6] & 0x07) << 5) + tmp[7];

      // write decoded buffer to `dec'
      dec = (unsigned char *) realloc(dec, size + 5);
      for (i = 0; i < 5; ++i) {
        dec[size++] = buf[i];
      }

      // reset
      i = 0;
    }
  }

  // remainder
  if (i > 0) {
    // fill `tmp' with `\0' at most 8 times
    for (j = i; j < 8; ++j) {
      tmp[j] = '\0';
    }

    // translate remainder
    for (j = 0; j < 8; ++j) {
        // find translation char in `b32_table'
        for (l = 0; l < 32; ++l) {
          if (tmp[j] == b32_table[l]) {
            tmp[j] = l;
            break;
          }
        }
    }

    // decode remainder
    buf[0] = (tmp[0] << 3) + ((tmp[1] & 0x1c) >> 2);
    buf[1] = ((tmp[1] & 0x03) << 6) + (tmp[2] << 1) + ((tmp[3] & 0x10) >> 4);
    buf[2] = ((tmp[3] & 0x0f) << 4) + ((tmp[4] & 0x1e) >> 1);
    buf[3] = ((tmp[4] & 0x01) << 7) + (tmp[5] << 2) + ((tmp[6] & 0x18) >> 3);
    buf[4] = ((tmp[6] & 0x07) << 5) + tmp[7];

    // write remainder decoded buffer to `dec'
    dec = (unsigned char *) realloc(dec, size + i*5/8);
    for (j = 0; (j < i*5/8); ++j) {
      dec[size++] = buf[j];
    }
  }

  // Make sure we have enough space to add '\0' character at end.
  dec = (unsigned char *) realloc(dec, size + 1);
  dec[size] = '\0';

  // Return back the size of decoded string if demanded.
  if (decsize != NULL) *decsize = size;

  return dec;
}
