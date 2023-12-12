/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "dma2d.h"
#include "fatfs.h"
#include "i2c.h"
#include "ltdc.h"
#include "rtc.h"
#include "sdmmc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"
#include "stm32746g_discovery_lcd.h"
#include "lcd_log.h"
#include "stm32746g_discovery_ts.h"

/* ************************************************************************************************ */

/* LPS22HH */
#include "lps22hh_reg.h"

/* HTS221 */
#include "hts221_reg.h"

/* file3 pour l'image de la page 0 */

#include "file3.h"

/* file1 pour l'image de la page 1 */

#include "file1.h"

/* file2 pour l'image de la page 2 */

#include "file2.h"


/* pour String + Printf */

#include <string.h>
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* Bouton 1 Home */

#define BUTTON_X      BSP_LCD_GetXSize() / 2
#define BUTTON_Y      BSP_LCD_GetYSize() / 2
#define BUTTON_RADIUS 50

/* Bouton NEXT ' page1 + page2 ' */

#define BUTTON_X2      420
#define BUTTON_Y2      11
#define width 		  60
#define Height  	  250

/* Bouton Increment page 0 */

#define BUTTON_X3      10
#define BUTTON_Y3      120
#define width3 		  40
#define Height3  	  40

/* Bouton Decrement page 0 */

#define BUTTON_X4      10
#define BUTTON_Y4      180
#define width4 		  40
#define Height4  	  40

/* Bouton Switch to Second page 0 */

#define BUTTON_X5      70
#define BUTTON_Y5      120
#define width5 		  40
#define Height5  	  40

/* Bouton Switch to Minutes page 0 */

#define BUTTON_X6      70
#define BUTTON_Y6      180
#define width6 		  40
#define Height6  	  40


/* Bouton enter to Graph of temperature page 1 */

#define BUTTON_X7      24
#define BUTTON_Y7      133
#define width7 		  150
#define Height7  	  40

/* FOR GRAPH */
/* Define the maximum number of data points to display on the graph */

#define MAX_DATA_POINTS 100  // Number of data points to display on the graph
#define maxS 10000
#define maxCh 150

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* Touch screen état */

static TS_StateTypeDef *TS_State;
uint8_t ts_int = 0;

/* Cordonnees pour touch screen */

uint16_t x = 0;
uint16_t y = 0;

/* Initialiser l'interface a page 0 au début */

uint8_t page=0;
uint8_t i=0;

/* Ecran On == 0 */

uint8_t DisplayState = 0;
uint8_t etat=0;

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;


/* LPS22HH */
static uint32_t data_raw_pressure;
static int16_t data_raw_temperature;
static float pressure_hPa;
static float temperature_degC;
static uint8_t whoamI_lps22hh, rst;
static uint8_t tx_buffer_lps22hh[1000];
static uint8_t tx_buffer_lps22hh2[1000];

/* HTS221 */
static int16_t data_raw_humidity;
static float humidity_perc;
static uint8_t whoamI_hts221;
static uint8_t tx_buffer_hts221[1000];

/* Buffers of sensors (à chaque acquisition en stock les valeurs sur les tableaux) */

float temperature_data[MAX_DATA_POINTS];
float pressure_data[MAX_DATA_POINTS];
float humidity_data[MAX_DATA_POINTS];

char tab[maxCh];

/* PARTIE GRAPH */

int data_index = 0;  // in order to track of the current position in the array

/* PARTIE RTC */

char time[30];
char date[30];

RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

uint32_t previousSeconds1 = 0;
uint32_t previousSeconds2 = 0;
uint32_t previousSeconds3 = 0;
uint32_t previousSecondsX = 0;

uint32_t previousMinutes =  0;
uint32_t previousMinutes2 = 0;
uint32_t previousMinutes3 = 0;
uint32_t previousMinutes4 = 0;


char buff[130];  // Chaîne pour stocker l'heure formatée en secondes
char buff2[130];  // Chaîne pour stocker l'heure formatée en minutes
uint8_t q=0;
/* Acquisition choisi par l'utilisateur */

uint8_t acquisition = 1;

