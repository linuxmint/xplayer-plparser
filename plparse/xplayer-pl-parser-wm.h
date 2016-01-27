/* 
   2002, 2003, 2004, 2005, 2006, 2007 Bastien Nocera
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

#ifndef XPLAYER_PL_PARSER_WM_H
#define XPLAYER_PL_PARSER_WM_H

G_BEGIN_DECLS

#ifndef XPLAYER_PL_PARSER_MINI
#include "xplayer-pl-parser.h"
#include "xplayer-pl-parser-private.h"
#include <gio/gio.h>
#else
#include "xplayer-pl-parser-mini.h"
#endif /* !XPLAYER_PL_PARSER_MINI */

const char * xplayer_pl_parser_is_asf (const char *data, gsize len);
const char * xplayer_pl_parser_is_asx (const char *data, gsize len);

#ifndef XPLAYER_PL_PARSER_MINI
XplayerPlParserResult xplayer_pl_parser_add_asf (XplayerPlParser *parser,
					     GFile *file,
					     GFile *base_file,
					     XplayerPlParseData *parse_data,
					     gpointer data);
XplayerPlParserResult xplayer_pl_parser_add_asx (XplayerPlParser *parser,
					     GFile *file,
					     GFile *base_file,
					     XplayerPlParseData *parse_data,
					     gpointer data);
#endif /* !XPLAYER_PL_PARSER_MINI */

G_END_DECLS

#endif /* XPLAYER_PL_PARSER_WM_H */
