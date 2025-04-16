#include <linux/uinput.h>
#include <thread>

struct screen
{
    int width{};
    int height{};
    int orientation{};
    std::vector<int> fd{};
};

struct touchOBJ
{
    int x{0};
    int y{0};
    int id{0};
    int TRACKING_ID{0};
    bool isDown{false};
    bool isUse{false};
};

class Vector2
{
public:
    Vector2();
    Vector2(float x, float y);
    Vector2(int x, int y);
    Vector2(Vector2 &va);
    Vector2& operator=(const Vector2& other);
    float x{};
    float y{};
};


class touch
{
public:
    touch();
    ~touch();
    void touchDown(const int& id,const Vector2 &pos);//按下,id可以是任何数
    void touchUp(const int& id);//释放
    void touchMove(const int& id,const Vector2 &pos);//x轴移动到x，y轴移动到y
    void monitorEvent(void (*callBack)(int slot,Vector2 data,int type));//监听触摸并调用回调函数 slot:可以理解为第几根手指 data:坐标 type: 0:touchDown,1:touchUp
private:
    std::vector<std::thread> threads;//储存PTScreenEventToFingerByFd
    uinput_user_dev usetup{};//驱动信息
    int uinputFd{};//uinput的文件标识符
    std::thread GetScreenorientationThread{};//循环获取屏幕方向的线程
    float screenToTouchRatio{};//比例
    touchOBJ Fingers[2][10]{};//手指，物理触摸屏和模拟触摸
    screen screenInfo{};//屏幕信息
    screen touchScreenInfo{};//触摸屏信息
    void (*monitorCallBack)(int slot,Vector2 data,int type){nullptr};//0:touchDown,1:touchUp
private:
    int GetNoUseIndex();//获取一个没有使用过的finger,仅限模拟触摸
    int GetindexById(const int& byId);
    void GetScrorientation();//循环获取屏幕方向
    static std::string exec(const std::string& command);
    Vector2 rotatePointx(const Vector2& pos, const Vector2& wh, bool reverse) const;//根据方向来重构坐标,pos是坐标，wh是宽高 --reverse为真代表要反向计算 //举个例子：假如你要在横屏时触摸200，200，就让reverse == ture,假如你要让原始坐标转为屏幕分辨率就让reverse == false
    void upLoad();//遍历Finger数组并上报
    void PTScreenEventToFinger(int fd=0);//将物理触摸屏的Event转化存到Finger数组
    void InitTouchScreenInfo();//初始化物理触摸屏信息
    void InitScreenInfo();//初始化屏幕信息
};