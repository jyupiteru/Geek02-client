
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<WinSock2.h>
#include<stdio.h>


int main(void)
{

	WSADATA wsaData;
	SOCKET sock;

	//�ڑ���̏�������\����
	sockaddr_in server;

	char buf[32];

	//winsock2�̏�����
	int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
	
	//winsock2�̃G���[�����@�K�{�I
	if (err != 0)
	{
		switch (err)
		{
		case WSASYSNOTREADY:		//System Not Ready 
				//�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��ĂȂ�
			printf("WSASYSNOTREADY");
			break;

		case WSAVERNOTSUPPORTED:	//Version Not Supported
				//�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����ĂȂ�
			printf("WSAVERNOTSUPPORTED");
			break;

		case WSAEINPROGRESS:		//Error In Progress
				//�u���b�L���O����̎��s���A�܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă���
			printf("WSAEINPROGRESS");
			break;

		case WSAEPROCLIM:			//Process Limited
				//winsock�������ł���ő�v���Z�X���ɒB����
			printf("WSAEPROCLIM");
			break;

		case WSAEFAULT:				//Fault
				//�������ł���lpWSAData�͗L���ȃ|�C���^�łȂ�
			printf("WSAEFAULT");
			break;
		}
	}

	//�\�P�b�g�̍쐬
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	//socket�̃G���[����
	if (sock == INVALID_SOCKET)
	{
		printf("error : %d\n", WSAGetLastError());
		return 1;
	}

	//�ڑ���w��p�\���̂̏���
	server.sin_family = AF_INET;							//�A�h���X�t�@�~��
	server.sin_port = htons(12345);							//�|�[�g�ԍ�
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");	//IP�A�h���X

	//�T�[�o�ɐڑ�
	connect(sock, (sockaddr *)&server, sizeof(server));

	//�T�[�o����f�[�^����M
	memset(buf, 0, sizeof(buf));//���߂Ƀo�C�g���Ƃ��Ă���̂ł��̍폜�H
	int n = recv(sock, buf, sizeof(buf), 0);//���b�Z�[�W����M����o�b�t�@�A��x�Ɏ�M����o�C�g��
	printf("%d , %s\n",n,buf);

	//winsock�̏I��
	WSACleanup();

	getchar();
}