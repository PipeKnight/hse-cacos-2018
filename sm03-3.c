int bitcount(STYPE value) {
    int result = 0;
    UTYPE uns_value = value;
    while (uns_value) {
        result += uns_value & 1;
        uns_value >>= 1;
    }
    return result;
}
