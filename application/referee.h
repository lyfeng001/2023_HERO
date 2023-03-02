#ifndef __REFEREEINFO_H__
#define __REFEREEINFO_H__

/******************
������Ϣ�����͸������֡��װ����
update:
	��������������������
	ȫ�ֱ���˵����uart2referee.h
	֧���ϴ�3��float����
******************/
#include <cstdint>
//#include "sys.h"
#include "stdio.h"  // define NULL
#include "stdbool.h" 
#include "can.h"
#include "main.h"
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef enum
{
    RED_HERO        = 1,
    RED_ENGINEER    = 2,
    RED_STANDARD_1  = 3,
    RED_STANDARD_2  = 4,
    RED_STANDARD_3  = 5,
    RED_AERIAL      = 6,
    RED_SENTRY      = 7,
    BLUE_HERO       = 11,
    BLUE_ENGINEER   = 12,
    BLUE_STANDARD_1 = 13,
    BLUE_STANDARD_2 = 14,
    BLUE_STANDARD_3 = 15,
    BLUE_AERIAL     = 16,
    BLUE_SENTRY     = 17,
} robot_id_t;
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define EN_USART6_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1���� 
#define USART6_dma_rx_len 		80
#define USART6_dma_tx_len 		128
void float2bytes(float chosen_value, u8* res_message);
float _bytes2float(uint8_t* chosen_Message);
void float2bytes(float chosen_value, u8* res_message);
void send_single_icon(char* name, int x, int y, int type, int color);
void send_multi_graphic();
// flaot���ֽڻ�ת
typedef union {
    float f;
    unsigned char b[4];
} Bytes2Float;

// float��u32��ת
typedef union {
    u32 u32_value;
    unsigned char b[4];
} Bytes2U32;


#define REFEREE_FRAME_HEADER_SOF                ((uint8_t)(0xA5))

#define REFEREE_STUDENT_ROBOT_MAX               ((uint16_t)(0x0200))
#define REFEREE_STUDENT_ROBOT_MIN               ((uint16_t)(0x02FF))

#define REFEREE_STUDENT_CLIENT_SOF              ((uint16_t)(0xD180))  //������Ҫ��һ��ID

/* ����״̬���ݣ�0x0001������Ƶ�ʣ�1Hz */
typedef __packed struct
{
	uint8_t game_type : 4;//0-3 bit����������
	uint8_t game_progress : 4;//4-7 bit����ǰ�����׶�
	uint16_t stage_remain_time;//offset=1 ��ǰ�׶�ʣ��ʱ�䣬��λ s
	uint64_t SyncTimeStamp;//offset=3 �����˽��յ���ָ��ľ�ȷ Unix ʱ�䣬�����ض��յ���Ч�� NTP ��������ʱ����Ч
} ext_game_status_t;


/* ����������ݣ�0x0002������Ƶ�ʣ������������� */
typedef __packed struct
{
	uint8_t winner;//0 ƽ�� 1 �췽ʤ�� 2 ����ʤ��
} ext_game_result_t;


/* ������Ѫ�����ݣ�0x0003������Ƶ�ʣ�1Hz */
typedef __packed struct
{
	uint16_t red_1_robot_HP;//offset=0 �� 1 Ӣ�ۻ�����Ѫ����δ�ϳ��Լ�����Ѫ��Ϊ 0
	uint16_t red_2_robot_HP;//offset=2 �� 2 ���̻�����Ѫ��
	uint16_t red_3_robot_HP;//offset=4 �� 3 ����������Ѫ��
	uint16_t red_4_robot_HP;//offset=6 �� 4 ����������Ѫ��
	uint16_t red_5_robot_HP;//offset=8 �� 5 ����������Ѫ��
	uint16_t red_7_robot_HP;//offset=10 �� 7 �ڱ�������Ѫ��
	uint16_t red_outpost_HP;//offset=12 �췽ǰ��սѪ��
	uint16_t red_base_HP;//offset=14 �췽����Ѫ��

	uint16_t blue_1_robot_HP;//offset=16 �� 1 Ӣ�ۻ�����Ѫ��
	uint16_t blue_2_robot_HP;//offset=18 �� 2 ���̻�����Ѫ��
	uint16_t blue_3_robot_HP;//offset=20 �� 3 ����������Ѫ��
	uint16_t blue_4_robot_HP;//offset=22�� 4 ����������Ѫ��
	uint16_t blue_5_robot_HP;//offset=24 �� 5 ����������Ѫ��
	uint16_t blue_7_robot_HP;//offset=26 �� 7 �ڱ�������Ѫ��
	uint16_t blue_outpost_HP;//offset=28 ����ǰ��վѪ��
	uint16_t blue_base_HP;//offset=30 ��������Ѫ��
} ext_game_robot_HP_t;

