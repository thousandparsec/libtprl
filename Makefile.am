SUBDIRS = tprl test

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libtprl.pc 

EXTRA_DIST = base.dox Doxyfile autogen.sh

doc: Doxyfile
	doxygen Doxyfile
