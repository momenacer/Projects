/*
 * capteurs.h
 *
 *  Created on: 19 mars 2024
 *      Author: x
 */

/********************** temperature var  *****************////
/********************** temperature var  *****************////
/********************** temperature var  *****************////


#include "driver/i2c.h"

#include <stdio.h>
#include <string.h>
//#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
//#include "driver/gpio.h"
//#include "esp_freertos_hooks.h"
//#include "freertos/semphr.h"
//#include "esp_timer.h"
//#include "esp_system.h"
//#include "sdkconfig.h"
//#include "driver/gptimer.h"  // replace driver/timer.h (since 2023)
//#include "esp_log.h"		//  for debug fct :ESP_LOGI/W/E/D/V( )
#include "stts751_reg.h"

#ifndef MAIN_CAPTEURS_H_
#define MAIN_CAPTEURS_H_
#define _I2C_NUMBER(num) I2C_NUM_##num
#define I2C_NUMBER(num) _I2C_NUMBER(num)

#define DELAY_TIME_BETWEEN_ITEMS_MS 1000 /*!< delay time between different test items */

#define I2C_MASTER_SCL_IO CONFIG_I2C_MASTER_SCL               /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO CONFIG_I2C_MASTER_SDA               /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM I2C_NUMBER(CONFIG_I2C_MASTER_PORT_NUM) /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ CONFIG_I2C_MASTER_FREQUENCY        /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */

#define STTS751_ADDR_7BITS 0x4a //adresse sur 7 bite du capteur de température
#define SENSOR_BUS I2C_MASTER_NUM
#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */

/********************** temperature var  *****************////
/********************** temperature var  *****************////
/********************** temperature var  *****************////

//++++++++ magnometre var ++++++++++++++/
//++++++++ magnometre var ++++++++++++++/
//++++++++ magnometre var ++++++++++++++/


#include "lis2mdl_reg.h"
#define LIS2MDL_ADDR_7BITS 0x1E


//++++++++ magnometre var ++++++++++++++/
//++++++++ magnometre var ++++++++++++++/
//++++++++ magnometre var ++++++++++++++/



//++++++++ magnometre fonction ++++++++++++++/
//++++++++ magnometre fonction ++++++++++++++/
//++++++++ magnometre fonction ++++++++++++++/

 int32_t i2c_master_read_slave_magn(uint8_t i2c_num, uint8_t regaddr, uint8_t *data_rd, uint16_t size);
 int32_t i2c_master_write_slave_magn(uint8_t i2c_num, uint8_t regaddr, uint8_t *data_wr, uint16_t size);

 void get_magnetic_task(void *args);

 void init_magn();

//++++++++ magnometre fonction ++++++++++++++/
//++++++++ magnometre fonction ++++++++++++++/
//++++++++ magnometre fonction ++++++++++++++/

 //++++++++ accelerom (sm6dso)++++++++++++++/
 //++++++++ accelerom (sm6dso)++++++++++++++/
 //++++++++ accelerom (sm6dso)++++++++++++++/

#include "lsm6dso_reg.h"
#define LSM6DSO_ADDR_7BITS 0x6B

 //++++++++ accelerom (sm6dso)++++++++++++++/
 //++++++++ accelerom (sm6dso)++++++++++++++/
 //++++++++ accelerom (sm6dso)++++++++++++++/


/********************** temperature fonction  *****************////
/********************** temperature fonction  *****************////
/********************** temperature fonction  *****************////

 int32_t i2c_master_read_slave_temp(uint8_t i2c_num, uint8_t regaddr, uint8_t *data_rd, uint16_t size);
 int32_t i2c_master_write_slave_temp(uint8_t i2c_num, uint8_t regaddr, uint8_t *data_wr, uint16_t size);
 esp_err_t i2c_master_init(void);

 void get_temp_task(void *args);
 void init_temp();

 /********************** temperature fonction  *****************////
 /********************** temperature fonction  *****************////
 /********************** temperature fonction  *****************////

 //++++++++ accelerom (sm6dso)++++++++++++++/
 //++++++++ accelerom (sm6dso)++++++++++++++/
 //++++++++ accelerom (sm6dso)++++++++++++++/

 int32_t i2c_master_read_slave_accel(uint8_t i2c_num, uint8_t regaddr, uint8_t *data_rd, uint16_t size);
 int32_t i2c_master_write_slave_accel(uint8_t i2c_num, uint8_t regaddr, uint8_t *data_wr, uint16_t size);

 void get_accel_task(void *args);
 void init_accel();
 void whoami_task(void *args);
 //++++++++ accelerom (sm6dso)++++++++++++++/
 //++++++++ accelerom (sm6dso)++++++++++++++/
 //++++++++ accelerom (sm6dso)++++++++++++++/


//++++++++ BLE ++++++++++++++/
//++++++++ BLE ++++++++++++++/

 void float_to_char_array(float value, char *result);

//++++++++ BLE ++++++++++++++/
//++++++++ BLE ++++++++++++++/


#endif /* MAIN_CAPTEURS_H_ */
