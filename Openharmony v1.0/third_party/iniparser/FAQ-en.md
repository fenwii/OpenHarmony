# iniparser FAQ #

## Is iniparser thread safe ?

Starting from version 4, iniparser is designed to be thread-safe, provided
you surround it with your own mutex logic. The choice to not add thread
safety inside the library has been made to provide more freedom for the
developer, especially when dealing with their own custom reading logic
e.g. acquiring the mutex, reading entries with iniparser, then releasing
the mutex.

## Your build system isn't portable, let me help you...

We have received countless contributions from distrib people to modify the
Makefile into what they think is the "standard", which we had to reject.
The default, standard Makefile for Debian bears absolutely no relationship
with the one from SuSE or RedHat and there is no possible way to merge them
all. A build system is something so specific to each environment that it
is completely pointless to try and push anything that claims to be
standard. The provided Makefile in this project is purely here to have
something to play with quickly.

## iniparser_dump() is slow

The dumping functions are based on fprintf, which can turn out to be
surprisingly slow on some embedded platforms. You can replace fprintf by a
combined use of sprintf and fwrite, or you can use setvbuf() to change
buffering parameters to accomodate fprintf(). Something like:

setvbuf(f, NULL, _IOFBF, 0);

## iniparser does not compile with my C++ compiler!

See the docs: iniparser is a C library. C++ is quite a different language,
despite the promises of compatibility. You will have to modify iniparser
quite heavily to make it work with a C++ compiler. Good luck!

