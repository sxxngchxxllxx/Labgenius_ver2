#pragma once

#define WM_MOTOR_POS_CHANGED	WM_USER + 100
#define WM_WAIT_TIME_CHANGED	WM_USER + 101
#define WM_START_PCR			WM_USER + 102
#define WM_MAGNET_CHANGED		WM_USER + 103
#define WM_HEATING_CHANGED		WM_USER + 104

// Magneto 관련 상수 선언
// 상수 define 이 아니므로, 전체 upper case 를 하지 않고, 첫 문자만 upper 로 naming 설정
namespace Magneto{
//	const static int ComPort = 9;
	const static int BaudRate = 115200;

	const static int MaxSlaves = 3;

	const static CString CompileMessageOk = L"Compile Success";

	const static int TimerRuntaskID = 0x01;
	const static int TimerRuntaskDuration = 200;

	// Motor 좌표 관련 값들
	// 드라이버 배치
	// (위에서 아래로)
	// front
	// 20 - filter
	// 28 - syringe
	// 42 - X axis
	// (위에서 아래로)
	// rear
	// 20 - rotate
	// 28 - Y axis
	// 42 - loading
	// 42 - magnet

	// XY 축 모터
	// X 축: M42, 4 mm/rev, stroke 41.66 mm
	// Y 축: M28, 1 mm/rev
	#define	M_X_AXIS_LEAD	4	// 4 mm/rev
	#define	M_Y_AXIS_LEAD	1	// 4 mm/rev
	#define M_X_AXIS_OFFSET -2	// mm    //center
	#define M_Y_AXIS_OFFSET -16.6	// mm // center
	#define	M_X_AXIS_PUSLE2MILI(pulse)	(pulse / 10000.0 * M_X_AXIS_LEAD)
	#define	M_Y_AXIS_PUSLE2MILI(pulse)	(pulse / 10000.0 * M_Y_AXIS_LEAD)
	// 마그넷 축에 대한 로딩 축의 상대 위치 (옵셋)
	// 챔버 포지션 테이블은 마그넷 축 위치 기준
	// 로드 축과 관계되는 x-y 평면상의 좌표는 이 옵셋을 고려.
	#define M_LOAD_OFFSET_FROM_MAGNET_X (int)(29.1)    // ksy
	#define M_LOAD_OFFSET_FROM_MAGNET_Y (int)( 0.0)    // ksy
	// 챔버 구조
	// 6번 챔버는 믹싱 전용. 바닥에 작은 홈이 있어 마이크로 파이펫 팁에 해당하는 튜브 관통.
	#define	MAX_CHAMBER		6
	#define	MIXING_CHAMBER	5
	// 
	//       (1)
	//        ^
	// (6)    |     (2)
	//    ----+----->
	// (5)    |     (3)
	//        |
	//       (4)
	// 챔버 포지션 (10000 마이크로 스텝 단위)
	// micro step = mm / (mm/rev) * (10000 step/rev)
	#define M_X_AXIS_MAGNET_POSITION (int)((  0.00 + M_X_AXIS_OFFSET) / M_X_AXIS_LEAD * 10000)
	#define M_Y_AXIS_MAGNET_POSITION (int)((  0.00 + M_Y_AXIS_OFFSET) / M_Y_AXIS_LEAD * 10000)
	#define	CHAMBER_1_POS_X	(int)((  0.00 + M_LOAD_OFFSET_FROM_MAGNET_X + M_X_AXIS_OFFSET) / M_X_AXIS_LEAD * 10000)	//       0
	#define	CHAMBER_1_POS_Y	(int)(( 14.49 + M_LOAD_OFFSET_FROM_MAGNET_Y + M_Y_AXIS_OFFSET) / M_Y_AXIS_LEAD * 10000)	//  144900
	#define	CHAMBER_2_POS_X	(int)((-12.55 + M_LOAD_OFFSET_FROM_MAGNET_X + M_X_AXIS_OFFSET) / M_X_AXIS_LEAD * 10000)	//   31375
	#define	CHAMBER_2_POS_Y	(int)((  7.24 + M_LOAD_OFFSET_FROM_MAGNET_Y + M_Y_AXIS_OFFSET) / M_Y_AXIS_LEAD * 10000)	//   72400
	#define	CHAMBER_3_POS_X	(int)((-12.55 + M_LOAD_OFFSET_FROM_MAGNET_X + M_X_AXIS_OFFSET) / M_X_AXIS_LEAD * 10000)	//   31375
	#define	CHAMBER_3_POS_Y	(int)(( -7.24 + M_LOAD_OFFSET_FROM_MAGNET_Y + M_Y_AXIS_OFFSET) / M_Y_AXIS_LEAD * 10000)	//  -72400
	#define	CHAMBER_4_POS_X	(int)((  0.00 + M_LOAD_OFFSET_FROM_MAGNET_X + M_X_AXIS_OFFSET) / M_X_AXIS_LEAD * 10000)	//       0
	#define	CHAMBER_4_POS_Y	(int)((-14.49 + M_LOAD_OFFSET_FROM_MAGNET_Y + M_Y_AXIS_OFFSET) / M_Y_AXIS_LEAD * 10000)	// -144900
	#define	CHAMBER_5_POS_X	(int)(( 12.55 + M_LOAD_OFFSET_FROM_MAGNET_X + M_X_AXIS_OFFSET) / M_X_AXIS_LEAD * 10000)	//  -31375
	#define	CHAMBER_5_POS_Y	(int)(( -7.24 + M_LOAD_OFFSET_FROM_MAGNET_Y + M_Y_AXIS_OFFSET) / M_Y_AXIS_LEAD * 10000)	//  -72400
	#define	CHAMBER_6_POS_X	(int)(( 12.55 + M_LOAD_OFFSET_FROM_MAGNET_X + M_X_AXIS_OFFSET) / M_X_AXIS_LEAD * 10000)	//  -31375
	#define	CHAMBER_6_POS_Y	(int)((  7.24 + M_LOAD_OFFSET_FROM_MAGNET_Y + M_Y_AXIS_OFFSET) / M_Y_AXIS_LEAD * 10000)	//   72400
	static const int gAxisPosition[MAX_CHAMBER][2] = {
		{CHAMBER_1_POS_X, CHAMBER_1_POS_Y},
		{CHAMBER_2_POS_X, CHAMBER_2_POS_Y},
		{CHAMBER_3_POS_X, CHAMBER_3_POS_Y},
		{CHAMBER_4_POS_X, CHAMBER_4_POS_Y},
		{CHAMBER_5_POS_X, CHAMBER_5_POS_Y},
		{CHAMBER_6_POS_X, CHAMBER_6_POS_Y},
	};
	#define M_X_AXIS_SPEED			(int)20000	// microstep / s 
	#define M_Y_AXIS_SPEED			(int)60000

