int mystrcmp(const char *str1, const char *str2) {
    while (*str1 == *str2 && *str1 != '\0') {
        ++str1;
        ++str2;
    }
    return (unsigned char) *str1 - (unsigned char) *str2;
}
