/* 
   Copyright (C) 2007 Bastien Nocera <hadess@hadess.net>

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

#ifndef XPLAYER_PL_PARSER_PODCAST_H
#define XPLAYER_PL_PARSER_PODCAST_H

G_BEGIN_DECLS

#ifndef XPLAYER_PL_PARSER_MINI
#include "xplayer-pl-parser.h"
#include "xplayer-pl-parser-private.h"
#include <gio/gio.h>
#else
#include "xplayer-pl-parser-mini.h"
#endif /* !XPLAYER_PL_PARSER_MINI */

const char * xplayer_pl_parser_is_rss (const char *data, gsize len);
const char * xplayer_pl_parser_is_atom (const char *data, gsize len);
const char * xplayer_pl_parser_is_opml (const char *data, gsize len);
const char * xplayer_pl_parser_is_xml_feed (const char *data, gsize len);

#ifndef XPLAYER_PL_PARSER_MINI

#ifndef HAVE_GMIME
#define WARN_NO_GMIME { \
	g_warning("Trying to parse a podcast, but xplayer-pl-parser built without libgmime support. Please contact your distribution provider."); \
	return XPLAYER_PL_PARSER_RESULT_ERROR; \
}
#endif /* !HAVE_GMIME */

gboolean xplayer_pl_parser_is_itms_feed (GFile *file);

XplayerPlParserResult xplayer_pl_parser_add_xml_feed (XplayerPlParser *parser,
						  GFile *file,
						  GFile *base_file,
						  XplayerPlParseData *parse_data,
						  gpointer data);
XplayerPlParserResult xplayer_pl_parser_add_atom (XplayerPlParser *parser,
					      GFile *file,
					      GFile *base_file,
					      XplayerPlParseData *parse_data,
					      gpointer data);
XplayerPlParserResult xplayer_pl_parser_add_rss (XplayerPlParser *parser,
					     GFile *file,
					     GFile *base_file,
					     XplayerPlParseData *parse_data,
					     gpointer data);
XplayerPlParserResult xplayer_pl_parser_add_itpc (XplayerPlParser *parser,
					      GFile *file,
					      GFile *base_file,
					      XplayerPlParseData *parse_data,
					      gpointer data);
XplayerPlParserResult xplayer_pl_parser_add_zune (XplayerPlParser *parser,
					      GFile *file,
					      GFile *base_file,
					      XplayerPlParseData *parse_data,
					      gpointer data);
XplayerPlParserResult xplayer_pl_parser_add_itms (XplayerPlParser *parser,
					      GFile *file,
					      GFile *base_file,
					      XplayerPlParseData *parse_data,
					      gpointer data);
XplayerPlParserResult xplayer_pl_parser_add_opml (XplayerPlParser *parser,
					      GFile *file,
					      GFile *base_file,
					      XplayerPlParseData *parse_data,
					      gpointer data);

#endif /* !XPLAYER_PL_PARSER_MINI */

G_END_DECLS

#endif /* XPLAYER_PL_PARSER_PODCAST_H */
