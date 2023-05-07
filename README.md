# MES

## Compiling

After cloning the repository, do the following:

```mkdir build```
```cmake ..```
```make```

It will generate MES executable inside build folder.

Use:
```./MES``` - to run the program
```./MES teste``` - to run the test

## Dependencies

Opcua library

```git clone https://github.com/open62541/open62541.git```
```cd open62541```
```git submodule update --init --recursive```
```mkdir build && cd build```
```cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo -DUA_NAMESPACE_ZERO=FULL ..```
```make```
```sudo make install```
```sudo /sbin/ldconfig -v```
