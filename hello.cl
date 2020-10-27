__kernel void mandelbrotProcess(__global unsigned int* iterations,
                                 int width, int height,
                                 double fromX, double fromY, double toX, double toY, int max_iteration, double fy, double fx) {
    int px = get_global_id(0) - 32;
    int py = get_global_id(1) - 32;
    if (px >= width || py >= height) return;

    double cy = toY - py * fy;
    double cx = fromX + px * fx;

    int iteration;
    double x = 0.0f;
    double y = 0.0f;
    for (iteration = 0; iteration < max_iteration; iteration++) {
        double xn = x * x - y * y + cx;
        y = 2 * x * y + cy;
        x = xn;
        if (x * x + y * y > 4.0) {
            break;
        }
    }
    double it = iteration;
    double t = it / max_iteration;
    int r =  (int)(9 * (1 - t) * t * t * t * 255) << 16;
    int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8;
    int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    int c = r | g | b;

    iterations[width * py + px] = c;
}
