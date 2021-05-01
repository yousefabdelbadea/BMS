/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updated by chegewara

   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as: 4fafc201-1fb5-459e-8fcc-c5c9c331914b
   And has a characteristic of: beb5483e-36e1-4688-b7f5-ea07361b26a8

   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.

   A connect hander associated with the server starts a background task that performs notification
   every couple of seconds.
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic1_s1 = NULL;
BLECharacteristic* pCharacteristic2_s1 = NULL;
BLECharacteristic* pCharacteristic3_s1 = NULL;
BLECharacteristic* pCharacteristic4_s1 = NULL;
BLECharacteristic* pCharacteristic5_s1 = NULL;
BLECharacteristic* pCharacteristic1_s2 = NULL;
BLECharacteristic* pCharacteristic2_s2 = NULL;
BLECharacteristic* pCharacteristic3_s2 = NULL;
BLECharacteristic* pCharacteristic4_s2 = NULL;
BLECharacteristic* pCharacteristic5_s2 = NULL;

bool deviceConnected = false;
bool oldDeviceConnected = false;
bool set_one = true;               // remove this variable when connecting to stm
uint8_t cell_info[5];
uint8_t permission_to_send = 1, safe_data = 1, received_resp = 0, i =0;     // initialize permission_to_send to 0 when dealing with stm
uint32_t ready_to_exit = 0;
hw_timer_t* timer = NULL;      // remove this variable when connecting to stm
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE1_UUID        "0000180f-0000-1000-8000-00805f9b34fb"       // current data service
#define SERVICE2_UUID        "00001802-0000-1000-8000-00805f9b34fb"       // alarming service
#define CHARACTERISTIC1_UUID "00002a00-0000-1000-8000-00805f9b34fb"       // device name
#define CHARACTERISTIC2_UUID "00002a6e-0000-1000-8000-00805f9b34fb"       // temperature      
#define CHARACTERISTIC3_UUID "00002ae0-0000-1000-8000-00805f9b34fb"       // current
#define CHARACTERISTIC4_UUID "00002ae1-0000-1000-8000-00805f9b34fb"       // voltage
#define CHARACTERISTIC5_UUID "00002a19-0000-1000-8000-00805f9b34fb"      // SOC


// defining some LEDs

#define ALL_DONE  2
#define REMAINING_DATA    4
#define CONNECTION_LOST 17


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void IRAM_ATTR onTimer(){                                  // remove this function when connecting to stm
  set_one = !set_one;
}

