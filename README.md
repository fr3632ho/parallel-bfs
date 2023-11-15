# parallel-bfs

Parallel BFS project. This project is intended to illustrate a possible approach of parallelizing the _Breadth-First Search_ algorithm using _pennants_.

# Building and installing

Build the project by navigating to root and using the following commands

```
$ cmake --preset=dev
$ cmake --build --preset=dev

```

### Tests

Test coverage is implemented for the `bag`, `pennant` and various `bfs` implementations in the repository.
To run the test after building you can use the following command

```
$ ctest --preset=dev
```

# Contributing

See the [CONTRIBUTING](CONTRIBUTING.md) document.

# Licensing

<!--
Please go to https://choosealicense.com/licenses/ and choose a license that
fits your needs. The recommended license for a project of this type is the
GNU AGPLv3.
-->
