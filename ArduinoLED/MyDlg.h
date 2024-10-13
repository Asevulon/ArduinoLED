
// MyDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно MyDlg
class MyDlg : public CDialogEx
{
// Создание
public:
	MyDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARDUINOLED_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMFCColorPickerCtrl ColorPicker;
	CMFCColorPickerCtrl LuminancePicker;
	CPalette ColorPickerPalette;
	CPalette LuminancePickerPalette;
	CSpinButtonCtrl RSpin;
	CSpinButtonCtrl GSpin;
	CSpinButtonCtrl BSpin;
	CEdit REdit;
	CEdit GEdit;
	CEdit BEdit;
	int R;
	int G;
	int B;
	afx_msg void OnBnClickedColorPicker();
	void UpdateControls();
	void UpdatePickers();
	afx_msg void OnBnClickedLuminanceBar();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	CComboBox PortsCombo;
	void FillPortsCombo();
	afx_msg void OnBnClickedOk();
};
