SUBDIRS = . tests
DIST_SUBDIRS = tests

lib_LTLIBRARIES = libxplayer-plparser.la libxplayer-plparser-mini.la

BUILTINFILES = xplayer-pl-parser-builtins.c xplayer-pl-parser-builtins.h
MARSHALFILES = xplayerplparser-marshal.c xplayerplparser-marshal.h

BUILT_SOURCES = $(MARSHALFILES) \
		$(BUILTINFILES)

xplayerplparser-marshal.c: xplayerplparser-marshal.list
	 $(AM_V_GEN) $(GLIB_GENMARSHAL) --prefix=_xplayerplparser_marshal --header --body --internal $< > $@

xplayerplparser-marshal.h: xplayerplparser-marshal.list
	$(AM_V_GEN) $(GLIB_GENMARSHAL) --prefix=_xplayerplparser_marshal --header --internal $< > $@

plparserincludedir = $(pkgincludedir)/1/plparser
nodist_plparserinclude_HEADERS = xplayer-pl-parser-builtins.h
plparserinclude_HEADERS =			\
	xplayer-pl-parser-features.h		\
	xplayer-pl-parser.h			\
	xplayer-pl-playlist.h			\
	xplayer-pl-parser-mini.h

plparser_sources =				\
	xplayer-disc.c				\
	xplayer-pl-parser.c			\
	xplayer-pl-parser-amz.c			\
	xplayer-pl-parser-lines.c			\
	xplayer-pl-parser-media.c			\
	xplayer-pl-parser-misc.c			\
	xplayer-pl-parser-pla.c			\
	xplayer-pl-parser-pls.c			\
	xplayer-pl-parser-podcast.c		\
	xplayer-pl-parser-qt.c			\
	xplayer-pl-parser-smil.c			\
	xplayer-pl-parser-videosite.c		\
	xplayer-pl-parser-wm.c			\
	xplayer-pl-parser-xspf.c			\
	xplayer-pl-playlist.c

nodist_libxplayer_plparser_la_SOURCES = \
	$(MARSHALFILES)				\
	$(BUILTINFILES)

dist_libxplayer_plparser_la_SOURCES =		\
	$(plparser_sources)			\
	xplayer-disc.h				\
	xplayer-pl-parser-features.h		\
	xplayer-pl-parser.h			\
	xplayer-pl-parser-lines.h			\
	xplayer-pl-parser-media.h			\
	xplayer-pl-parser-misc.h			\
	xplayer-pl-parser-pla.h			\
	xplayer-pl-parser-pls.h			\
	xplayer-pl-parser-podcast.h		\
	xplayer-pl-parser-private.h		\
	xplayer-pl-parser-qt.h			\
	xplayer-pl-parser-smil.h			\
	xplayer-pl-parser-videosite.h		\
	xplayer-pl-parser-wm.h			\
	xplayer-pl-parser-xspf.h			\
	xplayer-pl-playlist.h			\
	xplayer-pl-parser-amz.h			\
	xmlparser.h xmlparser.c			\
	xmllexer.h xmllexer.c			\
	bswap.h

libxplayer_plparser_la_CPPFLAGS = \
	-I$(top_srcdir)				\
	-I$(top_srcdir)/lib			\
	-I$(top_builddir)/plparse		\
	-DGNOMELOCALEDIR=\""$(datadir)/locale"\"\
	-DLIBEXECDIR=\""$(libexecdir)"\"	\
	$(DISABLE_DEPRECATED)			\
	$(AM_CPPFLAGS)

libxplayer_plparser_la_CFLAGS = \
	$(XPLAYER_PLPARSER_CFLAGS)	\
	$(ARCHIVE_CFLAGS)		\
	$(LIBGCRYPT_CFLAGS)		\
	$(DBUS_CFLAGS)			\
	$(WARN_CFLAGS)			\
	$(CODE_COVERAGE_CFLAGS)		\
	$(AM_CFLAGS)			\
	-D_FILE_OFFSET_BITS=64		\
	-D_LARGEFILE64_SOURCE		\
	-I$(top_srcdir)/lib		\
	-D_GNU_SOURCE

libxplayer_plparser_la_LIBADD = \
	$(XPLAYER_PLPARSER_LIBS)			\
	$(ARCHIVE_LIBS)				\
	$(LIBGCRYPT_LIBS)			\
	$(top_builddir)/lib/libxplayer_glibc.la

libxplayer_plparser_la_LDFLAGS =			\
	-version-info $(PLPARSER_LT_VERSION)	\
	-export-symbols $(srcdir)/plparser.symbols \
	-no-undefined				\
	$(CODE_COVERAGE_LDFLAGS)		\
	$(AM_LDFLAGS)

libxplayer_plparser_mini_la_SOURCES =		\
	xplayer-pl-parser-mini.h			\
	xplayer-pl-parser.c			\
	xplayer-pl-parser-lines.c			\
	xplayer-pl-parser-lines.h			\
	xplayer-pl-parser-misc.c			\
	xplayer-pl-parser-misc.h			\
	xplayer-pl-parser-pls.c			\
	xplayer-pl-parser-pls.h			\
	xplayer-pl-parser-podcast.c		\
	xplayer-pl-parser-podcast.h		\
	xplayer-pl-parser-private.h		\
	xplayer-pl-parser-qt.c			\
	xplayer-pl-parser-qt.h			\
	xplayer-pl-parser-smil.c			\
	xplayer-pl-parser-smil.h			\
	xplayer-pl-parser-videosite.c		\
	xplayer-pl-parser-videosite.h		\
	xplayer-pl-parser-wm.c			\
	xplayer-pl-parser-wm.h			\
	xplayer-pl-parser-xspf.c			\
	xplayer-pl-parser-xspf.h			\
	xplayer-pl-parser-amz.h			\
	xplayer-pl-parser-amz.c			\
	xplayer-pl-playlist.c			\
	xplayer-pl-playlist.h

