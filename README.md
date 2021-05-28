# FreeCircos
[![wakatime](https://wakatime.com/badge/github/Zeffiretti/FreeCircos.svg)](https://wakatime.com/badge/github/Zeffiretti/FreeCircos)
## Summary
To Develop A Program for Painting Circos Figure.
## Platform & Version

- Qt5: > 5.12
- Platform: Win32
- cmake: >=3.1.0
- Build Toolchain: msvc x64| mingw64

## TODO List:
1. ~~图片分辨率过低~~
2. 当只有一个基因or一个category时，仍然有gap
3. ~~`global setting` 界面不随程序关闭而关闭（程序关闭 `global setting` 还在）~~
4. ~~`trackarrow`采样率过低~~
5. ~~`gene name label`信息会被箭头覆盖,有没有可能弄成这个层级可以被用户调整？~~
6. 这左中右3个框有没有可能可以拖动？ 就是比如我把中间部分拖大一点之类的？
7. ~~能否弄个如果打开文件格式有问题 弹个框报错一下，不要直接崩溃?~~
8. ~~`Backbone`, `Trackarrow` 和 `link` 也都加个勾选框 可以选择是否隐藏吧.~~
9. ~~这个选择颜色选项这里加个边框吧，都看不出这是按钮了，然后这个黑色这个有木有啥解决办法？ 已经看不到strike字了~~
10. ~~`link`界面 这里`ColFun` 没用就删掉吧（突然发现是有用的）
然后当导入的是带`Stre` 参数的`link`   默认把 `thermometer` 那勾上 根据下面5个颜色框去调颜色
然后导入没有`Stre` 参数的时候， 默认勾`fixed color` 那里  ，然后那里可以调出颜色框~~
11. ~~`link` 界面的颜色框 也默认到当前选定颜色吧~~
12. ~~`backbone` 的颜色框 加一个 `Apply to all`和 `apply to category`（意思就是把同属一个category的gene 都替换成同一个颜色）
    Category 的颜色框 只加一个 `Apply to all`~~ 
    ~~link  那个 `fixed color` 颜色框 加上`Apply to all/apply to category/apply to gene`~~