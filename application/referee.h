#ifndef __REFEREEINFO_H__
#define __REFEREEINFO_H__

/******************
裁判信息解读与透传数据帧封装程序
update:
	视情况调用最后三个函数
	全局变量说明见uart2referee.h
	支持上传3个float数据
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
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#define EN_USART6_RX 			1		//使能（1）/禁止（0）串口1接收 
#define USART6_dma_rx_len 		80
#define USART6_dma_tx_len 		128
void float2bytes(float chosen_value, u8* res_message);
float _bytes2float(uint8_t* chosen_Message);
void float2bytes(float chosen_value, u8* res_message);
void send_single_icon(char* name, int x, int y, int type, int color);
void send_multi_graphic();
// flaot和字节互转
typedef union {
    float f;
    unsigned char b[4];
} Bytes2Float;

// float和u32互转
typedef union {
    u32 u32_value;
    unsigned char b[4];
} Bytes2U32;


#define REFEREE_FRAME_HEADER_SOF                ((uint8_t)(0xA5))

#define REFEREE_STUDENT_ROBOT_MAX               ((uint16_t)(0x0200))
#define REFEREE_STUDENT_ROBOT_MIN               ((uint16_t)(0x02FF))

#define REFEREE_STUDENT_CLIENT_SOF              ((uint16_t)(0xD180))  //这里需要改一下ID

/* 比赛状态数据：0x0001。发送频率：1Hz */
typedef __packed struct
{
	uint8_t game_type : 4;//0-3 bit：比赛类型
	uint8_t game_progress : 4;//4-7 bit：当前比赛阶段
	uint16_t stage_remain_time;//offset=1 当前阶段剩余时间，单位 s
	uint64_t SyncTimeStamp;//offset=3 机器人接收到该指令的精确 Unix 时间，当机载端收到有效的 NTP 服务器授时后生效
} ext_game_status_t;


/* 比赛结果数据：0x0002。发送频率：比赛结束后发送 */
typedef __packed struct
{
	uint8_t winner;//0 平局 1 红方胜利 2 蓝方胜利
} ext_game_result_t;


/* 机器人血量数据：0x0003。发送频率：1Hz */
typedef __packed struct
{
	uint16_t red_1_robot_HP;//offset=0 红 1 英雄机器人血量，未上场以及罚下血量为 0
	uint16_t red_2_robot_HP;//offset=2 红 2 工程机器人血量
	uint16_t red_3_robot_HP;//offset=4 红 3 步兵机器人血量
	uint16_t red_4_robot_HP;//offset=6 红 4 步兵机器人血量
	uint16_t red_5_robot_HP;//offset=8 红 5 步兵机器人血量
	uint16_t red_7_robot_HP;//offset=10 红 7 哨兵机器人血量
	uint16_t red_outpost_HP;//offset=12 红方前哨战血量
	uint16_t red_base_HP;//offset=14 红方基地血量

	uint16_t blue_1_robot_HP;//offset=16 蓝 1 英雄机器人血量
	uint16_t blue_2_robot_HP;//offset=18 蓝 2 工程机器人血量
	uint16_t blue_3_robot_HP;//offset=20 蓝 3 步兵机器人血量
	uint16_t blue_4_robot_HP;//offset=22蓝 4 步兵机器人血量
	uint16_t blue_5_robot_HP;//offset=24 蓝 5 步兵机器人血量
	uint16_t blue_7_robot_HP;//offset=26 蓝 7 哨兵机器人血量
	uint16_t blue_outpost_HP;//offset=28 蓝方前哨站血量
	uint16_t blue_base_HP;//offset=30 蓝方基地血量
} ext_game_robot_HP_t;

////飞镖发射状态：0x0004
//typedef __packed struct
//{
//	uint8_t dart_belong;
//	uint16_t stage_remaining_time;
//}ext_dart_status_t;