////���ڷ���״̬��0x0004
//typedef __packed struct
//{
//	uint8_t dart_belong;
//	uint16_t stage_remaining_time;
//}ext_dart_status_t;



/* �˹�������ս���ӳ���ͷ���״̬��0x0005������Ƶ�ʣ�1Hz ���ڷ��ͣ����ͷ�Χ�����л����� */
typedef __packed struct
{
	/* bit[0, 4, 8, 12, 16, 20]Ϊ F1 - F6 ����״̬��0 Ϊδ���1 Ϊ�Ѽ���
	   bit[1-3, 5-7, 9-11, 13-15, 17-19, 21-23]Ϊ F1-F6 ��״̬��Ϣ��*/
	uint8_t F1_zone_status : 1;//0bit F1����״̬
	uint8_t F1_zone_buff_debuff_status : 3;//1-3bit F1״̬��Ϣ
	uint8_t F2_zone_status : 1;//4bit F2����״̬
	uint8_t F2_zone_buff_debuff_status : 3;//5-7bit F2״̬��Ϣ
	uint8_t F3_zone_status : 1;//8bit F3����״̬
	uint8_t F3_zone_buff_debuff_status : 3;//9-11bit F3״̬��Ϣ
	uint8_t F4_zone_status : 1;//12bit F4����״̬
	uint8_t F4_zone_buff_debuff_status : 3;//13-15bit F4״̬��Ϣ
	uint8_t F5_zone_status : 1;//16bit F5״̬��Ϣ
	uint8_t F5_zone_buff_debuff_status : 3;//17-19bit F5״̬��Ϣ
	uint8_t F6_zone_status : 1;//20bit F6״̬��Ϣ
	uint8_t F6_zone_buff_debuff_status : 3;//21-23bit F6״̬��Ϣ
	uint16_t red1_bullet_left;//offset=3 �췽 1 ��ʣ�൯��
	uint16_t red2_bullet_left;//offset=5 �췽 2 ��ʣ�൯��
	uint16_t blue1_bullet_left;//offset=7 ���� 1 ��ʣ�൯��
	uint16_t blue2_bullet_left;//offset=9 ���� 2 ��ʣ�൯��
} ext_ICRA_buff_debuff_zone_status_t;


/* �����¼����ݣ�0x0101������Ƶ�ʣ�1Hz */
typedef __packed struct
{
	/*
	bit 8�������� R4/B4 ���θߵ�ռ��״̬ 1 Ϊ��ռ��
	bit 9���������ػ���״̬��1 Ϊ���������⻤��Ѫ����0 Ϊ���������⻤��Ѫ����
	bit 10������ǰ��ս״̬��
	1 Ϊǰ��ս��
	0 Ϊǰ��ս�����٣�
	bit 10 -31: ����
	*/
	uint32_t event_type;
} ext_event_data_t;


/* ����վ������ʶ��0x0102������Ƶ�ʣ������ı����, ���ͷ�Χ������������ */
typedef __packed struct
{
	uint8_t supply_projectile_id;//offset=0 ����վ�� ID�� 1��1 �Ų����ڣ� 2��2 �Ų�����
	/*
	���������� ID��0 Ϊ��ǰ�޻����˲�����1 Ϊ�췽Ӣ�ۻ����˲�����2 Ϊ�췽���̻�
���˲�����3/4/5 Ϊ�췽���������˲�����101 Ϊ����Ӣ�ۻ����˲�����102 Ϊ������
�̻����˲�����103/104/105 Ϊ�������������˲���
	*/
	uint8_t supply_robot_id;//offset=1 ˵������
	uint8_t supply_projectile_step;//offset=2 �����ڿ���״̬��0 Ϊ�رգ�1 Ϊ�ӵ�׼���У�2 Ϊ�ӵ�����
	uint8_t supply_projectile_num;//����������50��50 ���ӵ���100��100 ���ӵ���150��150 ���ӵ���200��200 ���ӵ���
} ext_supply_projectile_action_t;



