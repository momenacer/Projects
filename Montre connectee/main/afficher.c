/* File    : 17-2_lvgl_ME_task.c
 * date   : 11/03/2024
 * author : NR
 * Status : OK
 *
 * Actions :
 *           - When the BootBtn is pressed  (detected from GPIO IRQ)
 *              + the task "blink_Led" is resumed or suspended
 *              + the widget (text block) of page 0 is modified
 *               (Hello World -> Cornebidouille <-> Tarabistouille)
 *
 *           - Each 2 seconds (timer IRq), the current page to
 *           		   display is changed (detected from Timer IRQ)
 *           	                page 0-> 1 -> 2 -> 0 ...
 *
 *           - The display is refreshed every 500 ms using a Timer
 *                interrupt also
 *
 * Comments : provide the skeleton of any real-time application with
 *            GUI (lvgl here) : interaction by interrupts (GPIO,
 *            timers, ...) and a single call to refresh the HMI (so
 *            lv_task_handler() in LVGL case).
 *
 *            Updating the widgets in the corresponding tasks/fct
 *            allow to obtain a more dynamic interface. The required
 *            time for displaying the page is fixed and short.
*/
#include <stdio.h>
//#include <string.h>
#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
#include "driver/gpio.h"
//#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_timer.h"
//#include "esp_system.h"
#include "sdkconfig.h"

//******************************************************************
//**************************      1. USER INCLUDES     *************
//******************************************************************
/* Additional peripherals and tools */
#include "driver/gptimer.h"  // replace driver/timer.h (since 2023)
//#include "esp_log.h"		//  for debug fct :ESP_LOGI/W/E/D/V( )
#include "capteurs.h"
#include "NTP.h"
#include "ble_init.h"

/* Littlevgl specific */
#include "lvgl.h"
#include "lvgl_helpers.h"

//******************************************************************
//**************************      2. DEFINES      ******************
//******************************************************************
#define NB_MAX_SCREEN 3		// number of different pages for the HMI

#define LV_TICK_PERIOD_MS 1

// Used GPIO port
#define BootBtn 0 // Boot Button :Take Care : same GPIO port than
				  //     the Green Led

#define RedLed 0
#define GreenLed 2
#define BlueLed 4	// To select for applications


// TEMPERATURE
// TEMPERATURE
// TEMPERATURE


void affichage_temperature();
TaskHandle_t 	xTemp= NULL;
extern float temperature_degC;

// TEMPERATURE
// TEMPERATURE



// MAGNETIC
// MAGNETIC

void affichage_orion();
TaskHandle_t 	xAcceler= NULL;
extern char *boussole;

// MAGNETIC
// MAGNETIC

// ACCEL
// ACCEL

void affichage_accel();
TaskHandle_t 	xMagnometre= NULL;
extern uint16_t nbr_pas;

float Distance;
float Calories;

// ACCEL
// ACCEL

// TIME
// TIME

extern struct tm timeinfo;
void affichage_Time();
void calend();
extern int mois, jour, annee;

// TIME
// TIME


//******************************************************************
//***************************    3.GLOBAL VARIABLES    *************
//******************************************************************
TaskHandle_t  blink_task_Handle    = NULL;
TaskHandle_t  state_machine_Handle = NULL;
TaskHandle_t  timHandle			   = NULL;

SemaphoreHandle_t Btn_Semaphore        = NULL; // IRQ Button
SemaphoreHandle_t Acq_Timer_Semaphore  = NULL; // IRQ Timer Acq
SemaphoreHandle_t Aff_update_Semaphore = NULL; // IRQ Timer Display

QueueSetHandle_t Semaphore_QueueSet = NULL;  // The "queue set"  is
		// merging   the different semaphores for the state machine

// LVGL widgets management
lv_obj_t *screen[NB_MAX_SCREEN]; // table of the 3 LVGL screens

lv_obj_t *scr1_label1,			 // Text Object Label
		 *scr2_label1,			 // Text Object Label
		 *scr3_label1,			 // Text Object Label
		 *scr4_label1,
		 *scr5_label1,
		 *scr6_label1,
		 *scr7_label1,
		 *scr8_label1;

