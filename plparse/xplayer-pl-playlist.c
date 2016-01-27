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

/**
 * SECTION:xplayer-pl-playlist
 * @short_description: playlist object
 * @stability: Stable
 * @include: xplayer-pl-playlist.h
 *
 * #XplayerPlPlaylist represents a playlist, provides API to either navigate through
 * the playlist elements, or perform additions or modifications. See also
 * xplayer_pl_parser_save().
 *
 **/

/**
 * SECTION:xplayer-pl-playlist-iter
 * @short_description: playlist manipulation object
 * @stability: Stable
 * @include: xplayer-pl-playlist.h
 *
 * #XplayerPlPlaylistIter refers to an element in a playlist and is designed
 * to bridge between application provided playlist widgets or objects,
 * and #XplayerPlParser's saving code.
 *
 **/

#include "xplayer-pl-playlist.h"

typedef struct XplayerPlPlaylistPrivate XplayerPlPlaylistPrivate;

struct XplayerPlPlaylistPrivate {
        GList *items;
};

#define XPLAYER_PL_PLAYLIST_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), XPLAYER_TYPE_PL_PLAYLIST, XplayerPlPlaylistPrivate))

static void xplayer_pl_playlist_finalize (GObject *object);


G_DEFINE_TYPE (XplayerPlPlaylist, xplayer_pl_playlist, G_TYPE_OBJECT)


static void
xplayer_pl_playlist_class_init (XplayerPlPlaylistClass *klass)
{
        GObjectClass *object_class = G_OBJECT_CLASS (klass);

        object_class->finalize = xplayer_pl_playlist_finalize;

        g_type_class_add_private (klass, sizeof (XplayerPlPlaylistPrivate));
}

static void
xplayer_pl_playlist_init (XplayerPlPlaylist *playlist)
{
}

static void
xplayer_pl_playlist_finalize (GObject *object)
{
        XplayerPlPlaylistPrivate *priv;

        priv = XPLAYER_PL_PLAYLIST_GET_PRIVATE (object);

        g_list_foreach (priv->items, (GFunc) g_hash_table_destroy, NULL);
        g_list_free (priv->items);

        G_OBJECT_CLASS (xplayer_pl_playlist_parent_class)->finalize (object);
}

/**
 * xplayer_pl_playlist_new:
 *
 * Creates a new #XplayerPlPlaylist object.
 *
 * Returns: The newly created #XplayerPlPlaylist
 **/
XplayerPlPlaylist *
xplayer_pl_playlist_new (void)
{
        return g_object_new (XPLAYER_TYPE_PL_PLAYLIST, NULL);
}

/**
 * xplayer_pl_playlist_size:
 * @playlist: a #XplayerPlPlaylist
 *
 * Returns the number of elements in @playlist.
 *
 * Returns: The number of elements
 **/
guint
xplayer_pl_playlist_size (XplayerPlPlaylist *playlist)
{
        XplayerPlPlaylistPrivate *priv;

        g_return_val_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist), 0);

        priv = XPLAYER_PL_PLAYLIST_GET_PRIVATE (playlist);

        return g_list_length (priv->items);
}

static GHashTable *
create_playlist_item (void)
{
        return g_hash_table_new_full (g_str_hash,
                                      g_str_equal,
                                      (GDestroyNotify) g_free,
                                      (GDestroyNotify) g_free);
}

/**
 * xplayer_pl_playlist_prepend:
 * @playlist: a #XplayerPlPlaylist
 * @iter: (out): an unset #XplayerPlPlaylistIter for returning the location
 *
 * Prepends a new empty element to @playlist, and modifies @iter so
 * it points to it. To fill in values, you need to call
 * xplayer_pl_playlist_set() or xplayer_pl_playlist_set_value().
 **/