	// M_MAGNET (마그넷 상하 이동)
	// 마그넷 축: M?, 2 mm/rev, stroke ? mm
	#define	M_MAGNET_LEAD				2	// 2 mm/rev
	#define M_MAGNET_OFFSET				0	// mm
	#define	M_MAGNET_PUSLE2MILI(pulse)	(pulse / 10000.0 * M_MAGNET_LEAD)
	#define M_MAGNET_POS_ORIGIN			(int)(     0 + M_MAGNET_OFFSET)
	//#define M_MAGNET_POS_DOWN			(int)(-1*(48 + M_MAGNET_OFFSET) / M_MAGNET_LEAD * 10000)
	//#define M_MAGNET_POS_LOCK			(int)(-1*(50 + M_MAGNET_OFFSET) / M_MAGNET_LEAD * 10000)
	#define M_MAGNET_POS_DOWN			(int)(-1*(42 + M_MAGNET_OFFSET) / M_MAGNET_LEAD * 10000) // test
	#define M_MAGNET_POS_LOCK			(int)(-1*(44 + M_MAGNET_OFFSET) / M_MAGNET_LEAD * 10000) // test
	#define M_MAGNET_SPEED				(int)20000
	// M_LOAD (시약 주입 및 혼합)
	// 로딩 축: M?, 1 mm/rev, stroke ? mm
	#define	M_LOAD_LEAD					1	// 1 mm/rev
	#define M_LOAD_OFFSET				0	// mm
	#define	M_LOAD_PUSLE2MILI(pulse)	(pulse / 10000.0 * M_LOAD_LEAD)
	#define	M_LOAD_POS_ORIGIN			(int)(     0.0 + M_LOAD_OFFSET)
	#define	M_LOAD_POS_LOAD				(int)(-1*(23.0 + M_LOAD_OFFSET) / M_LOAD_LEAD * 10000)
	#define	M_LOAD_POS_MIXING_TOP		(int)(-1*(20.8 + M_LOAD_OFFSET) / M_LOAD_LEAD * 10000)
	#define	M_LOAD_POS_MIXING_BOTTOM	(int)(-1*(30.8 + M_LOAD_OFFSET) / M_LOAD_LEAD * 10000)
	#define M_LOAD_SPEED				(int)20000
	#define M_LOAD_MIXING_SPEED			(int)40000