lv_obj_t *temp,			 // Text Object Label
		 *dist,			 // Text Object Label
		 *nbrePas,			 // Text Object Label
		 *direc,
		 *calor;


lv_color_t blue = LV_COLOR_MAKE(3, 72, 73);

int Page = 0;


//******************************************************************
//***************************    4. IRQ Functions     **************
//******************************************************************
// All the interrupt Routines are sending a binary semaphore
// The semaphores are merged in a Queue for a single wait function
// in the state-machine (the simpler way to do it).
// So each routine uses is own semaphores to allow the detection
// of the sending routine.

//==================================================================
// gpio_IRQ_handler() : wake-up after BootButton was pressed
//==================================================================
static void IRAM_ATTR gpio_IRQ_handler(void *args)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	// The return BootBtn will be (args = 0) if the button is pushed
	xSemaphoreGiveFromISR( Btn_Semaphore, &xHigherPriorityTaskWoken);
}

//==================================================================
// Acq_timer_IRQ_handler() : wake-up after 2s (Timer interrupt)
//==================================================================
static bool IRAM_ATTR Acq_timer_IRQ_handler(gptimer_handle_t timer,
		    const gptimer_alarm_event_data_t *edata, void *user_ctx)
{
	// SM task has a higher priority, so no necessity to wake up it
	// with an higher priority
	static BaseType_t  xHigherPriorityTaskWoken = pdFALSE;

	xSemaphoreGiveFromISR( Acq_Timer_Semaphore,
			               &xHigherPriorityTaskWoken );
	return true;
}

//==================================================================
// Display_timer_IRQ_handler() : wake-up after 500ms (Timer IRQ)
//==================================================================
static bool IRAM_ATTR Display_timer_IRQ_handler(gptimer_handle_t timer,
		    const gptimer_alarm_event_data_t *edata, void *user_ctx)
{
	// SM task has a higher priority, so no necessity to wake up it
	// with an higher priority
	static BaseType_t  xHigherPriorityTaskWoken = pdFALSE;

	xSemaphoreGiveFromISR( Aff_update_Semaphore,
						   &xHigherPriorityTaskWoken );
	return true;
}

//==================================================================
// lv_tick_task() : wake-up after 1ms (Timer interrupt)
//==================================================================
static void lv_tick_task(void *arg)
{
    lv_tick_inc(LV_TICK_PERIOD_MS);
}

//******************************************************************
//***************************************    5. Functions     ******
//******************************************************************
//==================================================================
// Init_Acq_Timer( period in µs ): configure and install the IRQ
// Timer for Acquisition (change msg)
//==================================================================
// Must be runned after running the tasks, who are waiting the IRQ

void Init_Acq_Timer(uint64_t NR_delay)
{
	gptimer_handle_t NR_timer_handle = NULL;  // handle of the timer

	//..............................................................
	// Part 1 : configure the data structure
	//..............................................................
	gptimer_config_t NR_timer_config = {	// timer config struct
	    .clk_src = GPTIMER_CLK_SRC_DEFAULT,
	    .direction = GPTIMER_COUNT_UP,
	    .resolution_hz = 1000 * 1000, //Timer frequency => Fe =1MHz,
									  // so 1 tick = 1micro second
	};
	// create the new timer
	ESP_ERROR_CHECK(gptimer_new_timer(&NR_timer_config,
			                          &NR_timer_handle));

	//..............................................................
	// Part 2 : configure the alarm action
	//..............................................................
	gptimer_alarm_config_t NR_alarm_config ={
			.alarm_count = NR_delay,// alarm every NR_delay * 1 ms
			.reload_count = 0,      // for reload: restart to 0
			.flags.auto_reload_on_alarm  = true,
	};
	ESP_ERROR_CHECK(gptimer_set_alarm_action(NR_timer_handle,
			        &NR_alarm_config));

	//..............................................................
	// Part 3: configure the callback (interruption)
	//..............................................................
	gptimer_event_callbacks_t NR_cbs_config = {
	        .on_alarm = Acq_timer_IRQ_handler, //call the right fct!
	    };
	    ESP_ERROR_CHECK(gptimer_register_event_callbacks(NR_timer_handle,
	    		        &NR_cbs_config, NULL));

	//..............................................................
	// Part 4 : Start the timer
	//..............................................................
	ESP_ERROR_CHECK(gptimer_enable(NR_timer_handle));
	ESP_ERROR_CHECK(gptimer_start(NR_timer_handle));

} // end of void NR_Init_timer()
//==================================================================

