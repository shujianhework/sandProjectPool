set NDK_ROOT=android-ndk-r12
goto start
使用 eclipse adt 工程目录下运行
	cocos compile -p android --no-apk
如果使用 android studio 工程目录下运行
	cocos compile -p android --android-studio --no-apk
编译选项：
	-m MODE：MODE 可以是 debug 或 release, 默认是 debug
	-j JOBS：同时执行的任务数量，提高速度
	-o DIR：指定输出目录
android 编译选项：
	--no-apk：只编译，不生成 apk 文件
查看更多命令行选项：
	cocos compile -h
:start
cocos compile -p android -m release -s E:\Project\git\sandProjectPool\client\zww\game --ap android-21 --no-apk
pause
