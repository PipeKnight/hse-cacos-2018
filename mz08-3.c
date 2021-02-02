#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dlfcn.h>

void create_lib(const char *func_str) {
    int fd = open("my_func.c", O_WRONLY | O_TRUNC | O_CREAT, 0600);
    FILE * file = fdopen(fd, "w");
    char str[] = "#include <math.h>\n"
                "double my_func(double x) {\n"
                "    return";
    fprintf(file, "%s %s;\n}\n", str, func_str);
    fclose(file); 
    if (fork() == 0) {
        execlp("gcc", "gcc", "my_func.c", "-shared", "-lm", "-o", "my_func.so", "-fPIC", NULL);
        _exit(127);
    }
    wait(NULL);
    return;
}

int main(int argc, char *argv[]) {
    double left = strtod(argv[1], NULL);
    double right = strtod(argv[2], NULL);
    int n = atoi(argv[3]);
    create_lib(argv[4]);
    void *handle = dlopen("./my_func.so", RTLD_LAZY);
    void *func = dlsym(handle, "my_func");
    double dx = (right - left) / n;
    double area = 0;
    for (int i = 0; i != n; ++i) {
        double x_i = left + i * dx;
        area += ((double (*)(double)) func)(x_i) * dx;
    }
    printf("%.10g\n", area);
    dlclose(handle);
    return 0;
}
