#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "lumipon";
const char* password = "87654321";
char inputBuffer[7] = "";       //Input from Arduino
String outputBuffer = "";     //Output to Arduino

ESP8266WebServer server(80);


void handleApp(){
  String header;
  String arguments;
  Serial.println("Estou no tratador.");
    if(server.hasHeader("HEADER"))
    {
        header = server.header("HEADER");
        outputBuffer += header + ",";
        if(header == "LAMP1")
        {
          if(server.hasArg("LAMP_ON_OFF"))
          {
            arguments = server.arg("LAMP_ON_OFF");
            Serial.print(header); Serial.print("diz: ");
            Serial.println(arguments);
            outputBuffer += arguments + ","; 
            server.send(200,  "text/plain",  "Ok");
          } else
          {
            outputBuffer = "";
            server.send(404, "text/plain", "Error");
          }
          
        } else if(header == "LAMP2")
        {
          if(server.hasArg("LAMP_ON_OFF"))
          {
            Serial.print(header); Serial.print("diz: ");
            arguments = server.arg("LAMP_ON_OFF");
            Serial.println(arguments);
            outputBuffer += arguments + ",";
            server.send(200,  "text/plain",  "Ok");
          } else
          {
            outputBuffer = "";
            server.send(404, "text/plain", "Error");
          }

        } else if(header == "CONTEXT1")
        {
          if(server.hasArg("PLANTNAME"))
          {
            Serial.print(header); Serial.print("diz: ");
            arguments = server.arg("PLANTNAME");
            Serial.print(arguments);
            outputBuffer += arguments + ",";
            arguments = server.arg("TIME");

            Serial.print("\t recebe minutos: "); Serial.println(arguments);
            server.send(200,  "text/plain",  "Ok");
          } else
          {
            server.send(404, "text/plain", "Error");
          }

        } else if(header == "CONTEXT2")
        {
          if(server.hasArg("PLANTNAME"))
          {
            Serial.print(header); Serial.print("diz: ");
            arguments = server.arg("PLANTNAME");
            outputBuffer += arguments + ",";
            Serial.println(arguments);
            arguments = server.arg("TIME");
            outputBuffer += arguments + ",";
            Serial.print("\t"); Serial.println(arguments);
            server.send(200,  "text/plain",  "Ok");
          } else
          {
            outputBuffer = "";
            server.send(404, "text/plain", "Error");
          }
        } else
        {
          outputBuffer = "";
          server.send(404, "text/plain", "Error");
        }
    } else  
    {
      outputBuffer = "";
      server.send(404, "text/plain", "Error");
    }
}

void handleLamp(){
  server.send(200, "text/plain", inputBuffer);
}

//no need authentification
void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  //Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  //Serial.print("Connected to ");
  Serial.println(ssid);
  //Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  server.on("/", handleApp);
  server.on("/lampinfo", handleLamp);
  

  server.onNotFound(handleNotFound);
  //here the list of headers to be recorded
  const char * headerkeys[] = {"HEADER"} ;
  size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize );
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){

  server.handleClient();

  if (Serial.read() != -1)
  {
    inputBuffer[0] = NULL;
    Serial.readBytes(inputBuffer,7);
    Serial.println(outputBuffer);
    //COMENTAR
    server.send(200,  "text/plain",  outputBuffer);
    Serial.flush();
    outputBuffer = "";
  }

}
