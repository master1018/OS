#include <stdio.h>
#include <stdlib.h>

#define MAX_COMMAND_NUM     (2400)  // 进程指令最大数量
#define PHY_PAGE_NUM        (12)     // 页框数目
#define PHY_PAGE_SIZE       (24)    // 页的大小

struct phy_page{
    int vPageIdx;       // 虚拟页号
    int lastHit;        // 上一次命中时间
    int inTime;         // 进入内存中的时间
}phyPage[PHY_PAGE_NUM];

int visit[MAX_COMMAND_NUM]; // 指令使用到的虚拟页号序列

void initPage()
{
    for (int i = 0; i < PHY_PAGE_NUM; i++)
    {
        // 初始化-1表示未被使用
        phyPage[i].vPageIdx     = -1;
        phyPage[i].lastHit      = -1;
        phyPage[i].inTime       = -1;
    }
}

void getVisit()
{
    for (int i = 0; i < MAX_COMMAND_NUM; i++)
    {
        // 随机数模拟访问虚拟页号的序列
        visit[i] = rand() % PHY_PAGE_SIZE;
    }
}

double FIFO(int pageNum)
{
    initPage();
    int count = 0;  // 记录缺页次数
    int inTime = 0;  
    for (int i = 0; i < MAX_COMMAND_NUM; i++)
    {
        int flag = 1;  // 缺页表示为1
        for (int j = 0; j < pageNum; j++)
        {
            if (phyPage[j].vPageIdx == visit[i])
            {
                flag = 0;
                break;
            }
        }
        if (1 == flag) // 缺页情况
        {
            int pos = 0;
            int tmp = 1e9;
            for (int j = 0; j < pageNum; j++)
            {
                if (phyPage[j].vPageIdx == -1)
                {
                    pos = j;
                    break;
                }
                else
                {
                    if (tmp > phyPage[j].inTime)
                    {
                        tmp = phyPage[j].inTime;
                        pos = j;
                    }
                }
            }

            // 缺页替换
            count++;
            phyPage[pos].vPageIdx = visit[i];
            phyPage[pos].inTime = inTime++;
        }
    }

    return (double)(count * 1.0 / MAX_COMMAND_NUM);
}

double LRU(int pageNum)
{
    initPage();
    int count = 0;
    int lastHit = 0;  // 值越大表示访问的时间越近
    for (int i = 0; i < MAX_COMMAND_NUM; i++)
    {
        int flag = 1;
        for (int j = 0; j < pageNum; j++)
        {
            if (phyPage[j].vPageIdx == visit[i])
            {
                flag = 0;
                phyPage[j].lastHit = lastHit++; // 更新最近一次的使用时间
                break;
            }
        }

        if (1 == flag)
        {
            int pos = 0;
            int tmp = 1e9;
            for (int j = 0; j < pageNum; j++)
            {
                if (phyPage[j].vPageIdx == -1)
                {
                    pos = j;
                    break;
                }
                else
                {
                    if (tmp > phyPage[j].lastHit)
                    {
                        tmp = phyPage[j].lastHit;
                        pos = j;
                    }
                }
            }

            count++;
            phyPage[pos].vPageIdx = visit[i];
            phyPage[pos].lastHit = lastHit++;
        }
    }

    return (double)(count * 1.0 / MAX_COMMAND_NUM);
}

int main()
{
    printf("页框数  |   FIFO Rate   |   LRU Rate\n");
    for (int i = 3; i < 13; i++)
    {
        getVisit();
        printf("    %d\t|\t%.3f\t|\t%.3f\t\n", i, FIFO(i), LRU(i));
    }
    return 0;
}