//----���о�����Ϣ----
typedef __packed struct  //cmd_id (0x0104)
{
	uint8_t level;         //1:���� 2:���� 3:�и�
	uint8_t foul_robot_id;   //�и�ʱ��������IDΪ0�����ơ�������Ϊ���������ID
} ext_referee_warning_t;


//----���ڷ���ڵ���ʱ----
typedef __packed struct  //cmd_id(0x0105)
{
	uint8_t dart_remaining_time;  //15s����ʱ
} ext_dart_remaining_time_t;


//----����������״̬----
typedef __packed struct  //cmd_id(0x0201)
{
	uint8_t robot_id;
	//��������ID��1���췽Ӣ�ۻ����ˣ�2���췽���̻����ˣ�3/4/5���췽���������ˣ�6���췽���л����ˣ�
	//   7���췽�ڱ������ˣ�8���췽���ڻ����ˣ�9���췽�״�վ��101������Ӣ�ۻ����ˣ�102���������̻����ˣ�
	//   103/104/105���������������ˣ�106���������л����ˣ�107�������ڱ������ˣ�108���������ڻ����ˣ�109�������״�վ��

	uint8_t robot_level; //�����˵ȼ�  1��һ��  2������  3������
	uint16_t remain_HP;  //������ʣ��Ѫ��
	uint16_t max_HP;     //����������Ѫ��

	uint16_t shooter_id1_17mm_cooling_rate;  //������1��17mmǹ��ÿ����ȴֵ
	uint16_t shooter_id1_17mm_cooling_limit; //������1��17mmǹ����������
	uint16_t shooter_id1_17mm_speed_limit;   //������1��17mmǹ�������ٶ� ��λm/s

	uint16_t shooter_id2_17mm_cooling_rate;  //������2��17mmǹ��ÿ����ȴֵ
	uint16_t shooter_id2_17mm_cooling_limit; //������2��17mmǹ����������
	uint16_t shooter_id2_17mm_speed_limit;   //������2��17mmǹ�������ٶ� ��λm/s

	uint16_t shooter_id1_42mm_cooling_rate;  //������42mmǹ��ÿ����ȴֵ
	uint16_t shooter_id1_42mm_cooling_limit; //������42mmǹ����������
	uint16_t shooter_id1_42mm_speed_limit;   //������42mmǹ�������ٶ� ��λm/s

	uint16_t chassis_power_limit;    //�����˵��̹�����������
	uint8_t mains_power_gimbal_output : 1;  //���ص�Դ������  0bit:gimbal���    0Ϊ��24V�����1Ϊ��24V���
	uint8_t mains_power_chassis_output : 1; //                 1bit:chassis���   
	uint8_t mains_power_shooter_output : 1; //                 2bit:shooter���  
} ext_game_robot_status_t;


//----ʵʱ������������----
typedef __packed struct  // 0x0202
{
	uint16_t chassis_volt;  //���������ѹ ��λ ����
	uint16_t chassis_current;  //����������� ��λ ����
	float chassis_power;  //����������� ��λ W ��
	uint16_t chassis_power_buffer;  //���̹��ʻ��� ��λ J ���� ��ע�����¸��ݹ���������250J
	uint16_t shooter_id1_17mm_cooling_heat;  //1��17mm ǹ������
	uint16_t shooter_id2_17mm_cooling_heat;  //2��17mmǹ������
	uint16_t shooter_id1_42mm_cooling_heat;  //42mm ǹ������
} ext_power_heat_data_t;


