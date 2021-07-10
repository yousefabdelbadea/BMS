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
uint8_t cell_info[5] = {1,68,245,37,87};
uint8_t permission_to_send = 0, safe_data = 1, received_resp = 0, i =0, starting_index = 0, ending_index = 0;   
uint32_t ready_to_exit = 0;
String input_string;           // for incoming serial data
String numerical_string;


#define SERVICE1_UUID        "0000180f-0000-1000-8000-00805f9b34fb"       // current data service
#define SERVICE2_UUID        "00001802-0000-1000-8000-00805f9b34fb"       // alarming service
#define CHARACTERISTIC1_UUID "00002a00-0000-1000-8000-00805f9b34fb"       // device name
#define CHARACTERISTIC2_UUID "00002a6e-0000-1000-8000-00805f9b34fb"       // temperature      
#define CHARACTERISTIC3_UUID "00002ae0-0000-1000-8000-00805f9b34fb"       // current
#define CHARACTERISTIC4_UUID "00002ae1-0000-1000-8000-00805f9b34fb"       // voltage
#define CHARACTERISTIC5_UUID "00002a19-0000-1000-8000-00805f9b34fb"      // SOC


// defining some LEDs

#define ALL_DONE  2
#define NOT_DONE  5
#define REMAINING_DATA    4
#define CONNECTION_LOST 17

#define test_led 21

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {


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
                                                                    
// Create Client Characteristic Configuration BLE Descriptor for device name characterstic
  pCharacteristic1_s1->addDescriptor(new BLE2902());
  pCharacteristic1_s2->addDescriptor(new BLE2902());

 

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



  pinMode(ALL_DONE, OUTPUT);
  pinMode(NOT_DONE, OUTPUT);
  pinMode(REMAINING_DATA, OUTPUT);
  pinMode(CONNECTION_LOST, OUTPUT);
  
  pinMode(test_led, OUTPUT);                     // just for testing battery
  digitalWrite(test_led, HIGH);                         
}

void loop() {

  // remove these comments when mobile app works well with dummy data below
  /*if (Serial.available())                     
  {
    input_string = Serial.readString();                                                       // read the incoming data as string

    if (input_string[0] == '#' && input_string[input_string.length() - 1] == '$' )            // valid format
    {
      digitalWrite(ALL_DONE, HIGH);
      digitalWrite(NOT_DONE, LOW);
      starting_index = input_string.indexOf('C');
      
      for (i=0;i<5;i++) 
      {
        if (i==0)
          ending_index = input_string.indexOf('T');
        else if (i == 1)
          ending_index = input_string.indexOf('A');        
        else if (i == 2)
          ending_index = input_string.indexOf('V');   
        else if (i == 3)
          ending_index = input_string.indexOf('S');   
        else if (i == 4)
          ending_index = input_string.indexOf('$');    
  
  
        numerical_string = input_string.substring(starting_index  + 1, ending_index);
        cell_info[i] = numerical_string.toInt(); 
        starting_index = ending_index;
  
        if (cell_info[i] > 2 && cell_info[i] < 90)
          Serial.println("done");
        else
          Serial.println("failed");
      }

      permission_to_send = 1;
    }

    else                                                          // invalid format  
    {
      digitalWrite(NOT_DONE, HIGH);
      digitalWrite(ALL_DONE, LOW);
    }


  }*/
      
    // notify changed value
    if (deviceConnected) {


      permission_to_send = 1;                               // remove this line once dummy data works well with mobile app

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
            


        permission_to_send = 0;                 
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
