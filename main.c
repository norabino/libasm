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
    ssize_t ret = ft_write(1, "Test d'ecriture : salut !\n", 32);
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
        ret = ft_read(fd, read_buf, 20);
        read_buf[ret > 0 ? ret : 0] = '\0';
        printf("Lecture reussie (%zd octets) : %s\n", ret, read_buf);
        close(fd);
    }
    errno = 0;
    ret = ft_read(-1, read_buf, 10);
    printf("Erreur fd (-1) -> Retour : %zd, Errno : %d (%s)\n\n", ret, errno, strerror(errno));

    printf("========== 6. FT_STRDUP ==========" "\n");
    char *dup = ft_strdup("Hello world !");
    printf("ft_strdup : %s\n", dup);
    free(dup);
    printf("\n");

    printf("========== 7. FT_CALLOC ==========" "\n");
    int *arr = (int *)ft_calloc(5, sizeof(int));
    if (arr)
    {
        printf("calloc(5, sizeof(int)) [0, 0, 0, 0, 0] : ");
        for (int i = 0; i < 5; i++)
            printf("%d ", arr[i]);
        printf("\n");
        free(arr);
    }

    errno = 0;
    void *ptr_overflow = ft_calloc((size_t)-1, (size_t)-1);
    printf("Debordement calloc -> Pointeur : %p, Errno : %d (%s)\n\n", ptr_overflow, errno, strerror(errno));

    return (0);
}