#include <stdint.h>

typedef struct
{
  uint32_t cp1;
  uint16_t range;
  unsigned nmappings:5,		/* 0-18, # of uint32_t at <offset> */
    offset:14,			/* 0-16383, byte offset into mapdata */
    valid:1,
    mapped:1,
    ignored:1,
    deviation:1,
    disallowed:1,
    disallowed_std3_mapped:1,
    disallowed_std3_valid:1;
} IDNAMap;

typedef struct
{
  uint32_t cp1, cp2;
  char check;			/* 0=NO 2=MAYBE (YES if codepoint has no table entry) */
} NFCQCMap;

IDNAMap *get_idna_map (uint32_t c);
int get_map_data (uint32_t *dst, const IDNAMap *map);

NFCQCMap *get_nfcqc_map (uint32_t c);
