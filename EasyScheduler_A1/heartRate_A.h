void A_sensor(){

  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
     beatAvg /= RATE_SIZE;
    }
  }
  
  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);
  if (irValue > 3000){
    
  tft.fillRect(5, 220, 125, 20, tft.color24to16(0x6699FF));  
  tft.fillRect(30, 250, 100, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(50, 250);
  tft.print(beatAvg);

  }
  else
  {
  irValue = 0;
  beatAvg = 0;
  Serial.println(" No finger?");
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(2);//ขนาดข้อความ
  tft.setCursor(5, 220);
  tft.print("No finger?");
  
  tft.fillRect(30, 250, 100, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(50, 250);
  tft.print(beatAvg);
  }
}






/*  
//แสดงค่าที่วัดได้
//หัวใจ
  tft.fillRect(30, 250, 100, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(50, 250);
  tft.print(beatAvg);
//ออกซิเจน
  tft.fillRect(180, 250, 80, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(210, 250);
  long L = beatAvg+15;
  tft.print(L);
*/
