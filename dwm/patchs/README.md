### 使用方法

#### 本仓库下载

使用命令行

```
git clone https://github.com/gylt37/dwm-config
cd dwm-config/dwm
```

比如修补[alpha](https://dwm.suckless.org/patches/alpha/)补丁

```
patch <  ./patchs/dwm-alpha-20201019-61bb8b2.diff
```

再根据目录下未修改的`.rej`文件手动修改文件

卸载命令是

```bash
patch -R < ./patchs/dwm-alpha-20201019-61bb8b2.diff
```

#### 从官网下载

使用命令行

```bash
git clone https://git.suckless.org/dwm
cd dwm
```

打开官网补丁网址,下载最新的补丁,比如下载[alpha](https://dwm.suckless.org/patches/alpha/)补丁

```bash
wget https://dwm.suckless.org/patches/alpha/dwm-alpha-20201019-61bb8b2.diff
patch < dwm-alpha-20201019-61bb8b2.diff
```

再根据目录下未修改的`.rej`文件手动修改文件

卸载命令是

```bash
patch -R < dwm-alpha-20201019-61bb8b2.diff
```

### 补丁介绍

| 名称                                                         | 功能                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [alpha](https://dwm.suckless.org/patches/alpha/)             | 透明的标题栏                                                 |
| [awesomebar](https://dwm.suckless.org/patches/awesomebar/)   | 在标题栏显示所有窗口标题,配合dwmblocks                       |
| [barpadding](https://dwm.suckless.org/patches/barpadding/)   | 标题栏周围添加缝隙                                           |
| [cfacts](https://dwm.suckless.org/patches/cfacts/)和[vanitygaps](https://dwm.suckless.org/patches/vanitygaps/) | cfacts根据权重不同,修改平铺大小占比.vanitygaps调整平铺窗口的间隙.这两个补丁默认的版本冲突,下载这个[版本](https://dwm.suckless.org/patches/vanitygaps/dwm-cfacts-vanitygaps-6.2_combo.diff) |
| [clientopacity](https://dwm.suckless.org/patches/clientopacity/) | 修改窗口默认透明度                                           |
| [cool_autostart](https://dwm.suckless.org/patches/cool_autostart/) | 在dwm启动自动启动config.h文件中autostart[]数组中的命令       |
| [default_tag_apps](https://dwm.suckless.org/patches/default_tag_apps/) | 设置不同标签的默认应用                                       |
| [floatrules](https://dwm.suckless.org/patches/floatrules/)   | 设置浮动窗口默认位置和大小                                   |
| [focusonnetactive](https://dwm.suckless.org/patches/focusonnetactive/) | 与其他外部窗口管理器配合,比如打开网址,自动移动到浏览器       |
| [fullscreen](https://dwm.suckless.org/patches/fullscreen/)   | 让窗口真正的全屏,不是只隐藏标题栏                            |
| [hide_vacant_tags](https://dwm.suckless.org/patches/hide_vacant_tags/) | 不显示空的标签页                                             |
| [inplacerotate]( https://dwm.suckless.org/patches/inplacerotate/) | 更好的互换平铺窗口的窗口位置                                 |
| [moveresize](https://dwm.suckless.org/patches/moveresize/)   | 用键盘调整浮动窗口的位置跟大小                               |
| [pertag](https://dwm.suckless.org/patches/pertag/)           | 每个标签不同布局                                             |
| [scratchpads](https://dwm.suckless.org/patches/scratchpads/) | 一个特殊的便签窗口                                           |
| [viewontag](https://dwm.suckless.org/patches/viewontag/)     | 移动窗口到新标签后,自动移动到新标签                          |


[clientopacity](https://dwm.suckless.org/patches/clientopacity/)补丁有bug

修改补丁文件的opacity()函数中的if条件,当透明度为0时不透明

```diff
-  if(opacity >= 0 && opacity <= 1){
+  if(opacity > 0 && opacity <= 1) {
```

修改补丁文件的下面一行

```diff
- + NetWMWindowTypeDialog, NetClientList, NetLast, NetWMWindowsOpacity }; /* EWMH atoms */
+ + NetWMWindowTypeDialog, NetClientList, NetWMWindowsOpacity, NetLast}; /* EWMH atoms */
```

