#include <pthread.h>
#include "minirt.h"
#include "mlx.h"

#define NUM_THREADS 4

typedef struct s_thread_data
{
    t_minirt *minirt;
    int start;
    int end;
} t_thread_data;

void *ray_trace_thread(void *arg)
{
    t_thread_data *data = (t_thread_data *)arg;
    t_minirt *minirt = data->minirt;
    int start = data->start;
    int end = data->end;

    for (int y = start; y < end; y++)
    {
        for (int x = 0; x < minirt->width; x++)
        {
            // Perform ray tracing for each pixel
            // minirt_ray_trace(minirt, x, y);
        }
    }

    return NULL;
}

void ray_trac_loop(t_minirt *minirt)
{
    pthread_t threads[NUM_THREADS];
    t_thread_data thread_data[NUM_THREADS];
    int rows_per_thread = minirt->height / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].minirt = minirt;
        thread_data[i].start = i * rows_per_thread;
        thread_data[i].end = (i == NUM_THREADS - 1) ? minirt->height : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, ray_trace_thread, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
    mlx_loop(minirt->mlx);
}

int key_press(int keycode, t_minirt *minirt) {
    if (keycode == 53) // ESC key
        exit(0);
    // Handle other key presses
    return 0;
}

int mouse_move(int x, int y, t_minirt *minirt) {
    // Handle mouse movement
    return 0;
}
