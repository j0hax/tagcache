# tagcache

A tiny C program to write a [CACHEDIR.TAG](https://bford.info/cachedir/) file, commonly used for backup applications.

## Usage

```console
$ tagcache -h
Usage: tagcache [-hs] [DIRECTORIES]
Tags a directory as a cache for backup programs.

-h      print this help message
-s      silent mode

If no directories are specified, tagcache will use the current working directory.
For information about cache directory tags, see https://bford.info/cachedir/
```

## Compile and Install

`gcc` and `make` are required.

Standard procedure:
1. Run `make` to compile, or
2. `make install` to compile and move the binary file to the `$PREFIX`
