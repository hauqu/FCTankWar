#pragma once

/*
决定了敌人的攻击频率，移动频率，
生成ai指令

*/
enum class cmd
{
	NA,//无效
	Up, Right, Down, Left, Stop,//移动 上 右 下 左
	Attack,//攻击指令
	Explosion,//自爆
};
enum class Aicmd 
{

};//复杂指令，如寻找，围堵，可被拆分为基础指令
class cmdMaker
{
public:


};