//==================================================================
// Init_Display_Timer( period in µs ):
//          configure and install the IRQ Timer for display update
//			copy/paste from the previous function, could be improved
//==================================================================
// Must be runned after running the tasks, who are waiting the IRQ,
// so the semaphores
// Exactly the same function than the previous one, just changing
// the period and callback fct.
void Init_Display_Timer(uint64_t NR_delay)
{
	gptimer_handle_t NR_timer_handle = NULL;  // handle of the timer

	//..............................................................
	// Part 1 : configure the data structure
	//..............................................................
	gptimer_config_t NR_timer_config = {	// Timer config struct
	    .clk_src = GPTIMER_CLK_SRC_DEFAULT,
	    .direction = GPTIMER_COUNT_UP,
	    .resolution_hz = 1000 * 1000, // Timer freq ==> Fe =1MHz,
									  // so 1 tick = 1micro second
	};
	// create the new timer
	ESP_ERROR_CHECK(gptimer_new_timer(&NR_timer_config,
			                                     &NR_timer_handle));

	//..............................................................
	// Part 2 : configure the alarm action
	//..............................................................
	gptimer_alarm_config_t NR_alarm_config ={
			.alarm_count = NR_delay,// alarm every NR_delay * 1 ms
			.reload_count = 0,      // for reload: restart to 0
			.flags.auto_reload_on_alarm  = true,
	};
	ESP_ERROR_CHECK(gptimer_set_alarm_action(NR_timer_handle,
			                                     &NR_alarm_config));

	//..............................................................
	// Part 3: configure the callback (interruption)
	//..............................................................
	gptimer_event_callbacks_t NR_cbs_config = {
	        .on_alarm = Display_timer_IRQ_handler,//call right fct !
	    };
	    ESP_ERROR_CHECK(gptimer_register_event_callbacks(NR_timer_handle,
	    		                             &NR_cbs_config, NULL));

	//..............................................................
	// Part 4 : Start the timer
	//..............................................................
	ESP_ERROR_CHECK(gptimer_enable(NR_timer_handle));
	ESP_ERROR_CHECK(gptimer_start(NR_timer_handle));

} // end of void NR_Init_timer()
//==================================================================

//==================================================================
//  create_GUI_widgets() :
//create all the graphic objects required by the interface
//used labels and dynamical elements must be shared (global variable
//                                                         or other)
//3 screens are constructed (only one is downloaded at a given time)
//==================================================================
static void create_GUI_widgets(void)
{

	//--------------------------------------------------------------
	//                      Screen 1 : display horodate
	//--------------------------------------------------------------
	    screen[0] = lv_obj_create(NULL,NULL);
	    lv_obj_set_style_local_bg_color(screen[0], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, blue);

		//--------------------------------------------------------------
	    screen[1] = lv_obj_create(NULL, NULL);
	    lv_obj_set_style_local_bg_color(screen[1], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, blue);

	    //--------------------------------------------------------------
	    screen[2] = lv_obj_create(NULL, NULL);
	    lv_obj_set_style_local_bg_color(screen[2], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, blue);


	    temp = lv_label_create(screen[2], NULL);

	   		    			lv_label_set_long_mode(temp, LV_LABEL_LONG_SROLL_CIRC);     /*Circular scroll*/
	   		    			lv_obj_set_width(temp, 150);
	   		    			lv_label_set_text(temp, " La temperature est ");

	   		    			lv_obj_set_style_local_text_font(temp, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16);
	   		    			lv_obj_set_style_local_text_color(temp, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_WHITE);
	   		    			lv_obj_align(temp, NULL, LV_ALIGN_CENTER, 0, -100);


		nbrePas = lv_label_create(screen[2], NULL);

								lv_label_set_text(nbrePas, "Pas");

								lv_obj_set_style_local_text_font(nbrePas, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16);
								lv_obj_set_style_local_text_color(nbrePas, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_WHITE);
								lv_obj_align(nbrePas, NULL, LV_ALIGN_CENTER, 0, -20);


		 direc = lv_label_create(screen[2], NULL);

								lv_label_set_long_mode(direc, LV_LABEL_LONG_SROLL_CIRC);     /*Circular scroll*/
								lv_obj_set_width(direc, 150);
								lv_label_set_text(direc, " Votre direction maintenant est ");

								lv_obj_set_style_local_text_font(direc, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16);
								lv_obj_set_style_local_text_color(direc, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_WHITE);
								lv_obj_align(direc, NULL, LV_ALIGN_CENTER, 0, 100);


		 calor = lv_label_create(screen[2], NULL);

								lv_label_set_text(calor, "Calories");

								lv_obj_set_style_local_text_font(calor, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16);
								lv_obj_set_style_local_text_color(calor, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_WHITE);
								lv_obj_align(calor, NULL, LV_ALIGN_CENTER, -100, -20);


		dist = lv_label_create(screen[2], NULL);

								lv_label_set_text(dist, "Distance");

								lv_obj_set_style_local_text_font(dist, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16);
								lv_obj_set_style_local_text_color(dist, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_WHITE);
								lv_obj_align(dist, NULL, LV_ALIGN_CENTER, 100, -20);


	    // Charger l'écran 0
	    lv_scr_load(screen[0]);

}
//==================================================================

