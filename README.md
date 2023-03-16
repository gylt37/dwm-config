
| 文件夹                                                       | 介绍    |
| ------------------------------------------------------------ | ------- |
| [dwm](https://dwm.suckless.org/)  | dwm桌面 |
| [dwmblocks](https://github.com/LukeSmithxyz/dwmblocks) | 状态栏  |
| [st](https://st.suckless.org/)    | 终端    |

安装教程

```bash
git clone https://github.com/gylt37/dwm-config

cd dwm-config/dwm 
sudo make clean install #编译安装

cd ../dwmblocks
sudo make clean install  #编译安装

cd ../st
sudo make clean install  #编译安装
```

卸载
```bash
cd dwm-config/dwm   
sudo make clean uninstall #卸载
 
cd ../dwmblocks  
sudo make clean uninstall  #卸载
  
cd ../st  
sudo make clean uninstall  #卸载
```

### dwm补丁介绍

dwm补丁可以去[官方](https://dwm.suckless.org/patches/)和[GitHub合集](https://github.com/bakkeby/patches/wiki)找，中文详细介绍看[这里](https://github.com/Katzeee/dwm-patches-chinese/blob/master/dwm-patches-chinese.md)

| 名称                                                                                                                | 功能                                                             |
| ------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------- |
| [alpha](https://dwm.suckless.org/patches/alpha/)+[systray](https://dwm.suckless.org/patches/systray/)               | 透明的标题栏+托盘                                                |
| [autostart](https://dwm.suckless.org/patches/autostart/)                                                            | 自动启动，在dwm启动时自动启动脚本                                |
| [awesomebar](https://dwm.suckless.org/patches/awesomebar/)+[statuscmd](https://dwm.suckless.org/patches/statuscmd/) | 在标题栏显示所有窗口标题,隐藏窗口+dwmblock的信号量               |
| [barpadding](https://dwm.suckless.org/patches/barpadding/)                                                          | 状态栏添加间隙                                                   |
| [cfacts](https://dwm.suckless.org/patches/cfacts/)+[vanitygaps](https://dwm.suckless.org/patches/vanitygaps/)       | cfacts根据权重不同,修改平铺大小占比.vanitygaps调整平铺窗口的间隙 |
| [clientopacity](https://dwm.suckless.org/patches/clientopacity/)                                                    | 设置窗口默认透明度                                               |
| [default_tag_apps](https://dwm.suckless.org/patches/default_tag_apps/)                                              | 设置不同标签的默认应用                                           |
| [floatpos](https://github.com/bakkeby/patches/blob/master/dwm/dwm-floatpos-6.3.diff)                                | 更改浮动窗口的大小和位置,控制移动位置和大小                      |
| [focusonnetactive](https://dwm.suckless.org/patches/focusonnetactive/)                                              | 与其他外部窗口管理器配合,比如打开网址,自动移动到浏览器           |
| [fullscreen](https://dwm.suckless.org/patches/fullscreen/)                                                          | 让窗口真正的全屏,不是只隐藏标题栏                                |
| [hide_vacant_tags](https://dwm.suckless.org/patches/hide_vacant_tags/)                                              | 不显示空的标签页                                                 |
| [inplacerotate]( https://dwm.suckless.org/patches/inplacerotate/)                                                   | 更好的互换平铺窗口的窗口位置                                     |
| [pertag](https://dwm.suckless.org/patches/pertag/)                                                                  | 每个标签不同布局                                                 |
| [renamedscratchpads](https://github.com/bakkeby/patches/wiki/renamedscratchpads)                                    | 一个特殊的便签窗口                                               |
| [viewontag](https://dwm.suckless.org/patches/viewontag/)                                                            | 移动窗口到新标签后,自动移动到新标签                              |
| [grid_overview](https://github.com/gylt37/dwm-config/blob/main/dwm/patchs/dwm-grid_overview.diff)  |  网格布局和全预览模式|                                                                                                               |                                                                  |

### 脚本介绍
脚本在安装时会复制`script`所有脚本文件到/usr/local/share/dwm目录下。
| 脚本         | 介绍                   |
| ------------ | ---------------------- |
| autostart.sh | 自动启动               |
| exit.sh      | 可视化的退出           | 
| lock.sh      | 锁屏脚本               |
| rofi-drun.sh | rofi的运行脚本         |
| spnnn.sh     | 便签nnn                |
| terminal.sh  | 终端                   |
| update.sh    | 自动更新,配合dwmblocks |
### dwmblocks
[dwmblocks](https://github.com/LukeSmithxyz/dwmblocks)，脚本用的是别人修改的[版本](https://github.com/Wjinlei/my.scripts)，简单修改一下就能用，安装时会会复制`script`所有脚本文件到`/usr/local/share/dwmblocks`。

| 名称       | 介绍 |
| ---------- | ---- |
| Music.sh   | 音乐 |
| NetTraf.sh | 网络 |
| Volume.sh  | 音量 |
| Battery.sh | 电池 |
| Clock.sh   | 时间 |
| Update.sh  | 更新 |
### 终端St
| 名称                                                            | 介绍                     |
| --------------------------------------------------------------- | ------------------------ |
| [anysize](https://st.suckless.org/patches/anysize/)             | 调整窗口大小             |
| [desktopentry](https://st.suckless.org/patches/desktopentry/)|桌面图标 |
| [dracula](https://st.suckless.org/patches/dracula/)             | 好看的配色               |
|[dynamic-cursor-color](https://st.suckless.org/patches/dynamic-cursor-color/)| 反转选中颜色 |
| [font2](https://st.suckless.org/patches/font2/)                 | 更多字体                 |
| [focus](https://st.suckless.org/patches/alpha_focus_highlight/) | 使终端透明，改变焦点颜色 |
|[glyph wide support](https://st.suckless.org/patches/glyph_wide_support/) | 宽形字体支持 |
| [hidecursor](https://st.suckless.org/patches/hidecursor/)       | 自动隐藏鼠标             |
| [scrollback](https://st.suckless.org/patches/scrollback/)       | 滚动上下                 |