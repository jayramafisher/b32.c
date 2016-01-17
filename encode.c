
/**
 * `encode.c' - b32
 *
 * copyright (c) 2016 jay rama fisher
 * copyright (c) 2014 joseph werle
 */

#include <stdio.h>
#include <stdlib.h>
#include "b32.h"

char *
b32_encode (const unsigned char *src, size_t len) {
  int i = 0;
  int j = 0;
  char *enc = NULL;
  size_t size = 0;
  unsigned char buf[8];
  unsigned char tmp[5];

  // alloc
  enc = (char *) malloc(0);
  if (NULL == enc) { return NULL; }

  // parse until end of source
  while (len--) {
    // read up to 5 bytes at a time into `tmp'
    tmp[i++] = *(src++);

    // if 5 bytes read then encode into `buf'
    if (5 == i) {
      buf[0] = (tmp[0] & 0xf8) >> 3;
      buf[1] = ((tmp[0] & 0x07) << 2) + ((tmp[1] & 0xc0) >> 6);
      buf[2] = ((tmp[1] & 0x3e) >> 1);
      buf[3] = ((tmp[1] & 0x01) << 4) + ((tmp[2] & 0xf0) >> 4);
      buf[4] = ((tmp[2] & 0x0f) << 1) + ((tmp[3] & 0x80) >> 7);
      buf[5] = (tmp[3] & 0x7c) >> 2;
      buf[6] = ((tmp[3] & 0x03) << 3) + ((tmp[4] & 0xe0) >> 5);
      buf[7] = tmp[4] & 0x1f;

      // allocate 8 new bytes for `enc` and
      // then translate each encoded buffer
      // part by index from the base 32 index table
      // into `enc' unsigned char array
      enc = (char *) realloc(enc, size + 8);
      for (i = 0; i < 8; ++i) {
        enc[size++] = b32_table[buf[i]];
      }

      // reset index
      i = 0;
    }
  }

  // remainder
  if (i > 0) {
    // fill `tmp' with `\0' at most 5 times
    for (j = i; j < 5; ++j) {
      tmp[j] = '\0';
    }

    // perform same codec as above
    buf[0] = (tmp[0] & 0xf8) >> 3;
    buf[1] = ((tmp[0] & 0x07) << 2) + ((tmp[1] & 0xc0) >> 6);
    buf[2] = ((tmp[1] & 0x3e) >> 1);
    buf[3] = ((tmp[1] & 0x01) << 4) + ((tmp[2] & 0xf0) >> 4);
    buf[4] = ((tmp[2] & 0x0f) << 1) + ((tmp[3] & 0x80) >> 7);
    buf[5] = (tmp[3] & 0x7c) >> 2;
    buf[6] = ((tmp[3] & 0x03) << 3) + ((tmp[4] & 0xe0) >> 5);
    buf[7] = tmp[4] & 0x1f;

    // perform same write to `enc` with new allocation
    for (j = 0; (j < i*8/5 + 1); ++j) {
      enc = (char *) realloc(enc, size + 1);
      enc[size++] = b32_table[buf[j]];
    }

    // while there is still a remainder
    // append `=' to `enc'
    while ((j++ < 8)) {
      enc = (char *) realloc(enc, size + 1);
      enc[size++] = '=';
    }
  }

  // Make sure we have enough space to add '\0' character at end.
  enc = (char *) realloc(enc, size + 1);
  enc[size] = '\0';

  return enc;
}
