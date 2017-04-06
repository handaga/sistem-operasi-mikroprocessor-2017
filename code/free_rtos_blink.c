#include <Arduino_FreeRTOS.h>

//deklarasi aplikasi/Task
//nama aplikasi boleh diubah sesuai dengan aturan pembuatan
//identifier
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );


Void setup() {
	//create/inisialisasi applikasi freeRTOS
	xTaskCreate( 
	   TaskBlink    //Nama Aplikasi
	    ,    (const portCHAR *)"Blink"   //Label nama aplikasi biasanya utk identifikasi
	    ,  128  // ukuran HEAP memory atau memory untuk kerja aplikasi dalam BYTE
	    ,  NULL
	    ,  2   // Nomor prioritas : 0 prioritas paling rendah
	    ,  NULL );
	
	  xTaskCreate(
	    TaskAnalogRead
	    ,  (const portCHAR *) "AnalogRead"
	    ,  128  // Stack size
	    ,  NULL
	    ,  1  // Priority
	    ,  NULL );
	

}

Void loop() {
		//Tidak ada kode di sini
		//Baris kode yang ada di sini tidak pernah di eksekusi
}

// Definisi aplikasi/task/fungsi
void TaskBlink(void *pvParameters)  {
  (void) pvParameters;

  // seprti setup dalam arduino reguler, 
  // dieksekusi sekali saja selama ARDUINO ON
  pinMode(LED_BUILTIN, OUTPUT);

  for (;;)   {  //Perulangan TANPA HENTI
	//Perintah dalam blok ini akan dieksekusi secara berulang kali
	//selama ARDUINO ON
    digitalWrite(LED_BUILTIN, HIGH);  
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); //menunggu satu detik
    digitalWrite(LED_BUILTIN, LOW);    
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); 
	// 1 (vTaskDelay: FreeRTOS) = 15 (delay: Arduino original)

  }
}

void TaskAnalogRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
for (;;)
  {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // print out the value you read:
    Serial.println(sensorValue);
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}