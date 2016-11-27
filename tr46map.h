#include <stdint.h>

typedef struct
{
  uint32_t
    cp1, cp2;
  unsigned
    nmappings : 5, /* 0-18, # of uint32_t at <offset> */
    offset : 13, /* 0-8191, offset into mapdata */
    valid : 1,
    mapped : 1,
    ignored : 1,
    deviation : 1,
    disallowed : 1,
    disallowed_std3_mapped : 1,
    disallowed_std3_valid : 1,
    transitional : 1,
    nontransitional : 1;
} IDNAMap;

typedef struct
{
  uint32_t
    cp1, cp2;
  char
    check; /* 0=NO 2=MAYBE (YES if codepoint has no table entry) */
} NFCQCMap;

IDNAMap *_get_map(uint32_t c);
NFCQCMap *_get_nfcqc_map(uint32_t c);

extern uint32_t mapdata[];
