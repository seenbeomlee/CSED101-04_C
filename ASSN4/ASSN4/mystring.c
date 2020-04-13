#include <stddef.h>

int mystrlen(char *str)
{
	int i = 0;

	while (1)
	{
		if (str[i] == NULL) break;

		i++;
	}

	return i;
}

char *mystrcpy(char *toStr, char *fromStr)
{
	int i = 0;

	while (1)
	{
		if (fromStr[i] == NULL)
		{
			toStr[i] = fromStr[i];
			break;
		}

		toStr[i] = fromStr[i];
	}

	return toStr;
}

char *mystrcat(char *str1, char *str2)
{
	
	int i, j = 0;

	while (1)
	{
		if (str1[i] == NULL) break;

		i++;
	}

	while (1)
	{
		if (str2[j] == NULL)
		{
			str1[i] = str2[j];
			break;
		}

		str1[i] = str2[j];

		i++; j++;
	}

	return str1;
}

char *mystrchr(char *str, char c)
{
	int i = 0;

	while (1)
	{
		if (str[i] == NULL) return NULL;
		else if (str[i] == c) break;

		i++;
	}

	return &str[i];
}

