#!/usr/bin/perl

# Copyright (C) 2011 Simon Josefsson

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# I consider the output of this program to be unrestricted.  Use it as
# you will.

use strict;

my ($last);
my ($ctr) = 0;

while (<>) {
    next unless /^[BN]/;

    m,^.*;	(.*);	(.*);	(.*);	(NV8)?,;

    next if /\uD/;
    next if /123456789/;

    my ($source) = $1;
    my ($ustr) = $2;
    my ($astr) = $3;
    my ($nv8) = $4;

    $ustr = $source if ($ustr eq "");
    $astr = $ustr if ($astr eq "");

    next if ($ustr eq $last);

    print "/* $ctr source $source uni $ustr ace $astr nv8 $nv8 line $_ */\n";

    if ($ctr == 116) {
	print "/* punt2 */\n";
    } elsif ($nv8 eq "NV8") {
	if ($ctr == 103 || $ctr == 93 || $ctr == 99) {
	    print "{ \"$ustr\", \"$astr\", IDN2_UNASSIGNED },\n";
	} else {
	    print "{ \"$ustr\", \"$astr\", IDN2_DISALLOWED },\n";
	}
	$ctr++;
    } elsif (substr($astr, 0, 1) eq "[") {
	print "/* punt1 */\n";
    } else {
	print "{ \"$ustr\", \"$astr\", IDN2_OK },\n";
	$ctr++;
    }

    $last = $ustr;
}
