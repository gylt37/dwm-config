[dwm官网](https://dwm.suckless.org/)

自己使用的dwm窗口管理器的源码

dwmblocks是dwm桌面的状态栏的补丁,具体详细介绍请看下面介绍

| 文件夹                                                       | 介绍    |
| ------------------------------------------------------------ | ------- |
| [dwm](https://github.com/gylt37/dwm-config/tree/master/dwm)  | dwm桌面 |
| [dwmblocks](https://github.com/gylt37/dwm-config/tree/master/dwmblocks) | 状态栏  |
| [st](https://github.com/gylt37/dwm-config/tree/master/st)    | 终端    |

安装教

```
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

