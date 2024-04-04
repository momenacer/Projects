/*
 * capteurs.c
 *
 *  Created on: 19 mars 2024
 *      Author: xx
 */

#include "capteurs.h"


//******** temperature (stts751)**************/
//******** temperature (stts751)**************/
//******** temperature (stts751)**************/

typedef union{
  int16_t i16bit;
  uint8_t u8bit[2];
} axis1bit16_t;


stmdev_ctx_t dev_ctx;
static axis1bit16_t data_raw_temperature;
 float temperature_degC;
TaskHandle_t xHandle = NULL;

//******** temperature (stts751)**************/
//******** temperature (stts751)**************/
//******** temperature (stts751)**************/




//++++++++ magnometre (lis2mdl)++++++++++++++/
//++++++++ magnometre (lis2mdl)++++++++++++++/
//++++++++ magnometre (lis2mdl)++++++++++++++/

/* Private variables ---------------------------------------------------------*/

static int16_t data_raw_magnetic[3];
static float magnetic_mG[3];
static uint8_t rst;

float MagnetoAngle;
char *boussole;
stmdev_ctx_t dev_ctx_orientation;
int32_t angle;


//++++++++ magnometre (lis2mdl)++++++++++++++/
//++++++++ magnometre (lis2mdl)++++++++++++++/
//++++++++ magnometre (lis2mdl)++++++++++++++/


//++++++++ accelerom (sm6dso)++++++++++++++/
//++++++++ accelerom (sm6dso)++++++++++++++/
//++++++++ accelerom (sm6dso)++++++++++++++/


stmdev_ctx_t dev_ctx_mouvement;

uint8_t whoamI, ret;
int16_t data_raw_acceleration[3];
float acceleration_mg[3];
uint16_t nbr_pas;


//++++++++ accelerom (sm6dso)++++++++++++++/
//++++++++ accelerom (sm6dso)++++++++++++++/
//++++++++ accelerom (sm6dso)++++++++++++++/



//++++++++ BLE ++++++++++++++//
//++++++++ BLE ++++++++++++++//

 char temp_tab[5];
extern char prof_shared_buf[5];

//++++++++ BLE ++++++++++++++//
//++++++++ BLE ++++++++++++++//



//******** temperature (stts751)**************/
//******** temperature (stts751)**************/
//******** temperature (stts751)**************/


