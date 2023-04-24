/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       shoot.c/h
  * @brief      ������ܡ�
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. ���
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */

#ifndef SHOOT_H
#define SHOOT_H
#include "struct_typedef.h"

#include "CAN_receive.h"
#include "gimbal_task.h"
#include "remote_control.h"
#include "user_lib.h"

#define New_Hero

//������俪��ͨ������
#define SHOOT_RC_MODE_CHANNEL       1
//��̨ģʽʹ�õĿ���ͨ��

#define SHOOT_CONTROL_TIME          GIMBAL_CONTROL_TIME

#define SHOOT_FRIC_PWM_ADD_VALUE    100.0f

////���Ħ���ּ���� �ر�
//#define SHOOT_ON_KEYBOARD           KEY_PRESSED_OFFSET_Q
//#define SHOOT_OFF_KEYBOARD          KEY_PRESSED_OFFSET_E

//�����ɺ� �ӵ�����ȥ���ж�ʱ�䣬�Է��󴥷�
#define SHOOT_DONE_KEY_OFF_TIME     150
//��곤���ж�
#define PRESS_LONG_TIME             400
//ң����������ش��µ�һ��ʱ��� ���������ӵ� �����嵥
#define RC_S_LONG_TIME              2000
//Ħ���ָ��� ���� ʱ��
#define UP_ADD_TIME                 80
//�����������ֵ��Χ
#define HALF_ECD_RANGE              4096
#define ECD_RANGE                   8191
//���rmp �仯�� ��ת�ٶȵı���
#define MOTOR_RPM_TO_SPEED          0.00290888208665721596153948461415f
#define MOTOR_ECD_TO_ANGLE          0.000039929622401811//0.00004036791547f//0.000021305288720633905968306772076277f
#define FULL_COUNT                  10//18
//�����ٶ�
#define TRIGGER_SPEED               0.2f//5.0f
#define CONTINUE_TRIGGER_SPEED      5.0f
#define READY_TRIGGER_SPEED         5.0f

#define KEY_OFF_JUGUE_TIME          500
#define SWITCH_TRIGGER_ON           0
#define SWITCH_TRIGGER_OFF          1

//����ʱ�� �Լ���תʱ��
#define BLOCK_TRIGGER_SPEED         1.0f
#define BLOCK_TIME                  700//1500//700
#define REVERSE_TIME                600//800//500
#define REVERSE_SPEED_LIMIT         13.0f
#define MOVE_TIME                   1500

#define PI_FOUR                     0.78539816339744830961566084581988f
#define PI_TEN                      0.314f
#define PI_SEVEN					0.897f
#define PI_THREE						1.047197551196597746f//1.02f

#ifdef Old_Hero
//�����ֵ��PID
#define TRIGGER_SPEED_PID_KP        500.0f
#define TRIGGER_SPEED_PID_KI        0.0f
#define TRIGGER_SPEED_PID_KD        0.0f

#define TRIGGER_ANGLE_PID_KP        40.0f
#define TRIGGER_ANGLE_PID_KI        0.0f
#define TRIGGER_ANGLE_PID_KD        -5.0f

#define TRIGGER_BULLET_PID_MAX_OUT  10000.0f
#define TRIGGER_BULLET_PID_MAX_IOUT 9000.0f

#define TRIGGER_READY_PID_MAX_OUT   10000.0f
#define TRIGGER_READY_PID_MAX_IOUT  7000.0f

#endif

#ifdef New_Hero                                     //��Ӣ�ۣ����Ĳ�����pid
#define TRIGGER_SPEED_PID_KP        100.0f
#define TRIGGER_SPEED_PID_KI        0.0f
#define TRIGGER_SPEED_PID_KD        0.0f

#define TRIGGER_ANGLE_PID_KP        66.0f//37.0f
#define TRIGGER_ANGLE_PID_KI        0.0f
#define TRIGGER_ANGLE_PID_KD        -6.0f//-4.1f

#define TRIGGER_BULLET_PID_MAX_OUT  10000.0f
#define TRIGGER_BULLET_PID_MAX_IOUT 9000.0f

#define TRIGGER_READY_PID_MAX_OUT   10000.0f
#define TRIGGER_READY_PID_MAX_IOUT  7000.0f

#endif

#define FRIC_LEFT_SPEED_PID_KP      5.0f
#define FRIC_LEFT_SPEED_PID_KI			0.0f
#define FRIC_LEFT_SPEED_PID_KD			0.3f
#define FRIC_RIGHT_SPEED_PID_KP			5.0f
#define FRIC_RIGHT_SPEED_PID_KI     0.0f
#define FRIC_RIGHT_SPEED_PID_KD     0.3f

#define FRIC_LEFT_PID_MAX_OUT   30000.0f
#define FRIC_LEFT_PID_MAX_IOUT  5000.0f
#define FRIC_RIGHT_PID_MAX_OUT   30000.0f
#define FRIC_RIGHT_PID_MAX_IOUT  5000.0f


#define SHOOT_HEAT_REMAIN_VALUE     80

typedef enum
{
    SHOOT_STOP = 0,
    SHOOT_READY_FRIC,
//    SHOOT_READY_BULLET,
//    SHOOT_READY,
    SHOOT_BULLET,
    SHOOT_CONTINUE_BULLET,//Ӣ�۲����������
    SHOOT_DONE,
} shoot_mode_e;

typedef enum
{
	FRIC_OFF = 0,
	FRIC_ON = 1,
} fric_state_e;

typedef struct
{
  const motor_measure_t *fric_motor_measure;
  fp32 accel;
  fp32 speed;
  fp32 speed_set;
  int16_t give_current;
	pid_type_def fric_motor_pid;
} fric_motor_t;




typedef struct
{
    shoot_mode_e shoot_mode;
    const RC_ctrl_t *shoot_rc;
    const motor_measure_t *shoot_motor_measure;
    ramp_function_source_t fric1_ramp;
    uint16_t fric_pwm1;
    ramp_function_source_t fric2_ramp;
    uint16_t fric_pwm2;
    pid_type_def trigger_motor_pid;
	pid_type_def trigger_angle_motor_pid;
    fp32 trigger_speed_set;
    fp32 speed;
    fp32 speed_set;
    fp32 angle;
    fp32 set_angle;
	fp32 angle_begin;
    int16_t given_current;
    int8_t ecd_count;
	
	
    bool_t press_l;
    bool_t press_r;
    bool_t last_press_l;
    bool_t last_press_r;
    uint16_t press_l_time;
    uint16_t press_r_time;
    uint16_t rc_s_time;
	
	uint16_t move_time;
    uint16_t block_time;
    uint16_t reverse_time;
    bool_t move_flag;
	bool_t move_flag2;
    bool_t key;
    uint8_t key_time;

    uint16_t heat_limit;
    uint16_t heat;
		fric_state_e fric_state;
		uint8_t debug_flag;
} shoot_control_t;

//�����������̨ʹ��ͬһ��can��id��Ҳ�����������̨������ִ��

extern void shoot_init(void);
extern int16_t shoot_control_loop(void);




#endif