/* pour voir le temps d'acquisition choisi par l'utilisateur*/

char acq[maxCh];

/* le nombre d'itération pour stocker les resultats des capteurs sur le µSD*/

uint8_t ack=0;

/* variable pour savoir si on est en mode minute " k=0 " ou mode secondes "k=1" */

uint8_t k = 0;

/* Partie capteur de pluie */

volatile uint32_t impulseCountP = 0;
volatile uint8_t pluieDetected = 0;
float quantPluie=0;

static uint8_t tab_pluie[1000];

/* Partie capteur de direction du vent */

uint16_t val_analog =0;
float val_tension = 0;
char* direction;
static uint8_t tab_direction[1000];

/* Partie capteur de vitesse du vent */

volatile uint8_t vitesseDetected =0;
float vitesse = 0;
float vitesse_total = 0;
volatile uint32_t impulseCount = 0;
float tab_vitesse[1000];

/* Partie de stockage */

	FRESULT res;
	uint32_t byteswritten, bytesread;
	uint8_t wtextT[] = "\n****** Temperature ******\n";
	uint8_t wtextH[] = "****** Humidite ******\n";
	uint8_t wtextP[] = "****** Pluie ******\n";
	uint8_t wtextPr[] = "****** Pression ******\n";
	uint8_t wtextV[] = "****** Vitesse ******\n";
	uint8_t wtextD[] = "****** Direction wind ******\n";

	uint8_t workBuffer[_MAX_SS];

/* Buffers of sensors ( Convertir les valeurs des capteurs en chaine de caractères ) */

float tab_temp[maxS];
float tab_humid[maxS];
float tab_pres[maxS];
float tab_run[maxS];
float tab_wind[maxS];

uint32_t s=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void interface0();
void interface1();
void interfaceGRAPH();
void fonc_pour_synchroniser_capteurs();
char* direction_wind();
void calcul_vitesse();

/* HTS221 */

