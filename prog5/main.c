#include "main.h"


unsigned char *reflect(unsigned char *data, int x, int y, int n) {
    unsigned char tmp;
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x / 2; ++j) {
            for (int l = 0; l < n; ++l) {
                tmp = data[i * x * n + j * n + l];
                data[i * x * n + j * n + l] = data[(i + 1) * x * n - n - j * n + l];
                data[(i + 1) * x * n - n - j * n + l] = tmp;
            }
        }
    }
    return data;
}

int convert(char *input, char *output) {
    int x,y,n;
    unsigned char *data = stbi_load(input, &x, &y, &n, 0);
    if (!data)
        return -1;
	int t = clock();
    data = reflectasm(data, x, y, n);
	t = clock() - t;
    if (!stbi_write_jpg(output, x, y, n, data, 100))
        return -2;
    stbi_image_free(data);
    return t;
}

int main(int argc, char *argv[]) {
    int r;
    if (argc != 3) {
        printf("Wrong number of parameters: first must be input image, second must be output image\n");
    }
    char *input_name = argv[1];
    char *output_name = argv[2];
    r = convert(input_name, output_name);
    if (r == -1) {
        printf("Something wrong with your input file\n");
		return 1;
    }
    else if (r == -2) {
    	printf("Something wrong with your output file\n");
    	return 2;
	}
	printf("time spent %d\n", r);
    return 0;
}