//----������λ��----
typedef __packed struct  //0x0203
{
	float x;  //λ��x���꣬��λm
	float y;  //λ��y���꣬��λm
	float z;  //λ��z���꣬��λm
	float yaw;  //λ��ǹ�ڣ���λ��
} ext_game_robot_pos_t;


//----����������----
typedef __packed struct  //0x0204
{
	uint8_t power_rune_buff;
	//bit 0��������Ѫ����Ѫ״̬; bit 1��ǹ��������ȴ����; bit 2�������˷����ӳ�; bit 3�������˹����ӳ�; ����bit����

}ext_buff_t;


//----���л���������״̬----
typedef __packed struct  //0x0205
{
	uint8_t attack_time;   //�ɹ���ʱ�� ��λ s��30s �ݼ���0
} aerial_robot_energy_t;


//----�˺�״̬----
typedef __packed struct //0x0206
{
	uint8_t armor_id : 4;
	uint8_t hurt_type : 4;
	//bit 0-3����Ѫ���仯����Ϊװ���˺�������װ��ID��������ֵΪ0-4�Ŵ��������˵����װ��Ƭ������Ѫ���仯���ͣ��ñ�����ֵΪ0��
	//bit 4-7��Ѫ���仯����
	//0x0 װ���˺���Ѫ��
	//0x1 ģ����߿�Ѫ��
	//0x2 �����ٿ�Ѫ��
	//0x3 ��ǹ��������Ѫ��
	//0x4 �����̹��ʿ�Ѫ��
	//0x5 װ��ײ����Ѫ
} ext_robot_hurt_t;


//----ʵʱ�����Ϣ----
typedef __packed struct  //0x0207
{
	uint8_t bullet_type;  //�ӵ�����: 1��17mm���� 2��42mm����
	uint8_t shooter_id;   //�������ID��1��1��17mm�������; 2��2��17mm�������; 3��42mm �������
	uint8_t bullet_freq;  //�ӵ���Ƶ ��λ Hz
	float bullet_speed;   //�ӵ����� ��λ m/s
} ext_shoot_data_t;


//----�ӵ�ʣ�෢����----
typedef __packed struct  //0x0208
{
	uint16_t remaining_num_17mm;  //17mm�ӵ�ʣ�෢����Ŀ
	uint16_t remaining_num_42mm;  //42mm�ӵ�ʣ�෢����Ŀ
	uint16_t coin_remaining_num;  //ʣ��������
} ext_bullet_remaining_t;


//----������RFID״̬----
typedef __packed struct  //0x0209
{
	uint32_t rfid_status;
	//bit 0�����������RFID״̬��   bit 1���ߵ������RFID״̬��   bit 2���������ؼ����RFID״̬��  bit 3�����������RFID״̬��
	//bit 4��ǰ�ڸ������RFID״̬�� bit 6����Ѫ�������RFID״̬�� bit 7�����̻����˸��RFID״̬�� bit 8-31������

} ext_rfid_status_t;


//----���ڻ����˿ͻ���ָ������----
typedef __packed struct  //0x020A
{
	uint8_t dart_launch_opening_status;
	//��ǰ���ڷ���ڵ�״̬: 1���ر�; 2�����ڿ������߹ر���; 0���Ѿ�����	
	uint8_t dart_attack_target;
	//���ڵĴ��Ŀ�꣬Ĭ��Ϊǰ��վ; 0��ǰ��վ; 1�����ء�

	uint16_t target_change_time;  //�л����Ŀ��ʱ�ı���ʣ��ʱ�䣬��λ�룬��δ�л�Ĭ��Ϊ0
	uint16_t operate_launch_cmd_time;  //���һ�β�����ȷ������ָ��ʱ�ı���ʣ��ʱ�䣬��λ��, ��ʼֵΪ0��
} ext_dart_client_cmd_t;


/*----------0x0301���ֿ�ʼ------------*/
//----�������ݽ�����Ϣ----
typedef __packed struct //0x0301
{
	uint16_t data_cmd_id;//���� ID
	uint16_t sender_ID;//�����ߵ� ID
	uint16_t receiver_ID;//�����ߵ� ID
}ext_student_interactive_header_data_t;//ѧ�������˼�ͨ�����ݶ�ͷ�ṹ