static int32_t platform_write_hts221(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
static int32_t platform_read_hts221(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);

/* LPS22HH */

static int32_t platform_write_lps22hh(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
static int32_t platform_read_lps22hh(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);

typedef struct {
  float x0;
  float y0;
  float x1;
  float y1;
} lin_t;

float linear_interpolation(lin_t *lin, int16_t x)
{
  return ((lin->y1 - lin->y0) * x + ((lin->x1 * lin->y0) -
                                     (lin->x0 * lin->y1)))
         / (lin->x1 - lin->x0);
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* Bouton 1 Home */

int isPointInsideButton1(uint16_t x, uint16_t y) {
    int dx = x - BUTTON_X;
    int dy = y - BUTTON_Y;
    return (dx * dx + dy * dy) <= (BUTTON_RADIUS * BUTTON_RADIUS);
}
/* Bouton NEXT ' page1 + page2 ' */

int isPointInsideButton2(uint16_t x, uint16_t y) {
	if (x >= BUTTON_X2 && x <= (BUTTON_X2 + width) && y >= BUTTON_Y2 && y <= (BUTTON_Y2 + Height))
		return 1;
	 else
		return 0;

}
/* Bouton Increment page 0 */

int isPointInsideButton3(uint16_t x, uint16_t y) {
	if (x >= BUTTON_X3 && x <= (BUTTON_X3 + width3) && y >= BUTTON_Y3 && y <= (BUTTON_Y3 + Height3))
		return 1;
	 else
		return 0;

}

/* Bouton Decrement page 0 */

int isPointInsideButton4(uint16_t x, uint16_t y) {
	if (x >= BUTTON_X4 && x <= (BUTTON_X4 + width4) && y >= BUTTON_Y4 && y <= (BUTTON_Y4 + Height4))
		return 1;
	 else
		return 0;

}
/* Bouton Switch to Second page 0 */

int isPointInsideButton5(uint16_t x, uint16_t y) {
	if (x >= BUTTON_X5 && x <= (BUTTON_X5 + width5) && y >= BUTTON_Y5 && y <= (BUTTON_Y5 + Height5))
		return 1;
	 else
		return 0;

}

/* Bouton Switch to Minutes page 0 */

int isPointInsideButton6(uint16_t x, uint16_t y) {
	if (x >= BUTTON_X6 && x <= (BUTTON_X6 + width6) && y >= BUTTON_Y6 && y <= (BUTTON_Y6 + Height6))
		return 1;
	 else
		return 0;

}

/* Bouton enter to Graph of temperature page 1 */

int isPointInsideButton7(uint16_t x, uint16_t y) {
	if (x >= BUTTON_X7 && x <= (BUTTON_X7 + width7) && y >= BUTTON_Y7 && y <= (BUTTON_Y7 + Height7))
		return 1;
	 else
		return 0;

}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SDMMC1_SD_Init();
  MX_USART1_UART_Init();
  MX_FATFS_Init();
  MX_I2C1_Init();
  MX_ADC3_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_LTDC_Init();
  MX_RTC_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  /* Initialiser les timers 1 en mode capture (avec Interruption) et timer 2 en mode interruption */

  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
  HAL_TIM_Base_Start_IT(&htim2);

  //********************************************** BSP *****************************************

  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SetLayerVisible(LTDC_ACTIVE_LAYER, ENABLE);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
  BSP_TS_ITConfig();
  BSP_TS_ITClear();
  LCD_LOG_Init();


  BSP_TS_ResetTouchData(TS_State);
  BSP_LCD_SetFont(&Font12);

  /* Ajouter l'image pour la page 0 */

  BSP_LCD_DrawBitmap(0, 0, (uint8_t *)file3);

  /* Afficher le texte */

  BSP_LCD_DisplayStringAt(15, 83,(uint8_t *) " CHoose your time acquisition ", CENTER_MODE);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /* Initialiser le temps */

	  HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

	  /* Convertir la date et le temps en chaine de caracteres */

	  sprintf(buff2, "%02d-%02d-%02d   \t  \t  \t  \t         %02d : %02d : %02d",sDate.Date,sDate.Month,sDate.Year, sTime.Hours,sTime.Minutes,sTime.Seconds);

	  /* Convertir le temps en secondes et en minutes */

	  uint32_t currentSeconds = sTime.Hours * 3600 + sTime.Minutes * 60 + sTime.Seconds;
	  uint32_t currentMinutes = sTime.Hours * 60 + sTime.Minutes;

	  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	  /* Si la pluie est détecté */

	  if (pluieDetected == 1) {
			impulseCountP++;

			pluieDetected = 0;
	  }

	  /* Si la vitesse est détecté */

	  if (vitesseDetected == 1) {

				impulseCount++;
			  vitesseDetected = 0;
		}

	  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	  /* Chaque 30 secondes en etteint l'ecran  */

	  	  if (DisplayState==0 && (currentSeconds - previousSecondsX) >= 1) {
	  			q++;
	  			if(q==30){
	  				BSP_LCD_DisplayOff();
	  				DisplayState=1;
	  				q=0;
	  			}

	  			previousSecondsX = currentSeconds; // Mettre à jour le temps précédent
	  	  }

	  /* Chaque minute en calcule la quantité de pluie  */

	  if ((currentMinutes - previousMinutes2) >= 1) {
			quantPluie = impulseCountP * 0.279;

			impulseCountP=0;

			previousMinutes2 = currentMinutes; // Mettre à jour le temps précédent
	  }

	  /* On calcule la vitesse dans une seconde en km/h */

	  if ((currentSeconds - previousSeconds3) >= 1) {
			  vitesse+= impulseCount * 2.4;
			  impulseCount=0;

		  previousSeconds3 = currentSeconds; // Mettre à jour le temps précédent
	  }


	  /* On stock chaque 60 minute en réel mais la en test en stock chaque 4 minutes */

	  if ((currentMinutes - previousMinutes4) >= 4) {

	    BSP_LCD_Clear(LCD_COLOR_WHITE);
		  sprintf(buff2, " STOCKING ! ! ! wait for it ");
	  	  LCD_LOG_SetHeader((uint8_t *) buff2);


		if(k==0)
			ack=  4*60/acquisition;
		else
			ack=  4 / acquisition;

		/*##-2- Register the file system object to the FatFs module ##############*/
		 if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) != FR_OK)
		 {
		   /* FatFs Initialization Error */
		   Error_Handler();
		 }
		 else
		 {
		   /*##-3- Create a FAT file system (format) on the logical drive #########*/
		   /* WARNING: Formatting the uSD card will delete all content on the device */
		   if(f_mkfs((TCHAR const*)SDPath, FM_ANY, 0, workBuffer, sizeof(workBuffer)) != FR_OK)
		   {
			 /* FatFs Format Error */
			 Error_Handler();
		   }
		   else
		   {
			 /*##-4- Create and Open a new text file object with write access #####*/
			 if(f_open(&SDFile, "Stck.CSV", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
			 {
			   /* 'STM32.TXT' file Open for write Error */
			   Error_Handler();
			 }
			 else
			 {
				 /* stocker la date et l'heure */

				 res = f_write(&SDFile, buff2, sizeof(buff2), (void *)&byteswritten);

				 /* stocker la chaine de caractères " température " */

				 res = f_write(&SDFile, wtextT, sizeof(wtextT), (void *)&byteswritten);

				 /* Convertir les valeurs de température et les stocker dans la carte µSD */

				 for(int j=0;j<ack;j++){
					 sprintf(tab, "%.2f\n", tab_temp[j]);
					 res = f_write(&SDFile, tab, strlen(tab), (void *)&byteswritten);

				 }

				 /* stocker la chaine de caractères " Humidité " */

				 res = f_write(&SDFile, wtextH, sizeof(wtextH), (void *)&byteswritten);

				 /* Convertir les valeurs de l'humidité et les stocker dans la carte µSD */

				for(int j=0;j<ack;j++){
					 sprintf(tab, "%.2f\n", tab_humid[j]);
					 res = f_write(&SDFile, tab, strlen(tab), (void *)&byteswritten);
				 }

				/* stocker la chaine de caractères " Pression " */

				res = f_write(&SDFile, wtextPr, sizeof(wtextPr), (void *)&byteswritten);

				/* Convertir les valeurs de Pression et les stocker dans la carte µSD */

				for(int j=0;j<ack;j++){
					 sprintf(tab, "%.2f\n", tab_pres[j]);
					 res = f_write(&SDFile, tab, strlen(tab), (void *)&byteswritten);
				 }

				/* stocker la chaine de caractères " Vitesse " */

				res = f_write(&SDFile, wtextV, sizeof(wtextV), (void *)&byteswritten);

				/* Convertir les valeurs de Vitesse et les stocker dans la carte µSD */

				for(int j=0;j<ack;j++){
					 sprintf(tab, "%.2f\n", tab_wind[j]);
					 res = f_write(&SDFile, tab, strlen(tab), (void *)&byteswritten);
				 }

				/* stocker la chaine de caractères " Pluie " */

				res = f_write(&SDFile, wtextP, sizeof(wtextP), (void *)&byteswritten);

				/* Convertir les valeurs de Pluie et les stocker dans la carte µSD */

				for(int j=0;j<ack;j++){
					 sprintf(tab, "%.2f\n", tab_run[j]);
					 res = f_write(&SDFile, tab, strlen(tab), (void *)&byteswritten);
				}

			   if((byteswritten == 0) || (res != FR_OK))
			   {
				 /* 'STM32.TXT' file Write or EOF Error */
				 Error_Handler();
			   }
			   else
			   {
				 /*##-6- Close the open text file #################################*/
				 f_close(&SDFile);

			   }
			 }
		   }
		 }

	   /*##-11- Unlink the micro SD disk I/O driver ###############################*/
	   FATFS_UnLinkDriver(SDPath);

	   /* Réinitialiser à 0 à la fin de stockage */

	   s=0;

	   /* Revenir à une des pages aprés que le sotckage termine */

	   if(page==0)
		   BSP_LCD_DrawBitmap(0, 0, (uint8_t *)file3);
	   else if(page==1)
		   BSP_LCD_DrawBitmap(0, 0, (uint8_t *)file2);
	   else if(page==2)
		   BSP_LCD_DrawBitmap(0, 0, (uint8_t *)file1);
	   else{}



		previousMinutes4 = currentMinutes; // Mettre à jour le temps précédent
	}


	  /* Si l'utilisateur a choisi le  mode Secondes */

	  if(k==0) {
		  if ((currentSeconds - previousSeconds2) >= acquisition) {
			  fonc_pour_synchroniser_capteurs();
			  direction_wind();
			  calcul_vitesse();
			  tab_temp[s]= temperature_degC;
			  tab_humid[s]= humidity_perc;
			  tab_pres[s]= pressure_hPa;
			  tab_wind[s]= vitesse_total;
			  tab_run[s]= quantPluie;

			  s++;

			  HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_10);
			  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_9, 0);
			  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_11, 1);

			  previousSeconds2 = currentSeconds; // Mettre à jour le temps précédent
		  }

	  /* Si l'utilisateur a choisi le mode Minutes */

	  }else {
		  if ((currentMinutes - previousMinutes) >= acquisition) {

			  fonc_pour_synchroniser_capteurs();
			  direction_wind();
			  calcul_vitesse();

			  tab_temp[s]= temperature_degC;
			  tab_humid[s]= humidity_perc;
			  tab_pres[s]= pressure_hPa;
			  tab_run[s]= quantPluie;
			  tab_wind[s]= vitesse_total;
			  s++;

			  HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_10);
			  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_9, 0);
			  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_11, 1);

			  previousMinutes = currentMinutes; // Mettre à jour le temps précédent
		  }
	  }

