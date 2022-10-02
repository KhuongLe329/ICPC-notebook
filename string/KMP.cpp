scanf("%s\n", &t[1]);
scanf("%s\n", &s[1]);
int j;
j = next[1] = 0;
for(int i = 2; s[i]; ++i) {
    while (j > 0 && s[j+1] != s[i]) j = next[j];
    if (s[j+1] == s[i]) ++j;
    next[i] = j;
}

j = 0;
for(int i = 1; t[i]; ++i) {
    while (j > 0 && s[j+1] != t[i]) j = next[j];
    if (s[j+1] == t[i]) ++j;

    if (s[j+1] == 0) { // Het xau s
        printf("%d ", i - j + 1);
        j = next[j];
    }
}
