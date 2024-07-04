#include "../includes/minishell.h"

static char *line_read = (char *)NULL;
char * rl_gets() {
  if (line_read) {
    free(line_read);
    line_read = (char *)NULL;
  }
  line_read = readline("prompt> ");
  if (line_read && *line_read) {
    add_history(line_read);
  }
  return (line_read);
}

int main() {
  char *line;
  while ((line = rl_gets())) {
    printf("Got: %s\n", line);
  }
  return 0;
}