void
xplayer_pl_playlist_prepend (XplayerPlPlaylist     *playlist,
                           XplayerPlPlaylistIter *iter)
{
        XplayerPlPlaylistPrivate *priv;
        GHashTable *item;

        g_return_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist));
        g_return_if_fail (iter != NULL);

        priv = XPLAYER_PL_PLAYLIST_GET_PRIVATE (playlist);

        item = create_playlist_item ();
        priv->items = g_list_prepend (priv->items, item);

        iter->data1 = playlist;
        iter->data2 = priv->items;
}

/**
 * xplayer_pl_playlist_append:
 * @playlist: a #XplayerPlPlaylist
 * @iter: (out): an unset #XplayerPlPlaylistIter for returning the location
 *
 * Appends a new empty element to @playlist, and modifies @iter so
 * it points to it. To fill in values, you need to call
 * xplayer_pl_playlist_set() or xplayer_pl_playlist_set_value().
 **/
void
xplayer_pl_playlist_append (XplayerPlPlaylist     *playlist,
                          XplayerPlPlaylistIter *iter)
{
        XplayerPlPlaylistPrivate *priv;
        GHashTable *item;
        GList *list_item;

        g_return_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist));
        g_return_if_fail (iter != NULL);

        priv = XPLAYER_PL_PLAYLIST_GET_PRIVATE (playlist);

        item = create_playlist_item ();

        list_item = g_list_alloc ();
        list_item->data = item;

        priv->items = g_list_concat (priv->items, list_item);

        iter->data1 = playlist;
        iter->data2 = list_item;
}

/**
 * xplayer_pl_playlist_insert:
 * @playlist: a #XplayerPlPlaylist
 * @position: position in the playlist
 * @iter: (out): an unset #XplayerPlPlaylistIter for returning the location
 *
 * Inserts a new empty element to @playlist at @position, and modifies
 * @iter so it points to it. To fill in values, you need to call
 * xplayer_pl_playlist_set() or xplayer_pl_playlist_set_value().
 *
 * @position may be minor than 0 to prepend elements, or bigger than
 * the current @playlist size to append elements.
 **/
void
xplayer_pl_playlist_insert (XplayerPlPlaylist     *playlist,
                          gint                 position,
                          XplayerPlPlaylistIter *iter)
{
        XplayerPlPlaylistPrivate *priv;
        GHashTable *item;

        g_return_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist));
        g_return_if_fail (iter != NULL);

        priv = XPLAYER_PL_PLAYLIST_GET_PRIVATE (playlist);

        item = create_playlist_item ();
        priv->items = g_list_insert (priv->items, item, position);

        iter->data1 = playlist;
        iter->data2 = g_list_find (priv->items, item);
}

static gboolean
check_iter (XplayerPlPlaylist     *playlist,
            XplayerPlPlaylistIter *iter)
{
        XplayerPlPlaylistPrivate *priv;

        if (!iter) {
                return FALSE;
        }

        if (iter->data1 != playlist) {
                return FALSE;
        }

        priv = XPLAYER_PL_PLAYLIST_GET_PRIVATE (playlist);

        if (g_list_position (priv->items, iter->data2) == -1) {
                return FALSE;
        }

        return TRUE;
}

/**
 * xplayer_pl_playlist_iter_first:
 * @playlist: a #XplayerPlPlaylist
 * @iter: (out): an unset #XplayerPlPlaylistIter for returning the location
 *
 * Modifies @iter so it points to the first element in @playlist.
 *
 * Returns: %TRUE if there is such first element.
 **/
gboolean
xplayer_pl_playlist_iter_first (XplayerPlPlaylist     *playlist,
                              XplayerPlPlaylistIter *iter)
{
        XplayerPlPlaylistPrivate *priv;

        g_return_val_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist), FALSE);
        g_return_val_if_fail (iter != NULL, FALSE);

        priv = XPLAYER_PL_PLAYLIST_GET_PRIVATE (playlist);

        if (!priv->items) {
                /* Empty playlist */
                return FALSE;
        }

        iter->data1 = playlist;
        iter->data2 = priv->items;

        return TRUE;
}