/* 人工智能挑战赛加成与惩罚区状态：0x0005。发送频率：1Hz 周期发送，发送范围：所有机器人 */
typedef __packed struct
{
	/* bit[0, 4, 8, 12, 16, 20]为 F1 - F6 激活状态：0 为未激活，1 为已激活
	   bit[1-3, 5-7, 9-11, 13-15, 17-19, 21-23]为 F1-F6 的状态信息：*/
	uint8_t F1_zone_status : 1;//0bit F1激活状态
	uint8_t F1_zone_buff_debuff_status : 3;//1-3bit F1状态信息
	uint8_t F2_zone_status : 1;//4bit F2激活状态
	uint8_t F2_zone_buff_debuff_status : 3;//5-7bit F2状态信息
	uint8_t F3_zone_status : 1;//8bit F3激活状态
	uint8_t F3_zone_buff_debuff_status : 3;//9-11bit F3状态信息
	uint8_t F4_zone_status : 1;//12bit F4激活状态
	uint8_t F4_zone_buff_debuff_status : 3;//13-15bit F4状态信息
	uint8_t F5_zone_status : 1;//16bit F5状态信息
	uint8_t F5_zone_buff_debuff_status : 3;//17-19bit F5状态信息
	uint8_t F6_zone_status : 1;//20bit F6状态信息
	uint8_t F6_zone_buff_debuff_status : 3;//21-23bit F6状态信息
	uint16_t red1_bullet_left;//offset=3 红方 1 号剩余弹量
	uint16_t red2_bullet_left;//offset=5 红方 2 号剩余弹量
	uint16_t blue1_bullet_left;//offset=7 蓝方 1 号剩余弹量
	uint16_t blue2_bullet_left;//offset=9 蓝方 2 号剩余弹量
} ext_ICRA_buff_debuff_zone_status_t;


/* 场地事件数据：0x0101。发送频率：1Hz */
typedef __packed struct
{
	/*
	bit 8：己方侧 R4/B4 梯形高地占领状态 1 为已占领
	bit 9：己方基地护盾状态：1 为基地有虚拟护盾血量；0 为基地无虚拟护盾血量；
	bit 10：己方前哨战状态：
	1 为前哨战存活；
	0 为前哨战被击毁；
	bit 10 -31: 保留
	*/
	uint32_t event_type;
} ext_event_data_t;


/* 补给站动作标识：0x0102。发送频率：动作改变后发送, 发送范围：己方机器人 */
typedef __packed struct
{
	uint8_t supply_projectile_id;//offset=0 补给站口 ID： 1：1 号补给口； 2：2 号补给口
	/*
	补弹机器人 ID：0 为当前无机器人补弹，1 为红方英雄机器人补弹，2 为红方工程机
器人补弹，3/4/5 为红方步兵机器人补弹，101 为蓝方英雄机器人补弹，102 为蓝方工
程机器人补弹，103/104/105 为蓝方步兵机器人补弹
	*/
	uint8_t supply_robot_id;//offset=1 说明见上
	uint8_t supply_projectile_step;//offset=2 出弹口开闭状态：0 为关闭，1 为子弹准备中，2 为子弹下落
	uint8_t supply_projectile_num;//补弹数量：50：50 颗子弹；100：100 颗子弹；150：150 颗子弹；200：200 颗子弹。
} ext_supply_projectile_action_t;



//----裁判警告信息----
typedef __packed struct  //cmd_id (0x0104)
{
	uint8_t level;         //1:黄牌 2:红牌 3:判负
	uint8_t foul_robot_id;   //判负时，机器人ID为0；黄牌、红牌是为犯规机器人ID
} ext_referee_warning_t;


//----飞镖发射口倒计时----
typedef __packed struct  //cmd_id(0x0105)
{
	uint8_t dart_remaining_time;  //15s倒计时
} ext_dart_remaining_time_t;