	// M_SYRINGE (잔여물 제거)
	// 시린지 축: M?, 1 mm/rev, stroke 50 mm
	#define	M_SYRINGE_LEAD					1	// 1 mm/rev
	#define M_SYRINGE_OFFSET				0	// mm
	#define	M_SYRINGE_PUSLE2MILI(pulse)		(pulse / 10000.0 * M_SYRINGE_LEAD)
	#define M_SYRINGE_POS_ORIGIN			(int)(     0.0 + M_SYRINGE_OFFSET)
	#define M_SYRINGE_POS_DOWN				(int)(-1*(40.0 + M_SYRINGE_OFFSET) / M_SYRINGE_LEAD * 10000)
	#define M_SYRINGE_SPEED					(int)100000
	// M_ROTATE (마그넷 회전)
	// 마그넷 회전 축: M?, 회전축, 홈 스위치 장착 요망
	// pulse to mili degree
	#define M_ROTATE_OFFSET					0	// mm
	#define	M_ROTATE_PUSLE2DEGREE(pulse)	(pulse / 10000.0 * 360 * 1000)
	#define M_ROTATE_POS_ORIGIN				(int)(   0 + M_ROTATE_OFFSET)
	#define M_ROTATE_POS_BLOCKED			(int)(   0 + M_ROTATE_OFFSET)
	#define M_ROTATE_POS_WASTE				(int)((+90 + M_ROTATE_OFFSET) / 360.0 * (10000/1))		// (10000 pulse/rev)
	#define M_ROTATE_POS_PCR				(int)((-90 + M_ROTATE_OFFSET) / 360.0 * (10000/1))		// (10000 pulse/rev)
	#define M_ROTATE_SPEED					(int)3500

	//********************************************* 13.10.2015 *********
	//#define M_ROTATING	0
	// Rotating axis
	#define M_CHAMBER_STEP_PER_REV			32000.0
	#define M_CHAMBER_GEAR_RATIO			2
	#define M_CHAMBER_OFFSET				1835 //1197	// origin offset (rotate 축 origin이후 보정 값)
	#define M_CHAMBER_DISK_OFFSET			3695	// 20.7844 deg (디스크 기준점에서 디스크의 홀까지 간격)
	#define M_CHAMBER_BACKLASH				0//680//682
	#define M_CHAMBER_DIFF					1304	// 7.335 deg
	#define M_CHAMBER_INTERVAL				4923	// chamber에 각 간격 사이//(float)27.692
	#define M_CHAMBER_STEP_PER_DEGREE		(float)(M_CHAMBER_GEAR_RATIO*M_CHAMBER_STEP_PER_REV/360)
	#define	M_CHAMBER_PUSLE2DEGREE(pulse)	(pulse / M_CHAMBER_STEP_PER_REV * 360)
	#define M_CHAMBER_SPEED					(int)16000//32000  //(int)16000  //KSY 챔버 회전 속도 

