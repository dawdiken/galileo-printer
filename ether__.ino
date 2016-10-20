// Web page and ajax function to poll switches and variables and return them to the web page for display

 void ether()
{
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                HTTP_req += c;  // save the HTTP request 1 char at a time
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: keep-alive");
                    client.println();
                    // AJAX request for switch state
                    if (HTTP_req.indexOf("ajax_switch") > -1) {
                        // read switch state and analog input
                        GetAjaxData(client);
                    }
                    else {  // HTTP request for web page
                        // send web page - contains JavaScript with AJAX calls
                        client.println("<!DOCTYPE html>");
                        client.println("<html>");
                        client.println("<head>");
                        client.println("<title>Intel Galileo 3D Printer</title>");
                        client.println("<script>");
                        client.println("function GetSwitchAnalogData() {");
                        client.println("nocache = \"&nocache=\" + Math.random() * 1000000;");
                        client.println("var request = new XMLHttpRequest();");
                        client.println("request.onreadystatechange = function() {");
                        client.println("if (this.readyState == 4) {");
                        client.println("if (this.status == 200) {");
                        client.println("if (this.responseText != null) {");
                        client.println("document.getElementById(\"sw_an_data\")\.innerHTML = this.responseText;");
                        client.println("}}}}");
                        client.println("request.open(\"GET\", \"ajax_switch\" + nocache, true);");
                        client.println("request.send(null);");
                        client.println("setTimeout('GetSwitchAnalogData()', 1000);");
                        client.println("}");
                        client.println("</script>");
                        client.println("</head>");
                        client.println("<body style=""background-color:lightgreen"";>");
                        client.println("<body onload=\"GetSwitchAnalogData()\">");
                        client.println("<h1>Intel Galileo 3D Printer</h1>");
                        //client.println("<img src= ""/home/root/download.jpg"">");
                        client.println("<div id=\"sw_an_data\">");
                        client.println("</div>");
                        client.println("</body>");
                        client.println("</html>");
                    }
                    // display received HTTP request on serial port
                    //Serial.print(HTTP_req);
                    HTTP_req = "";            // finished with request, empty string
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
}

// send the state of the switch to the web browser
void GetAjaxData(EthernetClient cl)
{
    int analog_val;
    
    if (digitalRead(2)) {
        cl.println("<p>Endstop Alarm: Clear</p>");
    }
    else {
        cl.println("<p>Endstop Alarm: ALARM ON!! Check Machine</p>");
    }
    if (digitalRead(3)) {
        cl.println("<p>Green Button state: OFF</p>");
    }
    else {
        cl.println("<p>Green Button state: ON</p>");
    }
    if (digitalRead(4)) {
        cl.println("<p>Yellow Button state: OFF</p>");
    }
    else {
        cl.println("<p>Yellow Button state: ON</p>");
    }
    if (digitalRead(5)) {
        cl.println("<p>Blue Button state: OFF</p>");
    }
    else {
        cl.println("<p>Blue Button state: ON</p>");
    }
    if (digitalRead(6)) {
        cl.println("<p>Red Button state: OFF</p>");
    }
    else {
        cl.println("<p>Red Button state: ON</p>");
    }
    if (digitalRead(7)) {
        cl.println("<p>Manual Mode: ON</p>");
    }
    else {
        cl.println("<p>Manual Mode: OFF</p>");
    }
    // read analog pin A2
    analog_val = analogRead(2);
    float voltage = analog_val * (5.0 / 1023.0);
    float temp = (voltage - 1.25)/0.005;
    cl.print("<p>Extruder Temperature deg C: ");
    cl.print(temp);
    cl.println("</p>");
    cl.print("<p>X: ");
    cl.print(Xpos);
    cl.println("</p>");
    cl.print("<p>Y: ");
    cl.print(Ypos);
    cl.println("</p>");
    cl.print("<p>E: ");
    cl.print(Epos);
    cl.println("</p>");
    
}