//==================================================================
// init_lvgl() : initialize the display and the LVGL interface,
//				 run the timer for LVGL tick management
//==================================================================
 void init_lvgl(void)
 {
	 lv_init();

	 /* Initialize SPI or I2C bus used by the drivers */
	 lvgl_driver_init();

	 static lv_color_t buf1[DISP_BUF_SIZE];

 /* Use double buffered when not working with monochrome displays */
	 static lv_color_t *buf2 = NULL;

	 static lv_disp_buf_t disp_buf;

	 uint32_t size_in_px = DISP_BUF_SIZE;

 /* Initialize the working buffer depending on the selected display.
 * NOTE: buf2 == NULL when using monochrome displays. */
	 lv_disp_buf_init(&disp_buf, buf1, buf2, size_in_px);

	 lv_disp_drv_t disp_drv;
	 lv_disp_drv_init(&disp_drv);
	 disp_drv.flush_cb = disp_driver_flush;

	 disp_drv.buffer = &disp_buf;
	 lv_disp_drv_register(&disp_drv);

 /* Create and start a periodic timer interrupt to call lv_tick_inc */
	 const esp_timer_create_args_t periodic_timer_args = {
		 .callback = &lv_tick_task,
		 .name = "periodic_gui"
	 };
	 esp_timer_handle_t periodic_timer;
	 ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args,
			                          &periodic_timer));
	 ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer,
			                             LV_TICK_PERIOD_MS * 1000));

 }

//******************************************************************
//***************************     Task Functions     ***************
//******************************************************************

