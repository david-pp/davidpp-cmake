libx : 
- 静态库

app : 
- dlopen动态加载plugin_1.so
- 链接libx_v1.a

plugin :
- 动态库
- 链接libx_v2.a

结果：
- app在没有用到libx提供的功能时，使用的plugin的libx_v2.a
- app在使用libx的符号时，使用的app自己的libx_v1.a

静态库链接：
- 链接阶段，用到的符号所在的编译单元全部链接进去(.o)，未定义的不管