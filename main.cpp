//====================================================================================================
//
// Windows_Calculation(main.cpp)
// Author (kimura kouta)
//
//====================================================================================================
#include<windows.h>//�C���N���[�h�t�@�C��

//====================================================================================================
// �}�N����`
//==================================================================================================== 
#define CLASS_NAME	"WindowsClass"
#define WINDOW_NAME	"�E�B���h�\������"
#define SCLEEN_WIDTH	(800)
#define SCLEEN_HEIGHT	(600)
#define ID_BUTTON000 (101)
#define ID_BUTTON001 (102)
#define ID_BUTTON002 (103)
#define ID_BUTTON003 (104)
#define ID_BUTTON004 (105)
#define ID_EDIT000	(111)
#define ID_EDIT001	(112)
#define ID_EDIT002	(113)
#define ID_TIMER	(121)
#define TIMER_INTERVAL	(1000/60)

//====================================================================================================
// �v���g�^�C�v�錾
//=====================================================================================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//====================================================================================================
//  ���C���֐�
//====================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstaPer, LPSTR lpCnd, int nCandShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							//�\������E�B���h�E�̃X�^�C��������
		WindowsProc,						//�E�B���h�E�v���V�[�W���̃A�h���X���w��
		0,									//�ʒ�͎g�p���Ȃ��̂�0
		0,									//�ʒ�͎g�p���Ȃ��̂�0
		hInstance,							//windows�̈����̃C���v�b�g

		LoadIcon(NULL,IDI_APPLICATION),		//�^�X�N�o�[��
		LoadCursor(NULL,IDC_ARROW),			//�g�p�}�E�X�J�[�\���̐F����Q�ύX�Ȃ�
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,								//���j���[���w��
		CLASS_NAME,							//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)		//�������A�C�R���̑[��Q������\������


	};
	HWND hwnd;
	MSG msg;

	//�E�B���h�E�N���X�̓o�^

	{
		RegisterClassEx(&wcex);

		//�E�B���h�E�N���X�̓o�^
		hwnd = CreateWindowEx(0,
			CLASS_NAME,						//�E�B���h�E�N���X��
			WINDOW_NAME,					//�E�B���h�E�̖��O
			WS_OVERLAPPEDWINDOW,			//�E�B���h�E�X�^�C��
			CW_USEDEFAULT,					//�E�B���h�E�̍���X��_�ύX�̉\������
			CW_USEDEFAULT,					//�E�B���h�E�̍���Y��_�ύX�̉\������
			SCLEEN_WIDTH,					//�E�B���h�E�̕�
			SCLEEN_HEIGHT,					//�E�B���h�E�̍���
			NULL,							//�e�E�B���h�E�̃n���h��
			NULL,							//���j���[�n���h���܂��͎q�E�B���h�E
			hInstance,					    //�C���X�^���X�n���h��
			NULL);						    //�E�B���h�E�쐬�f�[�^
	}

	//�E�B���h�E�̕\��
	ShowWindow(hwnd, nCandShow);		//�w�肳�ꂽ�E�B���h�E�̕\���ݒ�
	UpdateWindow(hwnd);					//�E�B���h�E�̃N���C�A���g�̈�X�V

										//���b�Z�[�W���[�v(���b�Z�[�W�L���[���烁�b�Z�[�W���擾)
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		//���b�Z�[�W�̖|���
		TranslateMessage(&msg);
		DispatchMessage(&msg);//�E�B���h�E�v���V�[�W���ɑ���

	}

	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;

}

