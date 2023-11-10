/* gendata.c - generate idna_table
   Copyright (C) 2019 Orivej Desh
   Copyright (C) 2022-2023 Simon Josefsson

   Libidn2 is free software: you can redistribute it and/or modify it
   under the terms of either:

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at
       your option) any later version.

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at
       your option) any later version.

   or both in parallel, as here.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see <http://www.gnu.org/licenses/>.
*/

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char line[1024];
int line_cnt = 0;

static int
next_line (void)
{
  line_cnt++;
  return fgets (line, sizeof line, stdin) != NULL;
}

static void
_ok (const char *fname, int fline, int rc)
{
  if (!rc)
    {
      fprintf (stderr, "%s:%d: unexpected failure at input line %d\n",
	       fname, fline, line_cnt);
      exit (EXIT_FAILURE);
    }
}

#define ok(rc) _ok (__FILE__, __LINE__, ((rc) != 0))

int
main (void)
{
  char *range_end;
  char *property;
  int idna_table_size = 0;
  enum
  { IANA, UTC } table_syntax;

  ok (next_line ());
  if (strstr (line, "Codepoint,Property,") == line)
    table_syntax = IANA;
  else if (strstr (line, "# Idna2008-") == line)
    table_syntax = UTC;
  else
    {
      fprintf (stderr, "gendata: unrecognized input\n");
      exit (EXIT_FAILURE);
    }

  puts ("/* This file is automatically generated.  DO NOT EDIT! */");
  puts ("");
  puts ("#include <config.h>");
  puts ("#include \"data.h\"");
  puts ("");
  puts ("const struct idna_table idna_table[] = {");

  while (next_line ())
    {
      if (table_syntax == IANA)
	{
	  ok (strtok (line, ","));
	  property = strtok (NULL, ",");
	  ok (property);

	  if (!strcmp (property, "UNASSIGNED"))
	    continue;

	  strtok (line, "-");
	  range_end = strtok (NULL, "");
	  if (!range_end)
	    range_end = line;

	  printf ("  {0x%s, 0x%s, %s},\n", line, range_end, property);
	  idna_table_size++;
	}
      else if (table_syntax == UTC)
	{
	  if (line[0] == '#')
	    continue;
	  if (line[0] == '\n')
	    continue;

	  ok (strtok (line, ";"));
	  property = strtok (NULL, "#");
	  ok (property);
	  ok (*property == ' ');
	  property++;

	  if (strstr (property, "UNASSIGNED") == property)
	    continue;

	  strtok (line, ".");
	  range_end = strtok (NULL, "");
	  if (range_end)
	    {
	      ok (*range_end == '.');
	      range_end++;
	    }
	  else
	    range_end = line;

	  strtok (line, " ");
	  strtok (range_end, " ");
	  strtok (property, " ");

	  printf ("  {0x%s, 0x%s, %s},\n", line, range_end, property);
	  idna_table_size++;
	}
    }

  puts ("};");
  printf ("const size_t idna_table_size = %d;\n", idna_table_size);
  return 0;
}
