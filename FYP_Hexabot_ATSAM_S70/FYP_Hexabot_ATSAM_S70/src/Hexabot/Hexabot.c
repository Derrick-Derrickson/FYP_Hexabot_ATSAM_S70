/*
 * Hexabot.c
 *
 * Created: 17/05/2016 4:11:50 PM
 *  Author: to300
 */ 
#include "Hexabot/Hexabot.h"
#include "Hexabot/Hexabot_Cmd.h"

#define REG_GAIN		0x00	/* Gain control, AGC[7:0] */
#define REG_BLUE		0x01	/* AWB - Blue chanel gain */
#define REG_RED			0x02	/* AWB - Red chanel gain */
#define REG_VREF		0x03	/* [7:6] - AGC[9:8], [5:3]/[2:0] */
#define  VREF_GAIN_MASK		0xc0	/* - VREF end/start low 3 bits */
#define REG_COM1		0x04
#define  COM1_CCIR656		0x40
#define REG_B_AVE		0x05
#define REG_GB_AVE		0x06
#define REG_GR_AVE		0x07
#define REG_R_AVE		0x08
#define REG_COM2		0x09
#define REG_PID			0x0a	/* Product ID MSB */
#define REG_VER			0x0b	/* Product ID LSB */
#define REG_COM3		0x0c
#define  COM3_SWAP		0x40
#define  COM3_VARIOPIXEL1	0x04
#define REG_COM4		0x0d	/* Vario Pixels  */
#define  COM4_VARIOPIXEL2	0x80
#define REG_COM5		0x0e	/* System clock options */
#define  COM5_SLAVE_MODE	0x10
#define  COM5_SYSTEMCLOCK48MHZ	0x80
#define REG_COM6		0x0f	/* HREF & ADBLC options */
#define REG_AECH		0x10	/* Exposure value, AEC[9:2] */
#define REG_CLKRC		0x11	/* Clock control */
#define  CLK_EXT		0x40	/* Use external clock directly */
#define  CLK_SCALE		0x3f	/* Mask for internal clock scale */
#define REG_COM7		0x12	/* SCCB reset, output format */
#define  COM7_RESET		0x80
#define  COM7_FMT_MASK		0x38
#define  COM7_FMT_VGA		0x40
#define	 COM7_FMT_CIF		0x20
#define  COM7_FMT_QVGA		0x10
#define  COM7_FMT_QCIF		0x08
#define	 COM7_RGB		0x04
#define	 COM7_YUV		0x00
#define	 COM7_BAYER		0x01
#define	 COM7_PBAYER		0x05
#define REG_COM8		0x13	/* AGC/AEC options */
#define  COM8_FASTAEC		0x80	/* Enable fast AGC/AEC */
#define  COM8_AECSTEP		0x40	/* Unlimited AEC step size */
#define  COM8_BFILT		0x20	/* Band filter enable */
#define  COM8_AGC		0x04	/* Auto gain enable */
#define  COM8_AWB		0x02	/* White balance enable */
#define  COM8_AEC		0x01	/* Auto exposure enable */
#define REG_COM9		0x14	/* Gain ceiling */
#define  COM9_GAIN_CEIL_MASK	0x70	/* */
#define REG_COM10		0x15	/* PCLK, HREF, HSYNC signals polarity */
#define  COM10_HSYNC		0x40	/* HSYNC instead of HREF */
#define  COM10_PCLK_HB		0x20	/* Suppress PCLK on horiz blank */
#define  COM10_HREF_REV		0x08	/* Reverse HREF */
#define  COM10_VS_LEAD		0x04	/* VSYNC on clock leading edge */
#define  COM10_VS_NEG		0x02	/* VSYNC negative */
#define  COM10_HS_NEG		0x01	/* HSYNC negative */
#define REG_HSTART		0x17	/* Horiz start high bits */
#define REG_HSTOP		0x18	/* Horiz stop high bits */
#define REG_VSTART		0x19	/* Vert start high bits */
#define REG_VSTOP		0x1a	/* Vert stop high bits */
#define REG_PSHFT		0x1b	/* Pixel delay after HREF */
#define REG_MIDH		0x1c	/* Manufacturer ID MSB */
#define REG_MIDL		0x1d	/* Manufufacturer ID LSB */
#define REG_MVFP		0x1e	/* Image mirror/flip */
#define  MVFP_MIRROR		0x20	/* Mirror image */
#define  MVFP_FLIP		0x10	/* Vertical flip */
#define REG_BOS			0x20	/* B channel Offset */
#define REG_GBOS		0x21	/* Gb channel Offset */
#define REG_GROS		0x22	/* Gr channel Offset */
#define REG_ROS			0x23	/* R channel Offset */
#define REG_AEW			0x24	/* AGC upper limit */
#define REG_AEB			0x25	/* AGC lower limit */
#define REG_VPT			0x26	/* AGC/AEC fast mode op region */
#define REG_BBIAS		0x27	/* B channel output bias */
#define REG_GBBIAS		0x28	/* Gb channel output bias */
#define REG_GRCOM		0x29	/* Analog BLC & regulator */
#define REG_EXHCH		0x2a	/* Dummy pixel insert MSB */
#define REG_EXHCL		0x2b	/* Dummy pixel insert LSB */
#define REG_RBIAS		0x2c	/* R channel output bias */
#define REG_ADVFL		0x2d	/* LSB of dummy line insert */
#define REG_ADVFH		0x2e	/* MSB of dummy line insert */
#define REG_YAVE		0x2f	/* Y/G channel average value */
#define REG_HSYST		0x30	/* HSYNC rising edge delay LSB*/
#define REG_HSYEN		0x31	/* HSYNC falling edge delay LSB*/
#define REG_HREF		0x32	/* HREF pieces */
#define REG_CHLF		0x33	/* reserved */
#define REG_ADC			0x37	/* reserved */
#define REG_ACOM		0x38	/* reserved */
#define REG_OFON		0x39	/* Power down register */
#define  OFON_PWRDN		0x08	/* Power down bit */
#define REG_TSLB		0x3a	/* YUVU format */
#define  TSLB_YUYV_MASK		0x0c	/* UYVY or VYUY - see com13 */
#define REG_COM11		0x3b	/* Night mode, banding filter enable */
#define  COM11_NIGHT		0x80	/* Night mode enable */
#define  COM11_NMFR		0x60	/* Two bit NM frame rate */
#define  COM11_BANDING		0x01	/* Banding filter */
#define  COM11_AEC_REF_MASK	0x18	/* AEC reference area selection */
#define REG_COM12		0x3c	/* HREF option, UV average */
#define  COM12_HREF		0x80	/* HREF always */
#define REG_COM13		0x3d	/* Gamma selection, Color matrix en. */
#define  COM13_GAMMA		0x80	/* Gamma enable */
#define	 COM13_UVSAT		0x40	/* UV saturation auto adjustment */
#define  COM13_UVSWAP		0x01	/* V before U - w/TSLB */
#define REG_COM14		0x3e	/* Edge enhancement options */
#define  COM14_EDGE_EN		0x02
#define  COM14_EEF_X2		0x01
#define REG_EDGE		0x3f	/* Edge enhancement factor */
#define  EDGE_FACTOR_MASK	0x0f
#define REG_COM15		0x40	/* Output range, RGB 555/565 */
#define  COM15_R10F0		0x00	/* Data range 10 to F0 */
#define	 COM15_R01FE		0x80	/* 01 to FE */
#define  COM15_R00FF		0xc0	/* 00 to FF */
#define  COM15_RGB565		0x10	/* RGB565 output */
#define  COM15_RGB555		0x30	/* RGB555 output */
#define  COM15_SWAPRB		0x04	/* Swap R&B */
#define REG_COM16		0x41	/* Color matrix coeff options */
#define REG_COM17		0x42	/* Single frame out, banding filter */
/* n = 1...9, 0x4f..0x57 */
#define	REG_MTX(__n)		(0x4f + (__n) - 1)
#define REG_MTXS		0x58
/* Lens Correction Option 1...5, __n = 0...5 */
#define REG_LCC(__n)		(0x62 + (__n) - 1)
#define  LCC5_LCC_ENABLE	0x01	/* LCC5, enable lens correction */
#define  LCC5_LCC_COLOR		0x04
#define REG_MANU		0x67	/* Manual U value */
#define REG_MANV		0x68	/* Manual V value */
#define REG_HV			0x69	/* Manual banding filter MSB */
#define REG_MBD			0x6a	/* Manual banding filter value */
#define REG_DBLV		0x6b	/* reserved */
#define REG_GSP			0x6c	/* Gamma curve */
#define  GSP_LEN		15
#define REG_GST			0x7c	/* Gamma curve */
#define  GST_LEN		15
#define REG_COM21		0x8b
#define REG_COM22		0x8c	/* Edge enhancement, denoising */
#define  COM22_WHTPCOR		0x02	/* White pixel correction enable */
#define  COM22_WHTPCOROPT	0x01	/* White pixel correction option */
#define  COM22_DENOISE		0x10	/* White pixel correction option */
#define REG_COM23		0x8d	/* Color bar test, color gain */
#define  COM23_TEST_MODE	0x10
#define REG_DBLC1		0x8f	/* Digital BLC */
#define REG_DBLC_B		0x90	/* Digital BLC B channel offset */
#define REG_DBLC_R		0x91	/* Digital BLC R channel offset */
#define REG_DM_LNL		0x92	/* Dummy line low 8 bits */
#define REG_DM_LNH		0x93	/* Dummy line high 8 bits */
#define REG_LCCFB		0x9d	/* Lens Correction B channel */
#define REG_LCCFR		0x9e	/* Lens Correction R channel */
#define REG_DBLC_GB		0x9f	/* Digital BLC GB chan offset */
#define REG_DBLC_GR		0xa0	/* Digital BLC GR chan offset */
#define REG_AECHM		0xa1	/* Exposure value - bits AEC[15:10] */
#define REG_BD50ST		0xa2	/* Banding filter value for 50Hz */
#define REG_BD60ST		0xa3	/* Banding filter value for 60Hz */

