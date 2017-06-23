#pragma once

namespace CLRTest {

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
	public: System::Windows::Forms::ListView^  listView1;
	protected: 

	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;

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
			System::Windows::Forms::ListViewGroup^  listViewGroup3 = (gcnew System::Windows::Forms::ListViewGroup(L"ListViewGroup1", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewGroup^  listViewGroup4 = (gcnew System::Windows::Forms::ListViewGroup(L"ListViewGroup2", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewItem^  listViewItem5 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(4) {L"12", 
				L"q", L"aa", L"qq"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem6 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(5) {L"13", 
				L"1", L"2", L"3", L"4"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem7 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(3) {L"we", 
				L"bvgfb", L"bvcbbvc"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem8 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(3) {L"wd", 
				L"ddd", L"ddd"}, -1));
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->SuspendLayout();
			// 
			// listView1
			// 
			this->listView1->AccessibleRole = System::Windows::Forms::AccessibleRole::TitleBar;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->columnHeader1, this->columnHeader2, 
				this->columnHeader3, this->columnHeader4});
			this->listView1->GridLines = true;
			listViewGroup3->Header = L"ListViewGroup1";
			listViewGroup3->Name = L"listViewGroup1";
			listViewGroup4->Header = L"ListViewGroup2";
			listViewGroup4->Name = L"listViewGroup2";
			this->listView1->Groups->AddRange(gcnew cli::array< System::Windows::Forms::ListViewGroup^  >(2) {listViewGroup3, listViewGroup4});
			listViewItem5->Group = listViewGroup3;
			listViewItem5->ToolTipText = L"12";
			listViewItem6->Group = listViewGroup3;
			listViewItem6->ToolTipText = L"23";
			listViewItem7->Group = listViewGroup4;
			listViewItem7->ToolTipText = L"qw";
			this->listView1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(4) {listViewItem5, listViewItem6, 
				listViewItem7, listViewItem8});
			this->listView1->Location = System::Drawing::Point(164, 33);
			this->listView1->Name = L"listView1";
			this->listView1->OwnerDraw = true;
			this->listView1->Size = System::Drawing::Size(279, 261);
			this->listView1->TabIndex = 0;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(676, 325);
			this->Controls->Add(this->listView1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
};
}

