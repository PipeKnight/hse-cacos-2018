int bitcount(STYPE value) {
    int result = 0;
    UTYPE nval = value;
    while (nval > 0) {
        result += nval & 1;
        nval >>= 1;
    }
    return result;
}
