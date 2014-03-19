rubygl
======

A little experiment in binding C/C++ to Ruby. Allows access to OpenGL using SDL as a middleware to simplify window handling.

Building
------

To build the extension, first generate a makefile using the extconf.rb file. If everything is OK, you should be able to run the makefile and generate the shared library. At the time of writing, this is working OK on Linux.

```
ruby extconf.rb
make
```

If the library cannot be loaded, you may need to add your lib path to RUBYLIB.