//----�����˼佻������----
typedef __packed struct
{
	ext_student_interactive_header_data_t header_data;//ѧ�������˼�ͨ�����ݶ�ͷ�ṹ
	uint8_t data[113];/*���ݶγ���С��113 */
} robot_interactive_data_t;//���� ID:0x0200~0x02FF


//----�ͻ���ɾ��ͼ��----
typedef __packed struct
{
	//���� ID:0x0100
	ext_student_interactive_header_data_t header_data;//ѧ�������˼�ͨ�����ݶ�ͷ�ṹ
	uint8_t operate_tpye; /*ͼ�β���������:
							0: �ղ�����
							1: ɾ��ͼ�㣻
							2: ɾ�����У�
							*/
	uint8_t layer;         //ͼ������0~9
} ext_client_custom_graphic_delete_t;


//----ͼ������----
typedef __packed struct
{
	uint8_t graphic_name[3];//ͼ����,��ɾ�����޸ĵȲ����У���Ϊ�ͻ��˵�������
	uint32_t operate_tpye : 3; //bit 0 - 2��ͼ�β���
	uint32_t graphic_tpye : 3;//Bit 3-5��ͼ������
	uint32_t layer : 4;// Bit 6 - 9��ͼ������0~9
	uint32_t color : 4;//Bit 10-13����ɫ
	uint32_t start_angle : 9;//Bit 14-22����ʼ�Ƕȣ���λ���㣬��Χ[0,360]��
	uint32_t end_angle : 9;//Bit 23-31����ֹ�Ƕȣ���λ���㣬��Χ[0,360]��
	uint32_t width : 10;//Bit 0-9���߿���
	uint32_t start_x : 11;//Bit 10-20����� x ���ꣻ
	uint32_t start_y : 11;//Bit 21-31����� y ���ꡣ
	uint32_t radius : 10;//Bit 0-9�������С���߰뾶��
	uint32_t end_x : 11;//Bit 10-20���յ� x ���ꣻ
	uint32_t end_y : 11;//Bit 21-31���յ� y ���ꡣ
} graphic_data_struct_t;//��������ֲ�22ҳ��


//----�ͻ��˻���һ��ͼ��----
typedef __packed struct
{
	//���� ID:0x0101
	ext_student_interactive_header_data_t header_data; //ѧ�������˼�ͨ�����ݶ�ͷ�ṹ
	graphic_data_struct_t graphic_data_struct;//ͼ�� 1 
} ext_client_custom_graphic_single_t;

//----�ͻ��˻�������ͼ��----
typedef __packed struct
{
	//���� ID:0x0102
	ext_student_interactive_header_data_t header_data;  //ѧ�������˼�ͨ�����ݶ�ͷ�ṹ
	graphic_data_struct_t graphic_data_struct[2];//ͼ��1��2
} ext_client_custom_graphic_double_t;


//----�ͻ��˻������ͼ��----
typedef __packed struct
{
	//���� ID:0x0103
	ext_student_interactive_header_data_t header_data;//ѧ�������˼�ͨ�����ݶ�ͷ�ṹ
	graphic_data_struct_t graphic_data_struct[5];//ͼ��1~5
} ext_client_custom_graphic_five_t;

//----�ͻ��˻����߸�ͼ��----
typedef __packed struct
{
	//���� ID:0x0104
	ext_student_interactive_header_data_t header_data;//ѧ�������˼�ͨ�����ݶ�ͷ�ṹ
	graphic_data_struct_t graphic_data_struct[7];//ͼ��1~7
} ext_client_custom_graphic_seven_t;

//----�ͻ��˻����ַ�----

typedef __packed struct
{
	//���� ID:0x0110
	ext_student_interactive_header_data_t header_data;//ѧ�������˼�ͨ�����ݶ�ͷ�ṹ
	graphic_data_struct_t graphic_data_struct;//�ַ�����
	uint8_t data[30];                        //�ַ�
} ext_client_custom_character_t;
/*----------0x0301���ֽ���------------*/




