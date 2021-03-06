#ifndef __MENU_H
#define __MENU_H			  	 
#include "sys.h"
#include "stdlib.h"

typedef enum// �˵�����
{
	home,//��ҳ�棺HOME
	tdwt,//һ���˵���ͨ��΢��
	tdzf,//һ���˵���ͨ������
	hksz,//һ���˵����������
	jsgl,//һ���˵������չ���
	scsz,//һ���˵����������
	tdys,//һ���˵���ͨ��ӳ��
	dljs,//һ���˵�����������
	xtsz,//һ���˵���ϵͳ����
	gybj,//һ���˵������ڱ���
	
	tdwt1,//�����˵���ͨ��1
	tdwt2,//�����˵���ͨ��2
	tdwt3,//�����˵���ͨ��3
	tdwt4,//�����˵���ͨ��4
	tdwt5,//�����˵���ͨ��5
	tdwt6,//�����˵���ͨ��6
	tdwt7,//�����˵���ͨ��7
	tdwt8,//�����˵���ͨ��8
	
	tdzf1,//�����˵���ͨ��1
	tdzf2,//�����˵���ͨ��2
	tdzf3,//�����˵���ͨ��3
	tdzf4,//�����˵���ͨ��4
	tdzf5,//�����˵���ͨ��5
	tdzf6,//�����˵���ͨ��6
	tdzf7,//�����˵���ͨ��7
	tdzf8,//�����˵���ͨ��8
	
	sjyhk,//�����˵�����������
	vyhk,//�����˵���V����
	cshk,//�����˵������ٻ��
	jfyhk,//�����˵���������
	
	xjjs,//�����˵����½�����
	xzmx,//�����˵���ѡ��ģ��
	bcmx,//�����˵�������ģ��
	txmm,//�����˵���ͨ������
	
	ppmsc,//�����˵���PPM���
	wxfs,//�����˵������߷���
	fsgl,//�����˵������书��
	
	tdys1,//�����˵���ͨ��1
	tdys2,//�����˵���ͨ��2
	tdys3,//�����˵���ͨ��3
	tdys4,//�����˵���ͨ��4
	tdys5,//�����˵���ͨ��5
	tdys6,//�����˵���ͨ��6
	tdys7,//�����˵���ͨ��7
	tdys8,//�����˵���ͨ��8
	
	dljs18,//�����˵���ͨ��1-8��������
	
	cysz,//�����˵�����������
	dysz,//�����˵�����ѹ����
	nzsz,//�����˵�����������
	ymsz,//�����˵�����������
	xcjz,//�����˵����г�У׼
	hfcc,//�����˵����ָ���������
	
	wtdw,//�����˵���΢����λ
	ajyx,//�����˵���������Ч
	kjhm,//�����˵�����������
	
	dyjz,//�����˵�����ѹУ׼
	bjdy,//�����˵���������ѹ
	jsbj,//�����˵������ձ���
	
	nzbj,//�����˵������ӱ���
	nzsc,//�����˵�������ʱ��
	kjzj,//�����˵��������Լ�
	
	ymph,//�����˵�������ƫ��
	ymqx,//�����˵�����������
	skbh,//�����˵���ʧ�ر���
	
	xcjzTip,//�����˵����뽫ң�˻���
	xcjz14,//�����˵���ͨ��1-4��ʾ
	
	hfccTip,//�����˵������ָ�Ĭ��
	hfcg,//�����˵����ָ��ɹ�
	
	gybjInf,//�����˵���J20RC�����Ŷ�-V2.0
	
	MENU_NUM, // �˵�ҳ����
}MENU_INDEX_LIST;


/*ͨ��΢���������������������ٽ󸱽��չ����½�ѡ��ģ�ͱ���������
��������߷��书��ӳ����ң�˿��ض�������ϵͳ���ñ��������г�У׼
�ָ����ڵ�λ������Ч�����洮���Ե�ѹ����ʱ��ƫ����ʧ��
�Լ��뽫���а����ϼ���Ĭ���ŶӲ˱����ֳ���*/

typedef struct{
	u8 current_index;	//��ŵ�ǰ����������ţ�
	u8 down_index;		//��Ű��¡�down�����£�����ʱ��Ҫ��ת���������ţ�
	u8 up_index;		//��Ű��¡�up�����ϣ�����ʱ��Ҫ��ת���������ţ�
	u8 enter_index;		//��Ű��¡�enter�����룩����ʱ��Ҫ��ת�������ţ�
	u8 esc_index;		//��Ű��¡�esc���˳�������ʱ��Ҫ��ת�������ţ�
	u8 home_index;		//��Ű��¡�home�������棩����ʱ��Ҫ��ת�������ţ�
	void (*operate)();	//����ָ���������ŵ�ǰ����������Ҫִ�еĺ�������ڵ�ַ��
}Key_index_struct;


