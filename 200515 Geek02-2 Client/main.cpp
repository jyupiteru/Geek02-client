
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<WinSock2.h>
#include<stdio.h>


int main(void)
{

	WSADATA wsaData;
	SOCKET sock;

	//接続先の情報を入れる構造体
	sockaddr_in server;

	char buf[32];

	//winsock2の初期化
	int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
	
	//winsock2のエラー処理　必須！
	if (err != 0)
	{
		switch (err)
		{
		case WSASYSNOTREADY:		//System Not Ready 
				//ネットワークサブシステムがネットワークへの接続を準備できてない
			printf("WSASYSNOTREADY");
			break;

		case WSAVERNOTSUPPORTED:	//Version Not Supported
				//要求されたwinsockのバージョンがサポートされてない
			printf("WSAVERNOTSUPPORTED");
			break;

		case WSAEINPROGRESS:		//Error In Progress
				//ブロッキング操作の実行中、またはサービスプロバイダがコールバック関数を処理している
			printf("WSAEINPROGRESS");
			break;

		case WSAEPROCLIM:			//Process Limited
				//winsockが処理できる最大プロセス数に達した
			printf("WSAEPROCLIM");
			break;

		case WSAEFAULT:				//Fault
				//第二引数であるlpWSADataは有効なポインタでない
			printf("WSAEFAULT");
			break;
		}
	}

	//ソケットの作成
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	//socketのエラー処理
	if (sock == INVALID_SOCKET)
	{
		printf("error : %d\n", WSAGetLastError());
		return 1;
	}

	//接続先指定用構造体の準備
	server.sin_family = AF_INET;							//アドレスファミリ
	server.sin_port = htons(12345);							//ポート番号
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");	//IPアドレス

	//サーバに接続
	connect(sock, (sockaddr *)&server, sizeof(server));

	//サーバからデータを受信
	memset(buf, 0, sizeof(buf));//多めにバイトをとっているのでその削除？
	int n = recv(sock, buf, sizeof(buf), 0);//メッセージを受信するバッファ、一度に受信するバイト数
	printf("%d , %s\n",n,buf);

	//winsockの終了
	WSACleanup();

	getchar();
}