	// pumping axi
	#define PI								(float)3.141592
	#define M_PUMPING_STEP_PER_REV			16000.0 //16000.0
	#define M_PUMPING_LEAD					1		// 1 mm / 1 rev
	#define M_PUMPING_OFFSET				0	    // mm
	#define	M_PUMPING_PUSLE2MILI(pulse)		(pulse / M_PUMPING_STEP_PER_REV * M_PUMPING_LEAD)
	#define	M_PUMPING_POS_ORIGIN			(int)(   0.0 + M_PUMPING_OFFSET)
	#define	M_PUMPING_POS_TOP				(int)((28.00 + M_PUMPING_OFFSET) / M_PUMPING_LEAD * M_PUMPING_STEP_PER_REV)
	#define M_PUMPING_POS_MIXING_TOP		(int)((28.00 + M_PUMPING_OFFSET) / M_PUMPING_LEAD * M_PUMPING_STEP_PER_REV)	// mixing 시에 상단값 설정
	#define	M_PUMPING_POS_BOTTOM			(int)((62.59 + M_PUMPING_OFFSET) / M_PUMPING_LEAD * M_PUMPING_STEP_PER_REV)
	#define M_PUMPING_POS_UP_OFFSET			(int)-7500 //KSY			// -값을 주면 PUMPING 축이 상승(원하는 위치에 도달하지 못했을 때)
															// +값을 주면 PUMPING 축이 하강(원하는 위치보다 초과하였을 때)
	#define M_PUMPING_DISK_RADIUS			(float)2.3	//kSY	// puming syringe의 반지름으로 mm 단위로 입력
	#define M_PUMPING_SPEED					(int)30000//(int)100000
	#define M_PUMPING_MIXING_SPEED			(int)30000//(int)100000

	// filter axis
	#define M_FILTER_STEP_PER_REV			10000.0		// step
	#define M_FILTER_OFFSET					770		// step ( about 5.24 deg)
	#define M_FILTER_GEAR_RATIO				5.25	
	#define M_FILTER_INTERVAL				90			// deg
	#define M_FILTER_INTERVAL_PULSE			(int)(M_FILTER_GEAR_RATIO * M_FILTER_STEP_PER_REV) * ( 90.0 / 360.0)
	#define	M_FILTER_PUSLE2DEGREE(pulse)	(pulse / M_FILTER_STEP_PER_REV * 360)
	#define M_FILTER_SPEED					(int)26250

	// 150920 YJ 
	static const int DefaultPos =			INT_MAX;
};

namespace DriverStatus{
	enum Enum{

		CONNECTED = 0,
		NOT_CONNECTED = 1,
		COMM_ERROR = 2,
		TOO_FEW_SLAVES = 3,
		TOO_MUCH_SLAVES = 4,
		SLAVE_ORDER_ERROR = 5,
		MAX = 5,
	};
};

namespace ProtocolCmd{
	enum Enum{
		GO = 0,
		FILTER = 1,
		MIX = 2,
		WAIT = 3,
		PUMPING_UP = 4,
		PUMPING_DOWN = 5,
		READY = 6,
		HOME = 7,
		
		//siri 151206 - add arduino cmd
		MAGNET_ON = 8,
		MAGNET_OFF = 9,
		HEATING = 10,
		PCR = 11,
		MAX = 11,
	};

	const static CString toString[MAX+1] =
	{
		L"GO", L"FILTER", L"MIX", L"WAIT", L"PUMPING_UP",
		L"PUMPING_DOWN", L"READY", L"HOME", L"MAGNET_ON",
		L"MAGNET_OFF", L"HEATING", L"PCR"
	};
};

namespace ActionCmd{
	enum Enum{
		MOVE_ABS = 0,
		MOVE_INC = 1,
		MOVE_DEC = 2,
		HOME = 3,
		WAIT = 4,
		SECOND_WAIT = 5,
		PROTOCOL_STOP = 6,
		INTERNAL_END = 7,
		
		MAGNET_ON = 8,
		MAGNET_OFF = 9,
		HEATING = 10,
		PCR = 11,
		MAX = 11,
	};

	const static CString toString[MAX + 1] =
	{
		L"MOVE_ABS", L"MOVE_INC", L"MOVE_DEC", L"HOME",
		L"WAIT", L"SECOND_WAIT", L"PROTOCOL_STOP", L"INTERNAL_END",
		L"MAGNET_ON", L"MAGNET_OFF", L"HEATING", L"PCR"
	};
};

