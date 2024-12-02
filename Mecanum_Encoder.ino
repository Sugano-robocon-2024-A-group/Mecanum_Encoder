#include <Arduino.h>

// エンコーダのピン設定 （左前　左後　右前　右後）
const int encoderA[4] = {22, 18, 32, 21}; // エンコーダA相ピン
const int encoderB[4] = {23, 19, 33, 16}; // エンコーダB相ピン

// エンコーダ関連の変数
volatile long encoderCount[4] = {0, 0, 0, 0}; // 各ホイールのエンコーダカウント

void handleEncoder(int index)
{
  if (index < 2)  // 左側のモーターの場合
  {
    if (digitalRead(encoderA[index]) != digitalRead(encoderB[index]))
    {
    encoderCount[index]++;
    }
    else
    {
      encoderCount[index]--;
    }
  }
  else  // 右側のモーターの場合
  {
    if (digitalRead(encoderA[index]) == digitalRead(encoderB[index]))
    {
      encoderCount[index]++;
    }
    else
    {
      encoderCount[index]--;
    }    
  }
}

void setup()
{
  Serial.begin(115200);

  for (int i = 0; i < 4; i++)
  {
    // モーターピンを出力に設定
    pinMode(encoderA[i], INPUT_PULLUP);
    pinMode(encoderB[i], INPUT_PULLUP);
  }

  attachInterrupt(digitalPinToInterrupt(encoderA[0]), []() { handleEncoder(0); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[1]), []() { handleEncoder(1); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[2]), []() { handleEncoder(2); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[3]), []() { handleEncoder(3); }, CHANGE);
}

void loop()
{
   
}
