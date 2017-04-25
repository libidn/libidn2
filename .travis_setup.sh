#!/bin/bash

if [[ "$TRAVIS_OS_NAME" = "osx" ]]; then
	brew update
	brew outdated autoconf || brew upgrade autoconf
	brew outdated automake || brew upgrade automake
	brew outdated libtool || brew upgrade libtool
	brew install gengetopt
	brew install gperf
	brew install gettext
	brew link --force gettext
fi
