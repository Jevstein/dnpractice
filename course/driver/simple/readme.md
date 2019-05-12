一、参考：  
[在Linux下写一个简单的驱动程序](https://www.cnblogs.com/amanlikethis/p/4914510.html)

二、测试：  
测试的整体步骤就是：首先编译驱动和上层测试应用；然后加载驱动，通过上层应用调用驱动；最后卸载驱动。详细如下：  
1.编译驱动: 生成“hellomodule.ko”   
```
#make
```  

2、编译上层应用: 生成“hellotest”  
```
#gcc hellotest.c -o hellotest
```

3、加载驱动: 会调用hello_init()   
```
#insmod hellomodule.ko
```
此时可通过"/proc/devices"，查看看到已经加载的模块 

4、创建节点  
```
#mknod /dev/hellodev c 231 0
```   
　　虽然已经加载了驱动hellomodule.ko，而且在/proc/devices文件中也看到了已经加载的模块HelloModule，但是这个模块仍然不能被使用，因为在设备目录/dev目录下还没有它对应的设备文件。所以，需要创建一个设备节点。   
　　在"/proc/devices"中看到HelloModule模块的主设备号为231，创建节点的时候就是将设备文件"/dev/hellodev"与主设备号建立连接。这样在应用程序操作文件"/dev/hellodev"的时候，就会定位到模块"HelloModule"。  

5、上层应用调用驱动
```
#./hellotest
```
　　hellotest应用程序先打开文件“/dev/hellodev”，然后向此文件中写入一个变量val。期间会调用底层驱动中的hello_open和hello_write函数  

6、卸载驱动
```
#rmmod hellomodule
```  
　　insmod卸载驱动的时候，会调用函数hello_exit()