
// MyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "ArduinoLED.h"
#include "MyDlg.h"
#include "afxdialogex.h"
#include "SerialManager.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно MyDlg



MyDlg::MyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARDUINOLED_DIALOG, pParent)
	, R(128)
	, G(128)
	, B(128)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLOR_PICKER, ColorPicker);
	DDX_Control(pDX, IDC_LUMINANCE_BAR, LuminancePicker);
	DDX_Control(pDX, IDC_RSPIN, RSpin);
	DDX_Control(pDX, IDC_GSPIN, GSpin);
	DDX_Control(pDX, IDC_BSPIN, BSpin);
	DDX_Control(pDX, IDC_EDIT1, REdit);
	DDX_Control(pDX, IDC_EDIT2, GEdit);
	DDX_Control(pDX, IDC_EDIT3, BEdit);
	DDX_Text(pDX, IDC_EDIT1, R);
	DDX_Text(pDX, IDC_EDIT2, G);
	DDX_Text(pDX, IDC_EDIT3, B);
	DDX_Control(pDX, IDC_COMBO_PORTS, PortsCombo);
}

BEGIN_MESSAGE_MAP(MyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COLOR_PICKER, &MyDlg::OnBnClickedColorPicker)
	ON_BN_CLICKED(IDC_LUMINANCE_BAR, &MyDlg::OnBnClickedLuminanceBar)
	ON_EN_CHANGE(IDC_EDIT1, &MyDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &MyDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &MyDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDOK, &MyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений MyDlg

BOOL MyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	ColorPicker.SetColor(RGB(R, G, B));
	ColorPicker.SetType(CMFCColorPickerCtrl::COLORTYPE::PICKER);
	ColorPicker.SetPalette(&ColorPickerPalette);

	LuminancePicker.SetColor(RGB(R, G, B));
	LuminancePicker.SetType(CMFCColorPickerCtrl::COLORTYPE::LUMINANCE);
	LuminancePicker.SetPalette(&LuminancePickerPalette);

	UDACCEL Accel;
	Accel.nInc = 1;
	Accel.nSec = 0;

	RSpin.SetBuddy(&REdit);
	RSpin.SetRange(0, 255);
	RSpin.SetAccel(1, &Accel);

	GSpin.SetBuddy(&GEdit);
	GSpin.SetRange(0, 255);
	GSpin.SetAccel(1, &Accel);

	BSpin.SetBuddy(&BEdit);
	BSpin.SetRange(0, 255);
	BSpin.SetAccel(1, &Accel);
	
	FillPortsCombo();
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void MyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void MyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR MyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void MyDlg::OnBnClickedColorPicker()
{
	// TODO: добавьте свой код обработчика уведомлений
	COLORREF color = ColorPicker.GetColor();
	LuminancePicker.SetColor(color);
	UpdateControls();
}

void MyDlg::UpdateControls()
{
	COLORREF c = ColorPicker.GetColor();
	R = GetRValue(c);
	G = GetGValue(c);
	B = GetBValue(c);

	//RSpin.SetPos(R);
	//GSpin.SetPos(G);
	//BSpin.SetPos(B);

	UpdateData(FALSE);
}

void MyDlg::UpdatePickers()
{
	UpdateData();

	//RSpin.SetPos(R);
	//GSpin.SetPos(G);
	//BSpin.SetPos(B);

	ColorPicker.SetColor(RGB(R, G, B));
	LuminancePicker.SetColor(RGB(R, G, B));
	UpdateControls();
}


void MyDlg::OnBnClickedLuminanceBar()
{
	// TODO: добавьте свой код обработчика уведомлений
	COLORREF color = LuminancePicker.GetColor();
	ColorPicker.SetColor(color);
	UpdateControls();
}


void MyDlg::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO:  Добавьте код элемента управления
	UpdatePickers();
}


void MyDlg::OnEnChangeEdit2()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	UpdatePickers();
}


void MyDlg::OnEnChangeEdit3()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	UpdatePickers();
}

void MyDlg::FillPortsCombo()
{
	SerialManager sm;
	auto ports = sm.GetPortNames();
	PortsCombo.Clear();
	for (auto& item : ports)
	{
		PortsCombo.AddString(item);
	}
	if (!ports.empty())PortsCombo.SetCurSel(0);
}


void MyDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
}
