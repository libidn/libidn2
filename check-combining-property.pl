#!/usr/bin/perl -w

# Copyright (C) 2011-2017 Simon Josefsson

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

while (<>) {
    if (m:([0-9A-F]+);[-0-9<>,a-zA-Z ]+;([A-Z])([a-z]);([0-9]+);:) {
	$cp = $1;
	$gc1 = $2;
	$gc2 = $3;
	$gc = $gc1 . $gc2;
	$ccc = $4;
	# Code points with combining class of 0 and non-Mc/Mn category
	die "cp $cp gc $gc ccc $ccc line $_"
	    if ($ccc ne "0" && $gc ne "Mc" && $gc ne "Mn");
	# Code points with non-M category and non-0 combining class
	#print "cp $cp gc $gc ccc $ccc line $_"
	#    if ($ccc eq "0" && $gc1 eq "M");
    } else {
	die "regexp failed on line: -->$_<--";
    }
}
