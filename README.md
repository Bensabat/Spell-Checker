TextMining Project
===

# Docker (recommanded way)

Generate executables

```bash
# TODO
```

# Configure

At the root-level:
```bash
$ bash configure

# It should create /out and /bin directories
```

# Launch (david production)

Execute the following command:
```bash
$ make
$ ./TextMiningCompiler words_perso.txt dict.bin
```

# Launch (production)

Execute the following command:
```bash
$ make
```
> Executables will be found under **bin/release**

# Launch (debug)

From Visual Studio Code, execute the default task to generate the debug configuration.
> Executables will be found under **bin/debug**

# Clean

Execute the following command:
```bash
$ make distclean
```