libxplayer_plparser_mini_la_CPPFLAGS = \
	-I$(top_srcdir)			\
	-I$(top_srcdir)/lib		\
	-I$(top_builddir)/plparse	\
	-DXPLAYER_PL_PARSER_MINI		\
	-DLIBEXECDIR=\""$(libexecdir)"\"\
	$(DISABLE_DEPRECATED)		\
	$(AM_CPPFLAGS)

libxplayer_plparser_mini_la_CFLAGS = \
	$(XPLAYER_PLPARSER_MINI_CFLAGS)	\
	$(WARN_CFLAGS)			\
	$(CODE_COVERAGE_CFLAGS)		\
	$(AM_CFLAGS)

libxplayer_plparser_mini_la_LIBADD =		\
	$(XPLAYER_PLPARSER_MINI_LIBS)		\
	$(top_builddir)/lib/libxplayer_glibc.la

libxplayer_plparser_mini_la_LDFLAGS =			\
	-version-info $(PLPARSER_LT_VERSION)		\
	-export-symbols $(srcdir)/plparser-mini.symbols	\
	-no-undefined					\
	$(CODE_COVERAGE_LDFLAGS)			\
	$(AM_LDFLAGS)

xplayer-pl-parser-builtins.h: xplayer-pl-parser.h
	$(AM_V_GEN) ($(GLIB_MKENUMS) \
			--fhead "#ifndef __XPLAYER_PL_PARSER_BUILTINS_H__\n#define __XPLAYER_PL_PARSER_BUILTINS_H__\n\n#include <glib-object.h>\n\nG_BEGIN_DECLS\n" \
			--fprod "/* enumerations from \"@filename@\" */\n" \
			--vhead "GType @enum_name@_get_type (void) G_GNUC_CONST;\n#define XPLAYER_TYPE_@ENUMSHORT@ (@enum_name@_get_type())\n" \
			--ftail "G_END_DECLS\n\n#endif /* __XPLAYER_PL_PARSER_BUILTINS_H__ */" $^ > xgen-$(@F) \
		&& mv -f xgen-$(@F) $@)

xplayer-pl-parser-builtins.c: xplayer-pl-parser.h xplayer-pl-parser-builtins.h
	$(AM_V_GEN) ($(GLIB_MKENUMS) \
			--fhead "#include \"xplayer-pl-parser.h\"\n#include \"xplayer-pl-parser-builtins.h\"" \
			--fprod "\n/* enumerations from \"@filename@\" */" \
			--vhead "GType\n@enum_name@_get_type (void)\n{\n  static GType etype = 0;\n  if (etype == 0) {\n    static const G@Type@Value values[] = {" \
			--vprod "      { @VALUENAME@, \"@VALUENAME@\", \"@valuenick@\" }," \
			--vtail "      { 0, NULL, NULL }\n    };\n    etype = g_@type@_register_static (\"@EnumName@\", values);\n  }\n  return etype;\n}\n" $^ > xgen-$(@F) \
		&& mv -f xgen-$(@F) $@)

CLEANFILES = $(BUILT_SOURCES)

DISTCLEANFILES = $(CLEANFILES)

EXTRA_DIST =				\
	xplayerplparser-marshal.list	\
	xplayer-pl-parser-features.h.in	\
	plparser.symbols		\
	plparser-mini.symbols

if HAVE_QUVI
libexec_PROGRAMS = xplayer-pl-parser-videosite
xplayer_pl_parser_videosite_SOURCES = videosite-parser.c
xplayer_pl_parser_videosite_CFLAGS = $(QUVI_CFLAGS) -DLIBEXECDIR=\""$(libexecdir)"\"
xplayer_pl_parser_videosite_LDADD = $(QUVI_LIBS)
endif

# Introspection
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --add-include-path=$(builddir) --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

if HAVE_INTROSPECTION
introspection_sources = \
	$(plparser_sources)		\
	$(plparserinclude_HEADERS)	\
	$(BUILTINFILES)			\
	xplayerplparser-marshal.c

XplayerPlParser-1.0.gir: libxplayer-plparser.la Makefile xplayerplparser-marshal.c xplayerplparser-marshal.h
XplayerPlParser_1_0_gir_SCANNERFLAGS = --namespace=XplayerPlParser --identifier-prefix=XplayerPl --symbol-prefix=xplayer_pl --identifier-prefix=XplayerDisc --symbol-prefix=xplayer_disc --identifier-prefix=XplayerCd --symbol-prefix=xplayer_cd --nsversion=1.0
XplayerPlParser_1_0_gir_INCLUDES = GObject-2.0 Gio-2.0
XplayerPlParser_1_0_gir_CFLAGS = \
	$(XPLAYER_PLPARSER_CFLAGS)	\
	$(DBUS_CFLAGS)			\
	$(AM_CFLAGS)			\
	-D_FILE_OFFSET_BITS=64		\
	-D_LARGEFILE64_SOURCE		\
	-I$(top_srcdir)			\
	-I$(top_srcdir)/lib		\
	-I$(top_builddir)/plparse	\
	-D_GNU_SOURCE
XplayerPlParser_1_0_gir_LIBS = libxplayer-plparser.la
XplayerPlParser_1_0_gir_FILES = $(introspection_sources)
INTROSPECTION_GIRS += XplayerPlParser-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(gir_DATA) $(typelib_DATA)
endif

@GNOME_CODE_COVERAGE_RULES@

-include $(top_srcdir)/git.mk
