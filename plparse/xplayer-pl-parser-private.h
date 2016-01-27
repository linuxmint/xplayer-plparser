/* 
   2002, 2003, 2004, 2005, 2006 Bastien Nocera
   Copyright (C) 2003 Colin Walters <walters@verbum.org>

   The Gnome Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The Gnome Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the Gnome Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301  USA.

   Author: Bastien Nocera <hadess@hadess.net>
 */

#ifndef XPLAYER_PL_PARSER_PRIVATE_H
#define XPLAYER_PL_PARSER_PRIVATE_H

#include <glib.h>
#include "xplayer_internal.h"

/* A macro to call functions synchronously or asynchronously, depending on whether
 * we're parsing sync or async. This is necessary because when doing a sync parse,
 * the main loop isn't iterated, and so any signals emitted in idle functions (a requirement
 * of an async parse) aren't emitted until the sync parsing function returns, which
 * is less than ideal. We therefore want those idle functions to be called synchronously
 * when parsing sync, and with g_idle_add() when parsing async.
 *
 * Whether we're parsing sync or async is determined by whether we're in a thread. If (for
 * whatever reason), we're parsing async -- but not in a thread -- this will work out fine
 * anyway, since signal emission will consequently happen in the main thread.
 *
 * We determine if we're in the main thread by comparing the GThread pointer of the current
 * thread to a stored GThread pointer known to be from the main thread
 * (XplayerPlParser->priv->main_thread).
 *
 * When using idle functions for async signal emission, we specify the same priority as
 * GSimpleAsyncResult uses for its completion function (G_PRIORITY_DEFAULT). If the
 * completion function has higher priority, the main loop will call it first.
 *
 * @p: a #XplayerPlParser
 * @c: callback (as if for g_idle_add())
 * @d: callback data
 */
#define CALL_ASYNC(p, c, d) {							\
	if (g_thread_self () == p->priv->main_thread)				\
		c (d);								\
	else									\
		g_idle_add_full (G_PRIORITY_DEFAULT, (GSourceFunc) c, d, NULL);	\
}

#ifndef XPLAYER_PL_PARSER_MINI
#include "xplayer-pl-parser.h"
#include <glib-object.h>
#include <gio/gio.h>
#include <gio/gio.h>
#include <string.h>
#include "xmlparser.h"
#else
#include "xplayer-pl-parser-mini.h"
#endif /* !XPLAYER_PL_PARSER_MINI */

#define MIME_READ_CHUNK_SIZE 1024
#define UNKNOWN_TYPE "application/octet-stream"
#define DIR_MIME_TYPE "inode/directory"
#define BLOCK_DEVICE_TYPE "x-special/device-block"
#define EMPTY_FILE_TYPE "application/x-zerosize"
#define TEXT_URI_TYPE "text/uri-list"
#define AUDIO_MPEG_TYPE "audio/mpeg"
#define RSS_MIME_TYPE "application/rss+xml"
#define ATOM_MIME_TYPE "application/atom+xml"
#define OPML_MIME_TYPE "text/x-opml+xml"
#define QUICKTIME_META_MIME_TYPE "application/x-quicktime-media-link"
#define ASX_MIME_TYPE "audio/x-ms-asx"
#define ASF_REF_MIME_TYPE "video/x-ms-asf"

#define XPLAYER_PL_PARSER_FIELD_FILE		"gfile-object"
#define XPLAYER_PL_PARSER_FIELD_BASE_FILE		"gfile-object-base"

#define DEBUG(file, x) {					\
	if (xplayer_pl_parser_is_debugging_enabled (parser)) {	\
		if (file != NULL) {				\
			char *uri;				\
								\
			uri = g_file_get_uri (file);		\
			x;					\
			g_free (uri);				\
		} else {					\
			const char *uri = "empty";		\
			x;					\
		}						\
	}							\
}
#define DEBUG1(x) {						\
	if (xplayer_pl_parser_is_debugging_enabled (parser)) {	\
		x;						\
	}							\
}

typedef struct {
	guint recurse_level;
	guint fallback : 1;
	guint recurse : 1;
	guint force : 1;
	guint disable_unsafe : 1;
} XplayerPlParseData;

#ifndef XPLAYER_PL_PARSER_MINI
char *xplayer_pl_parser_read_ini_line_string	(char **lines, const char *key);
int   xplayer_pl_parser_read_ini_line_int		(char **lines, const char *key);
char *xplayer_pl_parser_read_ini_line_string_with_sep (char **lines, const char *key,
						     const char *sep);
gboolean xplayer_pl_parser_is_debugging_enabled	(XplayerPlParser *parser);
char *xplayer_pl_parser_base_uri			(GFile *file);
void xplayer_pl_parser_playlist_end		(XplayerPlParser *parser,
						 const char *playlist_title);

int xplayer_pl_parser_num_entries			(XplayerPlParser   *parser,
                                                 XplayerPlPlaylist *playlist);

gboolean xplayer_pl_parser_scheme_is_ignored	(XplayerPlParser *parser,
						 GFile *file);
gboolean xplayer_pl_parser_line_is_empty		(const char *line);
gboolean xplayer_pl_parser_write_string		(GOutputStream *stream,
						 const char *buf,
						 GError **error);
gboolean xplayer_pl_parser_write_buffer		(GOutputStream *stream,
						 const char *buf,
						 guint size,
						 GError **error);
char * xplayer_pl_parser_relative			(GFile *output,
						 const char *filepath);
char * xplayer_pl_parser_resolve_uri		(GFile *base_gfile,
						 const char *relative_uri);
XplayerPlParserResult xplayer_pl_parser_parse_internal (XplayerPlParser *parser,
						    GFile *file,
						    GFile *base_file,
						    XplayerPlParseData *parse_data);
void xplayer_pl_parser_add_one_uri		(XplayerPlParser *parser,
						 const char *uri,
						 const char *title);
void xplayer_pl_parser_add_one_file		(XplayerPlParser *parser,
						 GFile *file,
						 const char *title);
void xplayer_pl_parser_add_uri			(XplayerPlParser *parser,
						 const char *first_property_name,
						 ...);
void xplayer_pl_parser_add_hash_table		(XplayerPlParser *parser,
						 GHashTable    *metadata,
						 const char    *uri,
						 gboolean       is_playlist);
gboolean xplayer_pl_parser_ignore			(XplayerPlParser *parser,
						 const char *uri);
xml_node_t * xplayer_pl_parser_parse_xml_relaxed	(char *contents,
						 gsize size);
gboolean xplayer_pl_parser_fix_string		(const char  *name,
						 const char  *value,
						 char       **ret);

#endif /* !XPLAYER_PL_PARSER_MINI */

G_END_DECLS

#endif /* XPLAYER_PL_PARSER_PRIVATE_H */
