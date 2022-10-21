[dwm官网](https://dwm.suckless.org/)个人使用的dwm窗口管理器的配置，dwmblocks是dwm桌面的状态栏信息，具体详细介绍请看下面介绍。

| 文件夹                                                       | 介绍    |
| ------------------------------------------------------------ | ------- |
| [dwm](https://github.com/gylt37/dwm-config/tree/master/dwm)  | dwm桌面 |
| [dwmblocks](https://github.com/gylt37/dwm-config/tree/master/dwmblocks) | 状态栏  |
| [st](https://github.com/gylt37/dwm-config/tree/master/st)    | 终端    |

安装教程

```bash
git clone https://github.com/gylt37/dwm-config

cd dwm-config/dwm 
sudo make clean install #编译安装

mkdir -p ~/.config/dwm 
cp script/* ~/.config/dwm/ #移动脚本

cd ../dwmblocks
sudo make clean install  #编译安装

mkdir -p ~/.config/dwmblocks
cp script/* ~/.config/dwmblocks/  #移动脚本

cd ../st
sudo make clean install  #编译安装
```

### dwm补丁介绍

dwm补丁可以去[官方](https://dwm.suckless.org/patches/)和[这里](https://github.com/bakkeby/patches/tree/master/dwm)找，中文详细介绍看[这里](https://github.com/Katzeee/dwm-patches-chinese/blob/master/dwm-patches-chinese.md)

| 名称                                                         | 功能                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [alpha](https://dwm.suckless.org/patches/alpha/)+[systray](https://dwm.suckless.org/patches/systray/) | 透明的标题栏+托盘                                            |
| [autostart](https://dwm.suckless.org/patches/autostart/)     | 自动启动，在dwm启动时自动启动脚本~/.config/dwm/autostart.sh  |
| [awesomebar](https://dwm.suckless.org/patches/awesomebar/)+[statuscmd](https://dwm.suckless.org/patches/statuscmd/) | 在标题栏显示所有窗口标题,隐藏窗口+dwmblock的信号量           |
| [barpadding](https://dwm.suckless.org/patches/barpadding/)   | 状态栏添加间隙                                               |
| [cfacts](https://dwm.suckless.org/patches/cfacts/)+[vanitygaps](https://dwm.suckless.org/patches/vanitygaps/) | cfacts根据权重不同,修改平铺大小占比.vanitygaps调整平铺窗口的间隙 |
| [clientopacity](https://dwm.suckless.org/patches/clientopacity/) | 设置窗口默认透明度                                           |
| [default_tag_apps](https://dwm.suckless.org/patches/default_tag_apps/) | 设置不同标签的默认应用                                       |
| [floatrules](https://dwm.suckless.org/patches/floatrules/)   | 设置浮动窗口, 默认位置,默认大小,默认边框                     |
| [focusonnetactive](https://dwm.suckless.org/patches/focusonnetactive/) | 与其他外部窗口管理器配合,比如打开网址,自动移动到浏览器       |
| [fullscreen](https://dwm.suckless.org/patches/fullscreen/)   | 让窗口真正的全屏,不是只隐藏标题栏                            |
| [hide_vacant_tags](https://dwm.suckless.org/patches/hide_vacant_tags/) | 不显示空的标签页                                             |
| [inplacerotate]( https://dwm.suckless.org/patches/inplacerotate/) | 更好的互换平铺窗口的窗口位置                                 |
| [moveresize](https://dwm.suckless.org/patches/moveresize/)   | 用键盘调整浮动窗口的位置跟大小                               |
| [pertag](https://dwm.suckless.org/patches/pertag/)           | 每个标签不同布局                                             |
| [scratchpads](https://dwm.suckless.org/patches/scratchpads/) | 一个特殊的便签窗口                                           |
| [viewontag](https://dwm.suckless.org/patches/viewontag/)     | 移动窗口到新标签后,自动移动到新标签                          |

### 脚本介绍

| 脚本        | 介绍                   |
| ----------- | ---------------------- |
| autolock.sh | 自动锁屏               |
| exit.sh     | 可视化的退出           |
| lock.sh     | 锁屏脚本               |
| trayer.sh   | 托盘脚本               |
| update.sh   | 自动更新,配合dwmblocks |


| 名称                                                      | 介绍         |
| --------------------------------------------------------- | ------------ |
| [alpha](https://st.suckless.org/patches/alpha/)           | 使终端透明   |
| [anysize](https://st.suckless.org/patches/anysize/)       | 调整窗口大小 |
| [dracula](https://st.suckless.org/patches/dracula/)       | 好看的配色   |
| [font2](https://st.suckless.org/patches/font2/)           | 更多字体     |
| [hidecursor](https://st.suckless.org/patches/hidecursor/) | 自动隐藏鼠标 |
| [scrollback](https://st.suckless.org/patches/scrollback/) | 滚动上下     |

**ps.** scrollback-mouse补丁是让鼠标滚动上下