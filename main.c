#include <unistd.h>
#include <stdarg.h>

void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[32];
    char *str;
    int num;
    unsigned int unum;
    char ch;

    while (*format) {
        if (*format != '%') {
            write(STDOUT_FILENO, format, 1);
            format++;
            continue;
        }

        format++;
        switch (*format) {
            case 's':
                str = va_arg(args, char *);
                while (*str) {
                    write(STDOUT_FILENO, str++, 1);
                }
                break;
            case 'd':
                num = va_arg(args, int);
                if (num < 0) {
                    write(STDOUT_FILENO, "-", 1);
                    num = -num;
                }
                int i = 0;
                do {
                    buffer[i++] = '0' + (num % 10);
                    num /= 10;
                } while (num > 0);
                while (i > 0) {
                    write(STDOUT_FILENO, &buffer[--i], 1);
                }
                break;
            case 'u':
                unum = va_arg(args, unsigned int);
                i = 0;
                do {
                    buffer[i++] = '0' + (unum % 10);
                    unum /= 10;
                } while (unum > 0);
                while (i > 0) {
                    write(STDOUT_FILENO, &buffer[--i], 1);
                }
                break;
            case 'c':
                ch = (char)va_arg(args, int);
                write(STDOUT_FILENO, &ch, 1);
                break;
            case '%':
                write(STDOUT_FILENO, "%", 1);
                break;
        }
        format++;
    }

    va_end(args);
}

int main() {
    my_printf("Hello, %s! The answer is %d, or %u in unsigned. Char: %c%%\n", 
              "world", -42, 42, 'A');
    return 0;
}
