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

#ifndef XPLAYER_PL_PARSER_H
#define XPLAYER_PL_PARSER_H

#include <glib.h>
#include <gio/gio.h>

#include "xplayer-pl-parser-features.h"
#include "xplayer-pl-parser-builtins.h"
#include "xplayer-pl-playlist.h"

G_BEGIN_DECLS

#define XPLAYER_TYPE_PL_PARSER            (xplayer_pl_parser_get_type ())
#define XPLAYER_PL_PARSER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), XPLAYER_TYPE_PL_PARSER, XplayerPlParser))
#define XPLAYER_PL_PARSER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), XPLAYER_TYPE_PL_PARSER, XplayerPlParserClass))
#define XPLAYER_IS_PL_PARSER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), XPLAYER_TYPE_PL_PARSER))
#define XPLAYER_IS_PL_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), XPLAYER_TYPE_PL_PARSER))

/**
 * XplayerPlParserResult:
 * @XPLAYER_PL_PARSER_RESULT_UNHANDLED: The playlist could not be handled.
 * @XPLAYER_PL_PARSER_RESULT_ERROR: There was an error parsing the playlist.
 * @XPLAYER_PL_PARSER_RESULT_SUCCESS: The playlist was parsed successfully.
 * @XPLAYER_PL_PARSER_RESULT_IGNORED: The playlist was ignored due to its scheme or MIME type (see xplayer_pl_parser_add_ignored_scheme()
 * and xplayer_pl_parser_add_ignored_mimetype()).
 * @XPLAYER_PL_PARSER_RESULT_CANCELLED: Parsing of the playlist was cancelled part-way through.
 *
 * Gives the result of parsing a playlist.
 **/
typedef enum {
	XPLAYER_PL_PARSER_RESULT_UNHANDLED,
	XPLAYER_PL_PARSER_RESULT_ERROR,
	XPLAYER_PL_PARSER_RESULT_SUCCESS,
	XPLAYER_PL_PARSER_RESULT_IGNORED,
	XPLAYER_PL_PARSER_RESULT_CANCELLED
} XplayerPlParserResult;

typedef struct XplayerPlParserPrivate XplayerPlParserPrivate;

/**
 * XplayerPlParser:
 *
 * All the fields in the #XplayerPlParser structure are private and should never be accessed directly.
 **/
typedef struct {
	GObject parent;
	XplayerPlParserPrivate *priv;
} XplayerPlParser;

/* Known metadata fields */

/**
 * XPLAYER_PL_PARSER_FIELD_URI:
 *
 * Metadata field for an entry's URI.
 *
 * Since: 2.26
 **/
#define XPLAYER_PL_PARSER_FIELD_URI		"url"
/**
 * XPLAYER_PL_PARSER_FIELD_GENRE:
 *
 * Metadata field for an entry's genre.
 **/
#define XPLAYER_PL_PARSER_FIELD_GENRE		"genre"
/**
 * XPLAYER_PL_PARSER_FIELD_TITLE:
 *
 * Metadata field for an entry's displayable title.
 **/
#define XPLAYER_PL_PARSER_FIELD_TITLE		"title"
/**
 * XPLAYER_PL_PARSER_FIELD_AUTHOR:
 *
 * Metadata field for an entry's author/composer/director.
 **/
#define XPLAYER_PL_PARSER_FIELD_AUTHOR		"author"
/**
 * XPLAYER_PL_PARSER_FIELD_ALBUM:
 *
 * Metadata field for an entry's album.
 **/
#define XPLAYER_PL_PARSER_FIELD_ALBUM		"album"
/**
 * XPLAYER_PL_PARSER_FIELD_BASE:
 *
 * Metadata field for an entry's base path.
 **/
#define XPLAYER_PL_PARSER_FIELD_BASE		"base"
/**
 * XPLAYER_PL_PARSER_FIELD_SUBTITLE_URI:
 *
 * The URI of the entry's subtitle file.
 **/