/**
 * xplayer_pl_playlist_iter_next:
 * @playlist: a #XplayerPlPlaylist
 * @iter: (in): a #XplayerPlPlaylistIter pointing to some item in @playlist
 *
 * Modifies @iter so it points to the next element it previously
 * pointed to. This function will return %FALSE if there was no
 * next element, or @iter didn't actually point to any element
 * in @playlist.
 *
 * Returns: %TRUE if there was next element.
 **/
gboolean
xplayer_pl_playlist_iter_next (XplayerPlPlaylist     *playlist,
                             XplayerPlPlaylistIter *iter)
{
        g_return_val_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist), FALSE);
        g_return_val_if_fail (check_iter (playlist, iter), FALSE);

        iter->data2 = ((GList *) iter->data2)->next;

        return (iter->data2 != NULL);
}

/**
 * xplayer_pl_playlist_iter_prev:
 * @playlist: a #XplayerPlPlaylist
 * @iter: (in): a #XplayerPlPlaylistIter pointing to some item in @playlist
 *
 * Modifies @iter so it points to the previous element it previously
 * pointed to. This function will return %FALSE if there was no
 * previous element, or @iter didn't actually point to any element
 * in @playlist.
 *
 * Returns: %TRUE if there was previous element.
 **/
gboolean
xplayer_pl_playlist_iter_prev (XplayerPlPlaylist     *playlist,
                             XplayerPlPlaylistIter *iter)
{
        g_return_val_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist), FALSE);
        g_return_val_if_fail (check_iter (playlist, iter), FALSE);

        iter->data2 = ((GList *) iter->data2)->prev;

        return (iter->data2 != NULL);
}

/**
 * xplayer_pl_playlist_get_value:
 * @playlist: a #XplayerPlPlaylist
 * @iter: a #XplayerPlPlaylistIter pointing to some item in @playlist
 * @key: data key
 * @value: an empty #GValue to set
 *
 * Gets the value for @key (Such as %XPLAYER_PL_PARSER_FIELD_URI) in
 * the playlist item pointed by @iter.
 *
 * Returns: %TRUE if @iter contains data for @key.
 **/
gboolean
xplayer_pl_playlist_get_value (XplayerPlPlaylist     *playlist,
                             XplayerPlPlaylistIter *iter,
                             const gchar         *key,
                             GValue              *value)
{
        GHashTable *item_data;
        gchar *str;

        g_return_val_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist), FALSE);
        g_return_val_if_fail (check_iter (playlist, iter), FALSE);
        g_return_val_if_fail (key != NULL, FALSE);
        g_return_val_if_fail (value != NULL, FALSE);

        item_data = ((GList *) iter->data2)->data;

        str = g_hash_table_lookup (item_data, key);

        if (!str) {
                return FALSE;
        }

        g_value_init (value, G_TYPE_STRING);
        g_value_set_string (value, str);

        return TRUE;
}

/**
 * xplayer_pl_playlist_get_valist:
 * @playlist: a #XplayerPlPlaylist
 * @iter: a #XplayerPlPlaylistIter pointing to some item in @playlist
 * @args: a va_list
 *
 * See xplayer_pl_playlist_get(), this function takes a va_list.
 **/
void
xplayer_pl_playlist_get_valist (XplayerPlPlaylist     *playlist,
                              XplayerPlPlaylistIter *iter,
                              va_list              args)
{
        GHashTable *item_data;
        gchar *key, **value;

        g_return_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist));
        g_return_if_fail (check_iter (playlist, iter));

        item_data = ((GList *) iter->data2)->data;

        key = va_arg (args, gchar *);

        while (key) {
                value = va_arg (args, gchar **);

                if (value) {
                        gchar *str;

                        str = g_hash_table_lookup (item_data, key);
                        *value = g_strdup (str);
                }

                key = va_arg (args, gchar *);
        }
}

