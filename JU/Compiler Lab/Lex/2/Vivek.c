int main()
{
    /* We can have multiline comments
       They will be ignored automatically */
    int a = 0, b = 5;

    char c = 'a';
    char str = "hello";

    float f = 22.5E-3;
    int hex = 0xffee;
    
    for(int i=0; i < 100; i++)
        return i; // We should not return

    return 0;
}