//***************************************************   PAGES   *****************************************************

	  if(page==0){
		  if ((currentSeconds - previousSeconds1) >= 1) {

			  	  /*  Afficher le Header plus l'heure et la date exacte  */

			  	  LCD_LOG_SetHeader((uint8_t *) buff2);
				  previousSeconds1 = currentSeconds; // Mettre à jour le temps précédent
		  }

		  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_9, 0);
		  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_11, 1);
		  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10, 0);


	  }else if (page == 1) {

		  	  	  	   /* Afficher les valeurs des 3 capteurs Humidité-Pression-Température sur la page 1 */

					   sprintf((char *)tx_buffer_lps22hh, "Temperature is %.2fC\r\n", temperature_degC);
					   BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // Couleur du texte
					   BSP_LCD_DisplayStringAt(28, 133, (uint8_t *)tx_buffer_lps22hh, LEFT_MODE);

					   sprintf((char *)tx_buffer_lps22hh2, "Pressure is %.2f hPa\r\n", pressure_hPa);
					   BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // Couleur du texte
					   BSP_LCD_DisplayStringAt(10, 230, (uint8_t *)tx_buffer_lps22hh2, CENTER_MODE);

					   sprintf((char *)tx_buffer_hts221, "Humidity is %.2f\r\n", humidity_perc);
					   BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // Couleur du texte
					   BSP_LCD_DisplayStringAt(89, 133, (uint8_t *)tx_buffer_hts221, RIGHT_MODE);

					  HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_9);
					  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_11, 0);
					  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10, 0);
		}
		else if (page == 2) {

						/* Afficher les valeurs des 3 capteurs Pluie-vitesse-direction sur la page 2 */

						sprintf((char *)tab_pluie, "Rain is %.2f mm\r\n", quantPluie);
						BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // Couleur du texte
						BSP_LCD_DisplayStringAt(55, 133, (uint8_t *)tab_pluie, LEFT_MODE);

						sprintf((char *)tab_vitesse, "Wind is %.2f km/h\r\n", vitesse_total);
						BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // Couleur du texte
						BSP_LCD_DisplayStringAt(22, 230, (uint8_t *)tab_vitesse, CENTER_MODE);

						sprintf((char *)tab_direction, " %s\r\n", direction);
						BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // Couleur du texte
						BSP_LCD_DisplayStringAt(130, 133, (uint8_t *)tab_direction, RIGHT_MODE);


						HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_9);
						HAL_GPIO_WritePin(GPIOH, GPIO_PIN_11, 0);
						HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10, 0);
		}
		else if (page == 3){

						/* Synchronisation des capteurs + allumage de la led */

						fonc_pour_synchroniser_capteurs();

					  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_9, 0);
					  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_11, 1);
					  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10, 0);

					/* Acquisition et dessinage d'une courbe chaque une seconde donc courbe en temps réel */

					if ((currentSeconds - previousSeconds1) >= 1) {

						temperature_data[data_index] = temperature_degC;

						  data_index = (data_index + 1) % MAX_DATA_POINTS;

						  BSP_LCD_Clear(LCD_COLOR_BLACK);
						  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
						  BSP_LCD_FillRect(70, 50, 320, 200);

						  BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
						  BSP_LCD_DrawVLine(70, 50, 200);
						  BSP_LCD_DrawHLine(70, 250, 350);

						  float scale_factor1 = 121 / 40.0;
						  int i;

						  /* Draw the temperature points (par point) on the graph */

						  for ( i = 0; i < data_index && i < MAX_DATA_POINTS; i++) {

							  int x1 = 80 + i * (320 / MAX_DATA_POINTS);
							  int y1 = 50 + 200 - (int)(temperature_data[i] * scale_factor1);

							  /* Draw a point on the LCD at (x1, y1) */

							  BSP_LCD_DrawPixel(x1, y1, LCD_COLOR_GREEN);
						  }

						  previousSeconds1 = currentSeconds; // Mettre à jour le temps précédent
					}

		}

	  /* Si l'utilisateur a touché l'écran */

	   if (ts_int == 1) {
		   q=0;
		   /* Si le click vient de la page 0 */

		   if(page==0 && (isPointInsideButton3(x, y) || isPointInsideButton4(x, y) || isPointInsideButton5(x, y) || isPointInsideButton6(x, y)) ){

			   	   /* Si le click vient de coté ou en incrémente */

				   if (isPointInsideButton3(x, y)) {
						 if (acquisition < 60) {
							 acquisition++;

						 }

						   /* Affichage de la valeur d'acquisition choisi par l'utilisateur */

						   sprintf((char *)acq, " %d \r\n", acquisition);
						   BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // Couleur du texte
						   BSP_LCD_DisplayStringAt(37, 170, (uint8_t *)acq, RIGHT_MODE);
					 }

				     /* Si le click vient de coté ou en décrémente */

					 else if (isPointInsideButton4(x, y)) {

						 if (acquisition > 1) {
							 acquisition--;
						 }
							 sprintf((char *)acq, " %d \r\n", acquisition);
							BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // Couleur du texte
							BSP_LCD_DisplayStringAt(34, 170, (uint8_t *)acq, RIGHT_MODE);

					 }

				     /* Si le click vient de coté ou en choisi le mode SECONDEs */

					 else if (isPointInsideButton5(x, y)) {
						   BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // Couleur du texte
						   BSP_LCD_DisplayStringAt(03, 209, (uint8_t *)" SECONDE(S) MODE ", RIGHT_MODE);
						   k=0;
					 }

				     /* Si le click vient de coté ou en choisi le mode MINUTEs */

					 else if (isPointInsideButton6(x, y)) {
						   BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // Couleur du texte
						   BSP_LCD_DisplayStringAt(03, 209, (uint8_t *)" MINUTE(S) MODE ", RIGHT_MODE);
						   k=1;
					 }
		   }

		   /* Si le click vient de bouton HOME */

		   else if(page==0 && isPointInsideButton1(x, y))
			   interface0();

		   /* Si le click vient de la page 1 et bouton NEXT */

		   else if(page == 1 && isPointInsideButton2(x, y))
			   interface1();

		   /* Si le click vient de la page 2 et bouton NEXT */

		   else if(page == 2 && isPointInsideButton2(x, y))
			   interface0();

		   /* Si le click vient de la page 1 et bouton TEMPERATURE */

		   else if(page == 1 && isPointInsideButton7(x, y))
			   interfaceGRAPH();

		   /* Si le click vient de la page 3 et bouton CENTRAL */

		   else if(page==3 && isPointInsideButton1(x, y))
			   interface0();

		   HAL_Delay(80);
		   ts_int=0;
	   }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* Fonction pour synchroniser les 3 capteurs d'himidité de température et de pression */

