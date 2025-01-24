    void ini_graphic(t_minirt *minirt)
    {
        minirt->graphic.mlx = mlx_init();
        if (minirt->graphic.mlx == NULL)
        {
            // Handle error
            errors(ER_MLX, minirt);
            return;
        }
        minirt->graphic.win = mlx_new_window(minirt->graphic.mlx, 800, 600, "MiniRT");
        if (minirt->graphic.win == NULL)
        {
            // Handle error
            errors(ER_MLX, minirt);
            return;
        }
        minirt->graphic.img = mlx_new_image(minirt->graphic.mlx, 800, 600);
        if (minirt->graphic.img == NULL)
        {
            // Handle error
            errors(ER_MLX, minirt);
            return;
        }
        minirt->graphic.addr = mlx_get_data_addr(minirt->graphic.img, \
            &minirt->graphic.bpp, &minirt->graphic.l_len, &minirt->graphic.end);
        if (minirt->graphic.addr == NULL)
        {
            // Handle error
            errors(ER_MLX, minirt);
            return;
        }
    }

    void ini_threads(t_minirt *minirt)
    {
        int i;

        minirt->threads = malloc(sizeof(pthread_t) * NUM_THREADS);
        if (minirt->threads == NULL)
        {
            // Handle error
            errors(ER_THREAD, minirt);
            return;
        }
        for (i = 0; i < NUM_THREADS; i++)
        {
            if (pthread_create(&minirt->threads[i], NULL, thread_function, (void *)minirt) != 0)
            {
                // Handle error
                errors(ER_THREAD, minirt);
                return;
            }
        }
    }
