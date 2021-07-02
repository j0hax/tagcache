#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAGNAME "CACHEDIR.TAG"
#define HEADER "Signature: 8a477f597d28d172789f06886806bc55\n"

#define NULLOUT "/dev/null"

int write_tag(char* path) {
  /* Get the full file path */
  char filename[PATH_MAX];
  char* dir = realpath(path, NULL);
  sprintf(filename, "%s/%s", dir, TAGNAME);

  free(dir);

  FILE* f = fopen(filename, "w");

  if (f == NULL) {
    /* File not created, so exit */
    fprintf(stderr, "Error: unable to write %s to '%s': %s\n", TAGNAME, dir,
            strerror(errno));
    return EXIT_FAILURE;
  }

  /* Write file contents */
  fputs(HEADER, f);
  fputs("# This file was created by tagcache:\n", f);
  fputs("#\thttps://github.com/j0hax/tagcache\n", f);
  fputs("# For information about cache directory tags, see:\n", f);
  fputs("#\thttps://bford.info/cachedir/", f);

  fclose(f);

  printf("Tagged '%s' as a cache directory\n", path);

  return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
  char c;
  while ((c = getopt(argc, argv, "hs")) != -1) {
    switch (c) {
      case '?':
      case 'h':
        puts("Usage: tagcache [-hs] [DIRECTORIES]");
        puts("Tags a directory as a cache for backup programs.\n");
        puts("-h\tprint this help message");
        puts("-s\tsilent mode\n");
        puts(
            "If no directories are specified, tagcache will use the current "
            "working directory.");
        puts(
            "For information about cache directory tags, see "
            "https://bford.info/cachedir/");
        exit(EXIT_SUCCESS);
      case 's':
        /* Simply redirect to the OS's null file */
        if (freopen(NULLOUT, "w", stdout) == NULL) {
          perror("Could not redirect to " NULLOUT);
          exit(EXIT_FAILURE);
        }
        break;
    }
  }

  /* If no argument is provided, use the current directory. Otherwise, try to
   * mark each provided directory. */
  if (optind >= argc) {
    write_tag(".");
  } else {
    for (int i = optind; i <= argc - optind; i++) {
      write_tag(argv[i]);
    }
  }

  exit(EXIT_SUCCESS);
}
