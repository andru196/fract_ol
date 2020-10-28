inline double get_color1(int iter, int maxiter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter != maxiter)
	{
		t = (double)iter / maxiter;
		r =  (int)(9 * (1 - t) * t * t * t * 255) << 16;
		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8;
		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		return (~r ^ ~g ^ ~b);
	}
	return (0);
}

inline double get_color2(int iter, int maxiter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter != maxiter)
	{
		t = (double)iter / maxiter;
		r =  (int)(9 * (1 - t) * t * t * t * 255) << 16;
		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8;
		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		return (r | g | b);
	}
	return (0);
}

__kernel void mandelbrotProcess(__global unsigned int* iterations,
								 int width, int height, double fromX, double fromY, double toX,
								 double toY, int max_iteration, double fy, double fx) {
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
	iterations[width * py + px] = get_color1(iteration, max_iteration);
}

inline double dabs_my(double n)
{
	if (n < 0)
		return (-n);
	return (n);                   
}

__kernel void burningShipProcess(__global unsigned int* iterations,
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
		y = -2 * dabs_my(x * y) + cy;
		x = xn;
		if (x * x + y * y > 4.0) {
			break;
		}
	}
	iterations[width * py + px] = get_color2(iteration, max_iteration);
}

__kernel void juliaProcess(__global unsigned int* iterations,
								 int width, int height,
								 double fromX, double fromY, double toX, double toY,
								 int max_iteration, double fy, double fx, double ky, double kx)
{
	int px = get_global_id(0) - 32;
	int py = get_global_id(1) - 32;
	if (px >= width || py >= height)
		return;
	int iteration;
	double x = fromX + px * fx;
	double y = toY - py * fy;

	for (iteration = 0; iteration < max_iteration; iteration++)
	{
		double x2 = x * x;
		double y2 = y * y;

		double xn = x2 - y2 - kx;
		y = 2 * x * y + ky;
		x = xn;
		
		if (x2 + y2 > 4.0)
			break;
	}
	iterations[width * py + px] = get_color2(iteration, max_iteration);
}