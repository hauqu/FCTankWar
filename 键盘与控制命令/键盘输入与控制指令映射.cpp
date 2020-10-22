enum class cmd
{
	NA,//无效
	Up,Right,Down,Left,Stop,//移动 上 右 下 左
	

};
cmd keyPro(char c);
int main(int arg,char *arv[])
{

	return 0;
}
cmd keyPro(char c)
{
	switch (c)
	{
	case 'w':
	case 'W':
		return cmd::Up; break;
	case 'd':
	case 'D':
		return cmd::Right; break;
	case 's':
	case 'S':
		return cmd::Down; break;
	case 'a':
	case 'A':
		return cmd::Left; break;
	default:
		return cmd::NA;
		break;
	}
}