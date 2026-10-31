main()
{
	extrn putchar, char;
	auto i, s;
	i = 0;
	s = "Hello, World!\n";
	while (char(s, i))
	{
		putchar(char(s, i));
		i++;
	}
}