//----�������ݽ�����Ϣ----
//����Ƶ�ʣ����� 30Hz
//typedef __packed struct //0x0302
//{
//	uint8_t data[]; //���ݶ�����,��С���Ϊ30�ֽڡ�
//} robot_interactive_data_t;



//----С��ͼ�·���Ϣ��ʶ----
/*����Ƶ�ʣ�����ʱ����.*/
typedef __packed struct  //0x0303
{
	float target_position_x;//Ŀ�� x λ�����꣬��λ m,������Ŀ������� ID ʱ������Ϊ 0
	float target_position_y;//Ŀ�� y λ�����꣬��λ m,������Ŀ������� ID ʱ������Ϊ 0
	float target_position_z;//Ŀ�� z λ�����꣬��λ m,������Ŀ������� ID ʱ������Ϊ 0
	uint8_t commd_keyboard;//����ָ��ʱ����̨�ְ��µļ�����Ϣ ,�ް���������Ϊ 0
	uint16_t target_robot_ID;//Ҫ���õ�Ŀ������� ID,������λ����Ϣʱ������Ϊ 0
	/*������ID��Ӧ��������ֲ�27ҳ*/


	//0x0304����һ����˽ṹ������
	int16_t mouse_x;			//��� X ����Ϣ
	int16_t mouse_y;			//��� Y ����Ϣ
	int16_t mouse_z;			//��������Ϣ
	uint8_t left_button_down;		//������
	uint8_t right_button_down;		//����Ҽ�����
	uint16_t keyboard_value;	//������Ϣ
	uint16_t reserved;			//����λ
} ext_robot_command_t;


//----С��ͼ������Ϣ��ʶ----
//������Ƶ�ʣ�10Hz��
//�״�վ���͵�������Ϣ���Ա����м����������ڵ�һ�ӽ�С��ͼ������
typedef __packed struct   //0x0305
{
	uint16_t target_robot_ID;//Ŀ������� ID 
	float target_position_x;//Ŀ�� x λ�����꣬��λ m
	float target_position_y;//Ŀ�� y λ�����꣬��λ m 
} ext_client_map_command_t;// �ͻ��˽�����Ϣ�����и�� x,y ��������ʱ����ʾ��



/*
������Ϣ��
bit 0������ W �Ƿ���
bit 1������ S �Ƿ���
bit 2������ A �Ƿ���
bit 3������ D �Ƿ���
bit 4������ SHIFT �Ƿ���
bit 5������ CTRL �Ƿ���
bit 6������ Q �Ƿ���
bit 7������ E �Ƿ���
bit 8������ R �Ƿ���
bit 9������ F �Ƿ���
bit 10������ G �Ƿ���
bit 11������ Z �Ƿ���
bit 12������ X �Ƿ���
bit 13������ C �Ƿ���
bit 14������ V �Ƿ���
bit 15������ B �Ƿ���
*/


// ʹ����������֡���̸���ȫ��������Ϣ��ؽṹ�塣(��У��)
// u8 frame_interpret(uint8_t * frame);
bool frame_interpret(uint8_t* _frame, uint16_t size);

// ���뵥�ֽ�������ȫ��������Ϣ��ؽṹ��, 
// �����ۻ��ֽ�Ϊһ�������ݰ�ʱ �ŵ���frame_interpret���� ��������ؽṹ�塣
void referee_info_update(uint8_t single_byte);
// �Զ�������֡, ��װ������ͷָ��custom_frame������ = 5+2+12+2 = 21
// ����ǰ��ȷ��ȫ�ֱ���MyData�ṹ���Ѹ���ֵ, 
// ����ʾ��:
// for(i=0;i<21;i++) {
//     USART_SendData(USART2, custom_frame_test[i]);
//     while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET);
// }


// debug�õ�ȫ�ֱ���
extern u8 referee_message[64];  // ��������֡���, ����44�͹���
extern u8 cmdID;;
extern u8 blood_counter;  // (debug)�������

// ������ʱ����
//// У������֡, CRC8��CRC16
//u8 Verify_frame(uint8_t * frame);

