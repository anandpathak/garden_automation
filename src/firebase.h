#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"


#include "config.h"
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

bool taskCompleted = false;

unsigned long dataMillis = 0;

void FireStoreConnect() {

  config.api_key = API_KEY;
    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

     config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

     #if defined(ESP8266)
    // In ESP8266 required for BearSSL rx/tx buffer for large data handle, increase Rx size as needed.
      fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 2048 /* Tx buffer size in bytes from 512 - 16384 */);
    #endif

    // Limit the size of response payload to be collected in FirebaseData
    fbdo.setResponseSize(2048);

    Firebase.begin(&config, &auth);

}

FirebaseJson getDocument() {
    String documentPath = "config";
    String mask = "";

    if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), mask.c_str())) {
          FirebaseJson json;
          json.setJsonData(fbdo.payload());
          json.toString(Serial,true);
          
          Serial.println();
          Serial.println();
          return json;
    }
    else{
      Serial.println(fbdo.errorReason());
    }     
    return NULL;
};