//----比赛机器人状态----
typedef __packed struct  //cmd_id(0x0201)
{
	uint8_t robot_id;
	//本机器人ID：1：红方英雄机器人；2：红方工程机器人；3/4/5：红方步兵机器人；6：红方空中机器人；
	//   7：红方哨兵机器人；8：红方飞镖机器人；9：红方雷达站；101：蓝方英雄机器人；102：蓝方工程机器人；
	//   103/104/105：蓝方步兵机器人；106：蓝方空中机器人；107：蓝方哨兵机器人；108：蓝方飞镖机器人；109：蓝方雷达站。

	uint8_t robot_level; //机器人等级  1：一级  2：二级  3：三级
	uint16_t remain_HP;  //机器人剩余血量
	uint16_t max_HP;     //机器人上限血量

	uint16_t shooter_id1_17mm_cooling_rate;  //机器人1号17mm枪口每秒冷却值
	uint16_t shooter_id1_17mm_cooling_limit; //机器人1号17mm枪口热量上限
	uint16_t shooter_id1_17mm_speed_limit;   //机器人1号17mm枪口上限速度 单位m/s

	uint16_t shooter_id2_17mm_cooling_rate;  //机器人2号17mm枪口每秒冷却值
	uint16_t shooter_id2_17mm_cooling_limit; //机器人2号17mm枪口热量上限
	uint16_t shooter_id2_17mm_speed_limit;   //机器人2号17mm枪口上限速度 单位m/s

	uint16_t shooter_id1_42mm_cooling_rate;  //机器人42mm枪口每秒冷却值
	uint16_t shooter_id1_42mm_cooling_limit; //机器人42mm枪口热量上限
	uint16_t shooter_id1_42mm_speed_limit;   //机器人42mm枪口上限速度 单位m/s

	uint16_t chassis_power_limit;    //机器人底盘功率限制上限
	uint8_t mains_power_gimbal_output : 1;  //主控电源输出情况  0bit:gimbal输出    0为无24V输出，1为有24V输出
	uint8_t mains_power_chassis_output : 1; //                 1bit:chassis输出   
	uint8_t mains_power_shooter_output : 1; //                 2bit:shooter输出  
} ext_game_robot_status_t;


//----实时功率热量数据----
typedef __packed struct  // 0x0202
{
	uint16_t chassis_volt;  //底盘输出电压 单位 毫伏
	uint16_t chassis_current;  //底盘输出电流 单位 毫安
	float chassis_power;  //底盘输出功率 单位 W 瓦
	uint16_t chassis_power_buffer;  //底盘功率缓冲 单位 J 焦耳 备注：飞坡根据规则增加至250J
	uint16_t shooter_id1_17mm_cooling_heat;  //1号17mm 枪口热量
	uint16_t shooter_id2_17mm_cooling_heat;  //2号17mm枪口热量
	uint16_t shooter_id1_42mm_cooling_heat;  //42mm 枪口热量
} ext_power_heat_data_t;


//----机器人位置----
typedef __packed struct  //0x0203
{
	float x;  //位置x坐标，单位m
	float y;  //位置y坐标，单位m
	float z;  //位置z坐标，单位m
	float yaw;  //位置枪口，单位度
} ext_game_robot_pos_t;


//----机器人增益----
typedef __packed struct  //0x0204
{
	uint8_t power_rune_buff;
	//bit 0：机器人血量补血状态; bit 1：枪口热量冷却加速; bit 2：机器人防御加成; bit 3：机器人攻击加成; 其他bit保留

}ext_buff_t;


//----空中机器人能量状态----
typedef __packed struct  //0x0205
{
	uint8_t attack_time;   //可攻击时间 单位 s。30s 递减至0
} aerial_robot_energy_t;


//----伤害状态----
typedef __packed struct //0x0206
{
	uint8_t armor_id : 4;
	uint8_t hurt_type : 4;
	//bit 0-3：当血量变化类型为装甲伤害，代表装甲ID，其中数值为0-4号代表机器人的五个装甲片，其他血量变化类型，该变量数值为0。
	//bit 4-7：血量变化类型
	//0x0 装甲伤害扣血；
	//0x1 模块掉线扣血；
	//0x2 超射速扣血；
	//0x3 超枪口热量扣血；
	//0x4 超底盘功率扣血；
	//0x5 装甲撞击扣血
} ext_robot_hurt_t;


//----实时射击信息----
typedef __packed struct  //0x0207
{
	uint8_t bullet_type;  //子弹类型: 1：17mm弹丸 2：42mm弹丸
	uint8_t shooter_id;   //发射机构ID：1：1号17mm发射机构; 2：2号17mm发射机构; 3：42mm 发射机构
	uint8_t bullet_freq;  //子弹射频 单位 Hz
	float bullet_speed;   //子弹射速 单位 m/s
} ext_shoot_data_t;


