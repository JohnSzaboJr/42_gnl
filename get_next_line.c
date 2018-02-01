#include "./libft/libft.h"
#include "get_next_line.h"
//
#include <stdio.h>

static char	*ft_read_file(const int fd, char *str, int *end)
{
  int size;

  size = 0;
  if (!(size = read(fd, str, BUFF_SIZE)))
    *end = 1;
  str[size] = '\0';
  return (str);
}

static char	*ft_store_line(const int fd, int *end, char *str)
{
  char	*new;
  //  char	*saved;
  int	j;

  j = 0;
  if (!(new = ft_strnew(BUFF_SIZE)))
    return (NULL);
  if (!str)
    {
    if (!(str = ft_strnew(BUFF_SIZE)))
      return (NULL);
    str = ft_read_file(fd, str, end);
    }
  while (str[j] != '\n' && !*end)
    {
      j++;
      if (!str[j])
	{
	  //	  printf("%s\n", str);
	  new = ft_read_file(fd, new, end);
     	  if (!(str = ft_strjoin(str, new)))
     	    return (NULL);
	  //	  ft_strdel(&str);
	  //	  str = ft_strnew(ft_strlen(saved));
	  //	  str = ft_strcpy(str, saved);
	  //	  ft_strdel(&saved);
	}
    }
  ft_strdel(&new);
  if (str[ft_strlen(str) - 1] == '\n')
    str[ft_strlen(str) - 1] = '\0';
  return (str);
}

int	get_next_line(const int fd, char **line)
{
  static t_list *list;
  t_list	*node;
  t_list	*prev;
  int		end;
  int		i;

  end = 0;
  i = 0;
  node = NULL;
  prev = NULL;
  //  if (list)
  //    {
  //      printf("str: ");
  //      printf("%s\n", list->content);
  //    }
  if (list)
    node = list;
  ERROR(BUFF_SIZE < 1 || fd < 0 || line == NULL);
  while (list)
    {
      if (list->next && (list->next->content_size == (size_t)fd))
	prev = list;
      if (list->content_size == (size_t)fd)
	break ;
      list = list->next;
    }
  if (!list)
    {
      list = ft_lstnew(NULL, 0);
      list->content_size = fd;
      if (node)
	ft_lstadd(&node, list);
      node = list;
    }
  list->content = ft_store_line(fd, &end, list->content);
  if (end && !(((char *)(list->content))[0]))
    {
      *line = NULL;
      return (0);
    }
  while (((char *)(list->content))[i] != '\n' && ((char *)(list->content))[i] != '\0')
    i++;
  ERROR(!(*line = ft_strnew(i)));
  *line = ft_strncpy(*line, list->content, i);
  list->content = (char *)ft_memmove
      (list->content, (list->content) + i + 1, ft_strlen(list->content) - i + 1);
  if (!(((char *)(list->content))[0]))
      {
        if (node == list)
  	{
	  node = node->next;
  	  free(list);
  	  list = node;
  	  return (1);
  	}
        else
       	{
      	  prev->next = list->next;
       	  free(list);
       	  list = NULL;
       	}
      }
  list = node;
  return (1);

  // multiple fd
  // big files
  // segfaults the 42 tests... 
  // leaks
}
