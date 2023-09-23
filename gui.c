/*
Conway's Game of Life

~Andrea-Tomatis
*/

#include "./header.h"


#define NUM_CELLS DIM*DIM
#define TIME_STAMP 500

static int highlighted_cells[NUM_CELLS] = {0};

static bool ** mat;



static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer data) {
    guint width, height;
    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);

    // Set black background
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    double cell_width = (double)width / DIM;
    double cell_height = (double)height / DIM;

    // Draw grid lines
    cairo_set_source_rgb(cr, 0.0, 1.0, 0.0); // Set black color for grid lines
    cairo_set_line_width(cr, 1.0); // Set line width

    for (int i = 1; i < DIM; i++) {
        double x = i * cell_width;
        cairo_move_to(cr, x, 0);
        cairo_line_to(cr, x, height);
    }

    for (int i = 1; i < DIM; i++) {
        double y = i * cell_height;
        cairo_move_to(cr, 0, y);
        cairo_line_to(cr, width, y);
    }

    cairo_stroke(cr);

    // Highlight cells
    cairo_set_source_rgb(cr, 0.0, 1.0, 0.0); // Set green color for highlighted cells
    for (int i = 0; i < NUM_CELLS; i++) {
        int cell = highlighted_cells[i];
        int row = cell / DIM;
        int col = cell % DIM;

        double x = col * cell_width;
        double y = row * cell_height;

        cairo_rectangle(cr, x, y, cell_width, cell_height);
        cairo_fill(cr);
    }

    return FALSE;
}

static gboolean update_highlighted_cells(gpointer data) {
    
    
    update(&mat, DIM); // Random number of cells to highlight

    for (int i =0; i < NUM_CELLS; i++){
        int row = i / DIM;
        int col = i % DIM;
        if (mat[row][col])
            highlighted_cells[i] = i;
        else
            highlighted_cells[i] = 0;
    }

    gtk_widget_queue_draw(data);
    return G_SOURCE_CONTINUE;
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *drawing_area;

    srand(time(NULL)); // Initialize random number generator

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Game of Life");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

    // Set window background to black
    GdkRGBA color;
    gdk_rgba_parse(&color, "black");
    gtk_widget_override_background_color(window, GTK_STATE_FLAG_NORMAL, &color);

    drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), NULL);

    g_timeout_add(TIME_STAMP, update_highlighted_cells, drawing_area);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    init_mat(&mat, DIM);

    start_cond(&mat);


    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.grid-drawing", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);


    free(mat);

    return status;

}
