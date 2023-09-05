# xnqsbar
xnqsbar is a configurable, lightweight and ultra-modular status bar for dwm written in C++.
![image preview](https://i.imgur.com/rYbpYAK.png)

# Building
You can easily build xnqsbar by compiling main.cxx and module_loader.cxx together.

Example for GCC:

`g++ src/main.cxx src/module_loader.cxx -o main -O2`

# Modules
xnqsbar is built on modules and by default it will have none. For example, you can have a module for CPU usage, a module for RAM usage, a module for date, a module for time etc.

## Building and using modules
### Building modules
For each module you want to use, you will have to compile its .cxx file into a shared library (.so) file.
This is how you compile the CPU module using GCC:

```
g++ -fPIC -O2 -c src/modules/cpu/cpu.cxx -o src/modules/cpu/cpu.o
g++ -shared src/modules/cpu/cpu.o -o src/modules/cpu/cpu
```
### Using modules
You simply move its shared library file into `~/.config/xnqsbar/modules/`.

### Changing order in which modules are displayed
Let's say you have modules `cpu`, `ram` and `swap` in `~/.config/xnqsbar/modules/`. xnqsbar will display `cpu`, `ram` and `swap` in alphabetical/lexicographical order.
If you want to print `swap`, `ram` and `cpu` in that order, you can rename the modules as follows:

* `000-swap`
* `001-ram`
* `002-cpu`


## Creating your own modules
An xnqsbar module consists of a function:

```
extern "C" {   
void get_info(char* dest) {
    // do things here
}
}
```

that returns its output through the character array dest.