//----子弹剩余发射数----
typedef __packed struct  //0x0208
{
	uint16_t remaining_num_17mm;  //17mm子弹剩余发射数目
	uint16_t remaining_num_42mm;  //42mm子弹剩余发射数目
	uint16_t coin_remaining_num;  //剩余金币数量
} ext_bullet_remaining_t;


//----机器人RFID状态----
typedef __packed struct  //0x0209
{
	uint32_t rfid_status;
	//bit 0：基地增益点RFID状态；   bit 1：高地增益点RFID状态；   bit 2：能量机关激活点RFID状态；  bit 3：飞坡增益点RFID状态；
	//bit 4：前哨岗增益点RFID状态； bit 6：补血点增益点RFID状态； bit 7：工程机器人复活卡RFID状态； bit 8-31：保留

} ext_rfid_status_t;


//----飞镖机器人客户端指令数据----
typedef __packed struct  //0x020A
{
	uint8_t dart_launch_opening_status;
	//当前飞镖发射口的状态: 1：关闭; 2：正在开启或者关闭中; 0：已经开启	
	uint8_t dart_attack_target;
	//飞镖的打击目标，默认为前哨站; 0：前哨站; 1：基地。

	uint16_t target_change_time;  //切换打击目标时的比赛剩余时间，单位秒，从未切换默认为0
	uint16_t operate_launch_cmd_time;  //最近一次操作手确定发射指令时的比赛剩余时间，单位秒, 初始值为0。
} ext_dart_client_cmd_t;


/*----------0x0301部分开始------------*/
//----交互数据接收信息----
typedef __packed struct //0x0301
{
	uint16_t data_cmd_id;//内容 ID
	uint16_t sender_ID;//发送者的 ID
	uint16_t receiver_ID;//接收者的 ID
}ext_student_interactive_header_data_t;//学生机器人间通信数据段头结构


//----机器人间交互数据----
typedef __packed struct
{
	ext_student_interactive_header_data_t header_data;//学生机器人间通信数据段头结构
	uint8_t data[113];/*数据段长度小于113 */
} robot_interactive_data_t;//内容 ID:0x0200~0x02FF


//----客户端删除图形----
typedef __packed struct
{
	//内容 ID:0x0100
	ext_student_interactive_header_data_t header_data;//学生机器人间通信数据段头结构
	uint8_t operate_tpye; /*图形操作，包括:
							0: 空操作；
							1: 删除图层；
							2: 删除所有；
							*/
	uint8_t layer;         //图层数：0~9
} ext_client_custom_graphic_delete_t;


//----图形数据----
typedef __packed struct
{
	uint8_t graphic_name[3];//图形名,在删除，修改等操作中，作为客户端的索引。
	uint32_t operate_tpye : 3; //bit 0 - 2：图形操作
	uint32_t graphic_tpye : 3;//Bit 3-5：图形类型
	uint32_t layer : 4;// Bit 6 - 9：图层数，0~9
	uint32_t color : 4;//Bit 10-13：颜色
	uint32_t start_angle : 9;//Bit 14-22：起始角度，单位：°，范围[0,360]；
	uint32_t end_angle : 9;//Bit 23-31：终止角度，单位：°，范围[0,360]。
	uint32_t width : 10;//Bit 0-9：线宽；
	uint32_t start_x : 11;//Bit 10-20：起点 x 坐标；
	uint32_t start_y : 11;//Bit 21-31：起点 y 坐标。
	uint32_t radius : 10;//Bit 0-9：字体大小或者半径；
	uint32_t end_x : 11;//Bit 10-20：终点 x 坐标；
	uint32_t end_y : 11;//Bit 21-31：终点 y 坐标。
} graphic_data_struct_t;//详见裁判手册22页。


//----客户端绘制一个图形----
typedef __packed struct
{
	//内容 ID:0x0101
	ext_student_interactive_header_data_t header_data; //学生机器人间通信数据段头结构
	graphic_data_struct_t graphic_data_struct;//图形 1 
} ext_client_custom_graphic_single_t;

