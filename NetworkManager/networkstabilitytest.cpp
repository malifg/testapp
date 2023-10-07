#include "networkstabilitytest.h"

NetworkStabilityTest::NetworkStabilityTest()
{
}

int NetworkStabilityTest::initialize(){
    testStart = false;
    ethernetNumberOfSuccess = 0;
    wifiNumberOfSuccess = 0;
    gsm4GNumberOfSuccess = 0;
    numberOfTests = 0;

}

void NetworkStabilityTest::run(){

    while(true){
        if(testStart){
            EthernetTest::instance()->connect();
            WiFiTest::instance()->connect();
            GSM4GTest::instance()->connect();

            sleep(5);


            for(int i = 0; i < 100; i++){

                numberOfTests++;

                EthernetTest::instance()->connect();
                WiFiTest::instance()->disconnect();
                GSM4GTest::instance()->disconnect();

                if(EthernetTest::instance()->getStatus() == OK){
                    if(EthernetTest::instance()->sendLongResult() == OK){
                        if(EthernetTest::instance()->receiveData() == OK){
                            ethernetNumberOfSuccess++;
                        }
                    }
                }


                EthernetTest::instance()->disconnect();
                WiFiTest::instance()->connect();
                GSM4GTest::instance()->disconnect();

                if(WiFiTest::instance()->getStatus() == OK){
                    if(WiFiTest::instance()->sendLongResult() == OK){
                        if(WiFiTest::instance()->receiveData() == OK){
                            wifiNumberOfSuccess++;
                        }
                    }
                }

                EthernetTest::instance()->disconnect();
                WiFiTest::instance()->disconnect();
                GSM4GTest::instance()->connect();

                if(WiFiTest::instance()->getStatus() == OK){
                    if(GSM4GTest::instance()->sendLongResult() == OK){
                        if(GSM4GTest::instance()->receiveData() == OK){
                            gsm4GNumberOfSuccess++;
                        }
                    }
                }

                sleep(3);
            }

            testStart = false;
        }
    }


}
