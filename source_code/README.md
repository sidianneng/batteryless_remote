## 编译准备工作
```
apt install gcc-arm-none-eabi
```

## 编译固件
```
cd ./batteryless_remote
make
```

## 获取固件
```
ls ./batteryless_remote/build/*.hex
```

## 固件下载
* 通过J-flash工具打开工程根目录下tools/J-flash-project/batteryless_remote.jflash
* 将前一步骤中的hex文件放到J-flash中打开，然后进行固件烧写即可