void SdramCheck() {
	isi_disable_interrupt(ISI,1<<16|1<<17);
	isi_dma_channel_disable(ISI,1);
	int T=0;
	int cleanTest = 1;
	char buf[20];
	for(int i = 0;i<BOARD_SDRAM_ADDR_NUM;i++) {
		((uint16_t*)BOARD_SDRAM_ADDR)[i] = T;
		T++;
	}
	
	T=0;
	for(int i = 0;i<BOARD_SDRAM_ADDR_NUM;i++) {
		if(((uint16_t*)BOARD_SDRAM_ADDR)[i] != (T&0xFFFF)){
			sprintf(buf,"MEM ERROR AT 0x%x : EXP:0x%x , RCV: 0x%x \n",i,(T&0xFFFF),((uint16_t*)BOARD_SDRAM_ADDR)[i]);
			sendDebugString(buf);
			cleanTest = 0;
		}
		T++;
	}
	if(cleanTest) sendDebugString("SDRAM FULL CHECK COMPLETE");
	isi_enable_interrupt(ISI,1<<16|1<<17);
	isi_dma_channel_enable(ISI,1);
}

void i2cWriteReg(uint8_t chipin,uint8_t reg,uint8_t val) {
	int writeVal = val;
	twihs_packet_t ledApacket = {
		.addr[0] = reg,
		.addr_length = 1,
		.chip = (chipin),
		.buffer = &val,
	.length = 1 };
	
	if(twihs_master_write(TWIHS0,&ledApacket) != TWIHS_SUCCESS) {
		sendDebugString("I2C ERR!\n");
	}
}

int i2cReadReg(uint8_t chipin,uint8_t reg) {
	int retVal = 0;
	twihs_packet_t ledApacket = {
		.addr[0] = reg,
		.addr_length = 1,
		.chip = (chipin),
		.buffer = &retVal,
	.length = 1 };
	twihs_master_read(TWIHS0,&ledApacket);
	return retVal;
}

void ServoDriverInit(int ServoAddr) {
	char buf[20];
	sprintf(buf,"%x, ",i2cReadReg(ServoAddr,0x00));
	sendDebugString(buf);
	sprintf(buf,"%x, ",i2cReadReg(ServoAddr,0x01));
	sendDebugString(buf);
	sprintf(buf,"%x, ",i2cReadReg(ServoAddr,0x1E));
	sendDebugString(buf);
	sprintf(buf,"%x, ",i2cReadReg(ServoAddr,0xFE));
	sendDebugString(buf);
	
	delay_ms(1);
	i2cWriteReg(ServoAddr,0x00,0x01<<4);
	delay_ms(2);
	i2cWriteReg(ServoAddr,0xFE,0x80);
	delay_ms(2);
	i2cWriteReg(ServoAddr,0x00,0x00);
	
	i2cWriteReg(ServoAddr,0x00,0x01<<4);
	i2cWriteReg(ServoAddr,0x01,0x04);
	i2cWriteReg(ServoAddr,0x00,0x00);
	delay_ms(2);
	i2cWriteReg(ServoAddr,0x00,0x01<<7);
	sendDebugString("SERVO DRIVER SETUP COMPLEATE\n");
}

void cpyIn(int Ain,int Bin,int* memaddr) {
	memaddr[0] = Ain;
	memaddr[1] = Bin;
}

void legGetI2Caddr(int Leg,int Svo,int* addr) {
	switch(Leg) {
		case 0:
		if(Svo == 0)	  cpyIn(L0_S0_ADDR,addr);
		else if(Svo == 1) cpyIn(L0_S1_ADDR,addr);
		else if(Svo == 2) cpyIn(L0_S2_ADDR,addr);
		break;
		
		case 1:
		if(Svo == 0)	  cpyIn(L1_S0_ADDR,addr);
		else if(Svo == 1) cpyIn(L1_S1_ADDR,addr);
		else if(Svo == 2) cpyIn(L1_S2_ADDR,addr);
		break;
		
		case 2:
		if(Svo == 0)	  cpyIn(L2_S0_ADDR,addr);
		else if(Svo == 1) cpyIn(L2_S1_ADDR,addr);
		else if(Svo == 2) cpyIn(L2_S2_ADDR,addr);
		break;
		
		case 3:
		if(Svo == 0)	  cpyIn(L3_S0_ADDR,addr);
		else if(Svo == 1) cpyIn(L3_S1_ADDR,addr);
		else if(Svo == 2) cpyIn(L3_S2_ADDR,addr);
		break;
		
		case 4:
		if(Svo == 0)	  cpyIn(L4_S0_ADDR,addr);
		else if(Svo == 1) cpyIn(L4_S1_ADDR,addr);
		else if(Svo == 2) cpyIn(L4_S2_ADDR,addr);
		break;
		
		case 5:
		if(Svo == 0)	  cpyIn(L5_S0_ADDR,addr);
		else if(Svo == 1) cpyIn(L5_S1_ADDR,addr);
		else if(Svo == 2) cpyIn(L5_S2_ADDR,addr);
		break;
	}
}

