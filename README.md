# Q_Learning_Demo
一个实验性的基于Q_Learning思想的多目标寻径算法，基于VisualStudio2019 C++平台运行

运行程序需要哪些文件？

     一个文本文件(.txt)，可以从Excel的.xlsx文件导出，包括：
     
         四个列名（随意，但必须有四个列名，读文件时读取但不使用），为“start”，“end”，“distance”，“traffic”
         
         多个连通边（默认为双向连接，若需要单向连接，需要在main.cpp中修改Initialize函数）与其距离和交通状况(start,end,distance,traffic)
         
         一个数字STOP（默认为11111111，此时停止读取连通边）
         
         多个目标以及其期望(goal,willingness)
         
         一个数字STOP（默认为11111111，此时停止读取目标）
         
      几个参数修改，在function.cpp中：
      
         numGoal,目标数
         
         numCross,节点数
         
      几个注意事项：
         
         节点id默认从1开始
         
         交通状况Traffic默认为1（畅通），数字越大越拥堵
         
         距离Distance默认为0（不可达），非0为可达
