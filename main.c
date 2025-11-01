#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int ft_strlen(char *str);
char *ft_strcpy(char *dest, const char *src);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strdup(const char *s);
ssize_t ft_write(int fildes, const void *buf, size_t nbyte);
ssize_t ft_read(int fildes, const void *buf, size_t nbyte);

bool test_ft_strlen() {
    printf("=== TEST POUR FT_STRLEN ===\n\n");
    bool ok = true;

    if (ft_strlen("Bonjour.") != 8) ok = false;
    if (ft_strlen("123456789") != 9) ok = false;
    if (ft_strlen("Je ne sais pas quoi faire comme test.") != 37) ok = false;
    if (ft_strlen("") != 0) ok = false;

    printf(ok ? "FT_STRLEN OK ✅\n" : "FT_STRLEN NOT OK ❌\n");
    return ok;
}

bool test_ft_strcpy() {
    printf("=== TEST POUR FT_STRCPY ===\n\n");
    bool ok = true;

    char *buffer = malloc(5);
    ft_strcpy(buffer, "test");
    if (strcmp(buffer, "test") != 0) ok = false;
    free(buffer);

    char *buffer2 = malloc(8);
    ft_strcpy(buffer2, "Bonjour");
    if (strcmp(buffer2, "Bonjour") != 0) ok = false;
    free(buffer2);

    char *buffer3 = malloc(1);
    ft_strcpy(buffer3, "\0");
    if (strcmp(buffer3, "") != 0) ok = false;
    free(buffer3);

    printf(ok ? "FT_STRCPY OK ✅\n" : "FT_STRCPY NOT OK ❌\n");
    return ok;
}

bool test_ft_strcmp() {
    printf("=== TEST POUR FT_STRCMP ===\n\n");
    bool ok = true;

    if (ft_strcmp("bonjour", "bonjour") != 0) ok = false;
    if (ft_strcmp("bonjour", "bonjou") <= 0) ok = false;
    if (ft_strcmp("bonjou", "bonjour") >= 0) ok = false;
    if (ft_strcmp("", "") != 0) ok = false;
    if (ft_strcmp("", "bonjour") >= 0) ok = false;
    if (ft_strcmp("bonjou", "") <= 0) ok = false;

    printf(ok ? "FT_STRCMP OK ✅\n" : "FT_STRCMP NOT OK ❌\n");
    return ok;
}

bool test_ft_write() {
    printf("=== TEST POUR FT_WRITE ===\n\n");
    bool ok = true;
    ssize_t ret;
    errno = 0;

    // stdout
    ret = ft_write(1, "test de write\n", 14);
    if (ret != 14) ok = false;

    // fichier valide
    int fd = open("testwr1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return false;
    }
    errno = 0;
    ret = ft_write(fd, "ecriture dans un fichier\n", 26);
    if (ret != 26 || errno != 0) ok = false;
    close(fd);

    // fd invalide
    errno = 0;
    ret = ft_write(4000000000, "test", 4);
    if (ret != -1 || errno == 0) ok = false;

    // fd fermé
    fd = open("testwr1.txt", O_WRONLY);
    close(fd);
    errno = 0;
    ret = ft_write(fd, "fermé", 6);
    if (ret != -1 || errno == 0) ok = false;

    printf(ok ? "FT_WRITE OK ✅\n" : "FT_WRITE NOT OK ❌\n");
    return ok;
}

bool test_ft_read() {
    printf("=== TEST POUR FT_READ ===\n\n");
    bool ok = true;
    char buf[32] = {0};
    ssize_t ret;

    // Fichier valide
    int fd = open("testwr1.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return false;
    }
    errno = 0;
    ret = ft_read(fd, buf, 20);
    if (ret < 0 || errno != 0) ok = false;
    close(fd);

    // fd invalide
    errno = 0;
    ret = ft_read(4000000000, buf, 20);
    if (ret != -1 || errno == 0) ok = false;

    // fd fermé
    fd = open("testwr1.txt", O_RDONLY);
    close(fd);
    errno = 0;
    ret = ft_read(fd, buf, 20);
    if (ret != -1 || errno == 0) ok = false;

    printf(ok ? "FT_READ OK ✅\n" : "FT_READ NOT OK ❌\n");
    return ok;
}

bool test_ft_strdup() {
    printf("=== TEST POUR FT_STRDUP ===\n\n");
    bool ok = true;

    char *dup = ft_strdup("Hello");
    if (strcmp(dup, "Hello") != 0) ok = false;
    free(dup);

    dup = ft_strdup("");
    if (strcmp(dup, "") != 0) ok = false;
    free(dup);

    printf(ok ? "FT_STRDUP OK ✅\n" : "FT_STRDUP NOT OK ❌\n");
    return ok;
}

int main(void) {
    bool result = true;

    if (!test_ft_strlen()) result = false;
    printf("\n");
    if (!test_ft_strcpy()) result = false;
    printf("\n");
    if (!test_ft_strcmp()) result = false;
    printf("\n");
    if (!test_ft_write()) result = false;
    printf("\n");
    if (!test_ft_read()) result = false;
    printf("\n");
    if (!test_ft_strdup()) result = false;

    printf("\n====================\n");
    printf(result ? "ALL TESTS OK ✅\n" : "NOT OK ❌\n");
    return 0;
}
