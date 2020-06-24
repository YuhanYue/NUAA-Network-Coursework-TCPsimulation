#include "ClientForm.h"
#include <iostream>
#include <WinSock2.h>
#include <time.h>

using namespace Client;

time_t Start;//时间开始
time_t End;//时间结束

[STAThreadAttribute]



int main(array<System::String ^>^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew ClientForm());
	return 0;
}

void ClientForm::acceptMessage() {
	isStillReceive = true;
	isStillSend = true;
	array<Byte>^bytes = gcnew array<Byte>(256);
	try
	{
		
		//建立远端Endpoint
		Int32 port = 8888;
		IPAddress^ipAddress = IPAddress::Parse("127.0.0.1");
		IPEndPoint^remoteEP = gcnew IPEndPoint(ipAddress, port);
		//建立socket对象
		socketAtClient = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
		socketAtClient->Connect(remoteEP);

		if (socketAtClient->Connected) {
			//	isConnectionOK = true;
			tbSocketConn->Text = L"连接建立";
		}	
	}
	catch (Exception^)
	{
		MessageBox::Show("Exception accrued during connect server!", "Exception");
	}
}

void ClientForm::SendMessage() {
	try
	{
		while (isStillSend)//开始循环发送数据
		{
			SendMSG[2] = 0;//FIN = 0
			SendMSG[0] = Seqnum;
			Start = clock();
			socketAtClient->Send(SendMSG);//发送数据
			datanum = Seqnum % 10;
			Data[0] = datanum;
			tbSendData->AppendText(""+ datanum);//显示本次发送的数据
			tbSendNum->AppendText(""+Seqnum);//显示本次发送的帧序号
			if (flagError == 0)//是否重传
			{
				tbError->AppendText("否");
			}
			else if (flagError == 1) {
				tbError->AppendText("是");
				flagError = 0;
			}
			tbMSGHistory->AppendText("Send：    帧序号" + Seqnum + "  数据: " + datanum+"\r\n");//在消息历史中显示本次发送的内容

			Seqnum++;
			
			Thread::Sleep(1000);

			tbSendData->Clear();//清空本次消息内容
			tbSendNum->Clear();//清空本次序号内容
			tbError->Clear();//清空本次是否重传内容
		}

	}
	catch (Exception^)
	{
		MessageBox::Show("Exception accrued during Client", "Exception");
	}
}


void ClientForm::ReceiveMessage() {
	try
	{
		while (isStillReceive)
		{
			if (socketAtClient->Available > 0)
			{
				int byteCount = socketAtClient->Receive(ACKMSG);//开始接收数据
				End = clock();
				if (Seqnum - ACKMSG[0] == 5)//保证滑动窗口为5
				{
					Seqnum--;
					Thread::Sleep(5000);
				}
				if (byteCount > 0) {
					if (ACKMSG[1] == 1 || ACKMSG[1] == 3 || difftime(End,Start) > 1000)//有出错的情况，需要重传，只要帧不正常或者超时
					{
						Seqnum--;
						flagError = 1;
					}
					else if (ACKMSG[1] == 2 ) {//返回帧丢失
						tbMSGHistory->AppendText("Receive: 帧丢失:"+ ACKMSG[0] +"\r\n");
					}
					else if (ACKMSG[1] == 3) {
						tbMSGHistory->AppendText("Receive: 帧错误:" + ACKMSG[0] + "\r\n");
					}
					else
					{
						int temp = ACKMSG[0] + 1;//发送成功，下次期望收到的ACK
						tbRecvNum->AppendText("" + temp);
						tbMSGHistory->AppendText("Receive: ACK:" + temp+"\r\n");
					}
				}
			}


			Thread::Sleep(1000);

			tbRecvNum->Clear();
		}
	}
	catch (Exception^)
	{
		MessageBox::Show("Exception accrued during connect server!", "Exception");
	}

}