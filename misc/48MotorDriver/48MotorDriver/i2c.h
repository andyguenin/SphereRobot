#ifndef i2c__
#define i2c__

#define TWI_COMM_MASK ((1<<TWEN)|(0<<TWSTO)|(0<<TWWC)|(1<<TWIE)|(1<<TWEA)|(0<<TWSTA)|(1<<TWINT))

void init_i2c_slave_receiver(unsigned char address, unsigned char mask, unsigned char respond_to_announce);
void init_all();
char command_ready();
char* command();
void tx_var(char* txv);

#define CALIBRATE	0x00
#define IN			0x01
#define OUT			0x02
#define STOP		0X03
#define TX			0X04

#endif