void fonc_pour_synchroniser_capteurs(){
	//********************************************** CAPTEURS *****************************************************
	//***********************************  " temp , humid , press "  **************************************

		/* LPS22HH */

		/* Initialize mems driver interface */

		  stmdev_ctx_t dev_ctx_lps22hh;
		  dev_ctx_lps22hh.write_reg = platform_write_lps22hh;
		  dev_ctx_lps22hh.read_reg = platform_read_lps22hh;
		  dev_ctx_lps22hh.handle = &hi2c1;

		  /* HTS221 */

		  /* Initialize mems driver interface */

		  stmdev_ctx_t dev_ctx_hts221;
		  dev_ctx_hts221.write_reg = platform_write_hts221;
		  dev_ctx_hts221.read_reg = platform_read_hts221;
		  dev_ctx_hts221.handle = &hi2c1;

	  /* LPS22HH ******************************************************************************************/

				  /* Check device ID */
	  	  	  	  whoamI_lps22hh = 0;
				  lps22hh_device_id_get(&dev_ctx_lps22hh, &whoamI_lps22hh);
				  if ( whoamI_lps22hh != LPS22HH_ID ){/*manage here device not found */
					while (1);
				  }
				  /* Restore default configuration */
				  lps22hh_reset_set(&dev_ctx_lps22hh, PROPERTY_ENABLE);

				  do {
					lps22hh_reset_get(&dev_ctx_lps22hh, &rst);
				  } while (rst);

				  /* Enable Block Data Update */
				  lps22hh_block_data_update_set(&dev_ctx_lps22hh, PROPERTY_ENABLE);
				  /* Set Output Data Rate */
				  lps22hh_data_rate_set(&dev_ctx_lps22hh, LPS22HH_10_Hz_LOW_NOISE);


	  /* HTS221 *******************************************************************************************/

				  /* Check device ID */
				  whoamI_hts221 = 0;
				  hts221_device_id_get(&dev_ctx_hts221, &whoamI_hts221);
				  if ( whoamI_hts221 != HTS221_ID ){
					while (1); /*manage here device not found */
				  }

				  /* Read humidity calibration coefficient */
				  lin_t lin_hum;
				  hts221_hum_adc_point_0_get(&dev_ctx_hts221, &lin_hum.x0);
				  hts221_hum_rh_point_0_get(&dev_ctx_hts221, &lin_hum.y0);
				  hts221_hum_adc_point_1_get(&dev_ctx_hts221, &lin_hum.x1);
				  hts221_hum_rh_point_1_get(&dev_ctx_hts221, &lin_hum.y1);
				  /* Enable Block Data Update */
				  hts221_block_data_update_set(&dev_ctx_hts221, PROPERTY_ENABLE);
				  /* Set Output Data Rate */
				  hts221_data_rate_set(&dev_ctx_hts221, HTS221_ODR_1Hz);
				  /* Device power on */
				  hts221_power_on_set(&dev_ctx_hts221, PROPERTY_ENABLE);

	  //--------------------------------------- PARTIE SYNCHRO -------------------------------------------------------------------
	  //--------------------------------------------------------------------------------------------------------------------------


		     /* LPS22HH ************************************************************************************************************/

			  /************** Read temperature data ***********************/

			  memset(&data_raw_temperature, 0x00, sizeof(int16_t));
			  lps22hh_temperature_raw_get(&dev_ctx_lps22hh, &data_raw_temperature);
			  temperature_degC = lps22hh_from_lsb_to_celsius(data_raw_temperature );

			  /************** Read pressure data ****************************/

			  memset(&data_raw_pressure, 0x00, sizeof(uint32_t));
			  lps22hh_pressure_raw_get(&dev_ctx_lps22hh, &data_raw_pressure);
			  pressure_hPa = lps22hh_from_lsb_to_hpa( data_raw_pressure);


		    /* HTS221 *************************************************************************************************************/

			/****************** Read humidity data ***************/

			  hts221_reg_t reg;
			  hts221_status_get(&dev_ctx_hts221, &reg.status_reg);
			  if (reg.status_reg.h_da) {
				  memset(&data_raw_humidity, 0x00, sizeof(int16_t));
				  hts221_humidity_raw_get(&dev_ctx_hts221, &data_raw_humidity);
				  humidity_perc = linear_interpolation(&lin_hum, data_raw_humidity);

				  if (humidity_perc < 0) {
				  humidity_perc = 0;
				  }
				  if (humidity_perc > 100) {
				  humidity_perc = 100;
				  }
			  }
}

