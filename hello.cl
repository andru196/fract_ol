__kernel void mandelbrotProcess(__global unsigned int* iterations,
                                 int width, int height,
                                 double fromX, double fromY, double toX, double toY, int max_iteration) {
    int px = get_global_id(0);
    int py = get_global_id(1);
    if (px >= width || py >= height) return;

    double x0 = fromX + px * (toX - fromX) / width;
    double y0 = fromY + py * (toY - fromY) / height;

    double fx = (toX - fromX) / (width - 1);
    double fy = (toY - fromY) / (height - 1);

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
    iterations[width * py + px] = iteration;
}
