//====================================================================================================
//
// Windows_Calculation(main.cpp)
// Author (kimura kouta)
//
//====================================================================================================
#include<windows.h>//インクリードファイル

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#define CLASS_NAME	"WindowsClass"
#define WINDOW_NAME	"ウィンド表示処理"
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
// プロトタイプ宣言
//=====================================================================================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//====================================================================================================
//  メイン関数
//====================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstaPer, LPSTR lpCnd, int nCandShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							//表示するウィンドウのスタイルを決定
		WindowsProc,						//ウィンドウプロシージャのアドレスを指定
		0,									//通定は使用しないので0
		0,									//通定は使用しないので0
		hInstance,							//windowsの引数のインプット

		LoadIcon(NULL,IDI_APPLICATION),		//タスクバーに
		LoadCursor(NULL,IDC_ARROW),			//使用マウスカーソルの色決定＿変更なし
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,								//メニューを指定
		CLASS_NAME,							//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)		//小さいアイコンの措定＿いじる可能性あり


	};
	HWND hwnd;
	MSG msg;

	//ウィンドウクラスの登録

	{
		RegisterClassEx(&wcex);

		//ウィンドウクラスの登録
		hwnd = CreateWindowEx(0,
			CLASS_NAME,						//ウィンドウクラス名
			WINDOW_NAME,					//ウィンドウの名前
			WS_OVERLAPPEDWINDOW,			//ウィンドウスタイル
			CW_USEDEFAULT,					//ウィンドウの左上X軸_変更の可能性あり
			CW_USEDEFAULT,					//ウィンドウの左上Y軸_変更の可能性あり
			SCLEEN_WIDTH,					//ウィンドウの幅
			SCLEEN_HEIGHT,					//ウィンドウの高さ
			NULL,							//親ウィンドウのハンドル
			NULL,							//メニューハンドルまたは子ウィンドウ
			hInstance,					    //インスタンスハンドル
			NULL);						    //ウィンドウ作成データ
	}

	//ウィンドウの表示
	ShowWindow(hwnd, nCandShow);		//指定されたウィンドウの表示設定
	UpdateWindow(hwnd);					//ウィンドウのクライアント領域更新

										//メッセージループ(メッセージキューからメッセージを取得)
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		//メッセージの翻訳と
		TranslateMessage(&msg);
		DispatchMessage(&msg);//ウィンドウプロシージャに送る

	}

	//ウィンドウクラスの登録解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;

}

