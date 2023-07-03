* [English version](./README.md)
# WeActStudio.WCH-BLE-Core
![display](Images/1.png)
CH573F
> 60Mhz Max,18KB RAM,448KB ROM,RISC-V3A,BLE 4.2

CH582F
> 60Mhz Max,32KB RAM,448KB ROM,RISC-V4A,BLE 5.3

WCH 官方网站 www.wch.cn(zh-CN) / www.wch-ic.com(en)

## 时钟和电源
**时钟**：  
32Mhz HSE 高速无源晶体输入  
32.768k LSE 低速无源晶体输入  
**电源**：  
3.3V-5.5V电源输入，3.3V LDO最大100mA额外输出  
USB电源串有二极管，防止电流倒灌  
同时二极管可以通过短路焊盘旁路  
5V带有TVS二极管  

## 接口和按键
**接口**：  
12Pin 2.54mm间距 I/O接口 * 2  
**按键**：  
复位/B23按键 * 1  
Boot/B22按键 * 1  

## 目录说明
|目录名称|内容|
| :--:|:--:|
|Doc| 数据手册/参考手册|
|HDK| 硬件开发资料|
|SDK|软件开发资料|
|Examples|软件例程|

## 如何下载程序
方法
1. 安装`Tools`目录下的`WCHISPTool_Setup.exe`
2. 安装`Tools`目录下的`CH372DRV.EXE`或者从`http://www.wch.cn/downloads/CH372DRV_EXE.html`下载
3. 按住BOOT键然后用USB数据线连接电脑，释放BOOT键
4. 打开 `WCHISPTool` && 找到 `CH57x Series` 或 `CH58x Series`

```
/*---------------------------------------
- WeAct Studio Official Link
- taobao: weactstudio.taobao.com
- aliexpress: weactstudio.aliexpress.com
- github: github.com/WeActTC
- gitee: gitee.com/WeAct-TC
- blog: www.weact-tc.cn
---------------------------------------*/
```