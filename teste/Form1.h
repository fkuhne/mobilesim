#pragma once

#include "classRobo.h"
#include "string.h"
#include <iostream>
#include <fstream>

namespace teste {
    using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{ PioneerRobot *robo;
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//			
			tipoconexao->SelectedIndex=0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  tipoconexao;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  s8;

	private: System::Windows::Forms::Label^  s7;

	private: System::Windows::Forms::Label^  s6;

	private: System::Windows::Forms::Label^  s5;

	private: System::Windows::Forms::Label^  s4;

	private: System::Windows::Forms::Label^  s3;

	private: System::Windows::Forms::Label^  s2;

	private: System::Windows::Forms::Label^  s1;
	private: System::Windows::Forms::Label^  lfi;
	private: System::Windows::Forms::Label^  ly;
	private: System::Windows::Forms::Label^  lx;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Button^  button7;

	private: System::ComponentModel::IContainer^  components;

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tipoconexao = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->s8 = (gcnew System::Windows::Forms::Label());
			this->s7 = (gcnew System::Windows::Forms::Label());
			this->s6 = (gcnew System::Windows::Forms::Label());
			this->s5 = (gcnew System::Windows::Forms::Label());
			this->s4 = (gcnew System::Windows::Forms::Label());
			this->s3 = (gcnew System::Windows::Forms::Label());
			this->s2 = (gcnew System::Windows::Forms::Label());
			this->s1 = (gcnew System::Windows::Forms::Label());
			this->lfi = (gcnew System::Windows::Forms::Label());
			this->ly = (gcnew System::Windows::Forms::Label());
			this->lx = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(181, 25);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(91, 22);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Conectar";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(193, 242);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(61, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Desativada";
			// 
			// tipoconexao
			// 
			this->tipoconexao->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->tipoconexao->FormattingEnabled = true;
			this->tipoconexao->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"Robo Simulado", L"Robô Real - Rede Wireless", 
				L"Robô Real - Porta Serial"});
			this->tipoconexao->Location = System::Drawing::Point(12, 25);
			this->tipoconexao->Name = L"tipoconexao";
			this->tipoconexao->Size = System::Drawing::Size(163, 21);
			this->tipoconexao->TabIndex = 0;
			this->tipoconexao->DropDownClosed += gcnew System::EventHandler(this, &Form1::tipoconexao_DropDownClosed);
			this->tipoconexao->Click += gcnew System::EventHandler(this, &Form1::tipoconexao_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(135, 242);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(52, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Conexão:";
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(88, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Tipo de Conexão";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(168, 84);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(46, 22);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Frente";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(110, 128);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(46, 22);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Esq";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(168, 176);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(46, 22);
			this->button4->TabIndex = 6;
			this->button4->Text = L"Tras";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(226, 128);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(46, 22);
			this->button5->TabIndex = 7;
			this->button5->Text = L"Dir";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(168, 128);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(46, 22);
			this->button6->TabIndex = 8;
			this->button6->Text = L"Pára";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 2000;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(14, 128);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(20, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"S1";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(14, 145);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(20, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"S2";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(14, 179);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(20, 13);
			this->label6->TabIndex = 12;
			this->label6->Text = L"S4";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(14, 162);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(20, 13);
			this->label7->TabIndex = 11;
			this->label7->Text = L"S3";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(14, 245);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(20, 13);
			this->label8->TabIndex = 16;
			this->label8->Text = L"S8";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(14, 228);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(20, 13);
			this->label9->TabIndex = 15;
			this->label9->Text = L"S7";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(14, 211);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(20, 13);
			this->label10->TabIndex = 14;
			this->label10->Text = L"S6";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(14, 194);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(20, 13);
			this->label11->TabIndex = 13;
			this->label11->Text = L"S5";
			// 
			// s8
			// 
			this->s8->AutoSize = true;
			this->s8->Location = System::Drawing::Point(40, 245);
			this->s8->Name = L"s8";
			this->s8->Size = System::Drawing::Size(20, 13);
			this->s8->TabIndex = 24;
			this->s8->Text = L"S8";
			// 
			// s7
			// 
			this->s7->AutoSize = true;
			this->s7->Location = System::Drawing::Point(40, 228);
			this->s7->Name = L"s7";
			this->s7->Size = System::Drawing::Size(20, 13);
			this->s7->TabIndex = 23;
			this->s7->Text = L"S7";
			// 
			// s6
			// 
			this->s6->AutoSize = true;
			this->s6->Location = System::Drawing::Point(40, 211);
			this->s6->Name = L"s6";
			this->s6->Size = System::Drawing::Size(20, 13);
			this->s6->TabIndex = 22;
			this->s6->Text = L"S6";
			// 
			// s5
			// 
			this->s5->AutoSize = true;
			this->s5->Location = System::Drawing::Point(40, 194);
			this->s5->Name = L"s5";
			this->s5->Size = System::Drawing::Size(20, 13);
			this->s5->TabIndex = 21;
			this->s5->Text = L"S5";
			this->s5->Click += gcnew System::EventHandler(this, &Form1::label15_Click);
			// 
			// s4
			// 
			this->s4->AutoSize = true;
			this->s4->Location = System::Drawing::Point(40, 179);
			this->s4->Name = L"s4";
			this->s4->Size = System::Drawing::Size(20, 13);
			this->s4->TabIndex = 20;
			this->s4->Text = L"S4";
			// 
			// s3
			// 
			this->s3->AutoSize = true;
			this->s3->Location = System::Drawing::Point(40, 162);
			this->s3->Name = L"s3";
			this->s3->Size = System::Drawing::Size(20, 13);
			this->s3->TabIndex = 19;
			this->s3->Text = L"S3";
			this->s3->Click += gcnew System::EventHandler(this, &Form1::label17_Click);
			// 
			// s2
			// 
			this->s2->AutoSize = true;
			this->s2->Location = System::Drawing::Point(40, 145);
			this->s2->Name = L"s2";
			this->s2->Size = System::Drawing::Size(20, 13);
			this->s2->TabIndex = 18;
			this->s2->Text = L"S2";
			// 
			// s1
			// 
			this->s1->AutoSize = true;
			this->s1->Location = System::Drawing::Point(40, 128);
			this->s1->Name = L"s1";
			this->s1->Size = System::Drawing::Size(20, 13);
			this->s1->TabIndex = 17;
			this->s1->Text = L"S1";
			// 
			// lfi
			// 
			this->lfi->AutoSize = true;
			this->lfi->Location = System::Drawing::Point(40, 94);
			this->lfi->Name = L"lfi";
			this->lfi->Size = System::Drawing::Size(20, 13);
			this->lfi->TabIndex = 30;
			this->lfi->Text = L"S3";
			// 
			// ly
			// 
			this->ly->AutoSize = true;
			this->ly->Location = System::Drawing::Point(40, 77);
			this->ly->Name = L"ly";
			this->ly->Size = System::Drawing::Size(20, 13);
			this->ly->TabIndex = 29;
			this->ly->Text = L"S2";
			// 
			// lx
			// 
			this->lx->AutoSize = true;
			this->lx->Location = System::Drawing::Point(40, 60);
			this->lx->Name = L"lx";
			this->lx->Size = System::Drawing::Size(20, 13);
			this->lx->TabIndex = 28;
			this->lx->Text = L"S1";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(14, 94);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(12, 13);
			this->label15->TabIndex = 27;
			this->label15->Text = L"fi";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(14, 77);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(12, 13);
			this->label16->TabIndex = 26;
			this->label16->Text = L"y";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(14, 60);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(12, 13);
			this->label17->TabIndex = 25;
			this->label17->Text = L"x";
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(138, 206);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(104, 22);
			this->button7->TabIndex = 31;
			this->button7->Text = L"Get Laser";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(295, 264);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->lfi);
			this->Controls->Add(this->ly);
			this->Controls->Add(this->lx);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->s8);
			this->Controls->Add(this->s7);
			this->Controls->Add(this->s6);
			this->Controls->Add(this->s5);
			this->Controls->Add(this->s4);
			this->Controls->Add(this->s3);
			this->Controls->Add(this->s2);
			this->Controls->Add(this->s1);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->tipoconexao);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		   int sucesso;		   

			    if (tipoconexao->SelectedIndex==0) robo = new PioneerRobot(ConexaoSimulacao,"",&sucesso); 		   		   
		   else	if (tipoconexao->SelectedIndex==1) robo = new PioneerRobot(ConexaoRadio,"192.168.1.11",&sucesso);
		   else if (tipoconexao->SelectedIndex==2) robo = new PioneerRobot(ConexaoSerial,"COM4",&sucesso);		   
		   
		   if (sucesso) { label1->Text="Ativada";timer1->Enabled=true;}
		   else			label1->Text="Desativada (ERR)";		   

			 }
	private: System::Void tipoconexao_Click(System::Object^  sender, System::EventArgs^  e) {
			  
			 }
private: System::Void tipoconexao_DropDownClosed(System::Object^  sender, System::EventArgs^  e) {
		 
		 }
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 int s[8];			 
			 robo->getAllSonar(s);

			 char  st[10];					
			 itoa(s[0],st,10);
			 s1->Text=gcnew String(st);

			 itoa(s[1],st,10);
     		 s2->Text=gcnew String(st);

			 itoa(s[2],st,10);
			 s3->Text=gcnew String(st);

			 itoa(s[3],st,10);
			 s4->Text=gcnew String(st);

			 itoa(s[4],st,10);
     		 s5->Text=gcnew String(st);

			 itoa(s[5],st,10);
			 s6->Text=gcnew String(st);

			 itoa(s[6],st,10);
			 s7->Text=gcnew String(st);

			 itoa(s[7],st,10);
			 s8->Text=gcnew String(st);

			 itoa(robo->getXPos(),st,10);
			 lx->Text=gcnew String(st);

			 itoa(robo->getYPos(),st,10);
			 ly->Text=gcnew String(st);

			 itoa(robo->getAngBase(),st,10);
			 lfi->Text=gcnew String(st);
		 }


private: System::Void label17_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label15_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 robo->Move(50,50);
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 robo->Rotaciona(50,1);
		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 robo->Rotaciona(-50,1);
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			robo->Move(-50,-50);			
		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			 robo->pararMovimento();
		 } 
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
			// timer1->Enabled=false;
			 robo->getLaser();
		 }
};
}

