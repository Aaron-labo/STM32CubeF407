#ifndef DRIVERS_REMOTE_REMOTE_H_
#define DRIVERS_REMOTE_REMOTE_H_

#define ONE		162						//	1		2		3
#define TWO		98						//	4		5		6
#define THREE	226						//	7		8		9
#define FOUR	34						//	重置		无		取消
#define FIVE	2						//			无
#define SIX		194						//	稳定		确定		绕圈
#define SEVEN	224						//			移动
#define EIGHT	168
#define NINE	144

#define STABLE	16
#define MOVE	74
#define ROUND	90

#define DETER	56
#define REPLACE	104
#define CANCEL	176

#define ZERO	152
#define INIT	24

#define NOPRES	0

uint8_t Remote_Scan(void);

#endif /* DRIVERS_REMOTE_REMOTE_H_ */