/* Switcher entre les interfaces et afficher une image a chaque interface */

void interface0(){
	BSP_LCD_DrawBitmap(0, 0, (uint8_t *)file2);

	page=1;
}

void interface1(){
	BSP_LCD_DrawBitmap(0, 0, (uint8_t *)file1);

	page=2;

}

void interfaceGRAPH(){

	page=3;

}

/* Fonction d'interruption contients deux interruption soit de la touch screen soit de bouton pour allumer ou eteindre LCD */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == USER_BTN_Pin){
	        BSP_LCD_DisplayOn();
	        DisplayState=0;
	}





	if (GPIO_Pin == TS_INT_Pin ) {
		BSP_TS_GetState(TS_State);
		x = TS_State->touchX[0];
		y = TS_State->touchY[0];

		ts_int = 1;
	}
}

//**************************************************** CAPTEURS << TEMP + HUMID >> ***************************************
//************************************************************************************************************************

/* HTS221 */

static int32_t platform_write_hts221(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
	/* Write multiple command */
	  reg |= 0x80;
	  HAL_I2C_Mem_Write(handle, HTS221_I2C_ADDRESS, reg,
	                    I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);
  return 0;
}

static int32_t platform_read_hts221(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
	 /* Read multiple command */
	  reg |= 0x80;
	  HAL_I2C_Mem_Read(handle, HTS221_I2C_ADDRESS, reg,
	                   I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
  return 0;
}


/* LPS22HH */

static int32_t platform_write_lps22hh(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len)
{

  HAL_I2C_Mem_Write(handle, LPS22HH_I2C_ADD_H, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);
  return 0;
}

static int32_t platform_read_lps22hh(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{

  HAL_I2C_Mem_Read(handle, LPS22HH_I2C_ADD_H, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);

  return 0;
}

/* Fonction d'interruption pour le TIMER 1 qui prend en charche le capteur de vitesse (mode capture)  */

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {

		vitesseDetected = 1;
	}
}

/* Fonction d'interruption pour le TIMER 2 qui prend en charge le capteur de pluie  */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	if(htim->Instance == TIM2) {

		pluieDetected=1;
	}
}

