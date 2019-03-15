#include "echo.h"

int main()
{
	int size =0;
	int msg_id =0;

	key_t key;
	MSG_BUF msg_buf;

	if( (key = ftok(".",'a')) == -1)
	{
		perror("[server] ftok() : ");
		exit(1);
	}
	if( (msg_id = msgget(key,0)) == -1)
	{
		perror("[clinet] : msgget() : ");
		exit(2);
	}
	while(1)
	{
		memset(&msg_buf, 0x00,sizeof(MSG_BUF));
		if( (size = read(0,msg_buf.mdata,MAXSIZE)) < 0)
		{
			perror("[client] : read : ");
			break;
		}
		if(!strncmp(msg_buf.mdata,"end",3))
				break;
		msg_buf.mtype = SERVER_TYPE;
		if(msgsnd(msg_id,&msg_buf, strlen(msg_buf.mdata)+1,0) == -1)
		{
			perror("[clinet] : msgsnd : ");
			break;
		}
	}
	msg_buf.mtype = SERVER_TYPE;
	if( msgsnd(msg_id, &msg_buf, 0, 0) == -1)
			perror("[client] : msgsnd : ");
	exit(0);
}