/**
 * xplayer_pl_playlist_get:
 * @playlist: a #XplayerPlPlaylist
 * @iter: a #XplayerPlPlaylistIter pointing to some item in @playlist
 * @...: pairs of key/return location for value, terminated by %NULL
 *
 * Gets the value for one or more keys from the element pointed
 * by @iter.
 **/
void
xplayer_pl_playlist_get (XplayerPlPlaylist     *playlist,
                       XplayerPlPlaylistIter *iter,
                       ...)
{
        va_list args;

        g_return_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist));
        g_return_if_fail (check_iter (playlist, iter));

        va_start (args, iter);
        xplayer_pl_playlist_get_valist (playlist, iter, args);
        va_end (args);
}

/**
 * xplayer_pl_playlist_set_value:
 * @playlist: a #XplayerPlPlaylist
 * @iter: a #XplayerPlPlaylistIter pointing to some item in @playlist
 * @key: key to set the value for
 * @value: #GValue containing the key value
 *
 * Sets the value for @key in the element pointed by @iter.
 *
 * Returns: %TRUE if the value could be stored in @playlist
 **/
gboolean
xplayer_pl_playlist_set_value (XplayerPlPlaylist     *playlist,
                             XplayerPlPlaylistIter *iter,
                             const gchar         *key,
                             GValue              *value)
{
        GHashTable *item_data;
        gchar *str;

        g_return_val_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist), FALSE);
        g_return_val_if_fail (check_iter (playlist, iter), FALSE);
        g_return_val_if_fail (key != NULL, FALSE);
        g_return_val_if_fail (value != NULL, FALSE);

        item_data = ((GList *) iter->data2)->data;

        if (G_VALUE_TYPE (value) == G_TYPE_STRING) {
                str = g_value_dup_string (value);
        } else {
                GValue str_value = { 0 };

                g_value_init (&str_value, G_TYPE_STRING);

                if (g_value_transform (value, &str_value)) {
                        str = g_value_dup_string (&str_value);
                } else {
                        str = NULL;
                }

                g_value_unset (&str_value);
        }

        if (!str) {
                g_critical ("Value could not be transformed to string");
                return FALSE;
        }

        g_hash_table_replace (item_data, g_strdup (key), str);

        return TRUE;
}

/**
 * xplayer_pl_playlist_set_valist:
 * @playlist: a #XplayerPlPlaylist
 * @iter: a #XplayerPlPlaylistIter pointing to some item in @playlist
 * @args: a va_list
 *
 * See xplayer_pl_playlist_set(), this function takes a va_list.
 **/
void
xplayer_pl_playlist_set_valist (XplayerPlPlaylist     *playlist,
                              XplayerPlPlaylistIter *iter,
                              va_list              args)
{
        GHashTable *item_data;
        gchar *key, *value;

        g_return_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist));
        g_return_if_fail (check_iter (playlist, iter));

        item_data = ((GList *) iter->data2)->data;

        key = va_arg (args, gchar *);

        while (key) {
                value = va_arg (args, gchar *);

                g_hash_table_replace (item_data,
                                      g_strdup (key),
                                      g_strdup (value));

                key = va_arg (args, gchar *);
        }
}

/**
 * xplayer_pl_playlist_set:
 * @playlist: a #XplayerPlPlaylist
 * @iter: a #XplayerPlPlaylistIter pointing to some item in @playlist
 * @...: key/value string pairs, terminated with %NULL
 *
 * Sets the value for one or several keys in the element pointed
 * by @iter.
 **/
void
xplayer_pl_playlist_set (XplayerPlPlaylist     *playlist,
                       XplayerPlPlaylistIter *iter,
                       ...)
{
        va_list args;

        g_return_if_fail (XPLAYER_IS_PL_PLAYLIST (playlist));
        g_return_if_fail (check_iter (playlist, iter));

        va_start (args, iter);
        xplayer_pl_playlist_set_valist (playlist, iter, args);
        va_end (args);
}