void WriteServo(int Leg,int svo,float angle) 
{
	char buf[100];
	int addrData[2];
	legGetI2Caddr(Leg,svo,addrData);
	extern float* SvoCal;
	 //uint16_t stop = (int)((1.00+((angle)/180.00))*(4095.00/(20.00)));
	
	angle = angle - SvoCal[svo*12+2*Leg];
	
	
	uint16_t stop = (int)lroundf( (4095.00/(20.00)) * ((0.56) + (2.4-0.56)*(angle/180.00))  );	
		
	i2cWriteReg(addrData[0],addrData[1],0x01);
	i2cWriteReg(addrData[0],addrData[1]+1,0x00);
	i2cWriteReg(addrData[0],addrData[1]+2,stop);
	i2cWriteReg(addrData[0],addrData[1]+3,stop >> 8);
	
}


void SetupCameraVga() {
	write_SCCB(0x12, 0x80);
	write_SCCB(0x11, 0x83);
	write_SCCB(0x6b, 0x4a);
	write_SCCB(0x6a, 0x3e);
	write_SCCB(0x3b, 0x09);
	write_SCCB(0x13, 0xe0);
	write_SCCB(0x01, 0x80);
	write_SCCB(0x02, 0x80);
	write_SCCB(0x00, 0x00);
	write_SCCB(0x10, 0x00);
	write_SCCB(0x13, 0xe5);	//
	write_SCCB(0x39, 0x43); //50 for 30fps
	write_SCCB(0x38, 0x12); //92 for 30fps
	write_SCCB(0x37, 0x00);
	write_SCCB(0x35, 0x91); //81 for 30fps
	write_SCCB(0x0e, 0xa0);
	write_SCCB(0x1e, 0x04);	//
	write_SCCB(0xa8, 0x80);
	write_SCCB(0x12, 0x44);
	write_SCCB(0x04, 0x00);
	write_SCCB(0x0c, 0x04);
	write_SCCB(0x0d, 0x80);
	write_SCCB(0x18, 0xc6);
	write_SCCB(0x17, 0x26);
	write_SCCB(0x32, 0xad);
	write_SCCB(0x03, 0x00);
	write_SCCB(0x1a, 0x3d);
	write_SCCB(0x19, 0x01);
	write_SCCB(0x3f, 0xa6);
	write_SCCB(0x14, 0x2e);
	write_SCCB(0x15, 0x02|1<<6);
	write_SCCB(0x41, 0x00);
	write_SCCB(0x42, 0x08);
	//
	write_SCCB(0x1b, 0x00);
	write_SCCB(0x16, 0x06);
	write_SCCB(0x33, 0xe2); //c0 for internal regulator
	write_SCCB(0x34, 0xbf);
	write_SCCB(0x96, 0x04);
	write_SCCB(0x3a, 0x00);
	write_SCCB(0x8e, 0x00);
	//
	write_SCCB(0x3c, 0x77);
	write_SCCB(0x8b, 0x06);
	write_SCCB(0x94, 0x88);
	write_SCCB(0x95, 0x88);
	write_SCCB(0x40, 0xd1);
	write_SCCB(0x29, 0x3f); //2f for internal regulator
	write_SCCB(0x0f, 0x42);
	//
	write_SCCB(0x3d, 0x90);
	write_SCCB(0x69, 0x40);
	write_SCCB(0x5c, 0xb9);
	write_SCCB(0x5d, 0x96);
	write_SCCB(0x5e, 0x10);
	write_SCCB(0x59, 0xc0);
	write_SCCB(0x5a, 0xaf);
	write_SCCB(0x5b, 0x55);
	write_SCCB(0x43, 0xf0);
	write_SCCB(0x44, 0x10);
	write_SCCB(0x45, 0x68);
	write_SCCB(0x46, 0x96);
	write_SCCB(0x47, 0x60);
	write_SCCB(0x48, 0x80);
	write_SCCB(0x5f, 0xe0);
	write_SCCB(0x60, 0x8c); //0c for advanced AWB (related to lens)
	write_SCCB(0x61, 0x20);	write_SCCB(0xa5, 0xd9);
	write_SCCB(0xa4, 0x74);
	write_SCCB(0x8d, 0x02);
	write_SCCB(0x13, 0xe7);
	//
	write_SCCB(0x4f, 0xb7);
	write_SCCB(0x50, 0x2e);
	write_SCCB(0x51, 0x09);
	write_SCCB(0x52, 0x1f);
	write_SCCB(0x53, 0xb1);
	write_SCCB(0x54, 0x12);
	write_SCCB(0x55, 0x06);
	write_SCCB(0x56, 0x55);
	write_SCCB(0x57, 0xdb);
	write_SCCB(0x58, 0x77);
	//
	write_SCCB(0x8c, 0x23);
	write_SCCB(0x3e, 0x02);
	write_SCCB(0xa9, 0xb8);
	write_SCCB(0xaa, 0x92);
	write_SCCB(0xab, 0x0a);
	//
	write_SCCB(0x8f, 0xdf);
	write_SCCB(0x90, 0x00);
	write_SCCB(0x91, 0x00);
	write_SCCB(0x9f, 0x00);
	write_SCCB(0xa0, 0x00);
	write_SCCB(0x3a, 0x01);
	//
	write_SCCB(0x24, 0x70);
	write_SCCB(0x25, 0x64);
	write_SCCB(0x26, 0xc3);
	//
	write_SCCB(0x2a, 0x00); //10 for 50Hz
	write_SCCB(0x2b, 0x00); //40 for 50Hz
	//
	//gamma
	write_SCCB(0x6c, 0x40);
	write_SCCB(0x6d, 0x30);
	write_SCCB(0x6e, 0x4b);
	write_SCCB(0x6f, 0x60);
	write_SCCB(0x70, 0x70);
	write_SCCB(0x71, 0x70);
	write_SCCB(0x72, 0x70);
	write_SCCB(0x73, 0x70);
	write_SCCB(0x74, 0x60);
	write_SCCB(0x75, 0x60);
	write_SCCB(0x76, 0x50);
	write_SCCB(0x77, 0x48);
	write_SCCB(0x78, 0x3a);
	write_SCCB(0x79, 0x2e);
	write_SCCB(0x7a, 0x28);
	write_SCCB(0x7b, 0x22);
	write_SCCB(0x7c, 0x04);
	write_SCCB(0x7d, 0x07);
	write_SCCB(0x7e, 0x10);
	write_SCCB(0x7f, 0x28);
	write_SCCB(0x80, 0x36);
	write_SCCB(0x81, 0x44);
	write_SCCB(0x82, 0x52);
	write_SCCB(0x83, 0x60);
	write_SCCB(0x84, 0x6c);
	write_SCCB(0x85, 0x78);
	write_SCCB(0x86, 0x8c);
	write_SCCB(0x87, 0x9e);
	write_SCCB(0x88, 0xbb);
	write_SCCB(0x89, 0xd2);
	write_SCCB(0x8a, 0xe6);
	//
	write_SCCB(0x09, 0x11);
	write_SCCB(0x09, 0x01);
	
}