namespace MotorType{
	enum Enum{
		CHAMBER = 0,
		FILTER = 1,
		PUMPING = 2,
		X_AXIS = 12,
		Y_AXIS = 13,
		MAGNET = 14,
		LOAD = 15,
		SYRINGE = 16,
		ROTATE = 17,
		MAX = 8,
	};

	const static CString toString[MAX + 1] = {L"CHAMBER", L"FILTER", L"PUMPING", L"X_AXIS", L"Y_AXIS", L"MAGNET", L"LOAD", L"SYRINGE", L"ROTATE"};
};

// Protocol raw data 를 관리하는 구조체
typedef struct PROTOCOL_BINARY{
	int cmd;
	int arg;
} ProtocolBinary;

// Action 들에 대한 cmd 와 argument 를 관리하는 클래스
class ActionBinary{
public:
	int cmd;
	vector<int> args;

	ActionBinary(int cmd, int count, ...) 
		:cmd(cmd)
	{
		va_list ap;
		va_start(ap, count);
		for (int i = 0; i < count; ++i)
			this->args.push_back(va_arg(ap, int));

		va_end(ap);
	}
};

class ActionData{
public:
	int cmd;
	vector<ActionBinary> actions;

	ActionData(int cmd) :cmd(cmd){}
};

class ActionBeans{
public:
	CString parentAction;
	vector<CString> childAction;

	ActionBeans(CString parentAction) :parentAction(parentAction){}
};

// For send message data format
struct MotorPos{
	double targetPos;
	double cmdPos;
};

typedef struct HEATING_CONTROL{
	int temper;
} heat_ctrl;




class CMagneto {

private:
	/** Driver field				***************/
	bool connected;
	int comPortNo;
	int driverErrCnt;

	/** Protocol Management			***************/
	vector<ProtocolBinary> protcolBinary;
	vector<vector<ActionBinary>> preDefinedAction;
	vector<ActionData> actionList;
	
	CString protocolCompile(vector<CString> &protocol);

	void initPredefinedAction();
	void initDriverParameter();

	inline double pulse2mili(MotorType::Enum type, long value){
		if (type == MotorType::CHAMBER) return M_CHAMBER_PUSLE2DEGREE(value);
		else if (type == MotorType::PUMPING) return M_PUMPING_PUSLE2MILI(value);
		else if (type == MotorType::FILTER) return M_FILTER_PUSLE2DEGREE(value);


		else return 0.0;
	}

	/** Operation					***************/
	int currentAction;
	int currentSubAction;

	double currentTargetPos;
	double currnetPos;
	
	bool isStarted;
	bool isCompileEnd;

	/** For Waiting operation		***************/
	bool isWaitEnd;
	int waitCounter;
	HWND hwnd;
	
	/** Constructure field			***************/
public:
	CMagneto();
	virtual ~CMagneto();

	/** Connection					***************/
public:
	void searchPort(vector<CString> &portList);

	DriverStatus::Enum connect(int comPortNo);
	void disconnect();
	bool isConnected();
	void setHwnd(HWND hwnd);

	/** File Management				***************/
public:
	CString loadProtocol(CString filePath);
	bool isCompileSuccess(CString res);
	void generateActionList(vector<ActionBeans> &returnValue);

	/** Operation					***************/
private:
	bool isActionFinished();
	void runNextAction();
	void resetAction();

public:
	void start();
	bool runTask();
	void stop();

	/** For Waiting operation		***************/
public:
	bool isLimitSwitchPushed();
	HWND getSafeHwnd();
	int getWaitingTime();
	void setWaitEnded();
	bool isWaitEnded();
	bool isIdle();
	bool isCompileEnded();
	LPARAM getCurrentAction();
	MotorType::Enum getCurrentMotor();

	// siri 151207
public:
	bool isTargetTemp;
	void CMagneto::setIsTargetTemp(bool isTargetTemp);
	bool CMagneto::getIsStarted();
	int CMagneto::getProtocolLength();
};