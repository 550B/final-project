### 项目结构

#### 目录

[TOC]

#### 各种文件的作用

* `Scene`：只用来展示场景、画面元素等
* `Layer`：用来控制场景中的元素，比如：精灵的拖拽放置删除、选关、关卡信息增删改查
* `Sprite`：命名如`GanYuan`、`Enemy`或其他什么既不是`Scene`也不是`Layer`的玩意，有一个基类，名字带`Base`，后面实现角色继承这个基类。可以把不同角色分开不同文件，也可以比如把比较相似的敌人都写在一个文件里，看代码长度

#### 小记

* 按照文件架构，打开对应文件，补全代码，不完善的地方自己补充

* | `.cpp`、`.h`   | 作用                                           |
  | -------------- | ---------------------------------------------- |
  | AppDelegate    | 初始化屏幕大小，创建第一个场景                 |
  | Enemy          | 不同敌人的实现，继承Base                       |
  | EnemyBase      | 敌人基类                                       |
  | GanYuanBase    | 干员基类                                       |
  | GanYuanMedical | 医疗干员的实现，继承Base，在这里面挪动子弹     |
  | GanYuanShield  | 重装干员的实现，继承Base                       |
  | GanYuanShooter | 射手干员的实现，继承Base                       |
  | GameLayer      | 游戏逻辑的判断，比如：判断输赢                 |
  | GameManager    | 游戏关卡数据的记录，比如：场上节点的数据、时间 |
  | GameSprite     | 游戏放置删除                                   |
  | FailedScene    | 失败画面                                       |
  | WinScene       | 成功画面                                       |
  | Map1，2，...   | 由武同学负责地图部分创建                       |
  | LevelLayer     | 选关操作                                       |
  | LevelScene     | 选关页面                                       |
  | Wave           | 敌人出现的波次                                 |

  