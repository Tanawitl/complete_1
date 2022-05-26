void spo2_A (){
  
  double fred, fir;
  double SpO2 = 0; //raw SpO2 before low pass filtered

#ifdef USEFIFO
  particleSensor.check(); //Check the sensor, read up to 3 samples

  while (particleSensor.available())
  { //do we have new data
#ifdef MAX30105
    red = particleSensor.getFIFORed(); //Sparkfun's MAX30105
    ir = particleSensor.getFIFOIR();  //Sparkfun's MAX30105
#else
    red = particleSensor.getFIFOIR(); //why getFOFOIR output Red data by MAX30102 on MH-ET LIVE breakout board
    ir = particleSensor.getFIFORed(); //why getFIFORed output IR data by MAX30102 on MH-ET LIVE breakout board
#endif



    i++;
    fred = (double)red;
    fir = (double)ir;
    avered = avered * frate + (double)red * (1.0 - frate);//average red level by low pass filter
    aveir = aveir * frate + (double)ir * (1.0 - frate); //average IR level by low pass filter
    sumredrms += (fred - avered) * (fred - avered); //square sum of alternate component of red level
    sumirrms += (fir - aveir) * (fir - aveir);//square sum of alternate component of IR level


    if (ir < FINGER_ON) ESpO2 = MINIMUM_SPO2; //indicator for finger detached


    if ((i % Num) == 0)
    {
      double R = (sqrt(sumredrms) / avered) / (sqrt(sumirrms) / aveir);
      // Serial.println(R);
      SpO2 = -23.3 * (R - 0.4) + 100; 
      ESpO2 = FSpO2 * ESpO2 + (1.0 - FSpO2) * SpO2;//low pass filter
      if (ESpO2 >= 100) {
        ESpO2 = 100;
      }
      //  Serial.print(SpO2);Serial.print(",");Serial.println(ESpO2);
      sumredrms = 0.0; sumirrms = 0.0; i = 0;
      break;
    }
    particleSensor.nextSample(); //We're finished with this sample so move to next sample
  }
#endif



  Serial.print(", ESpO2=");
  Serial.println(ESpO2);
  if (ir > 3000){
    
  tft.fillRect(170, 220, 130, 20, tft.color24to16(0x6699FF));
  tft.fillRect(200, 250, 120, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(200, 250);
  tft.print(ESpO2);
  }
   else
  {
  ESpO2 = 0;
  Serial.println(" No finger?");
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(2);//ขนาดข้อความ
  tft.setCursor(170, 220);
  tft.print("No finger?");

  tft.fillRect(200, 250, 120, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(200, 250);
  tft.print(ESpO2);
  }
}