//ウィンドウプロシージャー関数
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	HWND hWndButton000;//終了ボタン用
	HWND hWndButton001;//足し算ボタン用
	HWND hWndButton002;//引き算ボタン用
	HWND hWndButton003;//掛け算ボタン用
	HWND hWndButton004;//割り算ボタン用


	static HWND hWndEdit000;//入力テキスト用
	static HWND hWndEdit001;//２つ目の入力テキスト用
	static HWND hWndEdit002;//答えのテキスト用

	char aData000[64];//文字列格納用
	char aData001[64];//文字列格納用
	char aAnswer[64];//文字列格納用

	int nData000;//計算用
	int nData001;//計算用
	int nAnswer;//計算用



	static int nPosX = 10;
	static int nPosY = 10;
	static int nMovX = 3;
	static int nnMovY = 3;
	const RECT rect = { 0,0,SCLEEN_WIDTH ,SCLEEN_HEIGHT };

	switch (uMsg)
	{

	
	case WM_KEYDOWN:  //キーが押された際のメッセージ表示
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "本当に終了しますか？", "警告", MB_YESNO);
	
		case VK_LEFT:
			nPosX++;
			//
			InvalidateRect(hWnd, &rect, FALSE);
			break;
		}

	case WM_CREATE:				//ウィンドウ生成時に発生（一度だけ）

		hWndButton000 = CreateWindowEx(0,//終了処理
									"Button",
									" ",
									(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
									520, 450, 200, 40,//X,Y,幅,高さ
									hWnd,

									(HMENU)ID_BUTTON000,
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
									NULL);
		SetWindowText(hWndButton000, "終了");

		hWndButton001 = CreateWindowEx(0,//足し算の処理
									"Button",
									" ",
									(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
									100, 100, 40, 40,//X,Y,幅,高さ
									hWnd,

									(HMENU)ID_BUTTON001,
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
									NULL);
		SetWindowText(hWndButton001, "+");


		hWndButton002 = CreateWindowEx(0,//引き算の処理
								"Button",
								" ",
								(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
								150, 100, 40, 40,//X,Y,幅,高さ
								hWnd,

								(HMENU)ID_BUTTON002,
								(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
								NULL);
		SetWindowText(hWndButton002, "-");

		hWndButton003 = CreateWindowEx(0,//掛け算の処理
								"Button",
								" ",
								(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
								200, 100, 40, 40,//X,Y,幅,高さ
								hWnd,

								(HMENU)ID_BUTTON003,
								(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
								NULL);
		SetWindowText(hWndButton003, "x");

		hWndButton004 = CreateWindowEx(0,//割り算の処理
							"Button",
							" ",
							(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
							250, 100, 40, 40,//X,Y,幅,高さ
							hWnd,

							(HMENU)ID_BUTTON004,
							(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
							NULL);
		SetWindowText(hWndButton004, "÷");



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


	case WM_DESTROY:  //ウィンドウ確率メッセージ
					  //ウィンドウを破棄(WM_DESTROYメッセージの発生)
		PostQuitMessage(0);    //閉じる処理
		break;



	default:
		break;

	case WM_LBUTTONDOWN:
		//nID = MessageBox(hwnd, "左クリックを押した", "ああ", MB_OK);
		SetFocus(hWnd);
		break;

	case WM_COMMAND:

		if (LOWORD(wParam) == ID_BUTTON000)
		{
			nID = MessageBox(hWnd, "本当に終了しますか？", "警告", MB_YESNO);
			if (nID == IDYES)//YESの時のメッセージ
			{
				DestroyWindow(hWnd);   //[ESC]キーが押された際のメッセージ表示
			}
			break;
		}
		else if (LOWORD(wParam) == ID_BUTTON001)//足し算の計算
		{
			GetWindowText(hWndEdit000, &aData000[0], 64);
			GetWindowText(hWndEdit001, &aData001[0], 64);

			nData000 = atoi(&aData000[0]);
			nData001 = atoi(&aData001[0]);

			nAnswer = nData000 + nData001;
			wsprintf(&aAnswer[0], "%d", nAnswer);

			SetWindowText(hWndEdit002, &aAnswer[0]);
		}
		else if (LOWORD(wParam) == ID_BUTTON002)//引き算の計算
		{
			GetWindowText(hWndEdit000, &aData000[0], 64);
			GetWindowText(hWndEdit001, &aData001[0], 64);

			nData000 = atoi(&aData000[0]);
			nData001 = atoi(&aData001[0]);

			nAnswer = nData000 - nData001;
			wsprintf(&aAnswer[0], "%d", nAnswer);

			SetWindowText(hWndEdit002, &aAnswer[0]);
		}
		else if (LOWORD(wParam) == ID_BUTTON003)//掛け算の計算
		{
			GetWindowText(hWndEdit000, &aData000[0], 64);
			GetWindowText(hWndEdit001, &aData001[0], 64);

			nData000 = atoi(&aData000[0]);
			nData001 = atoi(&aData001[0]);

			nAnswer = nData000 * nData001;
			wsprintf(&aAnswer[0], "%d", nAnswer);

			SetWindowText(hWndEdit002, &aAnswer[0]);
		}
		else if (LOWORD(wParam) == ID_BUTTON004)//割り算の計算
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
		
		nID = MessageBox(hWnd, "本当に終了しますか？", "警告", MB_YESNO);
			if (nID == IDYES)//YESの時のメッセージ
		{
			
			DestroyWindow(hWnd);   //[ESC]キーが押された際のメッセージ表示
		}
		else
		{
			return 0;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}