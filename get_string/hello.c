#include <stdio.h>
#include <stdlib.h>

typedef char *string;
typedef struct node
{
	char *str;
	struct node *next;
}
node;

char *get_string(char *prompt);
char *listtostr(node *list, size_t len);
void freelist(node *list);

int main(void)
{
	string str = get_string("What's your name? ");
	printf("Hello, %s\n", str);
	free(str);
	return 0;
}

char *get_string(char *prompt)
{
	printf("%s", prompt);
	node *list = malloc(sizeof(node *));
	if(list == NULL)
	{
		return NULL;
	}
	node *ptr = list;
	ptr->str = malloc(sizeof(char) << 3);
	if (ptr->str == NULL)
	{
		free(list);
	}
	char in;
	for (int i = 0; i < 8; i++)
	{
		in = getchar();
		ptr->str[i] = in;
		switch (in)
		{
			case '\n':
				ptr->next = NULL;
				return listtostr(list, i + 1);
			default:
				break;
		}
	}
	
	size_t t = 1, len = 8;
	char h = 1;
	// gain = t.height
	ptr->next = malloc(sizeof(node));
	if(ptr->next == NULL)
	{
		freelist(list);
	}
	ptr = ptr->next;
	ptr->str = malloc(sizeof(char) * h << 3);
	if(ptr->str == NULL)
	{
		ptr->next = NULL;
		freelist(list);
	}
	
	while (1)
	{
		for (int i = 0, max_i = (int)h << 3; i < max_i; i++, ++len)
		{
			in = getchar();
			ptr->str[i] = in;
			switch (in) {
			case '\n':
				ptr->next = NULL;
				return listtostr(list, len);
			default:
				break;
			}
		}
		ptr->next = malloc(sizeof(node));
		if(ptr->next == NULL)
		{
			freelist(list);
		}
		ptr = ptr->next;
		t++;
		switch (t >> (int)h)
		{
			case 0:
				break;
			default:
				h++;
				break;
		}
		ptr->str = malloc(sizeof(char) * h << 3);
		if(ptr->str == NULL)
		{
			ptr->next = NULL;
			freelist(list);
		}
	}
}

char *listtostr(node *list, size_t len)
{
	char *ret = malloc(sizeof(char) * len);
	if(ret == NULL)
	{
		freelist(list);
		return NULL;
	}
	for (int i = 0; i < 8; i++)
	{
		switch (list->str[i])
		{
			case '\n':
				free(list->str);
				free(list);
				ret[len] = '\0';
				return ret;
			default:
				ret[i] = list->str[i];
				break;
		}
	}
	size_t t = 1, count = 8;
	char h = 1;
	node *tmp = list->next;
	free(list->str);
	free(list);
	list = tmp;
	
	while (1)
	{
		for (int i = 0, max_i = (int)h << 3; i < max_i; i++, count++)
		{
			switch (list->str[i])
			{
				case '\n':
					free(list->str);
					free(list);
					ret[len] = '\0';
					return ret;
				default:
					ret[count] = list->str[i];
					break;
			}
		}

		tmp = list->next;
		free(list->str);
		free(list);
		list = tmp;
		t++;
		
		switch (t >> (int)h)
		{
			case 0:
				break;
			default:
				h++;
				break;
		}
	}
}

void freelist(node *list)
{
	node *tmp = list->next;
	while(list != NULL)
	{
		free(list->str);
		free(list);
		list = tmp;
		tmp = tmp->next;
	}
}