//----客户端绘制两个图形----
typedef __packed struct
{
	//内容 ID:0x0102
	ext_student_interactive_header_data_t header_data;  //学生机器人间通信数据段头结构
	graphic_data_struct_t graphic_data_struct[2];//图形1，2
} ext_client_custom_graphic_double_t;


//----客户端绘制五个图形----
typedef __packed struct
{
	//内容 ID:0x0103
	ext_student_interactive_header_data_t header_data;//学生机器人间通信数据段头结构
	graphic_data_struct_t graphic_data_struct[5];//图形1~5
} ext_client_custom_graphic_five_t;

//----客户端绘制七个图形----
typedef __packed struct
{
	//内容 ID:0x0104
	ext_student_interactive_header_data_t header_data;//学生机器人间通信数据段头结构
	graphic_data_struct_t graphic_data_struct[7];//图形1~7
} ext_client_custom_graphic_seven_t;

//----客户端绘制字符----

typedef __packed struct
{
	//内容 ID:0x0110
	ext_student_interactive_header_data_t header_data;//学生机器人间通信数据段头结构
	graphic_data_struct_t graphic_data_struct;//字符配置
	uint8_t data[30];                        //字符
} ext_client_custom_character_t;
/*----------0x0301部分结束------------*/




//----交互数据接收信息----
//发送频率：上限 30Hz
//typedef __packed struct //0x0302
//{
//	uint8_t data[]; //内容段数据,大小最大为30字节。
//} robot_interactive_data_t;



//----小地图下发信息标识----
/*发送频率：触发时发送.*/
typedef __packed struct  //0x0303
{
	float target_position_x;//目标 x 位置坐标，单位 m,当发送目标机器人 ID 时，该项为 0
	float target_position_y;//目标 y 位置坐标，单位 m,当发送目标机器人 ID 时，该项为 0
	float target_position_z;//目标 z 位置坐标，单位 m,当发送目标机器人 ID 时，该项为 0
	uint8_t commd_keyboard;//发送指令时，云台手按下的键盘信息 ,无按键按下则为 0
	uint16_t target_robot_ID;//要作用的目标机器人 ID,当发送位置信息时，该项为 0
	/*机器人ID对应详见裁判手册27页*/


	//0x0304部分一起并入此结构体如下
	int16_t mouse_x;			//鼠标 X 轴信息
	int16_t mouse_y;			//鼠标 Y 轴信息
	int16_t mouse_z;			//鼠标滚轮信息
	uint8_t left_button_down;		//鼠标左键
	uint8_t right_button_down;		//鼠标右键按下
	uint16_t keyboard_value;	//键盘信息
	uint16_t reserved;			//保留位
} ext_robot_command_t;


//----小地图接收信息标识----
//最大接收频率：10Hz。
//雷达站发送的坐标信息可以被所有己方操作手在第一视角小地图看到。
typedef __packed struct   //0x0305
{
	uint16_t target_robot_ID;//目标机器人 ID 
	float target_position_x;//目标 x 位置坐标，单位 m
	float target_position_y;//目标 y 位置坐标，单位 m 
} ext_client_map_command_t;// 客户端接收信息，其中各项当 x,y 超出界限时则不显示。



/*
键盘信息：
bit 0：键盘 W 是否按下
bit 1：键盘 S 是否按下
bit 2：键盘 A 是否按下
bit 3：键盘 D 是否按下
bit 4：键盘 SHIFT 是否按下
bit 5：键盘 CTRL 是否按下
bit 6：键盘 Q 是否按下
bit 7：键盘 E 是否按下
bit 8：键盘 R 是否按下
bit 9：键盘 F 是否按下
bit 10：键盘 G 是否按下
bit 11：键盘 Z 是否按下
bit 12：键盘 X 是否按下
bit 13：键盘 C 是否按下
bit 14：键盘 V 是否按下
bit 15：键盘 B 是否按下
*/


// 使用完整数据帧立刻更新全部裁判信息相关结构体。(带校验)
// u8 frame_interpret(uint8_t * frame);
bool frame_interpret(uint8_t* _frame, uint16_t size);

