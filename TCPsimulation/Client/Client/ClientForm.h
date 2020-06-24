#pragma once

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Text;
	using namespace System::Threading;
	using namespace System::Timers;

	/// <summary>
	/// ClientForm 摘要
	/// </summary>
	public ref class ClientForm : public System::Windows::Forms::Form
	{
	public:
		ClientForm(void)
		{
			CheckForIllegalCrossThreadCalls = false;
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~ClientForm()
		{
			isStillReceive = false;
			if (components)
			{
				delete components;
			}
		}

	private:Socket ^ socketAtClient;
	private:Thread ^ readThread;
			bool isStillReceive;
			bool isStillSend;
			int datanum = 0;
			int Seqnum = 0;
			int SYN;
			int flagError = 0;//不重传为0
			Int32 action = 0;
	private: System::Windows::Forms::Button^  btnStopConn;
			 array<Byte> ^ACKMSG = gcnew array<Byte>(256);
			 array<Byte>^SendMSG = gcnew array<Byte>(256);//表示当前发送内容，包括数据和帧序号
			 array<Byte>^Data = gcnew array<Byte>(256);//表示当前发送数据
//	private:void ReceiveACK();
	
	private:void SendMessage();
	private:void ReceiveMessage();
	private:void acceptMessage();
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  tbIP;
	private: System::Windows::Forms::TextBox^  tbPort;
	private: System::Windows::Forms::TextBox^  tbSocketConn;
	private: System::Windows::Forms::TextBox^  tbSendData;
	private: System::Windows::Forms::TextBox^  tbSendNum;
	private: System::Windows::Forms::TextBox^  tbRecvNum;
	private: System::Windows::Forms::TextBox^  tbError;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Button^  btnConnectServer;
	private: System::Windows::Forms::Button^  btnSendData;
	private: System::Windows::Forms::Button^  btnRecvData;
	private: System::Windows::Forms::TextBox^  tbMSGHistory;
	private: System::Windows::Forms::Button^  btnStopSendData;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ClientForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->tbIP = (gcnew System::Windows::Forms::TextBox());
			this->tbPort = (gcnew System::Windows::Forms::TextBox());
			this->tbSocketConn = (gcnew System::Windows::Forms::TextBox());
			this->tbSendData = (gcnew System::Windows::Forms::TextBox());
			this->tbSendNum = (gcnew System::Windows::Forms::TextBox());
			this->tbRecvNum = (gcnew System::Windows::Forms::TextBox());
			this->tbError = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->btnConnectServer = (gcnew System::Windows::Forms::Button());
			this->btnSendData = (gcnew System::Windows::Forms::Button());
			this->btnRecvData = (gcnew System::Windows::Forms::Button());
			this->tbMSGHistory = (gcnew System::Windows::Forms::TextBox());
			this->btnStopSendData = (gcnew System::Windows::Forms::Button());
			this->btnStopConn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::HighlightText;
			this->label1->Location = System::Drawing::Point(28, 31);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(113, 15);
			this->label1->TabIndex = 0;
			this->label1->Text = L"服务器IP地址：";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::SystemColors::HighlightText;
			this->label2->Location = System::Drawing::Point(28, 75);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(97, 15);
			this->label2->TabIndex = 1;
			this->label2->Text = L"服务器端口：";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::SystemColors::HighlightText;
			this->label3->Location = System::Drawing::Point(28, 118);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(130, 15);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Socket连接状态：";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::SystemColors::HighlightText;
			this->label4->Location = System::Drawing::Point(28, 160);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(127, 15);
			this->label4->TabIndex = 3;
			this->label4->Text = L"当前发送的数据：";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::SystemColors::HighlightText;
			this->label5->Location = System::Drawing::Point(28, 202);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(97, 15);
			this->label5->TabIndex = 4;
			this->label5->Text = L"本次帧序号：";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::SystemColors::HighlightText;
			this->label6->Location = System::Drawing::Point(28, 242);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(142, 15);
			this->label6->TabIndex = 5;
			this->label6->Text = L"接收应答帧的序号：";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::SystemColors::HighlightText;
			this->label7->Location = System::Drawing::Point(28, 283);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(82, 15);
			this->label7->TabIndex = 6;
			this->label7->Text = L"是否重传：";
			// 
			// tbIP
			// 
			this->tbIP->Location = System::Drawing::Point(220, 21);
			this->tbIP->Name = L"tbIP";
			this->tbIP->Size = System::Drawing::Size(208, 25);
			this->tbIP->TabIndex = 7;
			this->tbIP->Text = L"127.0.0.1";
			this->tbIP->TextChanged += gcnew System::EventHandler(this, &ClientForm::tbIP_TextChanged);
			// 
			// tbPort
			// 
			this->tbPort->Location = System::Drawing::Point(220, 64);
			this->tbPort->Name = L"tbPort";
			this->tbPort->Size = System::Drawing::Size(208, 25);
			this->tbPort->TabIndex = 8;
			this->tbPort->Text = L"8888";
			// 
			// tbSocketConn
			// 
			this->tbSocketConn->Location = System::Drawing::Point(220, 107);
			this->tbSocketConn->Name = L"tbSocketConn";
			this->tbSocketConn->Size = System::Drawing::Size(208, 25);
			this->tbSocketConn->TabIndex = 9;
			this->tbSocketConn->Text = L"未连接";
			// 
			// tbSendData
			// 
			this->tbSendData->Location = System::Drawing::Point(220, 149);
			this->tbSendData->Name = L"tbSendData";
			this->tbSendData->Size = System::Drawing::Size(208, 25);
			this->tbSendData->TabIndex = 10;
			// 
			// tbSendNum
			// 
			this->tbSendNum->Location = System::Drawing::Point(220, 191);
			this->tbSendNum->Name = L"tbSendNum";
			this->tbSendNum->Size = System::Drawing::Size(208, 25);
			this->tbSendNum->TabIndex = 11;
			// 
			// tbRecvNum
			// 
			this->tbRecvNum->Location = System::Drawing::Point(220, 231);
			this->tbRecvNum->Name = L"tbRecvNum";
			this->tbRecvNum->Size = System::Drawing::Size(208, 25);
			this->tbRecvNum->TabIndex = 12;
			// 
			// tbError
			// 
			this->tbError->Location = System::Drawing::Point(220, 272);
			this->tbError->Name = L"tbError";
			this->tbError->Size = System::Drawing::Size(208, 25);
			this->tbError->TabIndex = 13;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::SystemColors::HighlightText;
			this->label8->Location = System::Drawing::Point(28, 327);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(82, 15);
			this->label8->TabIndex = 14;
			this->label8->Text = L"消息历史：";
			// 
			// btnConnectServer
			// 
			this->btnConnectServer->Location = System::Drawing::Point(454, 107);
			this->btnConnectServer->Name = L"btnConnectServer";
			this->btnConnectServer->Size = System::Drawing::Size(149, 26);
			this->btnConnectServer->TabIndex = 15;
			this->btnConnectServer->Text = L"连接服务器";
			this->btnConnectServer->UseVisualStyleBackColor = true;
			this->btnConnectServer->Click += gcnew System::EventHandler(this, &ClientForm::btnConnectServer_Click);
			// 
			// btnSendData
			// 
			this->btnSendData->Location = System::Drawing::Point(220, 318);
			this->btnSendData->Name = L"btnSendData";
			this->btnSendData->Size = System::Drawing::Size(94, 29);
			this->btnSendData->TabIndex = 16;
			this->btnSendData->Text = L"发送消息";
			this->btnSendData->UseVisualStyleBackColor = true;
			this->btnSendData->Click += gcnew System::EventHandler(this, &ClientForm::btnSendData_Click);
			// 
			// btnRecvData
			// 
			this->btnRecvData->Location = System::Drawing::Point(476, 318);
			this->btnRecvData->Name = L"btnRecvData";
			this->btnRecvData->Size = System::Drawing::Size(149, 29);
			this->btnRecvData->TabIndex = 17;
			this->btnRecvData->Text = L"接收服务端ACK";
			this->btnRecvData->UseVisualStyleBackColor = true;
			this->btnRecvData->Click += gcnew System::EventHandler(this, &ClientForm::btnRecvData_Click);
			// 
			// tbMSGHistory
			// 
			this->tbMSGHistory->Location = System::Drawing::Point(31, 369);
			this->tbMSGHistory->Multiline = true;
			this->tbMSGHistory->Name = L"tbMSGHistory";
			this->tbMSGHistory->Size = System::Drawing::Size(594, 299);
			this->tbMSGHistory->TabIndex = 18;
			// 
			// btnStopSendData
			// 
			this->btnStopSendData->Location = System::Drawing::Point(320, 318);
			this->btnStopSendData->Name = L"btnStopSendData";
			this->btnStopSendData->Size = System::Drawing::Size(108, 29);
			this->btnStopSendData->TabIndex = 19;
			this->btnStopSendData->Text = L"停止发送";
			this->btnStopSendData->UseVisualStyleBackColor = true;
			this->btnStopSendData->Click += gcnew System::EventHandler(this, &ClientForm::btnStopSendData_Click);
			// 
			// btnStopConn
			// 
			this->btnStopConn->Location = System::Drawing::Point(454, 149);
			this->btnStopConn->Name = L"btnStopConn";
			this->btnStopConn->Size = System::Drawing::Size(149, 26);
			this->btnStopConn->TabIndex = 20;
			this->btnStopConn->Text = L"断开连接";
			this->btnStopConn->UseVisualStyleBackColor = true;
			this->btnStopConn->Click += gcnew System::EventHandler(this, &ClientForm::btnStopConn_Click);
			// 
			// ClientForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::HighlightText;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(666, 680);
			this->Controls->Add(this->btnStopConn);
			this->Controls->Add(this->btnStopSendData);
			this->Controls->Add(this->tbMSGHistory);
			this->Controls->Add(this->btnRecvData);
			this->Controls->Add(this->btnSendData);
			this->Controls->Add(this->btnConnectServer);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->tbError);
			this->Controls->Add(this->tbRecvNum);
			this->Controls->Add(this->tbSendNum);
			this->Controls->Add(this->tbSendData);
			this->Controls->Add(this->tbSocketConn);
			this->Controls->Add(this->tbPort);
			this->Controls->Add(this->tbIP);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"ClientForm";
			this->Text = L"Client";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnConnectServer_Click(System::Object^  sender, System::EventArgs^  e) {//连接服务器
		readThread = gcnew Thread(gcnew ThreadStart(this, &ClientForm::acceptMessage));
		readThread->Start();
		
	}
	private: System::Void btnSendData_Click(System::Object^  sender, System::EventArgs^  e) {//发送消息按钮
		
		readThread = gcnew Thread(gcnew ThreadStart(this, &ClientForm::SendMessage));
		readThread->Start();
	}
	private: System::Void btnRecvData_Click(System::Object^  sender, System::EventArgs^  e) {//接收服务器端消息
		readThread = gcnew Thread(gcnew ThreadStart(this, &ClientForm::ReceiveMessage));
		readThread->Start();
	}
	private: System::Void btnStopSendData_Click(System::Object^  sender, System::EventArgs^  e) {//停止发送
		isStillSend = false;
		SendMSG[2] = 1;//传递FIN = 1
		socketAtClient->Send(SendMSG);//发送数据
		Thread::Sleep(1000);

	}
	private: System::Void btnStopConn_Click(System::Object^  sender, System::EventArgs^  e) {//断开连接
		isStillReceive = false;
		socketAtClient->Close();
		MessageBox::Show("Client Closed!", "OK");
	}
private: System::Void tbIP_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
};
}
