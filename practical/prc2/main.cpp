#include <iostream>

int main() {
    unsigned long src[] = {1, 2, 3, 4, 5};
    unsigned long dst[5];
    int i, m, n = sizeof(src);
    unsigned long *wdst = dst;  // текущая позиция в буфере назначения
    unsigned long *wsrc = src;  // текущая позиция в источнике
    unsigned char *cdst, *csrc;

    for (i = 0, m = n / sizeof(src[0]); i < m; i++)  // копируем основную часть блоками по 4 или 8 байт
        *(wdst++) = *(wsrc++);                     // (в зависимости от платформы)

    cdst = (unsigned char *) wdst;
    csrc = (unsigned char *) wsrc;

    for (i = 0, m = n % sizeof(long); i < m; i++)             // остаток копируем побайтно
        *(cdst++) = *(csrc++);
    for (int i = 0; i < 5; ++i) {
        std::cout << dst[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