void SetupCameraRAW() {
	write_SCCB(0x12, 0x80);
	write_SCCB(0x11, 0x81);
	write_SCCB(0x6b, 0x4a);
	write_SCCB(0x3b, 0x01);
	write_SCCB(0x6a, 0x83);
	write_SCCB(0x13, 0xe2);
	write_SCCB(0x10, 0x00);
	write_SCCB(0x00, 0x00);
	write_SCCB(0x01, 0x80);
	write_SCCB(0x02, 0x80);
	write_SCCB(0x13, 0xe7);	write_SCCB(0x39, 0x50);
	write_SCCB(0x38, 0x93);
	write_SCCB(0x37, 0x00);
	write_SCCB(0x35, 0x81);
	write_SCCB(0x0e, 0xa0);
	//
	write_SCCB(0xa8, 0x80);
	write_SCCB(0x12, 0x05);
	write_SCCB(0x04, 0x00);
	write_SCCB(0x0c, 0x00);	write_SCCB(0x0d, 0x00);
	write_SCCB(0x18, 0xbb);
	write_SCCB(0x17, 0x1b);
	write_SCCB(0x32, 0xa4);
	write_SCCB(0x19, 0x01);
	write_SCCB(0x1a, 0x81);
	write_SCCB(0x03, 0x12);
	//
	write_SCCB(0x1b, 0x00);
	write_SCCB(0x16, 0x07);
	write_SCCB(0x33, 0xe2); //c0 for internal regulator
	write_SCCB(0x34, 0xbf);
	write_SCCB(0x41, 0x00);
	write_SCCB(0x96, 0x04);
	//
	write_SCCB(0x3d, 0x19);
	write_SCCB(0x69, 0x40);
	write_SCCB(0x3a, 0x01);
	write_SCCB(0x8e, 0x00);
	//
	write_SCCB(0x3c, 0x73);
	write_SCCB(0x8f, 0xdf);
	write_SCCB(0x8b, 0x06);
	write_SCCB(0x8c, 0x20);
	write_SCCB(0x94, 0x88);
	write_SCCB(0x95, 0x88);
	write_SCCB(0x40, 0xc1);
	write_SCCB(0x29, 0x3f); //2f for internal regulator
	write_SCCB(0x0f, 0x42);
	write_SCCB(0xa5, 0x80);
	write_SCCB(0x1e, 0x04);
	write_SCCB(0xa9, 0xb8);
	write_SCCB(0xaa, 0x92);
	write_SCCB(0xab, 0x0a);
	//
	write_SCCB(0x24, 0x68);
	write_SCCB(0x25, 0x5c);
	write_SCCB(0x26, 0xc3);
	write_SCCB(0x14, 0x2e);}void SetupCameraC() {	write_SCCB(0x12,1<<7);		write_SCCB(0x12,1<<6);	//write_SCCB(0x12,1<<2);		write_SCCB(0x00,0xFF);	write_SCCB(0x01,0xFF);		write_SCCB(0x03,12|1<<6);	write_SCCB(0x04,00);	write_SCCB(0x05,00);	write_SCCB(0x06,00);	write_SCCB(0x08,00);	write_SCCB(0x09,03);	write_SCCB(0x0C,00);	write_SCCB(0x0D,00);	write_SCCB(0x0E,00);	write_SCCB(0x0F,00);	write_SCCB(0x10,40);	write_SCCB(0x11,0x00);	write_SCCB(0x13,0xFF);	write_SCCB(0x14,0x4A|1<<2);	write_SCCB(0x15,0);	write_SCCB(0x1E,00);	write_SCCB(0x3D,00);	write_SCCB(0x3A,0b00001101);	write_SCCB(0x3E,00);	write_SCCB(0x40,0b11010000);	write_SCCB(0x41,00);	write_SCCB(0x42,00);	}void SetupCameraYUVVGA() {	write_SCCB(0x12, 0x80);
	write_SCCB(0x11, 0x00);
	write_SCCB(0x6b, 0x0a);
	write_SCCB(0x6a, 0x3e);
	write_SCCB(0x3b, 0x09);
	write_SCCB(0x13, 0xe0);
	write_SCCB(0x01, 0x80);
	write_SCCB(0x02, 0x80);
	write_SCCB(0x00, 0x00);
	write_SCCB(0x10, 0x00);
	write_SCCB(0x13, 0xe5);
	//	write_SCCB(0x39, 0x43); //50 for 30fps
	write_SCCB(0x38, 0x12); //92 for 30fps
	write_SCCB(0x37, 0x00);
	write_SCCB(0x35, 0x91); //81 for 30fps
	write_SCCB(0x0e, 0x20);
	write_SCCB(0x1e, 0x34);
	//
	write_SCCB(0xa8, 0x80);
	write_SCCB(0x12, 0x40);
	write_SCCB(0x04, 0x00);
	write_SCCB(0x0c, 0x04);
	write_SCCB(0x0d, 0x80);
	write_SCCB(0x18, 0xc6);
	write_SCCB(0x17, 0x26);
	write_SCCB(0x32, 0xad);
	write_SCCB(0x03, 0x00);
	write_SCCB(0x1a, 0x81);
	write_SCCB(0x19, 0x01);
	write_SCCB(0x3f, 0xa6);
	write_SCCB(0x14, 0x2e);
	write_SCCB(0x15, 0x03|1<<3);
	write_SCCB(0x41, 0x02);
	write_SCCB(0x42, 0x08);
	//
	write_SCCB(0x1b, 0x00);
	write_SCCB(0x16, 0x06);
	write_SCCB(0x33, 0xe2); //c0 for internal regulator
	write_SCCB(0x34, 0xbf);
	write_SCCB(0x96, 0x04);
	write_SCCB(0x3a, 0x00);
	write_SCCB(0x8e, 0x00);
	//
	write_SCCB(0x3c, 0x77);
	write_SCCB(0x8b, 0x06);
	write_SCCB(0x94, 0x88);
	write_SCCB(0x95, 0x88);
	write_SCCB(0x40, 0xc1);
	write_SCCB(0x29, 0x3f); //2f for internal regulator
	write_SCCB(0x0f, 0x42);
	//
	write_SCCB(0x3d, 0x92);
	write_SCCB(0x69, 0x40);
	write_SCCB(0x5c, 0xb9);
	write_SCCB(0x5d, 0x96);
	write_SCCB(0x5e, 0x10);
	write_SCCB(0x59, 0xc0);
	write_SCCB(0x5a, 0xaf);
	write_SCCB(0x5b, 0x55);
	write_SCCB(0x43, 0xf0);
	write_SCCB(0x44, 0x10);
	write_SCCB(0x45, 0x68);
	write_SCCB(0x46, 0x96);
	write_SCCB(0x47, 0x60);
	write_SCCB(0x48, 0x80);
	write_SCCB(0x5f, 0xe0);
	write_SCCB(0x60, 0x8c); //0c for advanced AWB (related to lens)
	write_SCCB(0x61, 0x20);
	write_SCCB(0xa5, 0xd9);	write_SCCB(0xa4, 0x74);
	write_SCCB(0x8d, 0x02);
	write_SCCB(0x13, 0xe7);
	//
	write_SCCB(0x4f, 0x3a);
	write_SCCB(0x50, 0x3d);
	write_SCCB(0x51, 0x03);
	write_SCCB(0x52, 0x12);
	write_SCCB(0x53, 0x26);
	write_SCCB(0x54, 0x38);
	write_SCCB(0x55, 0x40);
	write_SCCB(0x56, 0x40);
	write_SCCB(0x57, 0x40);
	write_SCCB(0x58, 0x0d);
	//
	write_SCCB(0x8c, 0x23);
	write_SCCB(0x3e, 0x02);
	write_SCCB(0xa9, 0xb8);
	write_SCCB(0xaa, 0x92);
	write_SCCB(0xab, 0x0a);
	//
	write_SCCB(0x8f, 0xdf);
	write_SCCB(0x90, 0x00);
	write_SCCB(0x91, 0x00);
	write_SCCB(0x9f, 0x00);
	write_SCCB(0xa0, 0x00);
	write_SCCB(0x3a, 0x01);
	//
	write_SCCB(0x24, 0x70);
	write_SCCB(0x25, 0x64);
	write_SCCB(0x26, 0xc3);
	//
	write_SCCB(0x2a, 0x00); //10 for 50Hz
	write_SCCB(0x2b, 0x00); //40 for 50Hz
	//
	//gamma
	write_SCCB(0x6c, 0x40);
	write_SCCB(0x6d, 0x30);
	write_SCCB(0x6e, 0x4b);
	write_SCCB(0x6f, 0x60);
	write_SCCB(0x70, 0x70);
	write_SCCB(0x71, 0x70);
	write_SCCB(0x72, 0x70);
	write_SCCB(0x73, 0x70);
	write_SCCB(0x74, 0x60);
	write_SCCB(0x75, 0x60);
	write_SCCB(0x76, 0x50);
	write_SCCB(0x77, 0x48);
	write_SCCB(0x78, 0x3a);
	write_SCCB(0x79, 0x2e);
	write_SCCB(0x7a, 0x28);
	write_SCCB(0x7b, 0x22);
	write_SCCB(0x7c, 0x04);
	write_SCCB(0x7d, 0x07);
	write_SCCB(0x7e, 0x10);
	write_SCCB(0x7f, 0x28);
	write_SCCB(0x80, 0x36);
	write_SCCB(0x81, 0x44);	write_SCCB(0x82, 0x52);
	write_SCCB(0x83, 0x60);
	write_SCCB(0x84, 0x6c);
	write_SCCB(0x85, 0x78);
	write_SCCB(0x86, 0x8c);
	write_SCCB(0x87, 0x9e);
	write_SCCB(0x88, 0xbb);
	write_SCCB(0x89, 0xd2);
	write_SCCB(0x8a, 0xe6);}	void setupcameraLinuxDriver() {	const unsigned char ov_settings[][2] = {
		{ REG_COM2, 0x10 },	/* Set soft sleep mode */
		{ REG_COM5, 0x00 },	/* System clock options */
		{ REG_COM2, 0x01 },	/* Output drive, soft sleep mode */
		{ REG_COM10, 0x00 },	/* Slave mode, HREF vs HSYNC, signals negate */
		{ REG_EDGE, 0xa6 },	/* Edge enhancement treshhold and factor */
		{ REG_COM16, 0x00 },	/* Color matrix coeff double option */
		{ REG_COM17, 0x08 },	/* Single frame out, banding filter */
		{ 0x16, 0x06 },
		{ REG_CHLF, 0xc0 },	/* Reserved  */
		{ 0x34, 0xbf },
		{ 0xa8, 0x80 },
		{ 0x96, 0x04 },
		{ 0x8e, 0x00 },
		{ REG_COM12, 0x77 },	/* HREF option, UV average  */
		{ 0x8b, 0x06 },
		{ 0x35, 0x91 },
		{ 0x94, 0x88 },
		{ 0x95, 0x88 },
		{ REG_COM15, 0xc1 },	/* Output range, RGB 555/565 */
		{ REG_GRCOM, 0x2f },	/* Analog BLC & regulator */
		{ REG_COM6, 0x43 },	/* HREF & ADBLC options */
		{ REG_COM8, 0xe0 },	/* AGC/AEC options */
		{ REG_COM13, 0x50 },	/* Gamma selection, colour matrix, UV delay */
		{ REG_HV, 0x80 },	/* Manual banding filter MSB  */
		{ 0x5c, 0x96 },		/* Reserved up to 0xa5 */
		{ 0x5d, 0x96 },
		{ 0x5e, 0x10 },
		{ 0x59, 0xeb },
		{ 0x5a, 0x9c },
		{ 0x5b, 0x55 },
		{ 0x43, 0xf0 },
		{ 0x44, 0x10 },
		{ 0x45, 0x55 },
		{ 0x46, 0x86 },
		{ 0x47, 0x64 },
		{ 0x48, 0x86 },
		{ 0x5f, 0xe0 },
		{ 0x60, 0x8c },
		{ 0x61, 0x20 },
		{ 0xa5, 0xd9 },
		{ 0xa4, 0x74 },		/* reserved */
		{ REG_COM23, 0x02 },	/* Color gain analog/_digital_ */
		{ REG_COM8, 0xe7 },	/* Enable AEC, AWB, AEC */
		{ REG_COM22, 0x23 },	/* Edge enhancement, denoising */
		{ 0xa9, 0xb8 },
		{ 0xaa, 0x92 },
		{ 0xab, 0x0a },
		{ REG_DBLC1, 0xdf },	/* Digital BLC */
		{ REG_DBLC_B, 0x00 },	/* Digital BLC B chan offset */
		{ REG_DBLC_R, 0x00 },	/* Digital BLC R chan offset */
		{ REG_DBLC_GB, 0x00 },	/* Digital BLC GB chan offset */
		{ REG_DBLC_GR, 0x00 },
		{ REG_COM9, 0x3a },	/* Gain ceiling 16x */
		//{0x11,	0x3F},
			
		{ 0xff,0xff }
	};		const unsigned char ov_sxga[] = {
	0x00, 0x00, 0x00, 0x1d, 0xbd, 0xbf, 0x01, 0x81, 0x12,
	0x81, 0x93, 0x51,0xFF
};		const unsigned char ov_format[] = {
		0x12, 0x0c, 0x0d, 0x17, 0x18, 0x32, 0x19, 0x1a, 0x03,
		0x37, 0x38, 0x39,0xff
	};		const unsigned char ov_vga[] = {
		0x40, 0x04, 0x80, 0x26, 0xc6, 0xed, 0x01, 0x3d, 0x00,
		0x91, 0x12, 0x43,
	};		const unsigned char ov_qcif[] = {
	0x08, 0x04, 0x80, 0x28, 0x80, 0xed, 0x00, 0x24, 0x36,
	0x91, 0x12, 0x43,
};		for(int i = 0;  ov_settings[i][0] != 0xff;i++ ) write_SCCB(ov_settings[i][0],ov_settings[i][1]);	for(int i = 0; ov_format[i] != 0xff;i++ ) write_SCCB(ov_format[i],ov_vga[1]);	}void SetupCameraYUVVGA_OV7670() {		//Input clock 24Mhz,0x25fps
		 write_SCCB_76(0x12,0x80);
		 write_SCCB_76(0x11,0x00);
		 write_SCCB_76(0x3a,0x04);
		 write_SCCB_76(0x12,0x00);
		 write_SCCB_76(0x17,0x13);
		 write_SCCB_76(0x18,0x01);
		 write_SCCB_76(0x32,0xb6);
		 write_SCCB_76(0x19,0x02);
		 write_SCCB_76(0x1a,0x7a);
		 write_SCCB_76(0x03,0x0a);
		 write_SCCB_76(0x0c,0x00);
		 write_SCCB_76(0x3e,0x00);
		 write_SCCB_76(0x70,0x3a);
		 write_SCCB_76(0x71,0x35);
		 write_SCCB_76(0x72,0x11);
		 write_SCCB_76(0x73,0xf0);
		 write_SCCB_76(0xa2,0x02);
		 write_SCCB_76(0x7a,0x20);
		 write_SCCB_76(0x7b,0x10);
		 write_SCCB_76(0x7c,0x1e);
		 write_SCCB_76(0x7d,0x35);
		 write_SCCB_76(0x7e,0x5a);
		 write_SCCB_76(0x7f,0x69);
		 write_SCCB_76(0x80,0x76);
		 write_SCCB_76(0x81,0x80);
		 write_SCCB_76(0x82,0x88);
		 write_SCCB_76(0x83,0x8f);
		 write_SCCB_76(0x84,0x96);
		 write_SCCB_76(0x85,0xa3);
		 write_SCCB_76(0x86,0xaf);
		 write_SCCB_76(0x87,0xc4);
		 write_SCCB_76(0x88,0xd7);
		 write_SCCB_76(0x89,0xe8);
		 write_SCCB_76(0x13,0xe7);
		 write_SCCB_76(0x01,0x28);
		 write_SCCB_76(0x02,0x30);
		 write_SCCB_76(0x00,0x00);
		 write_SCCB_76(0x10,0x00);
		 write_SCCB_76(0x0d,0x40);
		 write_SCCB_76(0x14,0x18);
		 write_SCCB_76(0xa5,0x07);
		 write_SCCB_76(0xab,0x08);
		 write_SCCB_76(0x24,0x95);
		 write_SCCB_76(0x25,0x33);
		 write_SCCB_76(0x26,0xe3);
		 write_SCCB_76(0x9f,0x78);
		 write_SCCB_76(0xa0,0x68);
		 write_SCCB_76(0xa1,0x03);
		 write_SCCB_76(0xa6,0xd8);
		 write_SCCB_76(0xa7,0xd8);
		 write_SCCB_76(0xa8,0xf0);
		 write_SCCB_76(0xa9,0x90);
		 write_SCCB_76(0xaa,0x94);
		 write_SCCB_76(0x13,0xe7);
		 write_SCCB_76(0x0e,0x61);
		 write_SCCB_76(0x0f,0x4b);
		 write_SCCB_76(0x16,0x02);
		 write_SCCB_76(0x1e,0x07);
		 write_SCCB_76(0x21,0x02);
		 write_SCCB_76(0x22,0x91);
		 write_SCCB_76(0x29,0x07);
		 write_SCCB_76(0x33,0x0b);
		 write_SCCB_76(0x35,0x0b);
		 write_SCCB_76(0x37,0x1d);
		 write_SCCB_76(0x38,0x71);
		 write_SCCB_76(0x39,0x2a);
		 write_SCCB_76(0x3c,0x78);
		 write_SCCB_76(0x4d,0x40);
		 write_SCCB_76(0x4e,0x20);
		 write_SCCB_76(0x69,0x00);
		 write_SCCB_76(0x6b,0x0a);
		 write_SCCB_76(0x74,0x10);
		 write_SCCB_76(0x8d,0x4f);
		 write_SCCB_76(0x8e,0x00);
		 write_SCCB_76(0x8f,0x00);
		 write_SCCB_76(0x90,0x00);
		 write_SCCB_76(0x91,0x00);
		 write_SCCB_76(0x92,0x66);
		 write_SCCB_76(0x96,0x00);
		 write_SCCB_76(0x9a,0x80);
		 write_SCCB_76(0xb0,0x84);
		 write_SCCB_76(0xb1,0x0c);
		 write_SCCB_76(0xb2,0x0e);
		 write_SCCB_76(0xb3,0x82);
		 write_SCCB_76(0xb8,0x0a);
		 write_SCCB_76(0x43,0x14);
		 write_SCCB_76(0x44,0xf0);
		 write_SCCB_76(0x45,0x34);
		 write_SCCB_76(0x46,0x58);
		 write_SCCB_76(0x47,0x28);
		 write_SCCB_76(0x48,0x3a);
		 write_SCCB_76(0x59,0x88);
		 write_SCCB_76(0x5a,0x88);
		 write_SCCB_76(0x5b,0x44);
		 write_SCCB_76(0x5c,0x67);
		 write_SCCB_76(0x5d,0x49);
		 write_SCCB_76(0x5e,0x0e);
		 write_SCCB_76(0x64,0x04);
		 write_SCCB_76(0x65,0x20);
		 write_SCCB_76(0x66,0x05);
		 write_SCCB_76(0x94,0x04);
		 write_SCCB_76(0x95,0x08);
		 write_SCCB_76(0x6c,0x0a);
		 write_SCCB_76(0x6d,0x55);
		 write_SCCB_76(0x6e,0x11);
		 write_SCCB_76(0x6f,0x9e);
		 write_SCCB_76(0x6a,0x40);
		 write_SCCB_76(0x01,0x20);
		 write_SCCB_76(0x02,0x20);
		 write_SCCB_76(0x13,0xe7);
		 write_SCCB_76(0x4f,0x80);
		 write_SCCB_76(0x50,0x80);
		 write_SCCB_76(0x51,0x00);
		 write_SCCB_76(0x52,0x22);
		 write_SCCB_76(0x53,0x5e);
		 write_SCCB_76(0x54,0x80);
		 write_SCCB_76(0x58,0x9e);
		 write_SCCB_76(0x41,0x08);
		 write_SCCB_76(0x3f,0x00);
		 write_SCCB_76(0x75,0x03);
		 write_SCCB_76(0x76,0xe1);
		 write_SCCB_76(0x4c,0x00);
		 write_SCCB_76(0x77,0x00);
		 write_SCCB_76(0x3d,0x00);
		 write_SCCB_76(0x4b,0x09);
		 write_SCCB_76(0xc9,0x60);
		 write_SCCB_76(0x41,0x38);
		 write_SCCB_76(0x56,0x40);
		 write_SCCB_76(0x34,0x11);
		 write_SCCB_76(0x3b,0x0a);
		 write_SCCB_76(0xa4,0x88);
		 write_SCCB_76(0x96,0x00);
		 write_SCCB_76(0x97,0x30);
		 write_SCCB_76(0x98,0x20);
		 write_SCCB_76(0x99,0x30);
		 write_SCCB_76(0x9a,0x84);
		 write_SCCB_76(0x9b,0x29);
		 write_SCCB_76(0x9c,0x03);
		 write_SCCB_76(0x9d,0x98);
		 write_SCCB_76(0x9e,0x3f);
		 write_SCCB_76(0x78,0x04);
		 write_SCCB_76(0x79,0x01);
		 write_SCCB_76(0xc8,0xf0);
		 write_SCCB_76(0x79,0x0f);
		 write_SCCB_76(0xc8,0x00);
		 write_SCCB_76(0x79,0x10);
		 write_SCCB_76(0xc8,0x7e);
		 write_SCCB_76(0x79,0x0a);
		 write_SCCB_76(0xc8,0x80);
		 write_SCCB_76(0x79,0x0b);
		 write_SCCB_76(0xc8,0x01);
		 write_SCCB_76(0x79,0x0c);
		 write_SCCB_76(0xc8,0x0f);
		 write_SCCB_76(0x79,0x0d);
		 write_SCCB_76(0xc8,0x20);
		 write_SCCB_76(0x79,0x09);
		 write_SCCB_76(0xc8,0x80);
		 write_SCCB_76(0x79,0x02);
		 write_SCCB_76(0xc8,0xc0);
		 write_SCCB_76(0x79,0x03);
		 write_SCCB_76(0xc8,0x40);
		 write_SCCB_76(0x79,0x05);
		 write_SCCB_76(0xc8,0x30);
		 write_SCCB_76(0x79,0x26);
		 write_SCCB_76(0x2d,0x00);
		 write_SCCB_76(0x2e,0x00);		 write_SCCB_76(0x2e,0x00);		 write_SCCB_76(0x1b,0x00);		 write_SCCB_76(0x15,1<<3|1<<1);		 		 		 //Color saturation 0		//write_SCCB_76(0x4f, 0x80);
		//write_SCCB_76(0x50, 0x80);
		//write_SCCB_76(0x51, 0x00);
		//write_SCCB_76(0x52, 0x22);
		//write_SCCB_76(0x53, 0x5e);
		//write_SCCB_76(0x54, 0x80);
		//write_SCCB_76(0x58, 0x9e);		////0//write_SCCB_76(0x4f, 0x40);
//write_SCCB_76(0x50, 0x40);
//write_SCCB_76(0x51, 0x00);
//write_SCCB_76(0x52, 0x11);
//write_SCCB_76(0x53, 0x2f);
//write_SCCB_76(0x54, 0x40);
//write_SCCB_76(0x58, 0x9e);//write_SCCB_76(0x4f, 0x66);
//write_SCCB_76(0x50, 0x66);
//write_SCCB_76(0x51, 0x00);
//write_SCCB_76(0x52, 0x1b);
//write_SCCB_76(0x53, 0x4b);
//write_SCCB_76(0x54, 0x66);
//write_SCCB_76(0x58, 0x9e);		/*		const unsigned char ov7_settings[][2] =
{
	{0x3a, 0x04},
    {0x40, 0xd0},
    {0x12, 0x14},
    {0x32, 0x80},
    {0x17, 0x16},
    {0x18, 0x04},
    {0x19, 0x02},
    {0x1a, 0x7b},
    {0x03, 0x06},
    {0x0c, 0x00},
    {0x3e, 0x00},
    {0x70, 0x00},
    {0x71, 0x00},
    {0x72, 0x11},
    {0x73, 0x00},
    {0xa2, 0x02},
    {0x11, 0x81},
    {0x7a, 0x20},
    {0x7b, 0x1c},
    {0x7c, 0x28},
    {0x7d, 0x3c},
    {0x7e, 0x55},
    {0x7f, 0x68},
    {0x80, 0x76},
    {0x81, 0x80},
    {0x82, 0x88},
    {0x83, 0x8f},
    {0x84, 0x96},
    {0x85, 0xa3},
    {0x86, 0xaf},
    {0x87, 0xc4},
    {0x88, 0xd7},
    {0x89, 0xe8},
    {0x13, 0xe0},
    {0x00, 0x00},
    {0x10, 0x00},
    {0x0d, 0x00},
    {0x14, 0x28},
    {0xa5, 0x05},
    {0xab, 0x07},
    {0x24, 0x75},
    {0x25, 0x63},
    {0x26, 0xA5},
    {0x9f, 0x78},
    {0xa0, 0x68},
    {0xa1, 0x03},
    {0xa6, 0xdf},
    {0xa7, 0xdf},
    {0xa8, 0xf0},
    {0xa9, 0x90},
    {0xaa, 0x94},
    {0x13, 0xe5},
    {0x0e, 0x61},
    {0x0f, 0x4b},
    {0x16, 0x02},
    {0x1e, 0x17},
    {0x21, 0x02},
    {0x22, 0x91},
    {0x29, 0x07},
    {0x33, 0x0b},
    {0x35, 0x0b},
    {0x37, 0x1d},
    {0x38, 0x71},
    {0x39, 0x2a},
    {0x3c, 0x78},
    {0x4d, 0x40},
    {0x4e, 0x20},
    {0x69, 0x00},
    {0x6b, 0x00},
    {0x74, 0x19},
    {0x8d, 0x4f},
    {0x8e, 0x00},
    {0x8f, 0x00},
    {0x90, 0x00},
    {0x91, 0x00},
    {0x92, 0x00},
    {0x96, 0x00},
    {0x9a, 0x80},
    {0xb0, 0x84},
    {0xb1, 0x0c},
    {0xb2, 0x0e},
    {0xb3, 0x82},
    {0xb8, 0x0a},
    {0x43, 0x14},
    {0x44, 0xf0},
    {0x45, 0x34},
    {0x46, 0x58},
    {0x47, 0x28},
    {0x48, 0x3a},
    {0x59, 0x88},
    {0x5a, 0x88},
    {0x5b, 0x44},
    {0x5c, 0x67},
    {0x5d, 0x49},
    {0x5e, 0x0e},
    {0x64, 0x04},
    {0x65, 0x20},
    {0x66, 0x05},
    {0x94, 0x04},
    {0x95, 0x08},
    {0x6c, 0x0a},
    {0x6d, 0x55},
    {0x6e, 0x11},
    {0x6f, 0x9f},
    {0x6a, 0x40},
    {0x01, 0x40},
    {0x02, 0x40},
    {0x13, 0xe7},
    {0x15, 0x02},
    {0x4f, 0x80},
    {0x50, 0x80},
    {0x51, 0x00},
    {0x52, 0x22},
    {0x53, 0x5e},
    {0x54, 0x80},
    {0x58, 0x9e},   
    {0x41, 0x08},
    {0x3f, 0x00},
    {0x75, 0x05},
    {0x76, 0xe1},
    {0x4c, 0x00},
    {0x77, 0x01},
    {0x3d, 0xc2},  
    {0x4b, 0x09},
    {0xc9, 0x60},
    {0x41, 0x38},
    {0x56, 0x40},
    {0x34, 0x11},
    {0x3b, 0x02},
    {0xa4, 0x89},
    {0x96, 0x00},
    {0x97, 0x30},
    {0x98, 0x20},
    {0x99, 0x30},
    {0x9a, 0x84},
    {0x9b, 0x29},
    {0x9c, 0x03},
    {0x9d, 0x4c},
    {0x9e, 0x3f},
    {0x78, 0x04},   
    {0x79, 0x01},
    {0xc8, 0xf0},
    {0x79, 0x0f},
    {0xc8, 0x00},
    {0x79, 0x10},
    {0xc8, 0x7e},
    {0x79, 0x0a},
    {0xc8, 0x80},
    {0x79, 0x0b},
    {0xc8, 0x01},
    {0x79, 0x0c},
    {0xc8, 0x0f},
    {0x79, 0x0d},
    {0xc8, 0x20},
    {0x79, 0x09},
    {0xc8, 0x80},
    {0x79, 0x02},
    {0xc8, 0xc0},
    {0x79, 0x03},
    {0xc8, 0x40},
    {0x79, 0x05},
    {0xc8, 0x30},
    {0x79, 0x26},
    {0x09, 0x03},
    {0x3b, 0x42},
	{0xff, 0xff},
	};	for(int i = 0;  ov7_settings[i][0] != 0xff;i++ ) write_SCCB(ov7_settings[i][0],ov7_settings[i][1]);	*/		 }float getBatVoltage() {	afec_channel_enable(AFEC1,AFEC_CHANNEL_0);
	afec_start_software_conversion(AFEC1);
					
	while(!(afec_get_interrupt_status(AFEC1) & (1<<AFEC_CHANNEL_0)));

	uint16_t convRes = afec_channel_get_value(AFEC1,AFEC_CHANNEL_0) - 0x7f0;
	return (3.3*convRes/4095.00)*((140.00+960.00)/105.00);}void dumpFrame(int dumpLoc) {		isi_dma_channel_disable(ISI,1);
		sendDebugString("IMG:");
		volatile uint8_t* imgData = (uint8_t*)(dumpLoc);
		for(int i=0;i<320*240*2;i++){
			while(!uart_is_tx_ready(UART4));
			uart_write(UART4,imgData[i]);
		}
		sendDebugString(":ENDIMG\n");
		isi_dma_channel_enable(ISI,1);
		//memset(BOARD_SDRAM_ADDR,0,BOARD_SDRAM_ADDR_NUM);	}XZ calcRotation(float inX, float inZ, float cenX,  float cenZ, float rotAng, int opside, float turn) {
	inX = inX - cenX;
	inZ = inZ - cenZ;
	XZ out;
	
	out.X = inX*cos((opside==1)?-rotAng:rotAng) - inZ*sin((opside==1)?-rotAng:rotAng);
	out.Z = inX*sin((opside==1)?-rotAng:rotAng) + inZ*cos((opside==1)?-rotAng:rotAng);
	
	out.X = out.X + cenX;
	if(opside ==0 && turn != 0) out.Z = cenZ + (  out.Z*(1-abs(turn)) + (turn)*(inZ+cenZ)  );
	if(opside ==1 && turn != 0) out.Z = cenZ + (  out.Z*(1-abs(turn)) - (turn)*(inZ+cenZ)  );
	return out;
}