extern void update_from_dma(void);
extern u8 seq_real;
extern u8 usart6_dma_flag;
extern int shoot_counter_referee;
extern ext_game_status_t                           ext_game_state;// ����������Ϣ��0x0001��
extern ext_game_status_t                           ext_game_state;// ����״̬���ݣ�0x0001��
extern ext_game_result_t                          ext_game_result;//�����������(0x0002)
extern ext_game_robot_HP_t                 ext_game_robot_survivors;//�����˴������ݣ�0x0003��
//extern ext_dart_status_t                          ext_dart_status;//���ڷ���״̬��0x0004��
extern ext_event_data_t                           ext_event_data;//����ʱ�¼����ݣ�0x0101��
extern ext_supply_projectile_action_t             ext_supply_projectile_action;//����վ������ʶ��0x0102��
//extern ext_supply_projectile_booking_t            ext_supply_projectile_booking;//����վԤԼ�ӵ���0x0103��
extern ext_referee_warning_t                      ext_referee_warning;//���о�����Ϣ��0x0104��
extern ext_dart_remaining_time_t                  ext_dart_remaining_time;//���ڷ���ڵ���ʱ(0x0105)
extern ext_game_robot_status_t                     ext_game_robot_status;//����������״̬(0x0201)
extern ext_power_heat_data_t                      ext_power_heat_data;////ʵʱ�����������ݣ�0x0202��
extern ext_game_robot_pos_t                       ext_game_robot_pos;//������λ�ã�0x0203��
extern ext_buff_t                                 ext_buff;//���������棨0x0204��
extern aerial_robot_energy_t                      ext_aerial_robot_energy;//���л���������״̬��0x0205��
extern ext_robot_hurt_t                           ext_robot_hurt;//�˺�״̬��0x0206��
extern ext_shoot_data_t                           ext_shoot_data;//ʵʱ�����Ϣ��0x0207��
extern ext_bullet_remaining_t                     ext_bullet_remaining;//�ӵ�ʣ�෢����(0x0208)
extern ext_rfid_status_t                          ext_rfid_status;//������RFID״̬(0x0209)
extern ext_dart_client_cmd_t                      ext_dart_client_cmd;//���ڻ����˿ͻ���ָ������(0x020A)
extern graphic_data_struct_t                      graphic_data_struct;

extern ext_student_interactive_header_data_t      ext_student_interactive_header_data;//�������ݽ�����Ϣ��0x0301��
extern ext_client_custom_graphic_delete_t         ext_client_custom_graphic_delete;
extern ext_client_custom_graphic_single_t         ext_client_custom_graphic_single;
extern ext_client_custom_graphic_double_t         ext_client_custom_graphic_double;
extern ext_client_custom_graphic_five_t           ext_client_custom_graphic_five;
extern ext_client_custom_graphic_seven_t          ext_client_custom_graphic_seven;
//extern ext_robot_command_t                        ext_robot_command;//С��ͼ�������ݣ�0x0303��
extern robot_interactive_data_t                   robot_interactive_data;  //��������



/************************************************************/
typedef enum {
	game_status = 0x0001,     /*!< frequency = 1Hz */
	game_result = 0x0002,     /*!< send at game ending */
	game_robot_HP = 0x0003,     /*!< frequency = 1Hz */
//	dart_status = 0x0004,
  ICRA_buff_debuff_zone_status = 0x0005,
	event_data = 0x0101,     /*!< send at event changing */
	supply_projectile_action = 0x0102,     /*!< send at action */
//    supply_projectile_booking   = 0x0103,     /*!< send by user, max frequency = 10Hz */
referee_warning = 0x0104,
dart_remaining_time = 0x0105,
game_robot_status = 0x0201,     /*!< frequency = 10Hz */
power_heat_data = 0x0202,     /*!< frequency = 50Hz */
game_robot_pos = 0x0203,     /*!< frequency = 10Hz */
buff = 0x0204,     /*!< send at changing */
aerial_robot_energy = 0x0205,     /*!< frequency = 10Hz, only for aerial robot */
robot_hurt = 0x0206,     /*!< send at hurting */
shoot_data = 0x0207,     /*!< send at shooting */
bullet_remaining = 0x0208,
rfid_status = 0x0209,
dart_client_cmd = 0x020A,
student_interactive_header = 0x0301, /*!< send by user, max frequency = 10Hz */
robot_command = 0x0302,
} ext_cmd_id_t;

