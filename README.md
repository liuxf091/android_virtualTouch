# android_virtualTouch
## 介绍
在安卓上纯native层模拟手指触摸
<br>
不会和正常手指触摸冲突
## 使用
    void touchDown(const int& id,Vector2 pos);//按下,id可以是任何数
    void touchUp(const int& id);//释放
    void touchMove(const int& id,Vector2 pos);//x轴移动到x，y轴移动到y
    void monitorEvent(void (*callBack)(int slot,Vector2 data,int type));//监听触摸并调用回调函数 slot:可以理解为第几根手指 data:坐标 type: 0:touchDown,1:touchUp
## 关于
使用多点触控协议A类型  
之前使用b协议的版本放到了另一个分支，有需要可以去下载
-_-
## Q&A([更多](Q&A.md))
### Q:第一次执行正常使用，第二次无法使用  
#### A:出现这个问题大概率是apatch/kernelsu用户,因为root实现方式的原因(应该是),你直接划掉终端的进程并不会关闭本进程，导致本进程在后台一直运行,然后你第二次执行就出问题了,以正常方法关闭本进程即可     
### Q:这个模拟触摸会不会和真实手指触摸冲突,会不会抢手?   
#### A:本项目完全不会和真实手指触摸冲突,也就是说在项目模拟触摸期间你可正常触摸屏幕而不会造成任何影响   
### Q:模拟器虚拟机可以用吗?   
#### A:本项目设计之初以及代码中的逻辑均默认为真机使用,不过你可以尝试一下,可能能用,后续有适配虚拟机的想法   