int sign(float in) {
	if(in<0) return -1;
	else return 1;
}

angles legAngCalc(float x, float y, float z) {
	float G = sqrt(x*x + z*z);
	float H = sqrt(y*y+G*G);
	float b = acos((A*A + H*H - B*B)/(2*A*H));
	
	float h = asin(H*(sin(b))/B);
	
	angles Ang;
	
	
	if(H*H >= (A*A+B*B))Ang.S3 = h;
	else Ang.S3 = (M_PI)-h;
	Ang.S2 = (atan2(y,G))+b;
	Ang.S1 = atan2(x,z);
	
	Ang.S1 = Ang.S1*180.00/M_PI;
	Ang.S2 = 90 - Ang.S2*180.00/M_PI;
	Ang.S3 = 180 - Ang.S3*180.00/M_PI;
	
	
	return Ang;
}

void writeLegOut(int leg, float S0, float S1, float S2) {
	
	switch (leg) {
	
	case 0:
		WriteServo(L0_S0,S0);
		WriteServo(L0_S1,S1);
		WriteServo(L0_S2,S2);
	break;
	
	case 1:
		WriteServo(L1_S0,S0);
		WriteServo(L1_S1,S1);
		WriteServo(L1_S2,S2);
	break;

	case 2:
		WriteServo(L2_S0,S0);
		WriteServo(L2_S1,S1);
		WriteServo(L2_S2,S2);
	break;

	case 3:
		WriteServo(L3_S0,S0);
		WriteServo(L3_S1,S1);
		WriteServo(L3_S2,S2);
	break;

	case 4:
		WriteServo(L4_S0,S0);
		WriteServo(L4_S1,S1);
		WriteServo(L4_S2,S2);
	break;

	case 5:
		WriteServo(L5_S0,S0);
		WriteServo(L5_S1,S1);
		WriteServo(L5_S2,S2);
	break;
	
	
	}


}

