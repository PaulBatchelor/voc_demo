/* nuklear - v1.32.0 - public domain */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include <GLFW/glfw3.h>

#include "voc_demo.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL2_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_glfw_gl2.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define UNUSED(a) (void)a
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define LEN(a) (sizeof(a)/sizeof(a)[0])

/* ===============================================================
 *
 *                          EXAMPLE
 *
 * ===============================================================*/
/* This are some code examples to provide a small overview of what can be
 * done with this library. To try out an example uncomment the include
 * and the corresponding function. */
/*#include "../style.c"*/
/*#include "../calculator.c"*/
/*#include "../overview.c"*/
/*#include "../node_editor.c"*/

/* ===============================================================
 *
 *                          DEMO
 *
 * ===============================================================*/
static void error_callback(int e, const char *d)
{printf("Error %d: %s\n", e, d);}
int main(int argc, char *argv[])
{
    /* Platform */
    static GLFWwindow *win;
    int width = 0, height = 0;
    struct nk_context *ctx;
    struct nk_color background;

    voc_demo_d vd;
    int i;

    voc_demo_setup(&vd);
    voc_demo_start(&vd);

    /* GLFW */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stdout, "[GFLW] failed to init!\n");
        exit(1);
    }
    win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo", NULL, NULL);
    glfwMakeContextCurrent(win);
    glfwGetWindowSize(win, &width, &height);

    /* GUI */
    ctx = nk_glfw3_init(win, NK_GLFW3_INSTALL_CALLBACKS);
    /* Load Fonts: if none of these are loaded a default font will be used  */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */
    {struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&atlas);
    /*struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14, 0);*/
    /*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 14, 0);*/
    /*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
    /*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
    /*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
    /*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
    nk_glfw3_font_stash_end();
    /*nk_style_load_all_cursors(ctx, atlas->cursors);*/
    /*nk_style_set_font(ctx, &droid->handle);*/}

    /* style.c */
    /*set_style(ctx, THEME_WHITE);*/
    /*set_style(ctx, THEME_RED);*/
    /*set_style(ctx, THEME_BLUE);*/
    /*set_style(ctx, THEME_DARK);*/

    background = nk_rgb(28,48,62);
    while (!glfwWindowShouldClose(win))
    {
        /* Input */
        glfwPollEvents();
        nk_glfw3_new_frame();

        /* GUI */
        if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            nk_layout_row_static(ctx, 30, 200, 1);
            nk_label(ctx, "Gain:", NK_TEXT_LEFT);
            nk_slider_float(ctx, 0, &vd.gain, 1, 0.01);
            nk_label(ctx, "Frequency:", NK_TEXT_LEFT);
            nk_slider_float(ctx, 10, vd.freq, 400, 0.01);
            nk_label(ctx, "Velum:", NK_TEXT_LEFT);
            nk_slider_float(ctx, 0, vd.velum, 0.8, 0.01);
            nk_label(ctx, "Tenseness:", NK_TEXT_LEFT);
            nk_slider_float(ctx, 0, vd.tenseness, 1, 0.01);
        }
        nk_end(ctx);
        
        if (nk_begin(ctx, "Tract", nk_rect(300, 50, 230, 500),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            nk_layout_row_static(ctx, 30, 200, 1);
            for(i = 0; i < vd.tract_size; i++) {
                nk_slider_float(ctx, 0, &vd.tract[i], 3.5, 0.01);
            }
        }
        nk_end(ctx);
        
        if (nk_begin(ctx, "Mode", nk_rect(570, 50, 230, 500),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            nk_layout_row_static(ctx, 30, 200, 1);
            if(nk_option_label(ctx, "None", vd.mode == VOC_NONE)) {
                vd.mode = VOC_NONE;
            } 
            if(nk_option_label(ctx, "Tongue", vd.mode == VOC_TONGUE)) {
                vd.mode = VOC_TONGUE;
                nk_slider_float(ctx, 10, &vd.tongue_pos, 40, 0.2);
                nk_slider_float(ctx, 1, &vd.tongue_diam, 3.5, 0.01);
            }
        }
        nk_end(ctx);
        
        if (nk_begin(ctx, "Plot", nk_rect(50, 500, 530, 210),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            nk_layout_row_static(ctx, 150, 500, 1);
            nk_chart_begin(ctx, NK_CHART_COLUMN, 44, 0, 3.5);
            /* nk_plot(ctx, NK_CHART_COLUMN, vd.tract, 44, 0); */
            for(i = 0; i < 44; i++) {
                nk_chart_push(ctx, vd.tract[i]);
            }
            nk_chart_end(ctx);

        }
        nk_end(ctx);

        /* Draw */
        {float bg[4];
        nk_color_fv(bg, background);
        glfwGetWindowSize(win, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg[0], bg[1], bg[2], bg[3]);
        /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
         * with blending, scissor, face culling and depth test and defaults everything
         * back into a default state. Make sure to either save and restore or
         * reset your own state after drawing rendering the UI. */
        nk_glfw3_render(NK_ANTI_ALIASING_ON);
        glfwSwapBuffers(win);}
    }
    nk_glfw3_shutdown();
    glfwTerminate();

    voc_demo_stop(&vd);
    voc_demo_destroy(&vd);
    return 0;
}

