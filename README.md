# 一、编译

新建build目录，cd到bulid目录执行：cmake ..  && make (需要先安装libalsa:   sudo apt-get install libalsa-ocaml-dev)

# 二、录制

./TestAlsa  开始录制

![](/home/libin/图片/x.png)

# 三、测试录制音频文件

打开Audacity，在文件-》导入-》原始数据选择刚才录制的.pcm文件

设置编码，字节序，声道，采样率即可播放（需要和代码中设置的参数一致），如下图所示(sIGNED 16-bit PCM,  小尾端（little-endian）,2声道（立体声） ，0 100 4410)：

![2021-05-26 12-09-33 的屏幕截图](/home/libin/图片/2021-05-26 12-09-33 的屏幕截图.png)

点击导入，播放，就可以听到录制的声音了。[]()