void getS0cal(int Leg, float* angOff, float* Lin) {
	int calState = 0;
	float ang = 90;
	extern int But_Up;
	while(!(!pio_get(SW4) &&  calState >= 1 && !But_Up)) {
		
		if(!pio_get(SW4)&& !But_Up) {
			if(calState == 0){
				*angOff = 90 - ang;
			}
			calState++;
			ang = 45;
			But_Up = 1;
		}
		
		if(pio_get(SW4)) But_Up = 0;
		
		if(!pio_get(SW3)) {
			ang += 0.1;
		}
		
		if(!pio_get(SW2)) {
			ang -= 0.1;
		}
		
		if(calState == 1) pio_set(LED3);
		else pio_clear(LED3);
		
		WriteServo(Leg,0,ang);
			
	}
	But_Up = 1;
	*Lin = (*angOff+ang)/45.00;
	cmdServoMan(6,0,90.00);
	cmdServoMan(6,1,90.00);
	cmdServoMan(6,2,180.00);
}

void getS1cal(int Leg, float* angOff, float* Lin) {
	int calState = 0;
	float ang = 90;
	extern int But_Up;
	while(!(!pio_get(SW4) &&  calState >= 1 && !But_Up)) {
		
		if(!pio_get(SW4)&& !But_Up) {
			if(calState == 0){
				*angOff = 90 - ang;
			}
			calState++;
			ang = 45;
			But_Up = 1;
		}
		
		if(pio_get(SW4)) But_Up = 0;
		
		if(!pio_get(SW3)) {
			ang += 0.1;
		}
		
		if(!pio_get(SW2)) {
			ang -= 0.1;
		}
		
		if(calState == 1) pio_set(LED3);
		else pio_clear(LED3);
		
		WriteServo(Leg,1,ang);
	}
	But_Up = 1;
	*Lin = (*angOff+ang)/45.00;
	cmdServoMan(6,0,90.00);
	cmdServoMan(6,1,90.00);
	cmdServoMan(6,2,180.00);
}

