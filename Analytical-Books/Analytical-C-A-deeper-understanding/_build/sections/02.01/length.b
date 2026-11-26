/* length.b: the number of characters in a string, in B */
length(s) {
    auto n;
    n = 0;
    while (char(s, n) != '*e')
        n++;
    return (n);
}
