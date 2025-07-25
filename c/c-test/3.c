int lengthOfLongestSubstring(char *str)
{
    int n = strlen(str);

    if (!n)
        return 0;

    int L_len = 1;
    int C_len = 1;

    int P_ind, i;
    int visited[256];


    memset(visited, -1, sizeof(int) * 256);
    visited[str[0]] =
        0;
    for (i = 1; i < n; i++)
    {
        P_ind = visited[str[i]];
        if (P_ind == -1 || i - C_len > P_ind)
            C_len++;

        else
        {
            if (C_len > L_len)
                L_len = C_len;
            C_len = i - P_ind;
        }
        visited[str[i]] = i;
    }
    if (C_len > L_len)
        L_len = C_len;
    return L_len;
}

int lengthOfLongestSubstring(char *s)
{
    int cur_max = 0, max = 0;
    int counter[255];
    int end = 0;

    memset(counter, 0, sizeof(int) * 255);
    while (end < strlen(s))
    {
        if (counter[s[end]] == 0)
        {
            counter[s[end]]++;
            end++;
            cur_max++;
        }
        else
        {
            char c = s[end];
            memset(counter, 0, 255 * sizeof(int));
            if (cur_max >= max)
                max = cur_max;
            cur_max = 0;
            while (s[end - 1] != c) end--;
        }
    }
    if (cur_max >= max)
        max = cur_max;
    return max;
}