//�E�B���h�E�v���V�[�W���[�֐�
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	HWND hWndButton000;//�I���{�^���p
	HWND hWndButton001;//�����Z�{�^���p
	HWND hWndButton002;//�����Z�{�^���p
	HWND hWndButton003;//�|���Z�{�^���p
	HWND hWndButton004;//����Z�{�^���p


	static HWND hWndEdit000;//���̓e�L�X�g�p
	static HWND hWndEdit001;//�Q�ڂ̓��̓e�L�X�g�p
	static HWND hWndEdit002;//�����̃e�L�X�g�p

	char aData000[64];//������i�[�p
	char aData001[64];//������i�[�p
	char aAnswer[64];//������i�[�p

	int nData000;//�v�Z�p
	int nData001;//�v�Z�p
	int nAnswer;//�v�Z�p



	static int nPosX = 10;
	static int nPosY = 10;
	static int nMovX = 3;
	static int nnMovY = 3;
	const RECT rect = { 0,0,SCLEEN_WIDTH ,SCLEEN_HEIGHT };

	switch (uMsg)
	{

	
	case WM_KEYDOWN:  //�L�[�������ꂽ�ۂ̃��b�Z�[�W�\��
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�{���ɏI�����܂����H", "�x��", MB_YESNO);
	
		case VK_LEFT:
			nPosX++;
			//
			InvalidateRect(hWnd, &rect, FALSE);
			break;
		}

	case WM_CREATE:				//�E�B���h�E�������ɔ����i��x�����j

		hWndButton000 = CreateWindowEx(0,//�I������
									"Button",
									" ",
									(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
									520, 450, 200, 40,//X,Y,��,����
									hWnd,

									(HMENU)ID_BUTTON000,
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
									NULL);
		SetWindowText(hWndButton000, "�I��");

		hWndButton001 = CreateWindowEx(0,//�����Z�̏���
									"Button",
									" ",
									(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
									100, 100, 40, 40,//X,Y,��,����
									hWnd,

									(HMENU)ID_BUTTON001,
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
									NULL);
		SetWindowText(hWndButton001, "+");


		hWndButton002 = CreateWindowEx(0,//�����Z�̏���
								"Button",
								" ",
								(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
								150, 100, 40, 40,//X,Y,��,����
								hWnd,

								(HMENU)ID_BUTTON002,
								(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
								NULL);
		SetWindowText(hWndButton002, "-");

		hWndButton003 = CreateWindowEx(0,//�|���Z�̏���
								"Button",
								" ",
								(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
								200, 100, 40, 40,//X,Y,��,����
								hWnd,

								(HMENU)ID_BUTTON003,
								(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
								NULL);
		SetWindowText(hWndButton003, "x");

		hWndButton004 = CreateWindowEx(0,//����Z�̏���
							"Button",
							" ",
							(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
							250, 100, 40, 40,//X,Y,��,����
							hWnd,

							(HMENU)ID_BUTTON004,
							(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
							NULL);
		SetWindowText(hWndButton004, "��");



		hWndEdit000 = CreateWindowEx(0,
							"EDIT",
							" ",
							(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT),
							50, 50, 250, 25,
							hWnd,

							(HMENU)ID_EDIT000,
							(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
							NULL);


		hWndEdit001 = CreateWindowEx(0,
								"EDIT",
								" ",
								(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT),
								50, 165, 250, 25,
								hWnd,


								(HMENU)ID_EDIT001,
								(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
								NULL);

		hWndEdit002 = CreateWindowEx(0,
								"EDIT",
								" ",
								(WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_BORDER | ES_RIGHT),
								50, 400, 250, 25,
								hWnd,

								(HMENU)ID_EDIT002,
								(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
								NULL);
		break;


	case WM_DESTROY:  //�E�B���h�E�m�����b�Z�[�W
					  //�E�B���h�E��j��(WM_DESTROY���b�Z�[�W�̔���)
		PostQuitMessage(0);    //���鏈��
		break;



	default:
		break;

	case WM_LBUTTONDOWN:
		//nID = MessageBox(hwnd, "���N���b�N��������", "����", MB_OK);
		SetFocus(hWnd);
		break;

	case WM_COMMAND:

		if (LOWORD(wParam) == ID_BUTTON000)
		{
			nID = MessageBox(hWnd, "�{���ɏI�����܂����H", "�x��", MB_YESNO);
			if (nID == IDYES)//YES�̎��̃��b�Z�[�W
			{
				DestroyWindow(hWnd);   //[ESC]�L�[�������ꂽ�ۂ̃��b�Z�[�W�\��
			}
			break;
		}
		else if (LOWORD(wParam) == ID_BUTTON001)//�����Z�̌v�Z
		{
			GetWindowText(hWndEdit000, &aData000[0], 64);
			GetWindowText(hWndEdit001, &aData001[0], 64);

			nData000 = atoi(&aData000[0]);
			nData001 = atoi(&aData001[0]);

			nAnswer = nData000 + nData001;
			wsprintf(&aAnswer[0], "%d", nAnswer);

			SetWindowText(hWndEdit002, &aAnswer[0]);
		}
		else if (LOWORD(wParam) == ID_BUTTON002)//�����Z�̌v�Z
		{
			GetWindowText(hWndEdit000, &aData000[0], 64);
			GetWindowText(hWndEdit001, &aData001[0], 64);

			nData000 = atoi(&aData000[0]);
			nData001 = atoi(&aData001[0]);

			nAnswer = nData000 - nData001;
			wsprintf(&aAnswer[0], "%d", nAnswer);

			SetWindowText(hWndEdit002, &aAnswer[0]);
		}
		else if (LOWORD(wParam) == ID_BUTTON003)//�|���Z�̌v�Z
		{
			GetWindowText(hWndEdit000, &aData000[0], 64);
			GetWindowText(hWndEdit001, &aData001[0], 64);

			nData000 = atoi(&aData000[0]);
			nData001 = atoi(&aData001[0]);

			nAnswer = nData000 * nData001;
			wsprintf(&aAnswer[0], "%d", nAnswer);

			SetWindowText(hWndEdit002, &aAnswer[0]);
		}
		else if (LOWORD(wParam) == ID_BUTTON004)//����Z�̌v�Z
		{
			GetWindowText(hWndEdit000, &aData000[0], 64);
			GetWindowText(hWndEdit001, &aData001[0], 64);

			nData000 = atoi(&aData000[0]);
			nData001 = atoi(&aData001[0]);

			nAnswer = nData000 / nData001;
			wsprintf(&aAnswer[0], "%d", nAnswer);

			SetWindowText(hWndEdit002, &aAnswer[0]);
		}

		break;

	case WM_CLOSE:
		
		nID = MessageBox(hWnd, "�{���ɏI�����܂����H", "�x��", MB_YESNO);
			if (nID == IDYES)//YES�̎��̃��b�Z�[�W
		{
			
			DestroyWindow(hWnd);   //[ESC]�L�[�������ꂽ�ۂ̃��b�Z�[�W�\��
		}
		else
		{
			return 0;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}