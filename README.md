Demonstration of crash with websocketpp and RStudio
===================================================

This repository demonstrates a crash with a package that uses the websocketpp C++ library along with RStudio. The goal is to understand why the crash happens, and test whether the same thing can happen when two packages have C++ namespace conflicts.


##  Getting started

RStudio uses its own copy of websocketpp, version 0.5.1.

This repository has two R packages: **wspp051**, which uses websocketpp 0.5.1, and **wspp070**, which uses websocketpp 0.7.0.

To install both:

```R
devtools::install_github("wch/wsppcrash", subdir = "wspp051")
devtools::install_github("wch/wsppcrash", subdir = "wspp070")
```

Running the code from 0.5.1 works fine (the `"Underlying Transport Error"` is expected):

```R
wspp051::get_error_message()
#> [1] "Underlying Transport Error"
```

However, running the code from 0.7.0 causes RStudio to crash (R 3.4.4, RStudio 1.2.655, Mac):

```R
wspp070::get_error_message()   ## RStudio crashes
```

If the same command is run from R in a terminal, it does not crash.


The `get_error_message` C++ function is defined [here](https://github.com/wch/wsppcrash/blob/master/wspp070/src/websocketppcrash.cpp#L8-L14).


## Using websocketpp 0.5.1 and websocketpp 0.7.0 in the terminal

If you start R in a terminal, and then run those two commands, it does not crash:

```R
wspp051::get_error_message()
#> [1] "Underlying Transport Error"
wspp070::get_error_message()
#> [1] "Underlying Transport Error"
```

I think this means that when RStudio loads its code with websocketpp 0.5.1, it does something different compared to when R loads a DLL with websocketpp 0.5.1. When RStudio does it, it causes an incompatibility with 0.7.0; when R does it, it does not cause an incompatibility.

If two packages cannot conflict with each other, it's a good thing. But I would like to understand why it's different.


## Configuration differences between websocketpp 0.5.1 vs 0.7.0

There are a few configuration differences between websocketpp 0.5.1 and 0.7.0. These changes seemed necessary to get each version to compile, although I would have preferred to not have the differences. They are:

* With 0.5.1, the package uses Boost via the BH package; with 0.7.0, the package uses Asio, with the AsioHeaders package.
* With 0.5.1, the package is compiled with C++98; with 0.7.0, the package is compiled with C++11.
