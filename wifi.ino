String SSID = "SSID";
String password = "password";

//0 = Scan for SSID's, 1 = Add Credentials, 2 = Get stored credentials
int function = -1;

void setup() {

    Serial.begin(9600);

    if (function ==1)
        {
            Serial.println("Adding Credentials");
            WiFi.setCredentials(SSID, password);
        }
}

void loop() {
    
    if (WiFi.ready() == 1)
    {
        Particle.process();
        
        String stringRSSI;
        stringRSSI = String(WiFi.RSSI());  
        
        String stringIP;
        stringIP = String(WiFi.localIP());  
        
        String stringGateway;
        stringGateway = String(WiFi.gatewayIP());  
        
        String stringDNS;
        stringDNS = String(WiFi.dnsServerIP());  
        
        Serial.println("Wifi is Ready");
        Serial.print("RSSI = ");
        Serial.println(stringRSSI);
        Serial.print("IP Address = ");
        Serial.println(stringIP);
        Serial.print("Gateway IP = ");
        Serial.println(stringGateway);
        Serial.print("DNS Server = ");
        Serial.println(stringDNS);

      
        Particle.publish("RSSI",stringRSSI,60,PRIVATE);
        Particle.publish("localIP",stringIP,60,PRIVATE);
        Particle.publish("Gateway",stringGateway,60,PRIVATE);
        Particle.publish("DNS",stringDNS,60,PRIVATE);
        
        if (function ==0)
            {
                Serial.println("Scanning for SSID's");
                int result_count = WiFi.scan(wifi_scan_callback);
                Serial.print(result_count);
                Serial.println(" APs scanned.");
            }
            
        if (function == 2)
            {
                WiFiAccessPoint ap[5];
                int found = WiFi.getCredentials(ap, 5);
                for (int i = 0; i < found; i++) {
                    Serial.print("ssid: ");
                    Serial.println(ap[i].ssid);
                    // security is one of WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA, WLAN_SEC_WPA2
                    Serial.print("security: ");
                    Serial.println(ap[i].security);
                    // cipher is one of WLAN_CIPHER_AES, WLAN_CIPHER_TKIP
                    Serial.print("cipher: ");
                    Serial.println(ap[i].cipher);
                }
            }
    }
    delay(5000);
}

void wifi_scan_callback(WiFiAccessPoint* wap, void* data)
    {
        WiFiAccessPoint& ap = *wap;
        Serial.print("SSID: ");
        Serial.println(ap.ssid);
        Serial.print("Security: ");
        Serial.println(ap.security);
        Serial.print("Channel: ");
        Serial.println(ap.channel);
        Serial.print("RSSI: ");
        Serial.println(ap.rssi);
    }
