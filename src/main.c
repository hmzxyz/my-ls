#include <dirent.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  const char *path = ".";
  DIR *dir;
  if (argc > 1) {
    path = argv[1];
  }

  dir = opendir(path);
  if (!dir) {
    perror("opendir");
    return 1;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] != '.') {
      printf("%s\n", entry->d_name);
    }
  }

  if (closedir(dir) == -1) {
    perror("closedir");
    return 1;
  }
  return 0;
}
