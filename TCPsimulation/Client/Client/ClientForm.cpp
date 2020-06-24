#include "ClientForm.h"
#include <iostream>
#include <WinSock2.h>
#include <time.h>

using namespace Client;

time_t Start;//ʱ�俪ʼ
time_t End;//ʱ�����

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
		
		//����Զ��Endpoint
		Int32 port = 8888;
		IPAddress^ipAddress = IPAddress::Parse("127.0.0.1");
		IPEndPoint^remoteEP = gcnew IPEndPoint(ipAddress, port);
		//����socket����
		socketAtClient = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
		socketAtClient->Connect(remoteEP);

		if (socketAtClient->Connected) {
			//	isConnectionOK = true;
			tbSocketConn->Text = L"���ӽ���";
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
		while (isStillSend)//��ʼѭ����������
		{
			SendMSG[2] = 0;//FIN = 0
			SendMSG[0] = Seqnum;
			Start = clock();
			socketAtClient->Send(SendMSG);//��������
			datanum = Seqnum % 10;
			Data[0] = datanum;
			tbSendData->AppendText(""+ datanum);//��ʾ���η��͵�����
			tbSendNum->AppendText(""+Seqnum);//��ʾ���η��͵�֡���
			if (flagError == 0)//�Ƿ��ش�
			{
				tbError->AppendText("��");
			}
			else if (flagError == 1) {
				tbError->AppendText("��");
				flagError = 0;
			}
			tbMSGHistory->AppendText("Send��    ֡���" + Seqnum + "  ����: " + datanum+"\r\n");//����Ϣ��ʷ����ʾ���η��͵�����

			Seqnum++;
			
			Thread::Sleep(1000);

			tbSendData->Clear();//��ձ�����Ϣ����
			tbSendNum->Clear();//��ձ����������
			tbError->Clear();//��ձ����Ƿ��ش�����
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
				int byteCount = socketAtClient->Receive(ACKMSG);//��ʼ��������
				End = clock();
				if (Seqnum - ACKMSG[0] == 5)//��֤��������Ϊ5
				{
					Seqnum--;
					Thread::Sleep(5000);
				}
				if (byteCount > 0) {
					if (ACKMSG[1] == 1 || ACKMSG[1] == 3 || difftime(End,Start) > 1000)//�г�����������Ҫ�ش���ֻҪ֡���������߳�ʱ
					{
						Seqnum--;
						flagError = 1;
					}
					else if (ACKMSG[1] == 2 ) {//����֡��ʧ
						tbMSGHistory->AppendText("Receive: ֡��ʧ:"+ ACKMSG[0] +"\r\n");
					}
					else if (ACKMSG[1] == 3) {
						tbMSGHistory->AppendText("Receive: ֡����:" + ACKMSG[0] + "\r\n");
					}
					else
					{
						int temp = ACKMSG[0] + 1;//���ͳɹ����´������յ���ACK
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