extern volatile u8 nowMenuIndex;
extern volatile u8 lastMenuIndex;
	
void OLED_display(void);
void homeWindow(void);//������
void showSwState(void);

void menu_tdwt(void);//һ���˵���ͨ��΢��
void menu_tdzf(void);//һ���˵���ͨ������
void menu_hksz(void);//һ���˵����������
void menu_jsgl(void);//һ���˵������չ���
void menu_scsz(void);//һ���˵����������
void menu_tdys(void);//һ���˵���ͨ��ӳ��
void menu_dljs(void);//һ���˵�����������
void menu_xtsz(void);//һ���˵���ϵͳ����
void menu_gybj(void);//һ���˵������ڱ���

void menu_tdwt1(void);//�����˵���ͨ��1
void menu_tdwt2(void);//�����˵���ͨ��2
void menu_tdwt3(void);//�����˵���ͨ��3
void menu_tdwt4(void);//�����˵���ͨ��4
void menu_tdwt5(void);//�����˵���ͨ��5
void menu_tdwt6(void);//�����˵���ͨ��6
void menu_tdwt7(void);//�����˵���ͨ��7
void menu_tdwt8(void);//�����˵���ͨ��8

void menu_tdzf1(void);//�����˵���ͨ��1
void menu_tdzf2(void);//�����˵���ͨ��2
void menu_tdzf3(void);//�����˵���ͨ��3
void menu_tdzf4(void);//�����˵���ͨ��4
void menu_tdzf5(void);//�����˵���ͨ��5
void menu_tdzf6(void);//�����˵���ͨ��6
void menu_tdzf7(void);//�����˵���ͨ��7
void menu_tdzf8(void);//�����˵���ͨ��8

void menu_sjyhk(void);//�����˵�����������
void menu_vyhk(void);//�����˵���V����
void menu_cshk(void);//�����˵������ٻ��
void menu_jfyhk(void);//�����˵���������

void menu_xjjs(void);//�����˵����½�����
void menu_xzmx(void);//�����˵���ѡ��ģ��
void menu_bcmx(void);//�����˵�������ģ��
void menu_txmm(void);//�����˵���ͨ������

void menu_ppmsc(void);//�����˵���PPM���
void menu_wxfs(void);//�����˵������߷���
void menu_fsgl(void);//�����˵������书��

void menu_tdys1(void);//�����˵���ͨ��1
void menu_tdys2(void);//�����˵���ͨ��2
void menu_tdys3(void);//�����˵���ͨ��3
void menu_tdys4(void);//�����˵���ͨ��4
void menu_tdys5(void);//�����˵���ͨ��5
void menu_tdys6(void);//�����˵���ͨ��6
void menu_tdys7(void);//�����˵���ͨ��7
void menu_tdys8(void);//�����˵���ͨ��8

void menu_dljs18(void);//�����˵���ͨ��1-8��������

void menu_cysz(void);//�����˵�����������
void menu_dysz(void);//�����˵�����ѹ����
void menu_nzsz(void);//�����˵�����������
void menu_ymsz(void);//�����˵�����������
void menu_xcjz(void);//�����˵����г�У׼
void menu_hfcc(void);//�����˵����ָ���������

void menu_wtdw(void);//�����˵���΢����λ
void menu_ajyx(void);//�����˵���������Ч
void menu_kjhm(void);//�����˵�����������

void menu_dyjz(void);//�����˵�����ѹУ׼
void menu_bjdy(void);//�����˵���������ѹ
void menu_jsbj(void);//�����˵������ձ���
	
void menu_nzbj(void);//�����˵������ӱ���
void menu_nzsc(void);//�����˵�������ʱ��
void menu_kjzj(void);//�����˵��������Լ�
	
void menu_ymph(void);//�����˵�������ƫ��
void menu_ymqx(void);//�����˵�����������
void menu_skbh(void);//�����˵���ʧ�ر���

void menu_xcjzTip(void);//�����˵����뽫ң�˻���
void menu_xcjz14(void);//�����˵���ͨ��1-4��ʾ

void menu_hfccTip(void);//�����˵������ָ�Ĭ��
void menu_hfcg(void);//�����˵����ָ��ɹ�

void menu_gybjInf(void);//�����˵���J20RC�����Ŷ�-V2.0
u16 IsInKeyMenu(u16 num);//�ж��Ƿ�Ϊ�û��༭ҳ��

#endif