void setup() {

  /*timerBegin();
  timerAlarmWrite();*/
  Serial.begin(9600,SERIAL_8N1);

  // Create the BLE Device
  BLEDevice::init("ESP32");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the current data Service
  BLEService *pService1 = pServer->createService(SERVICE1_UUID);

  // Create the device name Characteristic in the current data Service
  pCharacteristic1_s1 = pService1->createCharacteristic(
                      CHARACTERISTIC1_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  // Create the temperature Characteristic in the current data Service
  pCharacteristic2_s1 = pService1->createCharacteristic(
                      CHARACTERISTIC2_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  // Create the current Characteristic in the current data Service
  pCharacteristic3_s1 = pService1->createCharacteristic(
                      CHARACTERISTIC3_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );     

  // Create the voltage Characteristic in the current data Service
  pCharacteristic4_s1 = pService1->createCharacteristic(
                      CHARACTERISTIC4_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );    

  // Create the SOC Characteristic in the current data Service
  pCharacteristic5_s1 = pService1->createCharacteristic(
                      CHARACTERISTIC5_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );   
                                                                   



  // Create the alarming Service
  BLEService *pService2 = pServer->createService(SERVICE2_UUID);

  // Create the device name Characteristic in the alarming Service
  pCharacteristic1_s2 = pService2->createCharacteristic(
                      CHARACTERISTIC1_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  // Create the temperature Characteristic in the alarming Service
  pCharacteristic2_s2 = pService2->createCharacteristic(
                      CHARACTERISTIC2_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  // Create the current Characteristic in the alarming Service
  pCharacteristic3_s2 = pService2->createCharacteristic(
                      CHARACTERISTIC3_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );     

  // Create the voltage Characteristic in the alarming Service
  pCharacteristic4_s2 = pService2->createCharacteristic(
                      CHARACTERISTIC4_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY 
                    );    

  // Create the SOC Characteristic in the alarming Service
  pCharacteristic5_s2 = pService2->createCharacteristic(
                      CHARACTERISTIC5_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY 
                    );   
                                                                    
// Create Client Characteristic Configuration BLE Descriptor for all characterstics
  pCharacteristic1_s1->addDescriptor(new BLE2902());
  pCharacteristic2_s1->addDescriptor(new BLE2902());
  pCharacteristic3_s1->addDescriptor(new BLE2902());
  pCharacteristic4_s1->addDescriptor(new BLE2902());
  pCharacteristic5_s1->addDescriptor(new BLE2902());
  pCharacteristic1_s2->addDescriptor(new BLE2902());
  pCharacteristic2_s2->addDescriptor(new BLE2902());
  pCharacteristic3_s2->addDescriptor(new BLE2902());
  pCharacteristic4_s2->addDescriptor(new BLE2902());
  pCharacteristic5_s2->addDescriptor(new BLE2902());
 

  // Start the current data service
  pService1->start();
  // Start the alarming service
  pService2->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE1_UUID);
  pAdvertising->addServiceUUID(SERVICE2_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  //Serial.println("Waiting a client connection to notify...");


  pinMode(ALL_DONE, OUTPUT);
  pinMode(REMAINING_DATA, OUTPUT);
  pinMode(CONNECTION_LOST, OUTPUT);

  /*digitalWrite(ALL_DONE, HIGH);
  digitalWrite(REMAINING_DATA, HIGH);
  digitalWrite(CONNECTION_LOST, HIGH);*/

  // remove these statements on dealing with stm
  timer = timerBegin(0, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
  timerAttachInterrupt(timer, &onTimer, true); // edge (not level) triggered 
  timerAlarmWrite(timer, 30000000, true); // 30000000 * 1 us = 30 seconds, autoreload true
  timerAlarmEnable(timer); // enable
}

void loop() {

  if (set_one)            // remove this if and following else on dealing with stm
  {
    for (i=0;i<5;i++)
        cell_info[i] = 1;
  }
  else
  {
    for (i=0;i<5;i++)
        cell_info[i] = 2;
  }

    /*if (Serial.available() > 4)                     // remove /* when dealing with stm
    {      
      for (i=0;i<5;i++)
        cell_info[i] = Serial.read() - 48;            // remove -48 when dealing with stm but keep it when dealing with monitor
      permission_to_send = 1;

    }*/
      
    // notify changed value
    if (deviceConnected) {

      if (permission_to_send && safe_data)
      {
        pCharacteristic2_s1->setValue(cell_info+1,1);      // temperature
        pCharacteristic3_s1->setValue(cell_info+2,1);      // current
        pCharacteristic4_s1->setValue(cell_info+3,1);      // voltage
        pCharacteristic5_s1->setValue(cell_info+4,1);      //SOC
        pCharacteristic1_s1->setValue(cell_info,1);      // device_name
        pCharacteristic1_s1->notify();   
        
        received_resp = *(pCharacteristic1_s1->getData());

        while (received_resp)      // wait for acknowledgment
        {
          ready_to_exit++;
          if (ready_to_exit > 1000000)
              break;
          else
              received_resp = *(pCharacteristic1_s1->getData());
        }
        
        ready_to_exit = 0;
        
        if (received_resp == 0)      // acknowledgment received
        {
          Serial.println("acknowledged");
          digitalWrite(CONNECTION_LOST, HIGH);
          digitalWrite(REMAINING_DATA, LOW);
        }
            
        else                                          
        {
          Serial.println(received_resp);
          digitalWrite(REMAINING_DATA, HIGH);
          digitalWrite(CONNECTION_LOST, LOW);
        }
            


        //permission_to_send = 0;                 // remove // when dealing with stm
      }
          
          // serivce 2 here if safe_data ==0 with permission_to_send  
      }

    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}
