/*
 * snappy - 0.3
 *
 * Copyright (C) 2011-2013 Collabora Ltd.
 * Luis de Bethencourt <luis@debethencourt.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__

#include <gtk/gtk.h>

#include "gst_engine.h"
#include "screensaver.h"

#define CTL_SHOW_SEC 3
#define CTL_FADE_DURATION G_TIME_SPAN_MILLISECOND / 4

#define CONTROLS_WIDTH_RATIO 0.48f
#define CONTROLS_HEIGHT_RATIO 0.20f
#define CONTROLS_ASPECT_RATIO 4.0f
#define CONTROLS_MAX_WIDTH 480.0f
#define CONTROLS_MIN_WIDTH 300.0f

#define MAIN_BOX_W 0.95f
#define MAIN_BOX_H 0.8f

#define PLAY_TOGGLE_RATIO 0.38f
#define TITLE_RATIO 0.033f
#define SEEK_WIDTH_RATIO 0.9f
#define SEEK_HEIGHT_RATIO 0.10f
#define POS_RATIO 0.1f
#define VOLUME_ICON_RATIO 0.18f
#define VOLUME_WIDTH_RATIO 0.65f
#define VOLUME_HEIGHT_RATIO 0.05f

#define TITLE_LENGTH 40

#define SEC_IN_HOUR 3600
#define SEC_IN_MIN 60

#define PENALTY_TIME G_TIME_SPAN_MILLISECOND / 2

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

G_BEGIN_DECLS

enum
{
  STREAM_AUDIO,
  STREAM_TEXT,
  STREAM_VIDEO
};

typedef struct _UserInterface UserInterface;

struct _UserInterface
{
  gboolean controls_showing, keep_showing_controls;
  gboolean blind, fullscreen, hide, penalty_box_active, tags;
  gboolean subtitles_available;

  gint title_length, controls_timeout, progress_id;
  guint media_width, media_height;
  gint64 media_duration;
  gfloat stage_width, stage_height;
  gfloat screen_width, screen_height;
  gfloat windowed_width, windowed_height;
  gfloat playback_position, volume;
  gfloat seek_width, seek_height;
  gfloat volume_width, volume_height;

  gchar *filename, *fileuri;
  gchar *play_png, *pause_png;
  gchar *segment_png;
  gchar *volume_low_png, *volume_high_png;
  gchar *fullscreen_svg;
  gchar *subtitle_active_png, *subtitle_inactive_png;
  gchar *video_stream_toggle_png, *audio_stream_toggle_png;
  gchar *data_dir;
  gchar *duration_str;

  GList *uri_list;

  GtkWidget *window, *box, *clutter_widget;

  ClutterColor stage_bg_color, text_color, border_color;
  ClutterColor gradient_start, gradient_finish;

  ClutterActor *stage;
  ClutterActor *texture;
  ClutterActor *control_box;
  ClutterActor *control_bg, *control_title, *control_play_toggle;
  ClutterActor *control_seekbar;
  ClutterActor *control_pos;
  ClutterActor *volume_box;
  ClutterActor *volume_low, *volume_high;
  ClutterActor *fullscreen_button;
  ClutterActor *subtitle_toggle;
  ClutterActor *video_stream_toggle, *audio_stream_toggle;
  ClutterActor *vol_int, *vol_int_bg, *volume_point;
  ClutterActor *info_box;
  ClutterActor *pos_n_vol_box;
  ClutterActor *main_box;

  ClutterContent *seek_canvas;
  ClutterContent *vol_int_canvas;

  ClutterLayoutManager *main_box_layout;
  ClutterLayoutManager *info_box_layout;
  ClutterLayoutManager *pos_n_vol_layout;
  ClutterLayoutManager *middle_box_layout;

  GstEngine *engine;
  ScreenSaver *screensaver;
};

static const GtkTargetEntry drop_target_table[] = {
  {(gchar *) "text/uri-list", 0, 0}
};


// Declaration of non-static functions
void interface_init (UserInterface * ui);
gboolean interface_is_it_last (UserInterface * ui);
gboolean interface_load_uri (UserInterface * ui, gchar * uri);
void interface_on_drop_cb (GtkWidget * widget, GdkDragContext * context, gint x,
    gint y, GtkSelectionData * data, guint info, guint _time,
    UserInterface * ui);
void interface_play_next_or_prev (UserInterface * ui, gboolean next);
void interface_start (UserInterface * ui, gchar * uri);
gboolean interface_update_controls (UserInterface * ui);

G_END_DECLS
#endif /* __USER_INTERFACE_H__ */
