/*
 * Copyright 2014 © Samsung Research America, Silicon Valley
 *
 * Use of this source code is governed by the 3-Clause BSD license
 * specified in the COPYING file included with this source code.
 */
#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cairo.h>

#include "caskbench.h"
#include "caskbench_context.h"
#include "cairo-shapes.h"

// This test converts a text string to glyphs and displays it at various font sizes

static int max_dim;
static char rand_text_array[19][100];

static void
gen_random(char *s, const int len) {
    static const char alphanum[] =
        "ABCD EFG HIJKL MNOPQ RSTUVW XYZ";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rnd() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

int
ca_setup_text_glyphs(caskbench_context_t *ctx)
{
    max_dim = MIN (ctx->canvas_width, ctx->canvas_height)/2;
    return 1;
}

void
ca_teardown_text_glyphs(void)
{
}

int
ca_test_text_glyphs(caskbench_context_t *ctx)
{
    cairo_t *cr = ctx->cairo_cr;
    double font_size = 18;
    int ypos = 15, xpos = 0;
    int num_glyphs = 0, num_clusters = 0;

    double font_factor = 0.5;

    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_rectangle (cr, 0, 0, ctx->canvas_width ,ctx->canvas_height);
    cairo_fill (cr);
    for (int i = 0; i < ctx->size; i++)
    {
        num_glyphs = 0;
        num_clusters = 0;
        cairo_set_font_size (cr, font_size);
        cairoRandomizeColor (ctx);

        cairo_status_t status;
        cairo_scaled_font_t *font;
        font = cairo_get_scaled_font (cr);
        cairo_glyph_t *glyphs = NULL;
        cairo_text_cluster_t *clusters = NULL;
        cairo_text_cluster_flags_t cluster_flags;

        char text[(int)font_size];
        gen_random (text,font_size);

        status = cairo_scaled_font_text_to_glyphs (font,
                                                   xpos, ypos,
                                                   text, font_size,
                                                   &glyphs, &num_glyphs,
                                                   &clusters, &num_clusters, &cluster_flags);

        if (status == CAIRO_STATUS_SUCCESS) {
            cairo_show_text_glyphs (cr,
                                    text,font_size,
                                    glyphs, num_glyphs,
                                    clusters, num_clusters, cluster_flags);
        }

        font_size = font_size+font_factor;
        ypos += (font_size/2);
        if (font_size >= 36)
            font_size = 36;
        if (ypos > ctx->canvas_height/2)
            font_factor = -0.5;
        if (font_size < 18)
            font_size = 18;
    }
    return 1;
}

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99 :