/**
 * @brief test code to read esp-i2c-slave like a memory device
 *        We need to fill the buffer of esp slave device, then master can read them out.
 *
 * _____________________________________________________________________________________________________________________________________________
 * | start | slave_addr + wr_bit + ack | write 1 byte (register address) + ack | start | slave_addr + rd_bit + ack | read n bytes + nack | stop |
 * --------|---------------------------|---------------------------------------|-------|---------------------------|---------------------|------|
 *
 */
 int32_t i2c_master_read_slave_temp(uint8_t i2c_num, uint8_t regaddr, uint8_t *data_rd, uint16_t size)
{
    if (size == 0) {
        return ESP_OK;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (STTS751_ADDR_7BITS << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, regaddr, ACK_CHECK_EN);

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (STTS751_ADDR_7BITS << 1) | I2C_MASTER_READ, ACK_CHECK_EN);
    if (size > 1) {
        i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 500 / portTICK_PERIOD_MS);
    //esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

/**
 * @brief Test code to write esp-i2c-slave
 *        Master device write data to slave memory like device,
 *        the data will be stored in slave buffer.
 *        We can read them out from slave buffer.
 *
 * __________________________________________________________________________________________________________
 * | start | slave_addr + wr_bit + ack | write 1 byte (register address) + ack | write n bytes + ack  | stop |
 * --------|---------------------------|---------------------------------------|----------------------|------|
 *
 */
 int32_t i2c_master_write_slave_temp(uint8_t i2c_num, uint8_t regaddr, uint8_t *data_wr, uint16_t size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (STTS751_ADDR_7BITS << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, regaddr, ACK_CHECK_EN);
    i2c_master_write(cmd, data_wr, size, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 500 / portTICK_PERIOD_MS);
    //esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

/**
 * @brief i2c master initialization
 */
 esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;

    conf.clk_flags = 0;
    conf.mode = I2C_MODE_MASTER;// le configurer en mode master
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_DISABLE; // Pullup resistors are already present on X-NUCLEO-IKS01A3
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_DISABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}
//**********************************************recuperer la température ***********
 void get_temp_task(void *args)
{
	/* Read output only if not busy */
	uint8_t flag;

 while (1) {
	stts751_flag_busy_get(&dev_ctx, &flag);
	if (flag)
	{
	  /* Read temperature data */
	  memset(data_raw_temperature.u8bit, 0, sizeof(int16_t));
	  stts751_temperature_raw_get(&dev_ctx, &data_raw_temperature.i16bit);
	  temperature_degC = stts751_from_lsb_to_celsius(data_raw_temperature.i16bit);

	  float_to_char_array(temperature_degC, temp_tab);
	  for (uint8_t i = 0; i < 5; i++)
	  	  		  prof_shared_buf[i] = temp_tab[i];

	  printf("Temperature [degC]:%3.2f\r\n\n", temperature_degC);
	  vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
   }
}

void init_temp(){


		/* This acts as the entry point of ST's STTS751 driver */
		dev_ctx.write_reg = i2c_master_write_slave_temp;
		dev_ctx.read_reg = i2c_master_read_slave_temp;
		dev_ctx.i2c_number = SENSOR_BUS;

		/* Enable interrupt on high(=49.5 degC)/low(=-4.5 degC) temperature. */
		float temperature_high_limit = 49.5f;
		stts751_high_temperature_threshold_set(&dev_ctx, stts751_from_celsius_to_lsb(temperature_high_limit));

		float temperature_low_limit = -4.5f;
		stts751_low_temperature_threshold_set(&dev_ctx, stts751_from_celsius_to_lsb(temperature_low_limit));

		stts751_pin_event_route_set(&dev_ctx,  PROPERTY_ENABLE);

		  /* Set Output Data Rate */
		stts751_temp_data_rate_set(&dev_ctx, STTS751_TEMP_ODR_250mHz);

		  /* Set Resolution */
		stts751_resolution_set(&dev_ctx, STTS751_11bit);
}


//******** temperature (stts751)**************/
//******** temperature (stts751)**************/
//******** temperature (stts751)**************/



//++++++++ magnometre (lis2mdl)++++++++++++++/
//++++++++ magnometre (lis2mdl)++++++++++++++/
//++++++++ magnometre (lis2mdl)++++++++++++++/


/**
 * @brief test code to read esp-i2c-slave like a memory device
 *        We need to fill the buffer of esp slave device, then master can read them out.
 *
 * _____________________________________________________________________________________________________________________________________________
 * | start | slave_addr + wr_bit + ack | write 1 byte (register address) + ack | start | slave_addr + rd_bit + ack | read n bytes + nack | stop |
 * --------|---------------------------|---------------------------------------|-------|---------------------------|---------------------|------|
 *
 */
int32_t i2c_master_read_slave_magn(uint8_t i2c_num, uint8_t regaddr, uint8_t *data_rd, uint16_t size)
{
    if (size == 0) {
        return ESP_OK;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create(); // Créer un lien de commande
         i2c_master_start(cmd);
         i2c_master_write_byte(cmd, (LIS2MDL_ADDR_7BITS << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
         i2c_master_write_byte(cmd, regaddr, ACK_CHECK_EN);

         i2c_master_start(cmd);
         i2c_master_write_byte(cmd, (LIS2MDL_ADDR_7BITS << 1)  | I2C_MASTER_READ, ACK_CHECK_EN);
         if (size > 1) {
             i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
         }
         i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
         i2c_master_stop(cmd);
         esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
         i2c_cmd_link_delete(cmd);
         return ret;
}

/**
 * @brief Test code to write esp-i2c-slave
 *        Master device write data to slave memory like device,
 *        the data will be stored in slave buffer.
 *        We can read them out from slave buffer.
 *
 * __________________________________________________________________________________________________________
 * | start | slave_addr + wr_bit + ack | write 1 byte (register address) + ack | write n bytes + ack  | stop |
 * --------|---------------------------|---------------------------------------|----------------------|------|
 *
 */
int32_t i2c_master_write_slave_magn(uint8_t i2c_num, uint8_t regaddr, uint8_t *data_wr, uint16_t size)
{
	 i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	     i2c_master_start(cmd); //Bit de démarrage
	     i2c_master_write_byte(cmd, (LIS2MDL_ADDR_7BITS << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
	     i2c_master_write_byte(cmd, regaddr, ACK_CHECK_EN);
	     i2c_master_write(cmd, data_wr, size, ACK_CHECK_EN);
	     i2c_master_stop(cmd);
	     esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
	     i2c_cmd_link_delete(cmd);
	     return ret;
}

/**
 * @brief i2c master initialization
 */

//**********************************************recuperer la température ***********
 void get_magnetic_task(void *args)
{
	while (1) {
	// 		if(xSemaphoreTake(xSemaphore, pdMS_TO_TICKS(300)) == pdTRUE)
	// 			 	{
	 	/* Lire les données de champ magnétique */
	 	memset(data_raw_magnetic, 0x00, 3 * sizeof(int16_t));
	 	lis2mdl_magnetic_raw_get(&dev_ctx_orientation, data_raw_magnetic);
	 	magnetic_mG[0] = lis2mdl_from_lsb_to_mgauss(data_raw_magnetic[0]);
	 	magnetic_mG[1] = lis2mdl_from_lsb_to_mgauss(data_raw_magnetic[1]);
	 	magnetic_mG[2] = lis2mdl_from_lsb_to_mgauss(data_raw_magnetic[2]);

	 	printf("magnetic_mG:%4.2f\t%4.2f\t%4.2f\r\n",magnetic_mG[0],magnetic_mG[1],magnetic_mG[2]);
	 	/* donne l'angle entre  -pi et pi*/
	    MagnetoAngle = atan2( magnetic_mG[1],magnetic_mG[0]);
	    /*l'angle en degres  entre -180 et 180*/
	    angle= (int32_t)(180 * MagnetoAngle/M_PI);
	    /* on ajoute 180 pour que l'angle soit entre 0 et 360*/
	    angle+=180;
	    /* oriontation */
		switch(angle)
				{
				case 0 ... 44:
	             boussole="N";
				printf("orientation:N\n");
				break;
				case 45 ... 68:
				boussole="NO";
				printf("orientation NO\n");
				break;
				case 69 ... 106:
				boussole="O";
				printf("orientation O\n");
				break;
				case 107 ... 140:
				boussole="SO";
				printf("orientation: SO\n");
				break;
				case 141 ... 178:
				boussole="S";
				printf("orientation: S\n");
				break;
				case 179 ... 239:
				boussole="SE";
				printf("orientation :SE\n");
				break;
				case 240 ... 308:
				boussole="E";
				printf("orientation:E\n");
				break;
				case 309 ... 360:
				boussole="NE";
				printf("orientation:NE\n");
				break;
				}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	//	xSemaphoreGive(xSemaphore);
	//	 taskYIELD();
	 		}

}

void init_magn(){

	/* This acts as the entry point of ST's STTS751 driver */


		  dev_ctx_orientation.write_reg = i2c_master_write_slave_magn;
		  dev_ctx_orientation.read_reg = i2c_master_read_slave_magn;
		  dev_ctx_orientation.i2c_number = SENSOR_BUS;
	    /* Restore default configuration */
		  lis2mdl_reset_set(&dev_ctx_orientation, PROPERTY_ENABLE);
		  	  do {
		  	    lis2mdl_reset_get(&dev_ctx_orientation, &rst);
		  	  } while (rst);

		  /* Enable Block Data Update */
		 lis2mdl_block_data_update_set(&dev_ctx_orientation, PROPERTY_ENABLE);

		 /* Set Output Data Rate */
		 lis2mdl_data_rate_set(&dev_ctx_orientation, LIS2MDL_ODR_10Hz);

		 /* Set / Reset sensor mode */
		 lis2mdl_set_rst_mode_set(&dev_ctx_orientation, LIS2MDL_SENS_OFF_CANC_EVERY_ODR);

		 /* Enable temperature compensation */
		 lis2mdl_offset_temp_comp_set(&dev_ctx_orientation, PROPERTY_ENABLE);

		 /* Set device in continuous mode */
		 lis2mdl_operating_mode_set(&dev_ctx_orientation, LIS2MDL_CONTINUOUS_MODE);

}

//++++++++ magnometre (lis2mdl)++++++++++++++/
//++++++++ magnometre (lis2mdl)++++++++++++++/
//++++++++ magnometre (lis2mdl)++++++++++++++/

//++++++++ accelerom (sm6dso)++++++++++++++/
//++++++++ accelerom (sm6dso)++++++++++++++/
//++++++++ accelerom (sm6dso)++++++++++++++/


/**
 * @brief test code to read esp-i2c-slave like a memory device
 *        We need to fill the buffer of esp slave device, then master can read them out.
 *
 * _____________________________________________________________________________________________________________________________________________
 * | start | slave_addr + wr_bit + ack | write 1 byte (register address) + ack | start | slave_addr + rd_bit + ack | read n bytes + nack | stop |
 * --------|---------------------------|---------------------------------------|-------|---------------------------|---------------------|------|
 *
 */
 int32_t i2c_master_read_slave_accel(uint8_t i2c_num, uint8_t regaddr, uint8_t *data_rd, uint16_t size)
{
	if (size == 0) {
	        return ESP_OK;
	    }
	    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	    i2c_master_start(cmd);
	    i2c_master_write_byte(cmd, (LSM6DSO_ADDR_7BITS << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
	    i2c_master_write_byte(cmd, regaddr, ACK_CHECK_EN);

	    i2c_master_start(cmd);
	    i2c_master_write_byte(cmd, (LSM6DSO_ADDR_7BITS << 1)  | I2C_MASTER_READ, ACK_CHECK_EN);
	    if (size > 1) {
	        i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
	    }
	    i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
	    i2c_master_stop(cmd);
	    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
	    i2c_cmd_link_delete(cmd);
	    return ret;
}

/**
 * @brief Test code to write esp-i2c-slave
 *        Master device write data to slave memory like device,
 *        the data will be stored in slave buffer.
 *        We can read them out from slave buffer.
 *
 * __________________________________________________________________________________________________________
 * | start | slave_addr + wr_bit + ack | write 1 byte (register address) + ack | write n bytes + ack  | stop |
 * --------|---------------------------|---------------------------------------|----------------------|------|
 *
 */
 int32_t i2c_master_write_slave_accel(uint8_t i2c_num, uint8_t regaddr, uint8_t *data_wr, uint16_t size)
{
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	    i2c_master_start(cmd);
	    i2c_master_write_byte(cmd, (LSM6DSO_ADDR_7BITS << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
	    i2c_master_write_byte(cmd, regaddr, ACK_CHECK_EN);
	    i2c_master_write(cmd, data_wr, size, ACK_CHECK_EN);
	    i2c_master_stop(cmd);
	    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
	    i2c_cmd_link_delete(cmd);
	    return ret;
}

/**
 * @brief i2c master initialization
 */

//**********************************************recuperer la température ***********
 void get_accel_task(void *args)
{
	uint8_t reg;

	 while (1) {

	//	 if(xSemaphoreTake(xSemaphore, pdMS_TO_TICKS(300)) == pdTRUE)
	//	 	 	{
		  lsm6dso_xl_flag_data_ready_get(&dev_ctx_mouvement, &reg);
		  /* Read acceleration field data */
		  	if (reg) {
		  		  /* Read acceleration field data */
		   memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
		   lsm6dso_acceleration_raw_get(&dev_ctx_mouvement, (uint8_t *)data_raw_acceleration);
		   acceleration_mg[0] =
		   lsm6dso_from_fs2_to_mg(data_raw_acceleration[0]);
		   acceleration_mg[1] =
		   lsm6dso_from_fs2_to_mg(data_raw_acceleration[1]);
		   acceleration_mg[2] =
		   lsm6dso_from_fs2_to_mg(data_raw_acceleration[2]);

		   printf("Acceleration [mg]:%4.2f\t%4.2f\t%4.2f\r\n",
		   acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
		   float length=sqrt((acceleration_mg[0]*acceleration_mg[0])+(acceleration_mg[1]*acceleration_mg[1])
		   	 		   +(acceleration_mg[2]*acceleration_mg[2]))/1000;

		   	    if (length>sqrt(2) ||length<1 )
		   	      { nbr_pas+=1;}

		   	   	   printf("Nombre de pas : %d \n", nbr_pas);
		  	}
		   lsm6dso_gy_flag_data_ready_get(&dev_ctx_mouvement, &reg);
		   vTaskDelay(1000 / portTICK_PERIOD_MS);
	//	   xSemaphoreGive(xSemaphore);
	//	  taskYIELD();

		    }
}

  void whoami_task(void *args)
 {

        printf("End of Task WHOAMI!!!!!!!!\n\n");

        /* whoami task is run only once. At the end we start get_temp_task n*/


 }
 void init_accel()
 {

     /* This acts as the entry point of ST's STTS751 driver */
     dev_ctx_mouvement.write_reg = i2c_master_write_slave_accel;
     dev_ctx_mouvement.read_reg = i2c_master_read_slave_accel;
     dev_ctx_mouvement.i2c_number = SENSOR_BUS;

     lsm6dso_device_id_get(&dev_ctx_mouvement, &whoamI);

     	/* Restore default configuration */
     	lsm6dso_reset_set(&dev_ctx_mouvement, PROPERTY_ENABLE);
     	do {
     		lsm6dso_reset_get(&dev_ctx_mouvement, &ret);
     	} while (ret);

     	/* Disable I3C interface */
     	lsm6dso_i3c_disable_set(&dev_ctx_mouvement, LSM6DSO_I3C_DISABLE);

     	/* Enable Block Data Update */
     	lsm6dso_block_data_update_set(&dev_ctx_mouvement, PROPERTY_ENABLE);

     	/* Set Output Data Rate */
     	lsm6dso_xl_data_rate_set(&dev_ctx_mouvement, LSM6DSO_XL_ODR_12Hz5);
     	lsm6dso_gy_data_rate_set(&dev_ctx_mouvement, LSM6DSO_GY_ODR_12Hz5);

     	/* Set full scale */
     	lsm6dso_xl_full_scale_set(&dev_ctx_mouvement, LSM6DSO_2g);
     	lsm6dso_gy_full_scale_set(&dev_ctx_mouvement, LSM6DSO_2000dps);

     	lsm6dso_i3c_disable_set(&dev_ctx_mouvement, LSM6DSO_I3C_DISABLE);

     	lsm6dso_xl_data_rate_set(&dev_ctx_mouvement, LSM6DSO_XL_ODR_26Hz);

 }

//++++++++ accelerom (sm6dso)++++++++++++++/
//++++++++ accelerom (sm6dso)++++++++++++++/
//++++++++ accelerom (sm6dso)++++++++++++++/
















