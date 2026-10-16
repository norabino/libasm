#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

extern size_t  ft_strlen(const char *s);
extern char    *ft_strcpy(char *dst, const char *src);
extern int     ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, void *buf, size_t count);
extern char    *ft_strdup(const char *s);
extern void    *ft_calloc(size_t nmemb, size_t size);

int main(void)
{
    printf("========== 1. FT_STRLEN ==========" "\n");
    char *test_str = "Hello world!";
    printf("C   strlen : %zu\n", strlen(test_str));
    printf("ASM ft_strlen : %zu\n\n", ft_strlen(test_str));

    printf("========== 2. FT_STRCPY ==========" "\n");
    char buf1[50];
    char buf2[50];
    printf("C   strcpy : %s\n", strcpy(buf1, test_str));
    printf("ASM ft_strcpy : %s\n\n", ft_strcpy(buf2, test_str));

    printf("========== 3. FT_STRCMP ==========" "\n");
    printf("C   strcmp : %d\n", strcmp("ABC", "ABC"));
    printf("ASM ft_strcmp : %d\n", ft_strcmp("ABC", "ABC"));
    printf("C   strcmp : %d\n", strcmp("ABC", "ABD"));
    printf("ASM ft_strcmp : %d\n\n", ft_strcmp("ABC", "ABD"));

    printf("========== 4. FT_WRITE ==========" "\n");
    errno = 0;
    ssize_t ret = ft_write(1, "Test d'ecriture : salut !\n", 26);
    printf("Retour : %zd, Errno : %d (%s)\n", ret, errno, strerror(errno));

    errno = 0;
    ret = ft_write(-1, "Test", 4);
    printf("Erreur fd (-1) -> Retour : %zd, Errno : %d (%s)\n\n", ret, errno, strerror(errno));

    printf("========== 5. FT_READ ==========" "\n");
    char read_buf[100];
    int fd = open("main.c", O_RDONLY);
    if (fd != -1)
    {
        errno = 0;
        ret = ft_read(fd, read_buf, 18);
        read_buf[ret > 0 ? ret : 0] = '\0';
        printf("Lecture reussie (%zd octets) : %s\n", ret, read_buf);
        close(fd);
    }
    errno = 0;
    ret = ft_read(-1, read_buf, 10);
    printf("Erreur fd (-1) -> Retour : %zd, Errno : %d (%s)\n\n", ret, errno, strerror(errno));

    printf("========== 6. FT_STRDUP ==========" "\n");
    char *dup = strdup("Hello world !");
    printf("C   strdup : %s\n", dup);
    free(dup);

    dup = ft_strdup("Hello world !");
    printf("ASM ft_strdup : %s\n", dup);
    free(dup);

    printf("\n");

    printf("========== 7. FT_CALLOC ==========" "\n");
    size_t nmemb = 5;
    size_t size = sizeof(int);
    int *c_arr = (int *)calloc(nmemb, size);
    int *asm_arr = (int *)ft_calloc(nmemb, size);

    if (c_arr)
    {
        printf("C   calloc(%zu, %zu) : ", nmemb, size);
        for (size_t i = 0; i < nmemb; i++)
            printf("%d ", c_arr[i]);
        printf("\n");
    }
    if (asm_arr)
    {
        printf("ASM ft_calloc(%zu, %zu) : ", nmemb, size);
        for (size_t i = 0; i < nmemb; i++)
            printf("%d ", asm_arr[i]);
        printf("\n");
    }
    if (c_arr && asm_arr)
        printf("Comparaison : %s\n", memcmp(c_arr, asm_arr, nmemb * size) == 0 ? "OK" : "DIFF");
    free(c_arr);
    free(asm_arr);

    errno = 0;
    void *ptr_overflow = ft_calloc((size_t)-1, (size_t)-1);
    printf("ASM ft_calloc debordement -> Pointeur : %p, Errno : %d (%s)\n\n", ptr_overflow, errno, strerror(errno));

    return (0);
}

//ft_strcpy qui copie les mauvais bytes (unprintable)
//ft_strdup qui duplique que le premier char