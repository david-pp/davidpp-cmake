# davidpp-cmake
David's cmake examples &amp; templates.

**example ：cmake的特性示例**

- example-externs - 包含外部库的几种方式（Submodule、Download）
- example-find-package - find_package的用法
- example-modern-cmake - 现代cmake的一个简单工程组织
- example-prebuilt - 预先构建好的库使用

**demo ：测试用的项目**

**template ：项目模板**

- TODO：simple

## 命令行

无论是生成的make、ninja还是IDE，都可以使用cmake进行构建。

```bash
# -S指定源码路径 -B指定构建路径
cmake -S . -B build
# 构建所有
cmake --build build
# 构建指定Target
cmake --build build --target test

# 使用clang编译器
CC=clang CXX=clang++ cmake -S . -B build

# 指定Generator
cmake --help  # 查看支持那些
cmnake -G"My Tool" ..

# 构建时的详细信息（下面任何一个都可以）
cmake --build build -v
VERBOSE=1 make
make VERBOSE=1

# 调试追踪cmake文件的执行过程
cmake --trace-source="CMakeLists.txt"

# 常用选项
cmake -DCMAKE_BUILD_TYPE=Release/Debug/...  # 指定构建类型
cmake -DCMAKE_INSTALL_PREFIX=install       # 指定install路径
cmake -DBUILD_SHARED_LIBS=ON/OFF          # 是否构建动态库
cmake -DBUILD_TESTING=ON/OFF              # 是否构建单元测试

```

## 简单例子

```cmake
cmake_minimum_required(VERSION 3.14...3.18)
project(MyProject
  VERSION 1.0
  DESCRIPTION "Very nice project"
  LANGUAGES CXX)
add_executable(myexample simple.cpp)
```

## Concepts

<https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html>

**Targets：**
- Binary Targets
    - Binary Executables
    - Binary Libary Types
        - Normal Libraies（static vs. dynamic）
        - Object Libraries
   
- Pseudo Targets
   - Imporeted Targets
   - Alias Targets
   - Interface Targets
   
**Properties：**


**Variables：**

- Local Variable
- Cached Varaiable - 被缓存的变量，可以通过cmake -DVAR=xx进行修改

```cmake
set(MY_VARIABLE "I am a variable")
set(MY_CACHE_VAR "I am a cached variable" CACHE STRING "Description")

# 下面两句等价
option(MY_OPTION "On or off" OFF) 
set(MY_OPTION OFF CACHE BOOL "On or off")
```

## CheetSheet

**Target：**

```cmake
# 可执行文件
add_executable(<name> [source1] [source2 ...])

# 例子：
add_library(archive archive.cpp zip.cpp lzma.cpp)
add_executable(zipapp zipapp.cpp)
target_link_libraries(zipapp archive)

# Normal Lib（静态 vs. 动态）
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
            
# 例子：静态库
add_library(archive STATIC archive.cpp zip.cpp lzma.cpp)
# 例子：动态库
add_library(archive SHARED archive.cpp zip.cpp lzma.cpp)

##############
# Object Lib（目标文件库，不生成archive文件）
add_library(<name> OBJECT [<source>...])

# 例子：作为obj文件集合被引用
add_library(archive OBJECT archive.cpp zip.cpp lzma.cpp)
add_library(archiveExtras STATIC $<TARGET_OBJECTS:archive> extras.cpp)
add_executable(test_exe $<TARGET_OBJECTS:archive> test.cpp)

# 例子：可以被链接到其它target
add_library(archive OBJECT archive.cpp zip.cpp lzma.cpp)

add_library(archiveExtras STATIC extras.cpp)
target_link_libraries(archiveExtras PUBLIC archive)

add_executable(test_exe test.cpp)
target_link_libraries(test_exe archive)

##############
# Interface Lib（接口库，不进行编译和生成archive文件，主要用于header-only的库）
add_library(<name> INTERFACE)

# 例子：
add_library(Eigen INTERFACE
  src/eigen.h
  src/vector.h
  src/matrix.h
  )
target_include_directories(Eigen INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include/Eigen>
)

add_executable(exe1 exe1.cpp)
target_link_libraries(exe1 Eigen)

##############
# Imported Lib（导入的库，外部构建好的库）
add_library(<name> <STATIC/SHARED/MODULE/UNKNOWN/OBJECT/INTERFACE> IMPORTED [GLOBAL])

##############
# Alias Target（Target别名，不能install和export）
add_library(<name> ALIAS <target>)
```


**Properties Commands：**

```cmake
# TARGET-ORIENTED NEW COMMANDS

# 链接依赖
target_link_libraries(<target> [VISIBILITY] ... <item>... ...)
# 包含路径
target_include_directories(<target> [VISIBILITY] <include_path>)

# 预编译定义
target_compile_definitions(<target> [VISIBILITY] <preprocessor_flags>)
# 编译器选项
target_compile_options(<target> [VISIBILITY] <compilation_flags>)
# 编译器特性支持
target_compile_features(<target> [VISIBILITY]> <feature>)
# 链接选项
target_link_options(<target> [VISIBILITY] <linker_flags>)
# 指定链接目录（不建议使用）
target_link_directories(<target> [VISIBILITY] <link_path) 

```

**Deprecated Commands：**

