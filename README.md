# NanoKiosk

## Building the UI

###### install Qt to your system

Download Qt 6 for your desktop using the online installer, and place it at
a location of your choice.

###### generate the build system

```
cmake \
-B./build \
-H./ -DCMAKE_PREFIX_PATH=/your/path/to/qt/6.0.0/clang_64/ \
-DCMAKE_EXPORT_COMPILE_COMMANDS=YES
```

###### run the build command

```
make -C build
```

###### Generate compile commands if using CCLS code completion

```
cp build/compile_commands.json ./
```


###### run the UI app

```
./build/nanokiosk
```