typedef __packed struct {     //֡ͷ����
	uint8_t     sof;                    /*!< Fixed value 0xA5 */
	uint16_t    data_length;            /*!< Length of next data pack */
	uint8_t     seq;                    /*!< Pack sequene id */
	uint8_t     crc8;                   /*!< CRC checksum for frame header pack */
} ext_frame_header_t;

typedef enum {
	robotid_red_hero = 1,
	robotid_red_engineer = 2,
	robotid_red_infantry_1 = 3,
	robotid_red_infantry_2 = 4,
	robotid_red_infantry_3 = 5,
	robotid_red_aerial = 6,
	robotid_red_sentry = 7,
	robotid_red_radar = 9,         //�����췽�״�վID
	robotid_blue_hero = 101,
	robotid_blue_engineer = 102,
	robotid_blue_infantry_1 = 103,
	robotid_blue_infantry_2 = 104,
	robotid_blue_infantry_3 = 105,
	robotid_blue_aerial = 106,
	robotid_blue_sentry = 107,
	robotid_blue_radar = 109,     //���������״�վID 

	clientid_red_hero = 0x0101,
	clientid_red_engineer = 0x0102,
	clientid_red_infantry_1 = 0x0103,
	clientid_red_infantry_2 = 0x0104,
	clientid_red_infantry_3 = 0x0105,
	clientid_red_aerial = 0x0106,
	clientid_blue_hero = 0x0165,
	clientid_blue_engineer = 0x0166,
	clientid_blue_infantry_1 = 0x0167,
	clientid_blue_infantry_2 = 0x0168,
	clientid_blue_infantry_3 = 0x0169,
	clientid_blue_aerial = 0x016A,
} ext_id_t;

//typedef __packed union {
//    uint8_t     masks;
//    __packed struct {
//        uint8_t     led1 : 1;
//        uint8_t     led2 : 1;
//        uint8_t     led3 : 1;
//        uint8_t     led4 : 1;
//        uint8_t     led5 : 1;
//        uint8_t     led6 : 1;
//        uint8_t     : 2;
//    } masks_bits;
//} ext_client_custom_data_mask_t;

typedef __packed struct {
	ext_frame_header_t              header;
	uint16_t                        cmd_id;

	uint16_t                        data_id;            /*!< fixed value 0xD180 */
	uint16_t                        sender_id;
	uint16_t                        client_id;
	float                           data[3];
	//    ext_client_custom_data_mask_t   masks;

	uint16_t                        crc16;
} ext_client_custom_data_t;
typedef __packed struct {
	ext_frame_header_t  					header;
	uint16_t											cmd_id;

	uint16_t            					data_id;            /*!< range 0x200~0x2FF */
	uint16_t            					sender_id;
	uint16_t            					robot_id;
	graphic_data_struct_t                   graphic_data;          /*!< max data length = 13byte */

	uint16_t                      crc16;
} ext_robot_graphic_data_t;

typedef __packed struct {
	ext_frame_header_t  					header;
	uint16_t											cmd_id;

	uint16_t            					data_id;            /*!< range 0x200~0x2FF */
	uint16_t            					sender_id;
	uint16_t            					robot_id;
	ext_client_custom_graphic_seven_t			graphic_data;          /*!< max data length = 13byte */

	uint16_t                      crc16;
} ext_robot_sev_graphic_data_t;

typedef __packed struct {
	ext_frame_header_t  							header;
	uint16_t										cmd_id;

	uint16_t            							data_id;            /*!< range 0x200~0x2FF */
	uint16_t            							sender_id;
	uint16_t            							robot_id;
	ext_client_custom_character_t			character_data;          /*!< max data length = 43byte */

	uint16_t                      		crc16;
} ext_robot_character_data_t;



extern void init_referee_struct_data(void);
extern void referee_data_solve(uint8_t *frame);

extern void get_chassis_power_and_buffer(fp32 *power, fp32 *buffer);

extern uint8_t get_robot_id(void);
#endif  /*__REFEREEINFO_H__*/