#define XPLAYER_PL_PARSER_FIELD_SUBTITLE_URI	"subtitle-uri"
/**
 * XPLAYER_PL_PARSER_FIELD_VOLUME:
 *
 * Metadata field for an entry's playback volume.
 **/
#define XPLAYER_PL_PARSER_FIELD_VOLUME		"volume"
/**
 * XPLAYER_PL_PARSER_FIELD_AUTOPLAY:
 *
 * Metadata field for an entry's "autoplay" flag, which is %TRUE if the entry should play automatically.
 **/
#define XPLAYER_PL_PARSER_FIELD_AUTOPLAY		"autoplay"
/**
 * XPLAYER_PL_PARSER_FIELD_DURATION:
 *
 * Metadata field for an entry's playback duration, which should be parsed using xplayer_pl_parser_parse_duration().
 **/
#define XPLAYER_PL_PARSER_FIELD_DURATION		"duration"
/**
 * XPLAYER_PL_PARSER_FIELD_DURATION_MS:
 *
 * Metadata field for an entry's playback duration, in milliseconds. It's only used when an entry's
 * duration is available in that format, so one would get either the %XPLAYER_PL_PARSER_FIELD_DURATION
 * or %XPLAYER_PL_PARSER_FIELD_DURATION_MS as metadata.
 **/
#define XPLAYER_PL_PARSER_FIELD_DURATION_MS	"duration-ms"
/**
 * XPLAYER_PL_PARSER_FIELD_STARTTIME:
 *
 * Metadata field for an entry's playback start time, which should be parsed using xplayer_pl_parser_parse_duration().
 **/
#define XPLAYER_PL_PARSER_FIELD_STARTTIME		"starttime"
/**
 * XPLAYER_PL_PARSER_FIELD_ENDTIME:
 *
 * Metadata field for an entry's playback end time.
 **/
#define XPLAYER_PL_PARSER_FIELD_ENDTIME		"endtime"
/**
 * XPLAYER_PL_PARSER_FIELD_COPYRIGHT:
 *
 * Metadata field for an entry's copyright line.
 **/
#define XPLAYER_PL_PARSER_FIELD_COPYRIGHT		"copyright"
/**
 * XPLAYER_PL_PARSER_FIELD_ABSTRACT:
 *
 * Metadata field for an entry's abstract text.
 **/
#define XPLAYER_PL_PARSER_FIELD_ABSTRACT		"abstract"
/**
 * XPLAYER_PL_PARSER_FIELD_DESCRIPTION:
 *
 * Metadata field for an entry's description.
 **/
#define XPLAYER_PL_PARSER_FIELD_DESCRIPTION	"description"
/**
 * XPLAYER_PL_PARSER_FIELD_SUMMARY:
 *
 * Metadata field for an entry's summary. (In practice, identical to %XPLAYER_PL_PARSER_FIELD_DESCRIPTION.)
 **/
#define XPLAYER_PL_PARSER_FIELD_SUMMARY		XPLAYER_PL_PARSER_FIELD_DESCRIPTION
/**
 * XPLAYER_PL_PARSER_FIELD_MOREINFO:
 *
 * Metadata field for an entry's "more info" URI.
 **/
#define XPLAYER_PL_PARSER_FIELD_MOREINFO		"moreinfo"
/**
 * XPLAYER_PL_PARSER_FIELD_SCREENSIZE:
 *
 * Metadata field for an entry's preferred screen size.
 **/
#define XPLAYER_PL_PARSER_FIELD_SCREENSIZE	"screensize"
/**
 * XPLAYER_PL_PARSER_FIELD_UI_MODE:
 *
 * Metadata field for an entry's preferred UI mode.
 **/
#define XPLAYER_PL_PARSER_FIELD_UI_MODE		"ui-mode"
/**
 * XPLAYER_PL_PARSER_FIELD_PUB_DATE:
 *
 * Metadata field for an entry's publication date, which should be parsed using xplayer_pl_parser_parse_date().
 **/
