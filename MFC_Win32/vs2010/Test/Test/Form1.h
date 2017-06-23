#pragma once

namespace Test {

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
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::CheckedListBox^  checkedListBox1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::LinkLabel^  linkLabel1;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::MonthCalendar^  monthCalendar1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::NotifyIcon^  notifyIcon1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::RichTextBox^  richTextBox2;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripDropDownButton^  toolStripDropDownButton1;
	private: System::Windows::Forms::ToolStripMenuItem^  y54yr5ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gtygtToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSplitButton^  toolStripSplitButton1;
	private: System::Windows::Forms::ToolStripDropDownButton^  toolStripDropDownButton2;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem4;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem5;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem6;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripContainer^  toolStripContainer1;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::TreeNode^  treeNode1 = (gcnew System::Windows::Forms::TreeNode(L"zzz"));
			System::Windows::Forms::TreeNode^  treeNode2 = (gcnew System::Windows::Forms::TreeNode(L"aaa", gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) {treeNode1}));
			System::Windows::Forms::ListViewGroup^  listViewGroup1 = (gcnew System::Windows::Forms::ListViewGroup(L"ListViewGroup", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(L""));
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->monthCalendar1 = (gcnew System::Windows::Forms::MonthCalendar());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->notifyIcon1 = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripDropDownButton1 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->y54yr5ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gtygtToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSplitButton1 = (gcnew System::Windows::Forms::ToolStripSplitButton());
			this->toolStripDropDownButton2 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem6 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripContainer1 = (gcnew System::Windows::Forms::ToolStripContainer());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->contextMenuStrip1->SuspendLayout();
			this->toolStripContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(139, 160);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 69);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(202, 85);
			this->textBox1->TabIndex = 1;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 12;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(12) {L"dds", L"ds", L"ds", L"ds", L"ds", L"dsd", L"sdssd", 
				L"", L"", L"dsds", L"d", L"s"});
			this->listBox1->Location = System::Drawing::Point(368, 90);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(120, 136);
			this->listBox1->TabIndex = 2;
			// 
			// treeView1
			// 
			this->treeView1->Location = System::Drawing::Point(223, 90);
			this->treeView1->Name = L"treeView1";
			treeNode1->Name = L"节点1";
			treeNode1->Text = L"zzz";
			treeNode2->Name = L"节点0";
			treeNode2->Text = L"aaa";
			this->treeView1->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) {treeNode2});
			this->treeView1->Size = System::Drawing::Size(121, 153);
			this->treeView1->TabIndex = 3;
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Items->AddRange(gcnew cli::array< System::Object^  >(7) {L"ded", L"hghgh", L"dsds", L"ds", L"", L"fsd", 
				L""});
			this->checkedListBox1->Location = System::Drawing::Point(485, 94);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(120, 132);
			this->checkedListBox1->TabIndex = 4;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(7) {L"fd", L"fds", L"dfs", L"dfsd", L"fssd", L"dsf", 
				L"sd"});
			this->comboBox1->Location = System::Drawing::Point(0, 197);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 20);
			this->comboBox1->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(118, 186);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 12);
			this->label1->TabIndex = 6;
			this->label1->Text = L"hello\r\n";
			// 
			// linkLabel1
			// 
			this->linkLabel1->AccessibleRole = System::Windows::Forms::AccessibleRole::Link;
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->linkLabel1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->linkLabel1->LinkVisited = true;
			this->linkLabel1->Location = System::Drawing::Point(458, 229);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(61, 14);
			this->linkLabel1->TabIndex = 7;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"toxuexiao";
			this->linkLabel1->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			// 
			// listView1
			// 
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) {this->columnHeader1});
			listViewGroup1->Header = L"ListViewGroup";
			listViewGroup1->Name = L"listViewGroup1";
			this->listView1->Groups->AddRange(gcnew cli::array< System::Windows::Forms::ListViewGroup^  >(1) {listViewGroup1});
			this->listView1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(1) {listViewItem1});
			this->listView1->Location = System::Drawing::Point(585, 203);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(121, 97);
			this->listView1->TabIndex = 8;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listView1_SelectedIndexChanged);
			// 
			// monthCalendar1
			// 
			this->monthCalendar1->Location = System::Drawing::Point(12, 229);
			this->monthCalendar1->Name = L"monthCalendar1";
			this->monthCalendar1->TabIndex = 9;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(388, 340);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 50);
			this->pictureBox1->TabIndex = 10;
			this->pictureBox1->TabStop = false;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(260, 399);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(318, 23);
			this->progressBar1->TabIndex = 11;
			// 
			// notifyIcon1
			// 
			this->notifyIcon1->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"notifyIcon1.Icon")));
			this->notifyIcon1->Text = L"notifyIcon1";
			this->notifyIcon1->Visible = true;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(244, 270);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(100, 96);
			this->richTextBox1->TabIndex = 12;
			this->richTextBox1->Text = L"";
			// 
			// richTextBox2
			// 
			this->richTextBox2->Location = System::Drawing::Point(52, 517);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->Size = System::Drawing::Size(254, 96);
			this->richTextBox2->TabIndex = 13;
			this->richTextBox2->Text = L"fhcdsicvhgsdifvhc\nvfds\nvfgds\ng\nfdgfdgdhd\ngfh\n\ngs\n";
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Location = System::Drawing::Point(405, 517);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(200, 100);
			this->tabControl1->TabIndex = 14;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->button2);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(192, 74);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"tabPage1";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->label2);
			this->tabPage2->Controls->Add(this->textBox2);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(192, 74);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(49, 7);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 21);
			this->textBox2->TabIndex = 0;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(49, 21);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 0;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// tabPage3
			// 
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(192, 74);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"tabPage3";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(82, 35);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 12);
			this->label2->TabIndex = 1;
			this->label2->Text = L"label2";
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->toolStripProgressBar1, 
				this->toolStripStatusLabel1, this->toolStripDropDownButton1, this->toolStripSplitButton1, this->toolStripDropDownButton2});
			this->statusStrip1->Location = System::Drawing::Point(0, 655);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(784, 22);
			this->statusStrip1->TabIndex = 15;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size(100, 16);
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(118, 17);
			this->toolStripStatusLabel1->Text = L"toolStripStatusLabel1";
			// 
			// toolStripDropDownButton1
			// 
			this->toolStripDropDownButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripDropDownButton1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->y54yr5ToolStripMenuItem});
			this->toolStripDropDownButton1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripDropDownButton1.Image")));
			this->toolStripDropDownButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripDropDownButton1->Name = L"toolStripDropDownButton1";
			this->toolStripDropDownButton1->Size = System::Drawing::Size(29, 20);
			this->toolStripDropDownButton1->Text = L"toolStripDropDownButton1";
			// 
			// y54yr5ToolStripMenuItem
			// 
			this->y54yr5ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->gtygtToolStripMenuItem});
			this->y54yr5ToolStripMenuItem->Name = L"y54yr5ToolStripMenuItem";
			this->y54yr5ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->y54yr5ToolStripMenuItem->Text = L"y54yr5";
			// 
			// gtygtToolStripMenuItem
			// 
			this->gtygtToolStripMenuItem->Name = L"gtygtToolStripMenuItem";
			this->gtygtToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->gtygtToolStripMenuItem->Text = L"gtygt";
			// 
			// toolStripSplitButton1
			// 
			this->toolStripSplitButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripSplitButton1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripSplitButton1.Image")));
			this->toolStripSplitButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripSplitButton1->Name = L"toolStripSplitButton1";
			this->toolStripSplitButton1->Size = System::Drawing::Size(32, 20);
			this->toolStripSplitButton1->Text = L"toolStripSplitButton1";
			// 
			// toolStripDropDownButton2
			// 
			this->toolStripDropDownButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripDropDownButton2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripDropDownButton2.Image")));
			this->toolStripDropDownButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripDropDownButton2->Name = L"toolStripDropDownButton2";
			this->toolStripDropDownButton2->Size = System::Drawing::Size(29, 20);
			this->toolStripDropDownButton2->Text = L"toolStripDropDownButton2";
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->toolStripMenuItem1, 
				this->toolStripMenuItem2, this->toolStripMenuItem3, this->toolStripMenuItem4, this->toolStripMenuItem5, this->toolStripMenuItem6});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->contextMenuStrip1->Size = System::Drawing::Size(181, 136);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(180, 22);
			this->toolStripMenuItem1->Text = L"toolStripMenuItem1";
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(180, 22);
			this->toolStripMenuItem2->Text = L"toolStripMenuItem2";
			// 
			// toolStripMenuItem3
			// 
			this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
			this->toolStripMenuItem3->Size = System::Drawing::Size(180, 22);
			this->toolStripMenuItem3->Text = L"toolStripMenuItem3";
			// 
			// toolStripMenuItem4
			// 
			this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
			this->toolStripMenuItem4->Size = System::Drawing::Size(180, 22);
			this->toolStripMenuItem4->Text = L"toolStripMenuItem4";
			// 
			// toolStripMenuItem5
			// 
			this->toolStripMenuItem5->Name = L"toolStripMenuItem5";
			this->toolStripMenuItem5->Size = System::Drawing::Size(180, 22);
			this->toolStripMenuItem5->Text = L"toolStripMenuItem5";
			// 
			// toolStripMenuItem6
			// 
			this->toolStripMenuItem6->Name = L"toolStripMenuItem6";
			this->toolStripMenuItem6->Size = System::Drawing::Size(180, 22);
			this->toolStripMenuItem6->Text = L"toolStripMenuItem6";
			// 
			// toolStrip1
			// 
			this->toolStrip1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->toolStrip1->Location = System::Drawing::Point(0, 24);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(784, 25);
			this->toolStrip1->TabIndex = 17;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(784, 24);
			this->menuStrip1->TabIndex = 18;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// toolStripContainer1
			// 
			// 
			// toolStripContainer1.ContentPanel
			// 
			this->toolStripContainer1->ContentPanel->Size = System::Drawing::Size(150, 150);
			this->toolStripContainer1->ContentPanel->Load += gcnew System::EventHandler(this, &Form1::toolStripContainer1_ContentPanel_Load);
			this->toolStripContainer1->Location = System::Drawing::Point(596, 442);
			this->toolStripContainer1->Name = L"toolStripContainer1";
			this->toolStripContainer1->Size = System::Drawing::Size(150, 175);
			this->toolStripContainer1->TabIndex = 19;
			this->toolStripContainer1->Text = L"toolStripContainer1";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 677);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->toolStripContainer1);
			this->Controls->Add(this->richTextBox2);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->monthCalendar1);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->linkLabel1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->checkedListBox1);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->treeView1);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->contextMenuStrip1->ResumeLayout(false);
			this->toolStripContainer1->ResumeLayout(false);
			this->toolStripContainer1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->textBox1->Text="世界你好!";

			 }
	
	private: System::Void listView1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void toolStripContainer1_ContentPanel_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

