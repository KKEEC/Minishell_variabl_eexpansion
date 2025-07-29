int ft_isspace(const char c)
{
    if ((c >= 9 && c <= 13) || c == 32)
        return (1);
    return (0);
}

int ft_isspecialchar(const char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    return (0);
}