void getS2cal(int Leg, float* angOff, float* Lin) {
	int calState = 0;
	float ang = 180;
	extern int But_Up;
	while(!(!pio_get(SW4) &&  calState >= 1 && !But_Up)) {
		
		if(!pio_get(SW4)&& !But_Up) {
			if(calState == 0){
				*angOff = 90 - ang;
			}
			calState++;
			ang = 90;
			But_Up = 1;
		}
		
		if(pio_get(SW4)) But_Up = 0;
		
		if(!pio_get(SW3)) {
			ang += 0.1;
		}
		
		if(!pio_get(SW2)) {
			ang -= 0.1;
		}
		
		if(calState == 1) pio_set(LED3);
		else pio_clear(LED3);
		
		WriteServo(Leg,2,ang);
	}
	But_Up = 1;
	*Lin = (*angOff+ang)/90.00;
	cmdServoMan(6,0,90.00);
	cmdServoMan(6,1,90.00);
	cmdServoMan(6,2,180.00);
}


void calibServos(float* calData) {
	sendDebugString("Started servo cal\n");
	for(int i =0; i<6; i++) {
		byteToLEDs(i>>4,0xF0);
		cmdServoMan(6,0,90.00);
		cmdServoMan(6,1,90.00);
		cmdServoMan(6,2,180.00);
		getS0cal(i,&calData[i*2],&calData[i*2+1]);
	}
	for(int i =0; i<6; i++) {
		byteToLEDs(i>>4,0xF0);
		cmdServoMan(6,0,90.00);
		cmdServoMan(6,1,90.00);
		cmdServoMan(6,2,180.00);
		getS1cal(i,&calData[i*2+12],&calData[i*2+13]);
	}
	for(int i =0; i<6; i++) {
		byteToLEDs(i>>4,0xF0);
		cmdServoMan(6,0,90.00);
		cmdServoMan(6,1,90.00);
		cmdServoMan(6,2,180.00);
		getS2cal(i,&calData[i*2+24],&calData[i*2+25]);
	}
	sendDebugString("Finished servo cal data Follows:\n");
	char buf[100];
	for(int i =0; i<36; i++) {
		sprintf(buf,"%f,%f,%f\n",calData[i*2],calData[i*2+1]);
		sendDebugString(buf);
	}
}

void byteToLEDs(uint8_t disp,uint8_t mask) {
	if(mask&(1<<0) && disp&(1<<0)) pio_set(LED0);
	else if(mask&(1<<0)) pio_clear(LED0);
	
	if(mask&(1<<1) && disp&(1<<1)) pio_set(LED1);
	else if(mask&(1<<1)) pio_clear(LED1);
	
	if(mask&(1<<2) && disp&(1<<2)) pio_set(LED2);
	else if(mask&(1<<2)) pio_clear(LED2);
	
	if(mask&(1<<3) && disp&(1<<3)) pio_set(LED3);
	else if(mask&(1<<3)) pio_clear(LED3);
	
	if(mask&(1<<4) && disp&(1<<4)) pio_set(LED4);
	else if(mask&(1<<4)) pio_clear(LED4);
	
	if(mask&(1<<5) && disp&(1<<5)) pio_set(LED5);
	else if(mask&(1<<5)) pio_clear(LED5);
	
	if(mask&(1<<6) && disp&(1<<6)) pio_set(LED6);
	else if(mask&(1<<6)) pio_clear(LED6);
	
	if(mask&(1<<7) && disp&(1<<7)) pio_set(LED7);
	else if(mask&(1<<7)) pio_clear(LED7);
	
}
