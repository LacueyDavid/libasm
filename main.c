#include <stdio.h>
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

void test_ft_strlen(){
  printf("TEST POUR FT_STRLEN:\n\n");
  printf("Result = %d, expected = 8\n", ft_strlen("Bonjour."));
  printf("Result = %d, expected = 9\n", ft_strlen("123456789"));
  printf("Result = %d, expected = 37\n", ft_strlen("Je ne sais pas quoi faire comme test."));
  printf("Result = %d, expected = 0\n", ft_strlen(""));

  return ;
}

void test_ft_strcpy(){
  printf("TEST POUR FT_STRCPY:\n\n");

  char* buffer = malloc(5 * sizeof(char));
  ft_strcpy(buffer, "test");
  printf("Result = %s, Expected = test\n", buffer);
  free(buffer);

  char* buffer2 = malloc(8 * sizeof(char));
  ft_strcpy(buffer2, "Bonjour");
  printf("Result = %s, Expected = Bonjour\n", buffer2);
  free(buffer2);

  char* buffer3 = malloc(1 * sizeof(char));
  ft_strcpy(buffer3, "\0");
  printf("Result = \"%s\", Expected = \"\"\n", buffer3);
  free(buffer3);
}

void test_ft_strcmp(){
  printf("TEST POUR FT_STRCMP:\n\n");
  printf("Result = %d, Expected = 0\n", ft_strcmp("bonjour", "bonjour"));
  printf("Result = %d, Expected = positive value\n", ft_strcmp("bonjour", "bonjou"));
  printf("Result = %d, Expected = negative value\n", ft_strcmp("bonjou", "bonjour"));
  printf("Result = %d, Expected = 0\n", ft_strcmp("", ""));
  printf("Result = %d, Expected = negative value\n", ft_strcmp("", "bonjour"));
  printf("Result = %d, Expected = positive value\n", ft_strcmp("bonjou", ""));



}

void test_ft_write() {
    printf("=== TEST POUR FT_WRITE ===\n\n");

    ssize_t ret;
    errno = 0;

    // 1️⃣ Écriture sur stdout
    printf("[1] Écriture sur stdout :\n");
    ret = ft_write(1, "test de write\n", 14);
    printf(" → Result = %ld, Expected = 14\n", ret);
    printf(" → errno = %d (%s)\n\n", errno, strerror(errno));

    // 2️⃣ Écriture dans un fichier valide
    int fd = open("testwr1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }

    errno = 0;
    ret = ft_write(fd, "ecriture dans un fichier\n", 26);
    close(fd);
    printf("[2] Écriture dans un fichier valide :\n");
    printf(" → Result = %ld, Expected = 26\n", ret);
    printf(" → errno = %d (%s)\n\n", errno, strerror(errno));

    // 3️⃣ Mauvais descripteur (fd invalide)
    errno = 0;
    ret = ft_write(4000000000, "test", 4);
    printf("[3] Écriture avec fd invalide (4000000000) :\n");
    printf(" → Result = %ld, Expected = -1\n", ret);
    printf(" → errno = %d (%s)\n\n", errno, strerror(errno));

    // 4️⃣ Descripteur fermé
    fd = open("testwr1.txt", O_WRONLY);
    close(fd);
    errno = 0;
    ret = ft_write(fd, "fermé", 6);
    printf("[4] Écriture sur fd fermé :\n");
    printf(" → Result = %ld, Expected = -1\n", ret);
    printf(" → errno = %d (%s)\n\n", errno, strerror(errno));

    // 5️⃣ Buffer invalide (pointeur nul ou interdit)
    errno = 0;
    ret = ft_write(1, (void*)0x1, 10);
    printf("[5] Écriture avec buffer invalide :\n");
    printf(" → Result = %ld, Expected = -1\n", ret);
    printf(" → errno = %d (%s)\n\n", errno, strerror(errno));
}

void test_ft_read() {
    printf("=== TEST POUR FT_READ ===\n\n");

    char bytesread[10] = {0};
    char str[21] = {0};
    ssize_t ret;

    // 1️⃣ Lecture standard sur stdin
    printf("[1] Lecture sur stdin (tape quelque chose et ENTER)\n");
    ret = ft_read(0, bytesread, 10);
    printf("Result = %ld, Expected ≤ 10\n", ret);
    printf("Buffer lu = \"%s\"\n", bytesread);

    // 2️⃣ Lecture sur un fichier existant
    int fd = open("testwr1.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    errno = 0;
    ret = ft_read(fd, str, 20);
    close(fd);
    printf("[2] Lecture sur fichier valide\n");
    printf("Result = %ld, Expected = 20 ou moins\n", ret);
    printf("Buffer lu = \"%s\"\n", str);
    printf("errno = %d (%s)\n\n", errno, strerror(errno));

    // 3️⃣ Test avec un mauvais descripteur
    errno = 0;
    ret = ft_read(4000000000, str, 20);
    printf("[3] Lecture sur fd invalide (4000000000)\n");
    printf("Result = %ld, Expected = -1\n", ret);
    printf("errno = %d (%s)\n\n", errno, strerror(errno));

    // 4️⃣ Test avec un fd fermé
    fd = open("testwr1.txt", O_RDONLY);
    close(fd);
    errno = 0;
    ret = ft_read(fd, str, 20);
    printf("[4] Lecture sur fd fermé\n");
    printf("Result = %ld, Expected = -1\n", ret);
    printf("errno = %d (%s)\n\n", errno, strerror(errno));
}

void test_ft_strdup(){
  printf("TEST POUR FT_STRDUP:\n\n");
  char *str = ft_strdup("Hello");
  printf("%s\n", str);
  free(str);

  char *str2 = ft_strdup("");
  printf("%s\n", str2);
  free(str2);

}

int main(void) {
  printf("\n");
  test_ft_strlen();
  printf("\n");
  test_ft_strcpy();
  printf("\n");
  test_ft_strcmp();
  printf("\n");
  test_ft_write();
  printf("\n");
  test_ft_read();
  printf("\n");
  test_ft_strdup();

  return 0;
}