//==================================================================
// blink_task() : toggle the Blue Led in an infinite loop
//==================================================================
void blink_task(void *arg)
{
   // Or convergence point
    while(1)
    {
        // Step B2 : Led On
        gpio_set_level(BlueLed, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);

        // Step B3 : Led Off
        gpio_set_level(BlueLed, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    } // branch to while(1)
}

//==================================================================
// state_machine() :
//    manage the lvgl display refresh,
//    and the different tasks (no sleep mode in this version)
//==================================================================
void state_machine()
{
	uint8_t state_blink_task = 1;
	char *TAG ="State_machine Task";


	// Local "Queue set" merging the wait of binary semaphores
	//   coming from the different IRQs
	QueueSetMemberHandle_t received_semaphore;

	//-------------------------- Step sm1: start Blinking Led ------
	vTaskResume(blink_task_Handle);

	//--------------------- Infinite loop waiting for semaphore ----
	// recall: Screen1 is downloaded by the Create_GUI_widgets() fct

	while(1)
	{
		//---- Step sm2 (wait for a semaphore from the queue set) --
		//           this following line justifies the RTOS use
		// (imagine how to proceed without Queue, considering random
		//                                   order of coming events)
		received_semaphore = xQueueSelectFromSet(Semaphore_QueueSet,
				                                     portMAX_DELAY);

		//==========================================================
		//  Or divergence (ordered selection of sequences)
		//==========================================================

		//----------- Sequence 1: Button was pushed ----------------
		// No periodicity : event
		if( received_semaphore == Btn_Semaphore  )
		{	// Step 1.1
			// the token must be removed from the semaphore
			xSemaphoreTake(Btn_Semaphore, 0);

			// Step 1.2
			// Resume or Suspend the Blink Task
			// 					and modify the associated widget
			state_blink_task = !state_blink_task;
			ESP_LOGE(TAG, "ME: Button was pushed, blink_state :%s",
						( (state_blink_task==1 ) ? "off" : "on") );

			if (state_blink_task == 1)
			{
				vTaskResume(blink_task_Handle);
			}
			else
			{
				vTaskSuspend(blink_task_Handle);
			}

			if(Page==0){
				lv_scr_load(screen[1]);

				Page++;
			}

			else if(Page==1){
				lv_scr_load(screen[2]);

				Page++;
			}
			else if(Page==2){
				lv_scr_load(screen[0]);

				Page=0;
			};
		}

		//------------ Sequence 3: no more semaphore ---------------
		//               Periodicity : every 500 ms
		else if (received_semaphore == Aff_update_Semaphore)
		{   // Step 3.1
			// the token must be removed from the semaphore
			ESP_LOGI(TAG, "ME: Display_update");
			xSemaphoreTake(Aff_update_Semaphore, 0);

			vTaskResume(xTemp);
			vTaskResume(xAcceler);
			vTaskResume(xMagnometre);
			vTaskResume(timHandle);

			affichage_Time();
			calend();
			affichage_temperature();
			affichage_orion();
			affichage_accel();


			// Step 3.2 : whatever the duration of the following
			//            function, the state-machine will end it
			//            before to continue.
			lv_task_handler();

			lv_obj_del(scr1_label1);
			lv_obj_del(scr2_label1);
			lv_obj_del(scr3_label1);
			lv_obj_del(scr4_label1);
			lv_obj_del(scr5_label1);
			lv_obj_del(scr6_label1);
			lv_obj_del(scr7_label1);
			lv_obj_del(scr8_label1);


		}

	}
}
//##################################################################
//##################################################################
void affichage_Time(){


	char time_str[50];

			scr4_label1 = lv_label_create(screen[0], NULL);

			strftime(time_str, sizeof(time_str), "%H  H  %M", &timeinfo);

			// Update label with current time

			lv_label_set_text(scr4_label1, time_str);

			lv_obj_set_style_local_text_font(scr4_label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16);
			lv_obj_set_style_local_text_color(scr4_label1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_WHITE);
			lv_obj_align(scr4_label1, NULL, LV_ALIGN_CENTER,0,0);

	char date_str[50];

			scr8_label1 = lv_label_create(screen[0], NULL);

			strftime(date_str, sizeof(date_str), "%A  -  %d  -  %B  -  %Y", &timeinfo);

			// Update label with current time

			lv_label_set_text(scr8_label1, date_str);
			lv_obj_set_style_local_text_font(scr8_label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16);
			lv_obj_set_style_local_text_color(scr8_label1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_WHITE);
			lv_obj_align(scr8_label1, NULL, LV_ALIGN_CENTER,0,40);
}

//##################################################################
//##################################################################

void calend(){



	scr7_label1 = lv_calendar_create(screen[1], NULL);
	lv_obj_set_size(scr7_label1, 235, 235);
	lv_obj_align(scr7_label1, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_local_text_font(scr7_label1, LV_CALENDAR_PART_DATE, LV_STATE_DEFAULT, lv_theme_get_font_small());

    // Mettre en surbrillance certaines dates

    static lv_calendar_date_t highlighted_days[3];

    highlighted_days[0].year = 2024;
    highlighted_days[0].month = 4;
    highlighted_days[0].day = 1;

    highlighted_days[1].year = 2024;
    highlighted_days[1].month = 5;
    highlighted_days[1].day = 1;

    highlighted_days[2].year = 2024;
    highlighted_days[2].month = 5;
    highlighted_days[2].day = 20;

    lv_calendar_set_highlighted_dates(scr7_label1, highlighted_days, 3);

	 lv_calendar_date_t current_date;
	    current_date.year = annee;
	    current_date.month = mois;
	    current_date.day = jour;

	    lv_calendar_set_today_date(scr7_label1, &current_date);
	    lv_calendar_set_showed_date(scr7_label1, &current_date);

}

//##################################################################
//##################################################################

void affichage_temperature() {
							/* Affichage de la temperature */
					/* cette fonction sera appelée dans la state machine */
	char tempbuff[20];

		scr1_label1 = lv_label_create(screen[2], NULL);

			lv_snprintf(tempbuff, sizeof(tempbuff), "%0.2f", temperature_degC);
			lv_label_set_text(scr1_label1, tempbuff);
			lv_obj_set_style_local_text_font(scr1_label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16);
			lv_obj_set_style_local_text_color(scr1_label1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_WHITE);
			lv_obj_align(scr1_label1, screen[2], LV_ALIGN_CENTER, 0, -80);








}
//##################################################################
//##################################################################

void affichage_orion() {
							/* Affichage de la temperature */
					/* cette fonction sera appelée dans la state machine */
	char boussbuff[5];

		scr2_label1 = lv_label_create(screen[2], NULL);

			lv_snprintf(boussbuff, sizeof(boussbuff), boussole);
			lv_label_set_text(scr2_label1, boussbuff);
			lv_obj_set_style_local_text_font(scr2_label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16);
			lv_obj_set_style_local_text_color(scr2_label1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_WHITE);
			lv_obj_align(scr2_label1, screen[2], LV_ALIGN_CENTER,0, 80);

}

//##################################################################
//##################################################################
void affichage_accel(){
	/* Fonction chargée de l'affichage du nombre de pas elle sera appellée dans la state machine*/
			/* Affichage des minutes Au centre de l'ecran */
	Distance = nbr_pas*0.57;
	Calories = nbr_pas*0.45;
	char pasbuff[20];

		scr3_label1 = lv_label_create(screen[2], NULL);

			lv_snprintf(pasbuff, sizeof(pasbuff), "%d", nbr_pas);
			lv_label_set_text(scr3_label1, pasbuff);
			lv_obj_set_style_local_text_font(scr3_label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16);
			lv_obj_set_style_local_text_color(scr3_label1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_WHITE);
			lv_obj_align(scr3_label1, NULL, LV_ALIGN_CENTER,0, 0);


	char Distancebuff[20];

		scr5_label1 = lv_label_create(screen[2], NULL);

			lv_snprintf(Distancebuff, sizeof(Distancebuff), "%0.2f", Distance);
			lv_label_set_text(scr5_label1, Distancebuff);
			lv_obj_set_style_local_text_font(scr5_label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16);
			lv_obj_set_style_local_text_color(scr5_label1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_WHITE);
			lv_obj_align(scr5_label1, screen[2], LV_ALIGN_CENTER,100,0);


	char Caloriesbuff[20];

		scr6_label1 = lv_label_create(screen[2], NULL);

			lv_snprintf(Caloriesbuff, sizeof(Caloriesbuff), "%3.2f", Calories);
			lv_label_set_text(scr6_label1, Caloriesbuff);
			lv_obj_set_style_local_text_font(scr6_label1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16);
			lv_obj_set_style_local_text_color(scr6_label1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,LV_COLOR_WHITE);
			lv_obj_align(scr6_label1, screen[2], LV_ALIGN_CENTER ,-100, 0);
}



//##################################################################
//						app_main() function
//##################################################################

void app_main(void)
{
	char * TAG="App_main() :";
	ESP_LOGI(TAG, "Start App_main");


	//+++++++++++++++++++++++ NTP FLASH
	//+++++++++++++++++++++++ NTP FLASH
	//+++++++++++++++++++++++ NTP FLASH

	   esp_err_t ret = nvs_flash_init();
		if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		  ESP_ERROR_CHECK(nvs_flash_erase());
		  ret = nvs_flash_init();
		}
		ESP_ERROR_CHECK(ret);


	//+++++++++++++++++++++++ WIFI
	//+++++++++++++++++++++++ WIFI
	//+++++++++++++++++++++++ WIFI

		ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
		wifi_init_sta();

	//+++++++++++++++++++++++ END WIFI
	//+++++++++++++++++++++++ END WIFI

	//+++++++++++++++++++++++ RTC
	//+++++++++++++++++++++++ RTC

	// Événement IP_EVENT_STA_GOT_IP pour vérifier la connexion Wi-Fi

	ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &got_ip_event_handler, NULL, NULL));
	initialize_rtc(); // Initialize RTC after SNTP is set up

	//+++++++++++++++++++++++ END RTC
	//+++++++++++++++++++++++ END RTC

	//+++++++++++++++++++++++ BLE
	//+++++++++++++++++++++++ BLE

	ble_init();

	esp_ble_gap_register_callback(gap_event_handler);

	esp_ble_gatts_register_callback(gatts_event_handler);

	esp_ble_gatts_app_register(PROFILE_APP_ID);



	//+++++++++++++++++++++++ END BLE
	//+++++++++++++++++++++++ END BLE


	// Create task to update time
	xTaskCreate(update_time_task, "update_time_task", 2048, NULL, 2, &timHandle);


	//==============================================================
	// Step 1. Initialisation
	//==============================================================
	// Step 1.1 Peripherals initialization

	gpio_reset_pin(BootBtn);
	gpio_set_direction(BootBtn, GPIO_MODE_INPUT);
	gpio_set_intr_type(BootBtn, GPIO_INTR_NEGEDGE);	//default lvl= 1

	gpio_reset_pin(BlueLed);
	gpio_set_direction(BlueLed, GPIO_MODE_OUTPUT);
	gpio_set_level(BlueLed, 0);

	// Step 1.2 : Semaphore and Queue Set creation
	//            (The queue set merge the different semaphores)

	Btn_Semaphore        = xSemaphoreCreateBinary();
	Acq_Timer_Semaphore  = xSemaphoreCreateBinary();
	Aff_update_Semaphore = xSemaphoreCreateBinary();

	// Binary semaphore size = 1 (x 3 semaphores)

	Semaphore_QueueSet = xQueueCreateSet( 3 );
	xQueueAddToSet( Btn_Semaphore,        Semaphore_QueueSet );
	xQueueAddToSet( Acq_Timer_Semaphore,  Semaphore_QueueSet );
	xQueueAddToSet( Aff_update_Semaphore, Semaphore_QueueSet );


	//==============================================================
	// MY PARTY
	//==============================================================

	ESP_ERROR_CHECK(i2c_master_init());
	init_temp();
	init_magn();
	init_accel();

	//==============================================================
	//==============================================================
	// Step 1.3 : LVGL initialisation
	init_lvgl();
	create_GUI_widgets();

	//==============================================================
	// Step 2. Tasks installation
	//==============================================================
	// 2.1 Install the Blink task and Suspend it
	xTaskCreate(blink_task, "blink_task", 10000, NULL, 3,
			                                    &blink_task_Handle);
	vTaskSuspend( blink_task_Handle );

	// Create task to display time
	xTaskCreate(display_time_task, "display_time_task", 4096, NULL, 5, NULL);

	//==============================================================
	// MY PARTY
	//==============================================================

	xTaskCreate(get_temp_task, "i2c_temperature_task", 2048*2, (void *)0, 10, &xTemp);
	xTaskCreate(get_magnetic_task, "i2c_magnetometre_task", 1024 * 2, (void *)0, 10, &xAcceler);
    xTaskCreate(get_accel_task, "i2c_accelerometre_task", 1024 * 2, (void *)0, 10, &xMagnometre);
	//==============================================================
	//==============================================================


	// 2.2 Install and run the State_Machine
	xTaskCreate(state_machine, "state_machine", 10000, NULL, 6, &state_machine_Handle);

		//==============================================================
	// Step 3. Interrupt Routines install, include Timers Init IRQ
	//==============================================================
	gpio_install_isr_service(0);
	gpio_isr_handler_add(BootBtn, gpio_IRQ_handler,(void *)BootBtn);

	Init_Acq_Timer(2000 * 1000);	// Acquisition period : 2 s
	Init_Display_Timer(500 * 1000); // Display update     : 500 ms

	//==============================================================
	// end of the app_main()
	//==============================================================
	ESP_LOGI(TAG, "App_main is finished");
}
