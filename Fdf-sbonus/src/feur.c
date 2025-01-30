#include <pthread.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SAMPLE_RATE 44100
#define BUFFER_SIZE 1024 // Adjust size as needed

pthread_mutex_t buffer_mutex;
float audio_buffer[BUFFER_SIZE];  // Shared buffer for audio data
int buffer_index = 0;             // Index to track position in buffer

// PulseAudio structure
pa_simple *s = NULL;
pa_sample_spec ss;
pa_buffer_attr buffer_attr;
int error;

int	handle_key(int keycode, void *param)
{
	(void)param;
	if (keycode == 65307)
		exit(0);
	return (0);
}

void *audio_capture_thread(void *arg) {
	(void)arg;
    // Open PulseAudio stream
    pa_threaded_mainloop	*pa_mainloop;// setup the fucking mainloop with the documentation up your ass indeed

    ss.format = PA_SAMPLE_FLOAT32LE;
    ss.rate = SAMPLE_RATE;
    ss.channels = 1;
    buffer_attr.maxlength = (uint32_t)-1;
    buffer_attr.tlength = pa_usec_to_bytes(1000000 / SAMPLE_RATE, &ss);
    buffer_attr.prebuf = (uint32_t)-1;
    buffer_attr.minreq = (uint32_t)-1;

    s = pa_simple_new(NULL, "AudioCapture", PA_STREAM_RECORD, NULL, "Record", &ss, NULL, &buffer_attr, &error);
    if (!s) {
        fprintf(stderr, "PulseAudio connection error: %s\n", pa_strerror(error));
        return NULL;
    }

    while (1) {
        // Capture audio data into the buffer
        float buffer[BUFFER_SIZE];
        if (pa_simple_read(s, buffer, sizeof(buffer), &error) < 0) {
            fprintf(stderr, "PulseAudio read error: %s\n", pa_strerror(error));
            break;
        }

        // Lock the mutex before accessing the shared buffer
        pthread_mutex_lock(&buffer_mutex);

        // Copy the data into the shared buffer
        for (int i = 0; i < BUFFER_SIZE; i++) {
            audio_buffer[i] = buffer[i];
        }

        buffer_index = (buffer_index + 1) % BUFFER_SIZE;

        // Unlock the mutex after updating the buffer
        pthread_mutex_unlock(&buffer_mutex);
    }

    return NULL;
}

void *mlx_draw_thread() {
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Audio Visualization");
    int *img_data = mlx_new_image(mlx_ptr, 800, 600);
    int *data = (int *)mlx_get_data_addr(img_data, &(int){0}, &(int){0}, &(int){0});
	mlx_key_hook(win_ptr, handle_key, NULL);
    while (1) {
        // Lock the mutex before reading the shared buffer
        pthread_mutex_lock(&buffer_mutex);

        // Use the audio_buffer to update your visual representation
        for (int i = 0; i < BUFFER_SIZE; i++) {
            // You can map audio data (e.g., volume) to draw something
            int color = (int)(audio_buffer[i] * 255);
            color = color < 0 ? 0 : (color > 255 ? 255 : color);
            data[i] = (color << 16) | (color << 8) | color;  // Grayscale effect
        }

        // Unlock the mutex after reading the buffer
        pthread_mutex_unlock(&buffer_mutex);

        // Draw the image to the window
        mlx_put_image_to_window(mlx_ptr, win_ptr, img_data, 0, 0);
        mlx_loop(mlx_ptr);
    }

    return NULL;
}

int main(void)
{
    pthread_t audio_thread, mlx_thread;

    // Initialize the mutex
    pthread_mutex_init(&buffer_mutex, NULL);

    // Create threads
    pthread_create(&audio_thread, NULL, audio_capture_thread, NULL);
    pthread_create(&mlx_thread, NULL, mlx_draw_thread, NULL);

    // Wait for threads to finish (which never happens in this case)
    pthread_join(audio_thread, NULL);
    pthread_join(mlx_thread, NULL);

    // Clean up
    pthread_mutex_destroy(&buffer_mutex);
    return 0;
}

