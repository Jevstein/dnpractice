void make_next(const char *pattern, int *next) {
    int m = strlen(pattern);
    next[0] = 0;

    int i, j;
    for (i = 1, j = 0; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        } 

        if (pattern[i] == pattern[j]) {
            j++;
        }

        next[i] = j;
    }


}


int kmp_matcher(const char *text, const char *pattern, ) {
    
}