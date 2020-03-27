#include<string.h>
#include<errno.h>
#include<asm/segment.h>

char msg[24]; 
/***
function:将name的内容拷贝到msg,name的长度不超过23个字符
return:拷贝的字符数，如果name的字符个数超过了23，则返回“-1”，并置errno为EINVAL

  ****/
int sys_iam(const char *name)
{
	int i;
	// 临时存储输入字符串，操作失败时不影响msg
	char tmp[30];
	for(i = 0;i < 30; i++)
	{
			// 从用户态内存取得数据
			tmp[i] = get_fs_byte(name+i);
			if(tmp[i] == '\0')
					break;
	}
	i = 0;
	while(i < 30 && tmp[i] !='\0')
			i++;
	int len = i;
	if(len > 23)
	{
			return -(EINVAL);
	}
	strcpy(msg,tmp);
	return i;

}

int sys_whoami(char *name, unsigned int size)
/***
 
  function:将name的内容拷贝到msg,name的长度不超过23个字符
  return:拷贝的字符数，如果name的字符个数超过23，则返回“-1”，并置errno为EINVAL
 ****/
{
	// msg的长度大于size
	int len = 0;
	for(;msg[len] != '\0';len++);
	if(len > size)
	{
		return -(EINVAL);
	}
	int i = 0;
	// 把msg输出至name
	for(i = 0;i < size;i++)
	{
			put_fs_byte(msg[i],name+i);
			if(msg[i] == '\0')
					break;
	}
	return i;
}

