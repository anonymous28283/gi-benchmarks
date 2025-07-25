





uint64_t sdbm(const char* s)
{
    uint64_t hash = 0;
    size_t i = 0;
    while (s[i] != '\0')
    {
        hash = s[i] + (hash << 6) + (hash << 16) - hash;
        i++;
    }
    return hash;
}


void test_sdbm()
{
    assert(sdbm("Hello World") == 12881824461405877380U);
    assert(sdbm("Hello World!") == 7903571203300273309);
    assert(sdbm("Hello world") == 15154913742888948900U);
    assert(sdbm("Hello world!") == 15254999417003201661U);
    printf("Tests passed\n");
}




int main()
{
    test_sdbm();
    return 0;
}