/* Fonction pour séléctioner la direction du vent  */

char* direction_wind() {


	  HAL_ADC_Start(&hadc3);
	  HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY);
	  val_analog = HAL_ADC_GetValue(&hadc3);
	  val_tension = val_analog * 3.3 / 4095;

	  if(val_tension > 3.075 && val_tension < 3.15)
		  direction = "west";

	  else if(val_tension > 2.885 && val_tension < 3.075)
	  		  direction = "North-west";

	  else if(val_tension > 2.571 && val_tension < 2.885)
	  		  direction = "North";

	  else if(val_tension > 2.165 && val_tension < 2.571)
	  		  direction = "South West";

	  else if(val_tension > 1.7 && val_tension < 2.165)
	  		  direction = "North east";

	  else if(val_tension > 1.295 && val_tension < 1.7)
	  		  direction = "South";

	  else if(val_tension > 1.01 && val_tension < 1.295)
	  		  direction = "South EAst";

	  else if(val_tension > 0.835 && val_tension < 1.01)
	  		  direction = "East";

	  return direction;
}

/* Fonction pour calculer la vitesse total du vent en prenons en considération la vitesse du vent dans une seconde */

void calcul_vitesse(){

	/* Si le temps d'acquision est en secondes */

	if(k==0){
		vitesse_total=vitesse/acquisition;
		vitesse=0;

	/* Si le temps d'acquision est en Minutes */

	}else{
		vitesse_total=vitesse/(acquisition*60);
		vitesse=0;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