// 读入单字节来更新全部裁判信息相关结构体, 
// 即仅累积字节为一完整数据包时 才调用frame_interpret函数 来更新相关结构体。
void referee_info_update(uint8_t single_byte);
// 自定义数据帧, 封装入数组头指针custom_frame，长度 = 5+2+12+2 = 21
// 调用前请确保全局变量MyData结构体已更新值, 
// 发送示例:
// for(i=0;i<21;i++) {
//     USART_SendData(USART2, custom_frame_test[i]);
//     while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET);
// }


// debug用的全局变量
extern u8 referee_message[64];  // 完整数据帧存放, 理论44就够。
extern u8 cmdID;;
extern u8 blood_counter;  // (debug)被打计数

// 以下暂时不用
//// 校验数据帧, CRC8和CRC16
//u8 Verify_frame(uint8_t * frame);

extern void update_from_dma(void);
extern u8 seq_real;
extern u8 usart6_dma_flag;
extern int shoot_counter_referee;
extern ext_game_status_t                           ext_game_state;// 比赛进程信息（0x0001）
extern ext_game_status_t                           ext_game_state;// 比赛状态数据（0x0001）
extern ext_game_result_t                          ext_game_result;//比赛结果数据(0x0002)
extern ext_game_robot_HP_t                 ext_game_robot_survivors;//机器人存存活数据（0x0003）
//extern ext_dart_status_t                          ext_dart_status;//飞镖发射状态（0x0004）
extern ext_event_data_t                           ext_event_data;//场地时事件数据（0x0101）
extern ext_supply_projectile_action_t             ext_supply_projectile_action;//补给站动作标识（0x0102）
//extern ext_supply_projectile_booking_t            ext_supply_projectile_booking;//补给站预约子弹（0x0103）
extern ext_referee_warning_t                      ext_referee_warning;//裁判警告信息（0x0104）
extern ext_dart_remaining_time_t                  ext_dart_remaining_time;//飞镖发射口倒计时(0x0105)
extern ext_game_robot_status_t                     ext_game_robot_status;//比赛机器人状态(0x0201)
extern ext_power_heat_data_t                      ext_power_heat_data;////实时功率热量数据（0x0202）
extern ext_game_robot_pos_t                       ext_game_robot_pos;//机器人位置（0x0203）
extern ext_buff_t                                 ext_buff;//机器人增益（0x0204）
extern aerial_robot_energy_t                      ext_aerial_robot_energy;//空中机器人能量状态（0x0205）
extern ext_robot_hurt_t                           ext_robot_hurt;//伤害状态（0x0206）
extern ext_shoot_data_t                           ext_shoot_data;//实时射击信息（0x0207）
extern ext_bullet_remaining_t                     ext_bullet_remaining;//子弹剩余发射数(0x0208)
extern ext_rfid_status_t                          ext_rfid_status;//机器人RFID状态(0x0209)
extern ext_dart_client_cmd_t                      ext_dart_client_cmd;//飞镖机器人客户端指令数据(0x020A)
extern graphic_data_struct_t                      graphic_data_struct;

extern ext_student_interactive_header_data_t      ext_student_interactive_header_data;//交互数据接收信息（0x0301）
extern ext_client_custom_graphic_delete_t         ext_client_custom_graphic_delete;
extern ext_client_custom_graphic_single_t         ext_client_custom_graphic_single;
extern ext_client_custom_graphic_double_t         ext_client_custom_graphic_double;
extern ext_client_custom_graphic_five_t           ext_client_custom_graphic_five;
extern ext_client_custom_graphic_seven_t          ext_client_custom_graphic_seven;
//extern ext_robot_command_t                        ext_robot_command;//小地图交互数据（0x0303）
extern robot_interactive_data_t                   robot_interactive_data;  //交互数据



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

typedef __packed struct {     //帧头数据
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
	robotid_red_radar = 9,         //新增红方雷达站ID
	robotid_blue_hero = 101,
	robotid_blue_engineer = 102,
	robotid_blue_infantry_1 = 103,
	robotid_blue_infantry_2 = 104,
	robotid_blue_infantry_3 = 105,
	robotid_blue_aerial = 106,
	robotid_blue_sentry = 107,
	robotid_blue_radar = 109,     //新增蓝方雷达站ID 

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
