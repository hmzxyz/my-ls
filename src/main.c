#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  const char *path = ".";
  DIR *dir;
  int done_with_flags = 0;
  int show_all = 0;

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (!done_with_flags && strcmp(argv[i], "--") == 0) {
        done_with_flags = 1;
        continue;
      }
      if (!done_with_flags && argv[i][0] == '-') {
        if (argv[i][1] == 'a') {
          show_all = 1;
        }
      } else {
        path = argv[i];
      }
    }
  }

  dir = opendir(path);
  if (!dir) {
    perror("opendir");
    return 1;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (show_all == 1 || entry->d_name[0] != '.') {
      printf("%s\n", entry->d_name);
    }
  }

  if (closedir(dir) == -1) {
    perror("closedir");
    return 1;
  }
  return 0;
}
