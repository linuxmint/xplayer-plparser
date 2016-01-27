/*
   Copyright (C) 2009, Nokia

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

   Author: Carlos Garnacho <carlos@lanedo.com>
 */

#ifndef __XPLAYER_PL_PLAYLIST_H__
#define __XPLAYER_PL_PLAYLIST_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define XPLAYER_TYPE_PL_PLAYLIST            (xplayer_pl_playlist_get_type ())
#define XPLAYER_PL_PLAYLIST(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), XPLAYER_TYPE_PL_PLAYLIST, XplayerPlPlaylist))
#define XPLAYER_PL_PLAYLIST_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), XPLAYER_TYPE_PL_PLAYLIST, XplayerPlPlaylistClass))
#define XPLAYER_IS_PL_PLAYLIST(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), XPLAYER_TYPE_PL_PLAYLIST))
#define XPLAYER_IS_PL_PLAYLIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), XPLAYER_TYPE_PL_PLAYLIST))

/**
 * XplayerPlPlaylist:
 *
 * All the fields in the #XplayerPlPlaylist structure are private and should never be accessed directly.
 **/
typedef struct {
        GObject parent_instance;
} XplayerPlPlaylist;

/**
 * XplayerPlPlaylistClass:
 * @parent_class: the parent class
 *
 * All the fields in the #XplayerPlPlaylistClass structure are private and should never be accessed directly.
 **/
typedef struct {
        GObjectClass parent_class;
} XplayerPlPlaylistClass;

/**
 * XplayerPlPlaylistIter:
 *
 * All the fields in the #XplayerPlPlaylistIter structure are private and should never be accessed directly.
 **/
typedef struct {
        /*< private >*/
        gpointer data1;
        gpointer data2;
} XplayerPlPlaylistIter;

GType xplayer_pl_playlist_get_type (void) G_GNUC_CONST;

XplayerPlPlaylist * xplayer_pl_playlist_new (void);

guint xplayer_pl_playlist_size   (XplayerPlPlaylist     *playlist);

/* Item insertion methods */
void xplayer_pl_playlist_prepend (XplayerPlPlaylist     *playlist,
                                XplayerPlPlaylistIter *iter);
void xplayer_pl_playlist_append  (XplayerPlPlaylist     *playlist,
                                XplayerPlPlaylistIter *iter);
void xplayer_pl_playlist_insert  (XplayerPlPlaylist     *playlist,
                                gint                 position,
                                XplayerPlPlaylistIter *iter);

/* Navigation methods */
gboolean xplayer_pl_playlist_iter_first (XplayerPlPlaylist     *playlist,
                                       XplayerPlPlaylistIter *iter);
gboolean xplayer_pl_playlist_iter_next  (XplayerPlPlaylist     *playlist,
                                       XplayerPlPlaylistIter *iter);
gboolean xplayer_pl_playlist_iter_prev  (XplayerPlPlaylist     *playlist,
                                       XplayerPlPlaylistIter *iter);

/* Item edition methods */
gboolean xplayer_pl_playlist_get_value (XplayerPlPlaylist     *playlist,
                                      XplayerPlPlaylistIter *iter,
                                      const gchar         *key,
                                      GValue              *value);
void xplayer_pl_playlist_get_valist    (XplayerPlPlaylist     *playlist,
                                      XplayerPlPlaylistIter *iter,
                                      va_list              args);
void xplayer_pl_playlist_get           (XplayerPlPlaylist     *playlist,
                                      XplayerPlPlaylistIter *iter,
                                      ...) G_GNUC_NULL_TERMINATED;

gboolean xplayer_pl_playlist_set_value (XplayerPlPlaylist     *playlist,
                                      XplayerPlPlaylistIter *iter,
                                      const gchar         *key,
                                      GValue              *value);
void xplayer_pl_playlist_set_valist    (XplayerPlPlaylist     *playlist,
                                      XplayerPlPlaylistIter *iter,
                                      va_list              args);
void xplayer_pl_playlist_set           (XplayerPlPlaylist     *playlist,
                                      XplayerPlPlaylistIter *iter,
                                      ...) G_GNUC_NULL_TERMINATED;

G_END_DECLS

#endif /* __XPLAYER_PL_PLAYLIST_H__ */