```cmake
# DIRECTORY-ORIENTED OLD COMMANDS（Deprecated）
include_directories(<include_path>)	
add_definitions(<preprocessor_flags>)	
set(CMAKE_CXX_FLAGS <compilation_flags>)
set(CMAKE_LINKER_FLAGS <linker_flags>)	
```

## 常用的SSnippets

### Finding a header-only library

**FindFoo.cmake：**

```cmake
INCLUDE( FindPackageHandleStandardArgs )

# Checks an environment variable; note that the first check
# does not require the usual CMake $-sign.
IF( DEFINED ENV{FOO_DIR} )
  SET( FOO_DIR "$ENV{FOO_DIR}" )
ENDIF()

FIND_PATH(
  FOO_INCLUDE_DIR
    foo/foo.h
  HINTS
    ${FOO_DIR}
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS( FOO DEFAULT_MSG
  FOO_INCLUDE_DIR
)

IF( FOO_FOUND )
  SET( FOO_INCLUDE_DIRS ${FOO_INCLUDE_DIR} )

  MARK_AS_ADVANCED(
    FOO_INCLUDE_DIR
    FOO_DIR
  )
ELSE()
  SET( FOO_DIR "" CACHE STRING
    "An optional hint to a directory for finding `foo`"
  )
ENDIF()
```

**CMakeLists.txt：**

```cmake
LIST( APPEND CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/cmake/Modules
)

FIND_PACKAGE( foo REQUIRED )
TARGET_INCLUDE_DIRECTORIES( example ${FOO_INCLUDE_DIRS} )
```

### Finding a shared object or a static library

```cmake
# FindBar.cmake
#
INCLUDE( FindPackageHandleStandardArgs )

# Checks an environment variable; note that the first check
# does not require the usual CMake $-sign.
IF( DEFINED ENV{BAR_DIR} )
  SET( BAR_DIR "$ENV{BAR_DIR}" )
ENDIF()

FIND_PATH(
  BAR_INCLUDE_DIR
    bar/bar.h
  HINTS
    ${BAR_DIR}
)

FIND_LIBRARY( BAR_LIBRARY
  NAMES bar
  HINTS ${BAR_DIR}
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS( BAR DEFAULT_MSG
  BAR_INCLUDE_DIR
  BAR_LIBRARY
)

IF( BAR_FOUND )
  SET( BAR_INCLUDE_DIRS ${BAR_INCLUDE_DIR} )
  SET( BAR_LIBRARIES ${BAR_LIBRARY} )

  MARK_AS_ADVANCED(
    BAR_LIBRARY
    BAR_INCLUDE_DIR
    BAR_DIR
  )
ELSE()
  SET( BAR_DIR "" CACHE STRING
    "An optional hint to a directory for finding `bar`"
  )
ENDIF()

# CMakeListst.txt
TARGET_LINK_LIBRARIES( example ${BAR_LIBRARIES} )
```

### Versions checks

```cmake
IF( CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.4.1" )
  MESSAGE( STATUS "This compiler version might cause problems" )
ENDIF()
```

### Detecting an operating system
```cmake
IF( APPLE )
  MESSAGE( STATUS "Running under MacOS X" )
# Watch out, for this check also is TRUE under MacOS X because it
# falls under the category of Unix-like.
ELSEIF( UNIX )
  MESSAGE( STATUS "Running under Unix or a Unix-like OS" )
# Despite what you might think given this name, the variable is also
# true for 64bit versions of Windows.
ELSEIF( WIN32 )
  MESSAGE( STATUS "Running under Windows (either 32bit or 64bit)" )
ENDIF()
```

### Detecting a compiler
```cmake
IF( CMAKE_CXX_COMPILER_ID MATCHES "GNU" )
  MESSAGE( STATUS "g++ for the win!" )
  MESSAGE( STATUS ${CMAKE_CXX_COMPILER_VERSION} )
ENDIF()

IF( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
  MESSAGE( STATUS "LLVM, yeah!" )
ENDIF()
```

### Enabling C++11 or C++14

```cmake
SET( CMAKE_CXX_STANDARD 11 )
SET( CMAKE_CXX_STANDARD_REQUIRED ON )
```


## 参考资料

**官方：**

- Tutorial : <https://cmake.org/cmake/help/latest/guide/tutorial/index.html>
- Documentation : <https://cmake.org/cmake/help/latest/>
- Books：《Mastering CMake》<https://github.com/Akagi201/learning-cmake/tree/master/docs>
- CMake Wiki：<https://gitlab.kitware.com/cmake/community>

**例子：**
- 各种模板：<https://github.com/ttroy50/cmake-examples>
- 稍微简单些的，同时包含几本书：<https://github.com/Akagi201/learning-cmake>
- Cmake中文实战教程：<https://github.com/BrightXiaoHan/CMakeTutorial>


**Modern CMake**

- [Effective Modern CMake]( <https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1>) ：不错的gist，包含两位在cppcon上分享的视频链接，值得一看
- [An Introduction to Modern CMake](<https://cliutils.gitlab.io/modern-cmake/>) ：Modern CMake详细介绍
- [More Modern CMake](<https://hsf-training.github.io/hsf-training-cmake-webpage/aio/index.html>) ：进一步介绍
- [CMake Primer](<https://llvm.org/docs/CMakePrimer.html>) ： LLVM官网上的一篇CMake入门