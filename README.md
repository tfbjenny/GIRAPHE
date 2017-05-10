## Prerequisite

LLVM & Clang

Create a soft-link to lli

```
sudo ln -s /usr/local/opt/llvm38/bin/lli-3.8 /usr/local/bin/lli
```

## Compile & Test

```
make all
make test
```

### Hello World

Create the following `test.in` file
```
print("Hello World!");
```

Run `sh giraphe.sh test.in` in terminal

Output

```
Hello World!
```
