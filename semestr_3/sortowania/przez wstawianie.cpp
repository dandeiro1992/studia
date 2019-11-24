void sort_wstawianie(int tab[], int rozmiar)
{
	int x, i, j;
	for(j=n-2;j>=0;j--)
	{
		x = tab[j];
		i = j + 1;
		while((i < rozmiar) && (x > tab[i]))
		{
			tab[i - 1] = tab[i];
			i++;
		}
		tab[i - 1] = x;
	}
}

