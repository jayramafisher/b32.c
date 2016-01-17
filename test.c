
/**
 * `test.c' - b32
 *
 * copyright (c) 2016 jay rama fisher
 * copyright (c) 2014 joseph werle
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ok/ok.h>

#include "b32.h"

#define S(x) # x
#define t(m, a, b) ({                                                \
    char tmp[1024];                                                  \
    sprintf(tmp, "%s(%s) = %s", S(m), S(a), S(b));                   \
    char *r = (char *) m(a, strlen((char *) a));                     \
    assert(0 == strcmp(b, r));                                       \
    free(r);                                                         \
    ok(tmp);                                                         \
})

int
main (void) {

  // encode
  {
    t(b32_encode, (const unsigned char *) "bradley", "MJZGCZDMMV4Q====");
    t(b32_encode, (const unsigned char *) "kinkajou", "NNUW423BNJXXK===");
    t(b32_encode, (const unsigned char *) "vino", "OZUW43Y=");
    t(b32_encode,
        (const unsigned char *) "brian the monkey and bradley the kinkajou are friends",
        "MJZGSYLOEB2GQZJANVXW423FPEQGC3TEEBRHEYLENRSXSIDUNBSSA23JNZVWC2TPOUQGC4TFEBTHE2LFNZSHG===");
  }

  // decode
  {
    t(b32_decode, "MNQXG2LMNRSXE3Y=", "casillero");
    t(b32_decode, "NBQXQ===", "hax");
    t(b32_decode, "NVXW423FPFZSAYLOMQQGI33HOM======", "monkeys and dogs");
    t(b32_decode,
        "ORUGKIDLNFXGWYLKN52SAYLOMQQG233ONNSXSIDGN52WO2DUEBXXMZLSEB2GQZJAMJQW4YLOME",
        "the kinkajou and monkey fought over the banana");
  }

  ok_done();
  return 0;
}
