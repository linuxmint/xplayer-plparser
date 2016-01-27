noinst_LTLIBRARIES =					\
	libxplayer_glibc.la

common_defines = \
	-DGNOMELOCALEDIR=\""$(datadir)/locale"\"	\
	-DDATADIR=\""$(datadir)"\"			\
	$(DISABLE_DEPRECATED)

noinst_HEADERS = xplayer_internal.h

libxplayer_glibc_la_SOURCES = stub.c
libxplayer_glibc_la_LIBADD = @LTLIBOBJS@

EXTRA_DIST = asprintf.c

-include $(top_srcdir)/git.mk
