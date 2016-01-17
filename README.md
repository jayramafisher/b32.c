b32.c
=====

Base32 encode/decode

## install

```sh
$ clib install jayramafisher/b32.c
```

## usage

```c
#include <b32/b32.h>
```

or

```c
#include <b32.h>
```

```c

#include <stdio.h>
#include <string.h>
#include "b32.h"

int
main (void) {
  unsigned char *str = "brian the monkey and bradley the kinkajou are friends";
  char *enc = b32_encode(str, strlen(str));

  printf("%s\n", enc); // MJZGSYLOEB2GQZJANVXW423FPEQGC3TEEBRHEYLENRSXSIDUNBSSA23JNZVWC2TPOUQGC4TFEBTHE2LFNZSHG===

  char *dec = b32_decode(enc, strlen(enc));

  printf("%s\n", dec); // brian the monkey and bradley the kinkajou are friends
  return 0;
}
```

## api

Base32 index table

```c

static const char b32_table[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
  'Y', 'Z', '2', '3', '4', '5', '6', '7'
};
```

Encode `unsigned char *` source with `size_t` size.
Returns a `char *` base32 encoded string

```c
char *
b32_encode (const unsigned char *, size_t);
```

Dencode `char *` source with `size_t` size.
Returns a `unsigned char *` base32 decoded string

```c
unsigned char *
b32_decode (const char *, size_t);
```

## license

MIT