#define XPLAYER_PL_PARSER_FIELD_PUB_DATE		"publication-date"
/**
 * XPLAYER_PL_PARSER_FIELD_FILESIZE:
 *
 * Metadata field for an entry's filesize in bytes. This is only advisory, and can sometimes not match the actual filesize of the stream.
 **/
#define XPLAYER_PL_PARSER_FIELD_FILESIZE		"filesize"
/**
 * XPLAYER_PL_PARSER_FIELD_LANGUAGE:
 *
 * Metadata field for an entry's audio language.
 **/
#define XPLAYER_PL_PARSER_FIELD_LANGUAGE		"language"
/**
 * XPLAYER_PL_PARSER_FIELD_CONTACT:
 *
 * Metadata field for an entry's contact details for the webmaster.
 **/
#define XPLAYER_PL_PARSER_FIELD_CONTACT		"contact"
/**
 * XPLAYER_PL_PARSER_FIELD_IMAGE_URI:
 *
 * Metadata field for an entry's thumbnail image URI.
 *
 * Since: 2.26
 **/
#define XPLAYER_PL_PARSER_FIELD_IMAGE_URI		"image-url"
/**
 * XPLAYER_PL_PARSER_FIELD_DOWNLOAD_URI:
 *
 * Metadata field for an entry's download URI. Only used if an alternate download
 * location is available for the entry.
 *
 * Since: 2.26
 **/
#define XPLAYER_PL_PARSER_FIELD_DOWNLOAD_URI	"download-url"
/**
 * XPLAYER_PL_PARSER_FIELD_ID:
 *
 * Metadata field for an entry's identifier. Its use is dependent on the format
 * of the playlist parsed, and its origin.
 **/
#define XPLAYER_PL_PARSER_FIELD_ID		"id"
/**
 * XPLAYER_PL_PARSER_FIELD_IS_PLAYLIST:
 *
 * Metadata field used to tell the calling code that the parsing of a playlist
 * started. It is only %TRUE for the metadata passed to #XplayerPlParser::playlist-started or
 * #XplayerPlParser::playlist-ended signal handlers.
 **/
#define XPLAYER_PL_PARSER_FIELD_IS_PLAYLIST	"is-playlist"
/**
 * XPLAYER_PL_PARSER_FIELD_CONTENT_TYPE:
 *
 * Metadata field for an entry's content-type (usually a mime-type coming
 * from a web server).
 **/
#define XPLAYER_PL_PARSER_FIELD_CONTENT_TYPE	"content-type"
/**
 * XPLAYER_PL_PARSER_FIELD_PLAYING:
 *
 * Metadata field for an entry's status in a playlist. This is usually
 * used when saving the state of an on-going playlist.
 **/
#define XPLAYER_PL_PARSER_FIELD_PLAYING           "playing"

/**
 * XplayerPlParserClass:
 * @parent_class: the parent class
 * @entry_parsed: the generic signal handler for the #XplayerPlParser::entry-parsed signal,
 * which can be overridden by inheriting classes
 * @playlist_started: the generic signal handler for the #XplayerPlParser::playlist-started signal,
 * which can be overridden by inheriting classes
 * @playlist_ended: the generic signal handler for the #XplayerPlParser::playlist-ended signal,
 * which can be overridden by inheriting classes
 *
 * The class structure for the #XplayerPlParser type.
 **/
typedef struct {
	GObjectClass parent_class;

	/* signals */
	void (*entry_parsed) (XplayerPlParser *parser,
			      const char *uri,
			      GHashTable *metadata);
	void (*playlist_started) (XplayerPlParser *parser,
				  const char *uri,
				  GHashTable *metadata);
	void (*playlist_ended) (XplayerPlParser *parser,
				const char *uri);
} XplayerPlParserClass;

/**
 * XplayerPlParserType:
 * @XPLAYER_PL_PARSER_PLS: PLS parser
 * @XPLAYER_PL_PARSER_M3U: M3U parser
 * @XPLAYER_PL_PARSER_M3U_DOS: M3U (DOS linebreaks) parser
 * @XPLAYER_PL_PARSER_XSPF: XSPF parser
 * @XPLAYER_PL_PARSER_IRIVER_PLA: iRiver PLA parser
 *
 * The type of playlist a #XplayerPlParser will parse.
 **/
