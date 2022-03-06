#!/usr/bin/perl

# Copyright (C) 2011-2022 Simon Josefsson

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

my ($str, $escstr);

while (<>) {
    next if !m,/domains/root/db/(xn--.*).html">(.*)</a></td>,;

    $str = unpack("H*", $2);

    die "no dot?!" if (substr($str,0,2) != "2e");

    $str = substr($str,2);
    printf "// str $str\n";
    $escstr = "";
    while ($str) {
	$escstr .= "\\x" . substr ($str,0,2);
	$str = substr ($str,2);
    }

    printf "  {\"$escstr\", \"$1\" },\n";
}
