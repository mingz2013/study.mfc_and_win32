#pragma once

namespace WindowsTest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	protected: 

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::ListViewGroup^  listViewGroup1 = (gcnew System::Windows::Forms::ListViewGroup(L"ListViewGroup", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewGroup^  listViewGroup2 = (gcnew System::Windows::Forms::ListViewGroup(L"ListViewGroup", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewGroup^  listViewGroup3 = (gcnew System::Windows::Forms::ListViewGroup(L"ListViewGroup", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(L""));
			System::Windows::Forms::ListViewItem^  listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(L""));
			System::Windows::Forms::ListViewItem^  listViewItem3 = (gcnew System::Windows::Forms::ListViewItem(L""));
			System::Windows::Forms::ListViewItem^  listViewItem4 = (gcnew System::Windows::Forms::ListViewItem(L""));
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(12, 12);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 20);
			this->comboBox1->TabIndex = 0;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 12;
			this->listBox1->Location = System::Drawing::Point(13, 38);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(120, 88);
			this->listBox1->TabIndex = 1;
			// 
			// listView1
			// 
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->columnHeader1, this->columnHeader2, 
				this->columnHeader3});
			listViewGroup1->Header = L"ListViewGroup";
			listViewGroup1->Name = L"listViewGroup1";
			listViewGroup2->Header = L"ListViewGroup";
			listViewGroup2->Name = L"listViewGroup2";
			listViewGroup3->Header = L"ListViewGroup";
			listViewGroup3->Name = L"listViewGroup3";
			this->listView1->Groups->AddRange(gcnew cli::array< System::Windows::Forms::ListViewGroup^  >(3) {listViewGroup1, listViewGroup2, 
				listViewGroup3});
			this->listView1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(4) {listViewItem1, listViewItem2, 
				listViewItem3, listViewItem4});
			this->listView1->Location = System::Drawing::Point(67, 132);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(222, 124);
			this->listView1->TabIndex = 2;
			this->listView1->UseCompatibleStateImageBehavior = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->comboBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 comboBox1->Items->Add("123");
				 listBox1->
			 }
	};
}

