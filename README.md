## 基于Stm32的太阳能电池板自动追光系统设计

### 1-设计意义

​    目前存在的太阳能光伏板都是固定放置，即选择一定角度之后就固定不动，这次发电方式虽然结构简单，但是存在很多问题，光伏板接受到的光强大小为太阳光强在在光伏板竖直平面的投影，如图1-1所示，光伏板与平面的夹角为α，与太阳光之间的夹角为θ，若太阳光的光强功率为P1，那么光伏板接收到的光强P=sinθ*P1,根据三角函数的性质可以知道，sinθ永远小于等于1，在实际中，只有θ为Π/2时sinθ为1，因此P永远小于等于P1，只有当光伏板和太阳光之间的角度为Π/2时P=P1，此时发电功率最大。本次设计主要是设计一个以STM32为核心的智能追光发电系统，通过此系统光伏板与太阳光的夹角为几乎始终为Π/2，因此可以尽可能的接收光照，从而提高发电效率。

![image-20211201201850113](https://raw.githubusercontent.com/Halley826/Images/main/202112012036023.png?token=AWCL7MMO4DI4TETASLE6JBTBU5WIM)

### 2-开发环境、开发工具介绍

**硬件平台：**

1. STM32F103C8T6控制核心
2. TDA 2822芯片
3. USR-GPRS232-7S3模块
4. L298N驱动

**软件平台：**

1. KEIL MDK

2. STM32CubeMx软件

3. STM32CubeMx软件

   ![image-20211201202212419](https://raw.githubusercontent.com/Halley826/Images/main/202112012036242.png?token=AWCL7MO3SEK7QYE7IVVOYALBU5WIE)

### 3-系统方案选择和整体设计

**整体思路：**

![image-20211201202306065](https://raw.githubusercontent.com/Halley826/Images/main/202112012036083.png?token=AWCL7MI7RUEOIOTOL4EF2QTBU5WIA)

**基于遮光法设计寻光检测头：**

![image-20211201202419779](https://raw.githubusercontent.com/Halley826/Images/main/202112012036585.png?token=AWCL7MMW6G7UPJZD2RX2BDLBU5WH4)

### 4-系统设计

**STM32103C8T6外接引脚原理图**

> 控制核心

![image-20211201202512014](https://raw.githubusercontent.com/Halley826/Images/main/202112012036920.png?token=AWCL7MJLUXZ4TD376G5GDGLBU5WHW)

**USR-GPRS232-7S3短信透传模式：**

> 实现远程控制

![image-20211201202555984](https://raw.githubusercontent.com/Halley826/Images/main/202112012036720.png?token=AWCL7MLDZTUYGMYOPFUPFCLBU5WHQ)

**USR-GPRS232-7S3原理图：**

> GPRS模块原理图

![image-20211201202619276](https://raw.githubusercontent.com/Halley826/Images/main/202112012036257.png?token=AWCL7MK3CIGHFA2WIPZT6WLBU5WHK)

**L298N模块电驱动电路原理图：**

> 用来驱动马达，双通道

![image-20211201202658644](https://raw.githubusercontent.com/Halley826/Images/main/202112012036315.png?token=AWCL7MI6OO7C3A3UVNIZMMTBU5WHG)

**寻光检测头工作流程：**

> 寻光检测头设计思路

![image-20211201202733263](https://raw.githubusercontent.com/Halley826/Images/main/202112012036787.png?token=AWCL7MJFEEGJYR2Y4QQNS43BU5WHA)

**寻光检测头原理图：**

> 原理图

![image-20211201202752065](https://raw.githubusercontent.com/Halley826/Images/main/202112012035737.png?token=AWCL7MPJN32D55DOQCJBKR3BU5WG6)

### **5-成果展示**

> 时间：2019-09-24 15:00

**打开追踪系统：**

![image-20211201203049856](https://raw.githubusercontent.com/Halley826/Images/main/202112012035186.png?token=AWCL7MLS4D4LTJROJAXJEXLBU5WG2)

**关闭追踪系统：**

![image-20211201203110505](https://raw.githubusercontent.com/Halley826/Images/main/202112012035859.png?token=AWCL7MPATD33AZS6YO6ROWTBU5WG2)

### 相关的接线

![image-20220924211729019](README.assets/image-20220924211729019.png)
