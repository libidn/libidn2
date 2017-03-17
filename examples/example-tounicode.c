/* example-tounicode.c --- Example ToUnicode() code showing how to use Libidn2.
 *
 * This code is placed under public domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <idna.h>		/* idn2_to_unicode_8z8z() */

/*
 * Compiling using pkg-config is recommended:
 *
 * $ cc -o example-to-unicode example-to-unicode.c `pkg-config --cflags --libs libidn2`
 * $ ./example-tounicode
 * Input domain (ACE) encoded as `UTF-8': xn--nxasmm1c.com
 * Output string (length 15): ce b2 cf 8c ce bb ce bf cf 82 2e 63 6f 6d 0a
 *
 */

int
main (void)
{
  char buf[BUFSIZ];
  char *p;
  int rc;
  size_t i;

  if (!fgets (buf, BUFSIZ, stdin))
    perror ("fgets");
  buf[strlen (buf) - 1] = '\0';

  printf ("Read string (length %ld): ", (long int) strlen (buf));
  for (i = 0; i < strlen (buf); i++)
    printf ("%02x ", (unsigned) buf[i] & 0xFF);
  printf ("\n");

  rc = idn2_to_unicode_8z8z (buf, &p, 0);
  if (rc != IDNA_SUCCESS)
    {
      printf ("ToUnicode() failed (%d): %s\n", rc, idn2_strerror (rc));
      return EXIT_FAILURE;
    }

  printf ("ACE label (length %ld): '%s'\n", (long int) strlen (p), p);
  for (i = 0; i < strlen (p); i++)
    printf ("%02x ", (unsigned) p[i] & 0xFF);
  printf ("\n");

  free (p); /* or idn2_free() */

  return 0;
}