typedef enum {
	XPLAYER_PL_PARSER_PLS,
	XPLAYER_PL_PARSER_M3U,
	XPLAYER_PL_PARSER_M3U_DOS,
	XPLAYER_PL_PARSER_XSPF,
	XPLAYER_PL_PARSER_IRIVER_PLA,
} XplayerPlParserType;

/**
 * XplayerPlParserError:
 * @XPLAYER_PL_PARSER_ERROR_NO_DISC: Error attempting to open a disc device when no disc is present
 * @XPLAYER_PL_PARSER_ERROR_MOUNT_FAILED: An attempted mount operation failed
 * @XPLAYER_PL_PARSER_ERROR_EMPTY_PLAYLIST: Playlist to be saved is empty
 *
 * Allows you to differentiate between different
 * errors occurring during file operations in a #XplayerPlParser.
 **/
typedef enum {
	XPLAYER_PL_PARSER_ERROR_NO_DISC,
	XPLAYER_PL_PARSER_ERROR_MOUNT_FAILED,
	XPLAYER_PL_PARSER_ERROR_EMPTY_PLAYLIST
} XplayerPlParserError;

#define XPLAYER_PL_PARSER_ERROR (xplayer_pl_parser_error_quark ())

GQuark xplayer_pl_parser_error_quark (void);

GType    xplayer_pl_parser_get_type (void);

gint64  xplayer_pl_parser_parse_duration (const char *duration, gboolean debug);
guint64 xplayer_pl_parser_parse_date     (const char *date_str, gboolean debug);

gboolean xplayer_pl_parser_save (XplayerPlParser      *parser,
			       XplayerPlPlaylist    *playlist,
			       GFile              *dest,
			       const gchar        *title,
			       XplayerPlParserType   type,
			       GError            **error);

void	   xplayer_pl_parser_add_ignored_scheme (XplayerPlParser *parser,
					       const char *scheme);
void       xplayer_pl_parser_add_ignored_mimetype (XplayerPlParser *parser,
						 const char *mimetype);

XplayerPlParserResult xplayer_pl_parser_parse (XplayerPlParser *parser,
					   const char *uri, gboolean fallback);
void xplayer_pl_parser_parse_async (XplayerPlParser *parser, const char *uri,
				  gboolean fallback, GCancellable *cancellable,
				  GAsyncReadyCallback callback,
                                  gpointer user_data);
XplayerPlParserResult xplayer_pl_parser_parse_finish (XplayerPlParser *parser,
						  GAsyncResult *async_result,
						  GError **error);

XplayerPlParserResult xplayer_pl_parser_parse_with_base (XplayerPlParser *parser,
						     const char *uri,
						     const char *base,
						     gboolean fallback);
void xplayer_pl_parser_parse_with_base_async (XplayerPlParser *parser,
					    const char *uri, const char *base,
					    gboolean fallback,
					    GCancellable *cancellable,
					    GAsyncReadyCallback callback,
                    			    gpointer user_data);

XplayerPlParser *xplayer_pl_parser_new (void);

/**
 * XplayerPlParserMetadata: (skip)
 *
 * An alias for #GHashTable, used in the #XplayerPlParser::entry-parsed and
 * #XplayerPlParser::playlist-started signals due to #GHashTable not being a
 * boxed type when xplayer-pl-parser was originally written.
 *
 * The hash table is a mapping from field names (such as
 * %XPLAYER_PL_PARSER_FIELD_ALBUM) to their associated values.
 *
 * It is safe to use #GHashTable instead of #XplayerPlParserMetadata everywhere.
 */
typedef GHashTable XplayerPlParserMetadata;

GType xplayer_pl_parser_metadata_get_type (void) G_GNUC_CONST;
#define XPLAYER_TYPE_PL_PARSER_METADATA (xplayer_pl_parser_metadata_get_type())

G_END_DECLS

#endif /* XPLAYER_PL_PARSER_H */
